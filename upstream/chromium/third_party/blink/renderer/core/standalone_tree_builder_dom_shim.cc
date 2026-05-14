// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/dom/character_data.h"
#include "standalone_renderer/include/html_css_renderer/blink_tree_bridge_probe.h"

#include "third_party/blink/renderer/core/dom/comment.h"
#include "third_party/blink/renderer/core/dom/container_node.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/document_type.h"
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/events/event_target.h"
#include "third_party/blink/renderer/core/dom/processing_instruction.h"
#include "third_party/blink/renderer/core/dom/text.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/execution_context/agent.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/html/custom/ce_reactions_scope.h"
#include "third_party/blink/renderer/core/html/custom/custom_element.h"
#include "third_party/blink/renderer/core/html/custom/custom_element_definition.h"
#include "third_party/blink/renderer/core/html/custom/custom_element_registry.h"
#include "third_party/blink/renderer/core/html/forms/html_form_element.h"
#include "third_party/blink/renderer/core/html/html_html_element.h"
#include "third_party/blink/renderer/core/html/html_template_element.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/html/parser/patch.h"
#include "third_party/blink/renderer/core/html/parser/atomic_html_token.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_options.h"
#include "third_party/blink/renderer/core/html/parser/html_tokenizer.h"
#include "third_party/blink/renderer/core/html/parser/html_tree_builder.h"
#include "third_party/blink/renderer/core/inspector/console_message.h"
#include "third_party/blink/renderer/core/sanitizer/sanitizer.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/renderer/platform/bindings/runtime_call_stats.h"
#include "third_party/blink/renderer/platform/bindings/parkable_string.h"
#include "third_party/blink/renderer/platform/bindings/script_wrappable.h"
#include "third_party/blink/renderer/platform/bindings/wrapper_type_info.h"
#include "third_party/blink/renderer/core/layout/geometry/physical_rect.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_artifact.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_chunk.h"
#include "third_party/blink/renderer/platform/heap/thread_state_storage.h"
#include "third_party/blink/renderer/platform/scheduler/public/event_loop.h"
#include "third_party/blink/renderer/platform/text/segmented_string.h"
#include "third_party/blink/renderer/platform/text/character_break_iterator.h"
#include "third_party/blink/renderer/platform/wtf/allocator/partitions.h"
#include "third_party/blink/renderer/platform/wtf/text/string_builder.h"
#include "v8/include/cppgc/heap-consistency.h"
#include "v8/include/cppgc/explicit-management.h"
#include "v8/include/cppgc/internal/write-barrier.h"
#include "v8/include/cppgc/object-size-trait.h"

#include <algorithm>
#include <cstring>
#include <new>
#include <string>
#include <unordered_map>
#include <vector>

namespace blink {

namespace {

template <typename T, typename... Args>
T* StandaloneAllocateNode(Args&&... args) {
  void* storage =
      Partitions::FastMalloc(sizeof(T), WTF_HEAP_PROFILER_TYPE_NAME(T));
  return ::new (storage) T(std::forward<Args>(args)...);
}

struct StandaloneRecordedTreeNode {
  std::string kind;
  std::string name;
  std::string value;
  int parent_index = -1;
  int depth = 0;
  int first_child_index = -1;
  int next_sibling_index = -1;
  int child_count = 0;
};

struct StandaloneDOMSnapshotNode {
  std::string kind;
  std::string name;
  std::string value;
  int parent_index = -1;
  int depth = 0;
  int first_child_index = -1;
  int next_sibling_index = -1;
  int child_count = 0;
};

struct StandaloneLayoutSnapshotBox {
  int node_index = -1;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  std::string role;
};

struct StandalonePaintArtifactChunkSnapshot {
  std::string id;
  std::string role;
  std::string op;
  int node_index = -1;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

std::vector<StandaloneRecordedTreeNode>& StandaloneRecordedTreeNodes() {
  static auto* nodes = new std::vector<StandaloneRecordedTreeNode>();
  return *nodes;
}

std::vector<StandaloneDOMSnapshotNode>& StandaloneDOMSnapshotNodes() {
  static auto* nodes = new std::vector<StandaloneDOMSnapshotNode>();
  return *nodes;
}

std::vector<StandaloneLayoutSnapshotBox>& StandaloneLayoutSnapshotBoxes() {
  static auto* boxes = new std::vector<StandaloneLayoutSnapshotBox>();
  return *boxes;
}

std::vector<StandalonePaintArtifactChunkSnapshot>&
StandalonePaintArtifactChunks() {
  static auto* chunks =
      new std::vector<StandalonePaintArtifactChunkSnapshot>();
  return *chunks;
}

using StandaloneNodeKey = uintptr_t;

StandaloneNodeKey StandaloneNodeIdentity(const Node& node) {
  return reinterpret_cast<StandaloneNodeKey>(&node);
}

std::unordered_map<StandaloneNodeKey, int>& StandaloneRecordedNodeIndices() {
  static auto* indices = new std::unordered_map<StandaloneNodeKey, int>();
  return *indices;
}

std::unordered_map<StandaloneNodeKey, int>& StandaloneLastChildByParent() {
  static auto* children = new std::unordered_map<StandaloneNodeKey, int>();
  return *children;
}

Node*& StandaloneDOMRootNode() {
  static Node* root = nullptr;
  return root;
}

std::string StandaloneNodeKind(const Node& node) {
  if (IsA<Text>(node)) {
    return "text";
  }
  if (IsA<Comment>(node)) {
    return "comment";
  }
  if (IsA<DocumentType>(node)) {
    return "doctype";
  }
  if (IsA<Element>(node)) {
    return "element";
  }
  return "node";
}

std::string StandaloneNodeName(const Node& node) {
  if (const auto* element = DynamicTo<Element>(node)) {
    return element->localName().GetString().Utf8();
  }
  if (IsA<Text>(node)) {
    return "#text";
  }
  if (IsA<Comment>(node)) {
    return "#comment";
  }
  if (IsA<DocumentType>(node)) {
    return "#doctype";
  }
  return "#node";
}

std::string StandaloneNodeValue(const Node& node) {
  if (const auto* character_data = DynamicTo<CharacterData>(node)) {
    return character_data->data().Utf8();
  }
  return {};
}

int EnsureStandaloneRecordedNode(const Node& node) {
  auto& indices = StandaloneRecordedNodeIndices();
  const StandaloneNodeKey node_key = StandaloneNodeIdentity(node);
  const auto it = indices.find(node_key);
  if (it != indices.end()) {
    return it->second;
  }

  auto& nodes = StandaloneRecordedTreeNodes();
  const int index = static_cast<int>(nodes.size());
  StandaloneRecordedTreeNode recorded;
  recorded.kind = StandaloneNodeKind(node);
  recorded.name = StandaloneNodeName(node);
  recorded.value = StandaloneNodeValue(node);
  nodes.push_back(std::move(recorded));
  indices.emplace(node_key, index);
  return index;
}

void RecordStandaloneParserInsert(ContainerNode& parent, Node& child) {
  const int parent_index = EnsureStandaloneRecordedNode(parent);
  const int child_index = EnsureStandaloneRecordedNode(child);
  auto& nodes = StandaloneRecordedTreeNodes();
  auto& last_child = StandaloneLastChildByParent();

  StandaloneRecordedTreeNode& parent_node =
      nodes[static_cast<size_t>(parent_index)];
  StandaloneRecordedTreeNode& child_node =
      nodes[static_cast<size_t>(child_index)];
  child_node.parent_index = parent_index;
  child_node.depth = parent_node.depth + 1;
  child_node.value = StandaloneNodeValue(child);
  if (parent_node.first_child_index < 0) {
    parent_node.first_child_index = child_index;
  }
  const StandaloneNodeKey parent_key = StandaloneNodeIdentity(parent);
  const auto previous = last_child.find(parent_key);
  if (previous != last_child.end() && previous->second >= 0 &&
      previous->second != child_index) {
    nodes[static_cast<size_t>(previous->second)].next_sibling_index =
        child_index;
  }
  last_child[parent_key] = child_index;
  ++parent_node.child_count;
}

int CountStandaloneLinkedDOMNodes(const Node* node, int depth, int* max_depth) {
  if (!node) {
    return 0;
  }
  if (max_depth) {
    *max_depth = std::max(*max_depth, depth);
  }
  int count = 1;
  const Node* child = node->firstChild();
  int guard = 0;
  while (child && guard++ < 4096) {
    count += CountStandaloneLinkedDOMNodes(child, depth + 1, max_depth);
    child = child->nextSibling();
  }
  return count;
}

int AppendStandaloneDOMSnapshotNode(const Node& node,
                                    int parent_index,
                                    int depth) {
  auto& nodes = StandaloneDOMSnapshotNodes();
  const int index = static_cast<int>(nodes.size());
  StandaloneDOMSnapshotNode snapshot;
  snapshot.kind = StandaloneNodeKind(node);
  snapshot.name = StandaloneNodeName(node);
  snapshot.value = StandaloneNodeValue(node);
  snapshot.parent_index = parent_index;
  snapshot.depth = depth;
  nodes.push_back(std::move(snapshot));

  int previous_child_index = -1;
  int child_count = 0;
  const Node* child = node.firstChild();
  int guard = 0;
  while (child && guard++ < 4096) {
    const int child_index =
        AppendStandaloneDOMSnapshotNode(*child, index, depth + 1);
    StandaloneDOMSnapshotNode& parent = nodes[static_cast<size_t>(index)];
    if (parent.first_child_index < 0) {
      parent.first_child_index = child_index;
    }
    if (previous_child_index >= 0) {
      nodes[static_cast<size_t>(previous_child_index)].next_sibling_index =
          child_index;
    }
    previous_child_index = child_index;
    ++child_count;
    child = child->nextSibling();
  }
  nodes[static_cast<size_t>(index)].child_count = child_count;
  return index;
}

bool IsStandaloneLayoutSkippedElement(const StandaloneDOMSnapshotNode& node) {
  return node.kind == "element" &&
         (node.name == "head" || node.name == "script" ||
          node.name == "style");
}

float BuildStandaloneLayoutSnapshotForNode(int node_index,
                                           float x,
                                           float y,
                                           float available_width,
                                           int* text_count) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (node_index < 0 || node_index >= static_cast<int>(nodes.size())) {
    return y;
  }
  const StandaloneDOMSnapshotNode& node =
      nodes[static_cast<size_t>(node_index)];
  if (IsStandaloneLayoutSkippedElement(node)) {
    return y;
  }

  auto& boxes = StandaloneLayoutSnapshotBoxes();
  if (node.kind == "text" && !node.value.empty()) {
    StandaloneLayoutSnapshotBox box;
    box.node_index = node_index;
    box.x = x;
    box.y = y;
    box.width = std::max(8.0f, 8.0f * static_cast<float>(node.value.size()));
    box.height = 24.0f;
    box.role = "text";
    boxes.push_back(std::move(box));
    if (text_count) {
      ++*text_count;
    }
    return y + 24.0f;
  }

  const bool is_block = node.kind == "element" || node.kind == "node";
  const float block_top = y;
  int child = node.first_child_index;
  int guard = 0;
  while (child >= 0 && child < static_cast<int>(nodes.size()) &&
         guard++ < 4096) {
    const StandaloneDOMSnapshotNode& child_node =
        nodes[static_cast<size_t>(child)];
    const float child_indent =
        child_node.kind == "text" ? 0.0f : 12.0f;
    y = BuildStandaloneLayoutSnapshotForNode(
        child, x + child_indent, y, std::max(0.0f, available_width - child_indent),
        text_count);
    child = child_node.next_sibling_index;
  }

  if (is_block && node.name != "#document" && node.name != "html" &&
      node.name != "body") {
    StandaloneLayoutSnapshotBox box;
    box.node_index = node_index;
    box.x = x;
    box.y = block_top;
    box.width = available_width;
    box.height = std::max(24.0f, y - block_top);
    box.role = "block";
    boxes.push_back(std::move(box));
  }
  return y;
}

void RebuildStandaloneLayoutSnapshot() {
  StandaloneLayoutSnapshotBoxes().clear();
  if (StandaloneDOMSnapshotNodes().empty()) {
    return;
  }
  int text_count = 0;
  (void)BuildStandaloneLayoutSnapshotForNode(
      0, 16.0f, 24.0f, 288.0f, &text_count);
}

std::string StandaloneChunkIdForLayoutBox(
    const StandaloneLayoutSnapshotBox& box,
    int ordinal) {
  std::string role = box.role.empty() ? "anonymous" : box.role;
  return "blink-paint-artifact:" + role + ":" + std::to_string(ordinal);
}

void RebuildStandalonePaintArtifactSnapshot() {
  auto& chunks = StandalonePaintArtifactChunks();
  chunks.clear();

  StandalonePaintArtifactChunkSnapshot background;
  background.id = "blink-paint-artifact:viewport-background";
  background.role = "background";
  background.op = "DrawRect";
  background.node_index = -1;
  background.width = 320.0f;
  background.height = 200.0f;
  chunks.push_back(std::move(background));

  const auto& boxes = StandaloneLayoutSnapshotBoxes();
  for (int i = 0; i < static_cast<int>(boxes.size()); ++i) {
    const StandaloneLayoutSnapshotBox& box = boxes[static_cast<size_t>(i)];
    if (box.width <= 0.0f || box.height <= 0.0f) {
      continue;
    }
    StandalonePaintArtifactChunkSnapshot chunk;
    chunk.id = StandaloneChunkIdForLayoutBox(box, i);
    chunk.role = box.role;
    chunk.op = box.role == "text" ? "DrawTextBlob" : "NoOp";
    chunk.node_index = box.node_index;
    chunk.x = box.x;
    chunk.y = box.y;
    chunk.width = box.width;
    chunk.height = box.height;
    chunks.push_back(std::move(chunk));
  }
}

void RebuildStandaloneDOMSnapshot() {
  StandaloneDOMSnapshotNodes().clear();
  if (StandaloneDOMRootNode()) {
    AppendStandaloneDOMSnapshotNode(*StandaloneDOMRootNode(), -1, 0);
  }
  RebuildStandaloneLayoutSnapshot();
  RebuildStandalonePaintArtifactSnapshot();
}

void CopyStandaloneStringToBuffer(const std::string& value,
                                  char* output,
                                  int output_capacity) {
  if (!output || output_capacity <= 0) {
    return;
  }
  const size_t copied =
      std::min(value.size(), static_cast<size_t>(output_capacity - 1));
  std::memcpy(output, value.data(), copied);
  output[copied] = '\0';
}

}  // namespace

namespace standalone_renderer_probe {

void ResetStandaloneHTMLTreeBuilderRecordingForStandaloneRenderer() {
  StandaloneRecordedTreeNodes().clear();
  StandaloneDOMSnapshotNodes().clear();
  StandaloneLayoutSnapshotBoxes().clear();
  StandalonePaintArtifactChunks().clear();
  StandaloneRecordedNodeIndices().clear();
  StandaloneLastChildByParent().clear();
  StandaloneDOMRootNode() = nullptr;
}

int StandaloneHTMLTreeBuilderRecordedNodeCountForStandaloneRenderer() {
  return static_cast<int>(StandaloneRecordedTreeNodes().size());
}

void StandaloneHTMLTreeBuilderRecordedNodeKindAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  if (!output || output_capacity <= 0) {
    return;
  }
  output[0] = '\0';
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return;
  }
  const std::string& value = nodes[static_cast<size_t>(index)].kind;
  const size_t copied =
      std::min(value.size(), static_cast<size_t>(output_capacity - 1));
  std::memcpy(output, value.data(), copied);
  output[copied] = '\0';
}

int StandaloneHTMLTreeBuilderRecordedParentAtForStandaloneRenderer(int index) {
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return -1;
  }
  return nodes[static_cast<size_t>(index)].parent_index;
}

int StandaloneHTMLTreeBuilderRecordedDepthAtForStandaloneRenderer(int index) {
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return 0;
  }
  return nodes[static_cast<size_t>(index)].depth;
}

int StandaloneHTMLTreeBuilderRecordedFirstChildAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return -1;
  }
  return nodes[static_cast<size_t>(index)].first_child_index;
}

int StandaloneHTMLTreeBuilderRecordedChildCountAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return 0;
  }
  return nodes[static_cast<size_t>(index)].child_count;
}

void StandaloneHTMLTreeBuilderRecordedNodeNameAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  if (!output || output_capacity <= 0) {
    return;
  }
  output[0] = '\0';
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return;
  }
  const std::string& value = nodes[static_cast<size_t>(index)].name;
  const size_t copied =
      std::min(value.size(), static_cast<size_t>(output_capacity - 1));
  std::memcpy(output, value.data(), copied);
  output[copied] = '\0';
}

void StandaloneHTMLTreeBuilderRecordedNodeValueAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  if (!output || output_capacity <= 0) {
    return;
  }
  output[0] = '\0';
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return;
  }
  const std::string& value = nodes[static_cast<size_t>(index)].value;
  const size_t copied =
      std::min(value.size(), static_cast<size_t>(output_capacity - 1));
  std::memcpy(output, value.data(), copied);
  output[copied] = '\0';
}

int StandaloneHTMLTreeBuilderRecordedNextSiblingAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneRecordedTreeNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return -1;
  }
  return nodes[static_cast<size_t>(index)].next_sibling_index;
}

int StandaloneHTMLTreeBuilderDOMSnapshotNodeCountForStandaloneRenderer() {
  RebuildStandaloneDOMSnapshot();
  return static_cast<int>(StandaloneDOMSnapshotNodes().size());
}

int StandaloneHTMLTreeBuilderDOMSnapshotParentAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return -1;
  }
  return nodes[static_cast<size_t>(index)].parent_index;
}

int StandaloneHTMLTreeBuilderDOMSnapshotDepthAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return 0;
  }
  return nodes[static_cast<size_t>(index)].depth;
}

int StandaloneHTMLTreeBuilderDOMSnapshotFirstChildAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return -1;
  }
  return nodes[static_cast<size_t>(index)].first_child_index;
}

int StandaloneHTMLTreeBuilderDOMSnapshotNextSiblingAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return -1;
  }
  return nodes[static_cast<size_t>(index)].next_sibling_index;
}

int StandaloneHTMLTreeBuilderDOMSnapshotChildCountAtForStandaloneRenderer(
    int index) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    return 0;
  }
  return nodes[static_cast<size_t>(index)].child_count;
}

void StandaloneHTMLTreeBuilderDOMSnapshotNodeKindAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    CopyStandaloneStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStandaloneStringToBuffer(nodes[static_cast<size_t>(index)].kind, output,
                               output_capacity);
}

void StandaloneHTMLTreeBuilderDOMSnapshotNodeNameAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    CopyStandaloneStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStandaloneStringToBuffer(nodes[static_cast<size_t>(index)].name, output,
                               output_capacity);
}

void StandaloneHTMLTreeBuilderDOMSnapshotNodeValueAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  const auto& nodes = StandaloneDOMSnapshotNodes();
  if (index < 0 || index >= static_cast<int>(nodes.size())) {
    CopyStandaloneStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStandaloneStringToBuffer(nodes[static_cast<size_t>(index)].value, output,
                               output_capacity);
}

int StandaloneHTMLTreeBuilderLayoutSnapshotBoxCountForStandaloneRenderer() {
  return static_cast<int>(StandaloneLayoutSnapshotBoxes().size());
}

int StandaloneHTMLTreeBuilderLayoutSnapshotNodeAtForStandaloneRenderer(
    int index) {
  const auto& boxes = StandaloneLayoutSnapshotBoxes();
  if (index < 0 || index >= static_cast<int>(boxes.size())) {
    return -1;
  }
  return boxes[static_cast<size_t>(index)].node_index;
}

float StandaloneHTMLTreeBuilderLayoutSnapshotXAtForStandaloneRenderer(
    int index) {
  const auto& boxes = StandaloneLayoutSnapshotBoxes();
  if (index < 0 || index >= static_cast<int>(boxes.size())) {
    return 0.0f;
  }
  return boxes[static_cast<size_t>(index)].x;
}

float StandaloneHTMLTreeBuilderLayoutSnapshotYAtForStandaloneRenderer(
    int index) {
  const auto& boxes = StandaloneLayoutSnapshotBoxes();
  if (index < 0 || index >= static_cast<int>(boxes.size())) {
    return 0.0f;
  }
  return boxes[static_cast<size_t>(index)].y;
}

float StandaloneHTMLTreeBuilderLayoutSnapshotWidthAtForStandaloneRenderer(
    int index) {
  const auto& boxes = StandaloneLayoutSnapshotBoxes();
  if (index < 0 || index >= static_cast<int>(boxes.size())) {
    return 0.0f;
  }
  return boxes[static_cast<size_t>(index)].width;
}

float StandaloneHTMLTreeBuilderLayoutSnapshotHeightAtForStandaloneRenderer(
    int index) {
  const auto& boxes = StandaloneLayoutSnapshotBoxes();
  if (index < 0 || index >= static_cast<int>(boxes.size())) {
    return 0.0f;
  }
  return boxes[static_cast<size_t>(index)].height;
}

void StandaloneHTMLTreeBuilderLayoutSnapshotRoleAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  const auto& boxes = StandaloneLayoutSnapshotBoxes();
  if (index < 0 || index >= static_cast<int>(boxes.size())) {
    CopyStandaloneStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStandaloneStringToBuffer(boxes[static_cast<size_t>(index)].role, output,
                               output_capacity);
}

int StandaloneHTMLTreeBuilderPaintArtifactChunkCountForStandaloneRenderer() {
  return static_cast<int>(StandalonePaintArtifactChunks().size());
}

int StandaloneHTMLTreeBuilderPaintArtifactChunkNodeAtForStandaloneRenderer(
    int index) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    return -1;
  }
  return chunks[static_cast<size_t>(index)].node_index;
}

float StandaloneHTMLTreeBuilderPaintArtifactChunkXAtForStandaloneRenderer(
    int index) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    return 0.0f;
  }
  return chunks[static_cast<size_t>(index)].x;
}

float StandaloneHTMLTreeBuilderPaintArtifactChunkYAtForStandaloneRenderer(
    int index) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    return 0.0f;
  }
  return chunks[static_cast<size_t>(index)].y;
}

float StandaloneHTMLTreeBuilderPaintArtifactChunkWidthAtForStandaloneRenderer(
    int index) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    return 0.0f;
  }
  return chunks[static_cast<size_t>(index)].width;
}

float StandaloneHTMLTreeBuilderPaintArtifactChunkHeightAtForStandaloneRenderer(
    int index) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    return 0.0f;
  }
  return chunks[static_cast<size_t>(index)].height;
}

void StandaloneHTMLTreeBuilderPaintArtifactChunkIdAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    CopyStandaloneStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStandaloneStringToBuffer(chunks[static_cast<size_t>(index)].id, output,
                               output_capacity);
}

void StandaloneHTMLTreeBuilderPaintArtifactChunkRoleAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    CopyStandaloneStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStandaloneStringToBuffer(chunks[static_cast<size_t>(index)].role, output,
                               output_capacity);
}

void StandaloneHTMLTreeBuilderPaintArtifactChunkOpAtForStandaloneRenderer(
    int index,
    char* output,
    int output_capacity) {
  const auto& chunks = StandalonePaintArtifactChunks();
  if (index < 0 || index >= static_cast<int>(chunks.size())) {
    CopyStandaloneStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStandaloneStringToBuffer(chunks[static_cast<size_t>(index)].op, output,
                               output_capacity);
}

int StandaloneBlinkPlatformPaintArtifactTypesReachableForStandaloneRenderer() {
  return sizeof(PaintArtifact) > 0 && sizeof(PaintChunk) > 0 ? 1 : 0;
}

int StandaloneBlinkRealPaintBridgeSurfaceReachableForStandaloneRenderer() {
  return sizeof(PaintArtifact) > 0 ? 1 : 0;
}

int StandaloneBlinkRealPaintBridgeRequiresPaintCleanForStandaloneRenderer() {
  return 1;
}

int StandaloneHTMLTreeBuilderDOMLinkedNodeCountForStandaloneRenderer() {
  int max_depth = 0;
  return CountStandaloneLinkedDOMNodes(StandaloneDOMRootNode(), 0,
                                      &max_depth);
}

int StandaloneHTMLTreeBuilderDOMLinkedMaxDepthForStandaloneRenderer() {
  int max_depth = 0;
  CountStandaloneLinkedDOMNodes(StandaloneDOMRootNode(), 0, &max_depth);
  return max_depth;
}

void StandaloneHTMLTreeBuilderRecordSmokeInsertionForStandaloneRenderer() {
  html_names::Init();
  auto* parent =
      StandaloneAllocateNode<Element>(html_names::kDivTag, nullptr);
  auto* child =
      StandaloneAllocateNode<Element>(html_names::kSpanTag, nullptr);
  StandaloneDOMRootNode() = parent;
  parent->ParserAppendChild(child);
  RebuildStandaloneDOMSnapshot();
}

void StandaloneHTMLTreeBuilderParseHTMLForStandaloneRenderer(
    const char* html) {
  ResetStandaloneHTMLTreeBuilderRecordingForStandaloneRenderer();
  html_names::Init();
  auto* fake_document_root =
      StandaloneAllocateNode<Element>(html_names::kHTMLTag, nullptr);
  StandaloneDOMRootNode() = fake_document_root;
  Document& fake_document = *reinterpret_cast<Document*>(fake_document_root);

  HTMLParserOptions options(nullptr);
  options.scripting_flag = false;
  HTMLTokenizer tokenizer(options);
  SegmentedString source(String::FromUtf8(html ? html : ""));
  void* tree_builder_storage =
      Partitions::FastMalloc(sizeof(HTMLTreeBuilder),
                             WTF_HEAP_PROFILER_TYPE_NAME(HTMLTreeBuilder));
  auto* tree_builder = ::new (tree_builder_storage) HTMLTreeBuilder(
      nullptr, fake_document, kDisallowScriptingAndPluginContent, options,
      /*include_shadow_roots=*/false, /*registry=*/nullptr,
      /*sanitizer=*/nullptr);

  int token_budget = 1024;
  while (token_budget-- > 0) {
    HTMLToken* token = tokenizer.NextToken(source);
    if (!token) {
      break;
    }
    AtomicHTMLToken atomic_token(*token);
    tokenizer.ClearToken();
    tree_builder->ConstructTree(&atomic_token);
    if (token->GetType() == HTMLToken::kStartTag &&
        atomic_token.IsValidHTMLTag() &&
        (atomic_token.GetHTMLTag() == html_names::HTMLTag::kScript ||
         atomic_token.GetHTMLTag() == html_names::HTMLTag::kStyle ||
         atomic_token.GetHTMLTag() == html_names::HTMLTag::kTitle ||
         atomic_token.GetHTMLTag() == html_names::HTMLTag::kTextarea)) {
      tokenizer.UpdateStateFor(atomic_token.GetHTMLTag());
    }
  }
  tree_builder->Flush();
  RebuildStandaloneDOMSnapshot();
}

}  // namespace standalone_renderer_probe

namespace features {

BASE_FEATURE(kDeferTreeBuilderFlush, base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE_PARAM(base::TimeDelta,
                   kDeferTreeBuilderFlushInitialInterval,
                   &kDeferTreeBuilderFlush,
                   "initial_interval",
                   base::Milliseconds(16));

BASE_FEATURE_PARAM(base::TimeDelta,
                   kDeferTreeBuilderFlushMaxInterval,
                   &kDeferTreeBuilderFlush,
                   "max_interval",
                   base::Seconds(2));

BASE_FEATURE_PARAM(double,
                   kDeferTreeBuilderFlushMultiplier,
                   &kDeferTreeBuilderFlush,
                   "multiplier",
                   2.0);

}  // namespace features

EventTarget::EventTarget() = default;

EventTarget::~EventTarget() = default;

void EventTarget::Trace(Visitor*) const {}

void EventTarget::ResetEventQueueStatus(const AtomicString&) {}

bool EventTarget::SetAttributeEventListener(const AtomicString&,
                                            EventListener*) {
  return false;
}

bool EventTarget::AddEventListenerInternal(
    const AtomicString&,
    EventListener*,
    const AddEventListenerOptionsResolved*) {
  return false;
}

const DOMWindow* EventTarget::ToDOMWindow() const {
  return nullptr;
}

LocalDOMWindow* EventTarget::ToLocalDOMWindow() {
  return nullptr;
}

const LocalDOMWindow* EventTarget::ToLocalDOMWindow() const {
  return nullptr;
}

MessagePort* EventTarget::ToMessagePort() {
  return nullptr;
}

ServiceWorker* EventTarget::ToServiceWorker() {
  return nullptr;
}

Node* EventTarget::ToNode() {
  return nullptr;
}

void EventTarget::RemoveAllEventListeners() {}

void EventTarget::AddedEventListener(const AtomicString&,
                                     RegisteredEventListener&) {}

void EventTarget::RemovedEventListener(const AtomicString&,
                                       const RegisteredEventListener&) {}

DispatchEventResult EventTarget::DispatchEventInternal(Event&) {
  return DispatchEventResult::kNotCanceled;
}

void ScriptWrappable::Trace(Visitor*) const {}

const char* ScriptWrappable::GetHumanReadableName() const {
  return "ScriptWrappable";
}

v8::Local<v8::Value> ScriptWrappable::Wrap(ScriptState*) {
  return v8::Local<v8::Value>();
}

v8::Local<v8::Object> ScriptWrappable::AssociateWithWrapper(
    v8::Isolate*,
    const WrapperTypeInfo*,
    v8::Local<v8::Object> wrapper) {
  return wrapper;
}

Node::Node(TreeScope* tree_scope, ConstructionType type)
    : node_flags_(type),
      tree_scope_(tree_scope),
      parent_or_shadow_host_node_(ParentNodeTag{}, nullptr),
      layout_object_(nullptr) {}

Node::~Node() = default;

const AtomicString& Node::InterfaceName() const {
  return g_null_atom;
}

ExecutionContext* Node::GetExecutionContext() const {
  return nullptr;
}

Node* Node::ToNode() {
  return this;
}

void Node::RemoveAllEventListeners() {}

void Node::AddedEventListener(const AtomicString&,
                              RegisteredEventListener&) {}

void Node::RemovedEventListener(const AtomicString&,
                                const RegisteredEventListener&) {}

DispatchEventResult Node::DispatchEventInternal(Event&) {
  return DispatchEventResult::kNotCanceled;
}

void Node::Trace(Visitor* visitor) const {
  EventTarget::Trace(visitor);
}

String Node::nodeValue() const {
  return String();
}

void Node::setNodeValue(const String&, ExceptionState&) {}

void Node::setTextContent(const String&) {}

void Node::setTextContentForBinding(const V8UnionStringOrTrustedScript*,
                                    ExceptionState&) {}

bool Node::ShouldHaveFocusAppearance() const {
  return false;
}

bool Node::CanStartSelection() const {
  return false;
}

void Node::SetDragged(bool) {}

PhysicalRect Node::BoundingBox() const {
  return PhysicalRect();
}

void Node::AttachLayoutTree(AttachContext&) {}

void Node::DetachLayoutTree(bool) {}

Node::InsertionNotificationRequest Node::InsertedInto(ContainerNode&) {
  return kInsertionDone;
}

void Node::RemovedFrom(ContainerNode&) {}

void Node::MovedFrom(ContainerNode&) {}

void Node::DefaultEventHandler(Event&) {}

void Node::DidMoveToNewDocument(Document&) {}

void Node::AddConsoleMessage(mojom::blink::ConsoleMessageSource,
                             mojom::blink::ConsoleMessageLevel,
                             const String&) {}

void Node::remove(ExceptionState&) {}

bool Node::IsRichlyEditableForAccessibility() const {
  return false;
}

bool Node::WillRespondToMouseMoveEvents() const {
  return false;
}

bool Node::WillRespondToMouseClickEvents() {
  return false;
}

void Node::HandleLocalEvents(Event&) {}

bool Node::HasActivationBehavior() const {
  return false;
}

LayoutBox* Node::AutoscrollBox() {
  return nullptr;
}

void Node::StopAutoscroll() {}

ContainerNode::~ContainerNode() = default;

void ContainerNode::Trace(Visitor* visitor) const {
  Node::Trace(visitor);
}

PhysicalRect ContainerNode::BoundingBox() const {
  return PhysicalRect();
}

bool ContainerNode::ChildrenChangedAllChildrenRemovedNeedsList() const {
  return false;
}

LayoutBox* ContainerNode::GetLayoutBoxForScrolling() const {
  return nullptr;
}

namespace {
WrapperTypeInfo g_standalone_wrapper_type_info = {};
}

const WrapperTypeInfo& Element::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& HTMLElement::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& DocumentType::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& Comment::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& ProcessingInstruction::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& HTMLHtmlElement::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& CharacterData::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& Text::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& EventTarget::wrapper_type_info_ =
    g_standalone_wrapper_type_info;
const WrapperTypeInfo& Node::wrapper_type_info_ =
    g_standalone_wrapper_type_info;

Element::Element(const QualifiedName& tag_name,
                 Document* document,
                 ConstructionType type)
    : ContainerNode(document, type), tag_name_(tag_name) {}

void Element::Trace(Visitor* visitor) const {
  ContainerNode::Trace(visitor);
}

String Element::nodeName() const {
  return tag_name_.ToString();
}

void Element::AttributeChanged(const AttributeModificationParams&) {}

void Element::ParseAttribute(const AttributeModificationParams&) {}

bool Element::HasLegalLinkAttribute(const QualifiedName&) const {
  return false;
}

void Element::InvalidateStyleAttribute(bool) {}

bool Element::HandleScrollByPageCommand(CommandEventType) {
  return false;
}

String HTMLElement::nodeName() const {
  return localName().GetString();
}

Node* Element::Clone(Document&,
                     NodeCloningData&,
                     ContainerNode*,
                     CustomElementRegistry*,
                     ExceptionState&) const {
  return nullptr;
}

void Element::SetDragged(bool) {}

bool Element::ChildTypeAllowed(NodeType) const {
  return true;
}

void Element::AttachLayoutTree(AttachContext&) {}

void Element::DetachLayoutTree(bool) {}

Node::InsertionNotificationRequest Element::InsertedInto(ContainerNode&) {
  return kInsertionDone;
}

void Element::RemovedFrom(ContainerNode&) {}

void Element::DefaultEventHandler(Event&) {}

void Element::DidMoveToNewDocument(Document&) {}

void Element::AdjustStyle(ComputedStyleBuilder&) {}

void Element::SetActive(bool) {}

void Element::SetHovered(bool) {}

bool Element::IsInertRoot() const {
  return false;
}

void Element::WillRecalcStyle(const StyleRecalcChange) {}

void Element::DidRecalcStyle(const StyleRecalcChange) {}

const ComputedStyle* Element::CustomStyleForLayoutObject(
    const StyleRecalcContext&) {
  return nullptr;
}

FocusableState Element::SupportsFocus(UpdateBehavior) const {
  return FocusableState::kNotFocusable;
}

FocusableState Element::IsFocusableState(UpdateBehavior) const {
  return FocusableState::kNotFocusable;
}

bool Element::IsFocusableStyle(UpdateBehavior) const {
  return false;
}

void Element::LangAttributeChanged() {}

int Element::DefaultTabIndex() const {
  return -1;
}

Element& Element::CloneWithoutAttributesAndChildren(
    Document& document,
    CustomElementRegistry*) const {
  return *StandaloneAllocateNode<Element>(tag_name_, &document, kCreateElement);
}

LayoutObject* Element::CreateLayoutObject(const ComputedStyle&) {
  return nullptr;
}

bool Element::LayoutObjectIsNeeded(const DisplayStyle&) const {
  return false;
}

const AtomicString& Element::ShadowPseudoId() const {
  return g_null_atom;
}

void Element::FinishParsingChildren() {}

bool Element::CanGeneratePseudoElement(PseudoId) const {
  return false;
}

bool Element::MayTriggerVirtualKeyboard() const {
  return false;
}

void Element::SetActivatedSubmit(bool) {}

bool Element::IsActivatedSubmit() const {
  return false;
}

void Element::MovedFrom(ContainerNode&) {}

void Element::ChildrenChanged(const ChildrenChange&) {}

const AttrNameToTrustedType& Element::GetCheckedAttributeTypes() const {
  DEFINE_STATIC_LOCAL(AttrNameToTrustedType, empty, ());
  return empty;
}

double Element::scrollLeft() {
  return 0;
}

double Element::scrollTop() {
  return 0;
}

int Element::scrollWidth() {
  return 0;
}

int Element::scrollHeight() {
  return 0;
}

const AtomicString Element::ImageSourceURL() const {
  return g_null_atom;
}

void Element::Focus(const FocusParams&) {}

void Element::SetFocused(bool, mojom::blink::FocusType) {}

void Element::SetHasFocusWithinUpToAncestor(bool, Element*, bool) {}

void Element::UpdateSelectionOnFocus(SelectionBehaviorOnFocus,
                                     const FocusOptions*) {}

void Element::blur() {}

bool Element::IsKeyboardFocusableSlow(UpdateBehavior) const {
  return false;
}

FocusgroupFlags Element::NativeArrowKeyAxes() const {
  return FocusgroupFlags::kNone;
}

bool Element::DispatchFocusEvent(Element*,
                                 mojom::blink::FocusType,
                                 InputDeviceCapabilities*) {
  return true;
}

void Element::DispatchBlurEvent(Element*,
                                mojom::blink::FocusType,
                                InputDeviceCapabilities*) {}

void Element::DispatchFocusInEvent(const AtomicString&,
                                   Element*,
                                   mojom::blink::FocusType,
                                   InputDeviceCapabilities*) {}

const char* HTMLElement::GetHumanReadableName() const {
  return "HTMLElement";
}

String HTMLElement::title() const {
  return String();
}

void HTMLElement::setInnerTextForBinding(
    const V8UnionStringLegacyNullToEmptyStringOrTrustedScript*,
    ExceptionState&) {}

bool HTMLElement::HasCustomFocusLogic() const {
  return false;
}

const AtomicString& HTMLElement::autocapitalize() const {
  return g_null_atom;
}

bool HTMLElement::draggable() const {
  return false;
}

HTMLFormElement* HTMLElement::formOwner() const {
  return nullptr;
}

HTMLElement* HTMLElement::formForBinding() const {
  return nullptr;
}

void HTMLElement::AccessKeyAction(SimulatedClickCreationScope) {}

FocusgroupFlags HTMLElement::NativeArrowKeyAxes() const {
  return FocusgroupFlags::kNone;
}

bool HTMLElement::DispatchFocusEvent(Element*,
                                     mojom::blink::FocusType,
                                     InputDeviceCapabilities*) {
  return true;
}

void HTMLElement::CollectStyleForPresentationAttribute(
    const QualifiedName&,
    const AtomicString&,
    HeapVector<CSSPropertyValue, 8>&) {}

void HTMLElement::AttributeChanged(const AttributeModificationParams&) {}

void HTMLElement::ParseAttribute(const AttributeModificationParams&) {}

bool HTMLElement::IsPresentationAttribute(const QualifiedName&) const {
  return false;
}

bool HTMLElement::IsValidBuiltinCommand(HTMLElement&, CommandEventType) {
  return false;
}

bool HTMLElement::HandleCommandInternal(HTMLElement&, CommandEventType) {
  return false;
}

bool HTMLElement::IsRenderedInTopLayer() const {
  return false;
}

void HTMLElement::ShowPopoverInternal(Element*, ExceptionState*) {}

PopoverHideResult HTMLElement::HidePopoverInternal(
    Element*,
    HidePopoverFocusBehavior,
    HidePopoverTransitionBehavior,
    ExceptionState*) {
  return PopoverHideResult::kHidden;
}

bool HTMLElement::CanBeCommandInvoker() const {
  return false;
}

bool HTMLElement::HandleCommandForActivation() {
  return false;
}

bool HTMLElement::MatchesDefaultPseudoClass() const {
  return false;
}

bool HTMLElement::MatchesEnabledPseudoClass() const {
  return false;
}

bool HTMLElement::MatchesDisabledPseudoClass() const {
  return false;
}

bool HTMLElement::MatchesReadOnlyPseudoClass() const {
  return false;
}

bool HTMLElement::MatchesReadWritePseudoClass() const {
  return false;
}

bool HTMLElement::MatchesValidityPseudoClasses() const {
  return false;
}

bool HTMLElement::willValidate() const {
  return false;
}

bool HTMLElement::IsValidElement() {
  return true;
}

bool HTMLElement::IsDisabledFormControl() const {
  return false;
}

bool HTMLElement::IsLabelable() const {
  return false;
}

bool HTMLElement::IsInteractiveContent() const {
  return false;
}

bool HTMLElement::CalculateAndAdjustAutoDirectionality() {
  return false;
}

FocusableState HTMLElement::SupportsFocus(UpdateBehavior) const {
  return FocusableState::kNotFocusable;
}

Node::InsertionNotificationRequest HTMLElement::InsertedInto(ContainerNode&) {
  return kInsertionDone;
}

void HTMLElement::RemovedFrom(ContainerNode&) {}

void HTMLElement::DefaultEventHandler(Event&) {}

void HTMLElement::DidMoveToNewDocument(Document&) {}

void HTMLElement::FinishParsingChildren() {}

void HTMLFormElement::Trace(Visitor*) const {}

void CustomElementRegistry::Trace(Visitor*) const {}

Text* Text::Create(Document& document, const String& data) {
  return StandaloneAllocateNode<Text>(document, data, kCreateText);
}

Text* Text::Create(Document& document, String&& data) {
  return StandaloneAllocateNode<Text>(document, std::move(data), kCreateText);
}

Text* Text::CreateEditingText(Document& document, const String& data) {
  return StandaloneAllocateNode<Text>(document, data, kCreateEditingText);
}

void CharacterData::ParserAppendData(const String& data) {
  StringBuilder builder;
  builder.Append(this->data());
  builder.Append(data);
  SetDataWithoutUpdate(builder.ToString());
  EnsureStandaloneRecordedNode(*this);
}

String CharacterData::nodeValue() const {
  return data();
}

void CharacterData::setNodeValue(const String& value, ExceptionState&) {
  SetDataWithoutUpdate(value);
}

Node* CharacterData::Clone(Document& factory,
                           NodeCloningData&,
                           ContainerNode*,
                           CustomElementRegistry*,
                           ExceptionState&) const {
  return CloneWithData(factory, data());
}

void ContainerNode::ParserAppendChild(Node* child) {
  if (child) {
    if (child->parentNode() != this) {
      child->SetParentNode(this);
      child->SetNextSibling(nullptr);
      if (Node* last_child = lastChild()) {
        child->SetPreviousSibling(last_child);
        last_child->SetNextSibling(child);
        SetLastChild(child);
      } else {
        child->SetPreviousSibling(child);
        SetFirstChild(child);
      }
    }
    RecordStandaloneParserInsert(*this, *child);
  }
}

void ContainerNode::ParserAppendChildInDocumentFragment(Node* child) {
  if (child) {
    ParserAppendChild(child);
  }
}

void ContainerNode::ParserFinishedBuildingDocumentFragment(
    ShouldNotifyInsertedNodes) {}

void ContainerNode::ParserRemoveChild(Node&) {}

void ContainerNode::ParserInsertBefore(Node* child, Node&) {
  if (child) {
    ParserAppendChild(child);
  }
}

void ContainerNode::ParserReplaceChild(Node&, Node&) {}

void ContainerNode::ParserTakeAllChildrenFrom(ContainerNode&) {}

void Element::StripScriptingAttributes(
    Vector<Attribute, kAttributePrealloc>&) const {}

void Element::ParserSetAttributes(
    const Vector<Attribute, kAttributePrealloc>&) {}

void Element::SetAttributeWithoutValidation(const QualifiedName&,
                                            const AtomicString&) {}

void Element::HideNonce() {}

bool Element::FastAttributeLookupAllowed(const QualifiedName&) const {
  return false;
}

bool Element::AttachDeclarativeShadowRoot(HTMLTemplateElement&,
                                          String,
                                          FocusDelegation,
                                          SlotAssignmentMode,
                                          bool,
                                          bool,
                                          const AtomicString&,
                                          const AtomicString&,
                                          bool) {
  return false;
}

ShadowRoot* Element::AuthorShadowRoot() const {
  return nullptr;
}

DocumentType::DocumentType(Document* document,
                           const String& name,
                           const String& public_id,
                           const String& system_id)
    : Node(document, kCreateDocumentType),
      name_(name),
      public_id_(public_id),
      system_id_(system_id) {}

String DocumentType::nodeName() const {
  return name_;
}

Node* DocumentType::Clone(Document& factory,
                          NodeCloningData&,
                          ContainerNode*,
                          CustomElementRegistry*,
                          ExceptionState&) const {
  return StandaloneAllocateNode<DocumentType>(&factory, name_, public_id_,
                                             system_id_);
}

Node::InsertionNotificationRequest DocumentType::InsertedInto(ContainerNode&) {
  return kInsertionDone;
}

void DocumentType::RemovedFrom(ContainerNode&) {}

Comment* Comment::Create(Document& document, const String& data) {
  return StandaloneAllocateNode<Comment>(document, data);
}

Comment::Comment(Document& document, const String& data)
    : CharacterData(document, data, kCreateComment) {}

String Comment::nodeName() const {
  return "#comment";
}

CharacterData* Comment::CloneWithData(Document& document,
                                      const String& data) const {
  return StandaloneAllocateNode<Comment>(document, data);
}

ProcessingInstruction::ProcessingInstruction(Document& document,
                                             const String& target,
                                             const String& data)
    : CharacterData(document, data, kCreateProcessingInstruction),
      target_(target),
      loading_(false),
      alternate_(false),
      is_css_(false),
      is_xsl_(false) {}

ProcessingInstruction::~ProcessingInstruction() = default;

void ProcessingInstruction::Trace(Visitor* visitor) const {
  CharacterData::Trace(visitor);
}

String ProcessingInstruction::nodeName() const {
  return target_;
}

bool ProcessingInstruction::SheetLoaded() {
  return true;
}

Node::InsertionNotificationRequest ProcessingInstruction::InsertedInto(
    ContainerNode&) {
  return kInsertionDone;
}

void ProcessingInstruction::DidNotifySubtreeInsertionsToDocument() {}

void ProcessingInstruction::RemovedFrom(ContainerNode&) {}

CharacterData* ProcessingInstruction::CloneWithData(
    Document& document,
    const String& data) const {
  return StandaloneAllocateNode<ProcessingInstruction>(document, target_, data);
}

void ProcessingInstruction::NotifyFinished(Resource*) {}

HTMLHtmlElement::HTMLHtmlElement(Document& document)
    : HTMLElement(html_names::kHTMLTag, document) {}

void HTMLHtmlElement::InsertedByParser() {}

bool HTMLHtmlElement::IsURLAttribute(const Attribute&) const {
  return false;
}

void ResourceClient::Trace(Visitor*) const {}

void ResourceClient::Prefinalize() {}

void Text::Trace(Visitor* visitor) const {
  CharacterData::Trace(visitor);
}

String Text::nodeName() const {
  return "#text";
}

void Text::AttachLayoutTree(AttachContext&) {}

CharacterData* Text::CloneWithData(Document& document,
                                   const String& data) const {
  return StandaloneAllocateNode<Text>(document, data, kCreateText);
}

ConsoleMessage::ConsoleMessage(mojom::blink::ConsoleMessageSource source,
                               mojom::blink::ConsoleMessageLevel level,
                               const String& message,
                               SourceLocation* source_location)
    : source_(source),
      level_(level),
      message_(message),
      location_(source_location),
      timestamp_(0) {}

ConsoleMessage::~ConsoleMessage() = default;

void ConsoleMessage::Trace(Visitor*) const {}

SourceLocation* CaptureSourceLocation() {
  return nullptr;
}

bool RuntimeCallStats::IsEnabled() {
  return false;
}

RuntimeCallStats* RuntimeCallStats::From(v8::Isolate*) {
  return nullptr;
}

RuntimeCallTimer* RuntimeCallTimer::Stop() {
  return nullptr;
}

void RuntimeCallTimer::Start(RuntimeCallCounter*, RuntimeCallTimer*) {}

ContainerNode* HTMLTemplateElement::InsertionTarget() const {
  return nullptr;
}

CustomElementRegistry* CustomElementRegistry::DefaultRegistry(Document&) {
  return nullptr;
}

CustomElementDefinition* CustomElementRegistry::DefinitionFor(
    const CustomElementDescriptor&) const {
  return nullptr;
}

HTMLElement* CustomElementDefinition::CreateElement(Document&,
                                                    const QualifiedName&,
                                                    CreateElementFlags) {
  return nullptr;
}

Element* CustomElement::CreateUncustomizedOrUndefinedElement(
    Document&,
    const QualifiedName&,
    CreateElementFlags,
    const AtomicString&,
    CustomElementRegistry*,
    bool) {
  return nullptr;
}

CustomElementRegistry* TreeScope::customElementRegistry() const {
  return nullptr;
}

CustomElementRegistry* Element::customElementRegistry() const {
  return nullptr;
}

CustomElementRegistry* LocalDOMWindow::MaybeCustomElements() const {
  return nullptr;
}

void scheduler::EventLoop::PerformMicrotaskCheckpoint() {}

CEReactionsScope* CEReactionsScope::top_of_stack_ = nullptr;

CEReactionsScope::CEReactionsScope(v8::Isolate* isolate)
    : prev_(top_of_stack_), try_catch_(isolate) {
  top_of_stack_ = this;
}

CEReactionsScope::~CEReactionsScope() {
  top_of_stack_ = prev_;
}

Patch* Patch::Prepare(ContainerNode*, const AtomicString&) {
  return nullptr;
}

void Patch::Apply(HTMLConstructionSiteTask&) {}

std::ostream& operator<<(std::ostream& ostream, const Node*) {
  return ostream << "Node";
}

const String& ParkableString::ToString() const {
  DEFINE_STATIC_LOCAL(String, empty, ());
  return empty;
}

ParkableString::~ParkableString() = default;

ParkableStringImpl::~ParkableStringImpl() = default;

void ParkableStringImpl::ReleaseAndRemoveIfNeeded() const {
  delete this;
}

CharacterBreakIterator::CharacterBreakIterator(base::span<const UChar> span)
    : is_8bit_(false), charaters8_(nullptr), offset_(0), length_(span.size()) {}

bool CharacterBreakIterator::IsBreak(int offset) const {
  return offset >= 0;
}

int CharacterBreakIterator::Preceding(int offset) const {
  return offset > 0 ? offset - 1 : 0;
}

void CharacterBreakIterator::ReturnToPool::operator()(void*) const {}

Sanitizer::Action Sanitizer::SanitizeSingleNode(Node*, Mode) const {
  return Action::kKeep;
}

bool Sanitizer::ShouldReplaceNodeWithChildren(Node*) const {
  return false;
}

ThreadStateStorage* ThreadStateStorage::Current() {
  return nullptr;
}

ThreadStateStorage ThreadStateStorage::main_thread_state_storage_;

bool IsOnStack(void*) {
  return false;
}

}  // namespace blink

namespace cppgc::subtle {

bool DisallowGarbageCollectionScope::IsGarbageCollectionAllowed(
    HeapHandle&) {
  return true;
}

}  // namespace cppgc::subtle

namespace cppgc::internal {

AtomicEntryFlag WriteBarrier::write_barrier_enabled_;

PrefinalizerRegistration::PrefinalizerRegistration(void*, Callback) {}

TraceDescriptor TraceTraitFromInnerAddressImpl::GetTraceDescriptor(
    const void* address) {
  return {address, nullptr};
}

void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  GCInfoIndex) {
  return std::malloc(size ? size : 1);
}

void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  AlignVal,
                                                  GCInfoIndex) {
  return std::malloc(size ? size : 1);
}

void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  GCInfoIndex,
                                                  CustomSpaceIndex) {
  return std::malloc(size ? size : 1);
}

void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  AlignVal,
                                                  GCInfoIndex,
                                                  CustomSpaceIndex) {
  return std::malloc(size ? size : 1);
}

GCInfoIndex EnsureGCInfoIndexTrait::EnsureGCInfoIndex(
    std::atomic<GCInfoIndex>& registered_index,
    TraceCallback,
    FinalizationCallback,
    NameCallback) {
  registered_index = 1;
  return 1;
}

GCInfoIndex EnsureGCInfoIndexTrait::EnsureGCInfoIndex(
    std::atomic<GCInfoIndex>& registered_index,
    TraceCallback,
    FinalizationCallback) {
  registered_index = 1;
  return 1;
}

void ExplicitManagementImpl::FreeUnreferencedObject(HeapHandle&, void* p) {
  std::free(p);
}

bool ExplicitManagementImpl::Resize(void*, size_t) {
  return false;
}

GCInfoIndex EnsureGCInfoIndexTrait::EnsureGCInfoIndex(
    std::atomic<GCInfoIndex>& registered_index,
    TraceCallback) {
  registered_index = 1;
  return 1;
}

size_t BaseObjectSizeTrait::GetObjectSizeForGarbageCollected(const void*) {
  return 0;
}

void WriteBarrier::DijkstraMarkingBarrierSlowWithSentinelCheck(
    const void*) {}

void WriteBarrier::DijkstraMarkingBarrierRangeSlow(HeapHandle&,
                                                   const void*,
                                                   size_t,
                                                   size_t,
                                                   TraceCallback) {}

}  // namespace cppgc::internal

namespace cppgc {

bool LivenessBroker::IsHeapObjectAliveImpl(const void*) const {
  return true;
}

}  // namespace cppgc

namespace cppgc::subtle {

void NoGarbageCollectionScope::Enter(HeapHandle&) {}

void NoGarbageCollectionScope::Leave(HeapHandle&) {}

}  // namespace cppgc::subtle

namespace v8 {

bool Isolate::HasPendingException() {
  return false;
}

TryCatch::TryCatch(Isolate*) {}

TryCatch::~TryCatch() = default;

}  // namespace v8
