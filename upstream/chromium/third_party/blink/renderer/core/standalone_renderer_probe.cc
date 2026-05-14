// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/css/css_property_names.h"
#include "third_party/blink/renderer/core/css_value_keywords.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_token_stream.h"
#include "third_party/blink/renderer/core/css/parser/css_tokenizer.h"
#include "third_party/blink/renderer/core/dom/document_init.h"
#include "third_party/blink/renderer/core/html/html_document.h"
#include "third_party/blink/renderer/core/html/parser/atomic_html_token.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_options.h"
#include "third_party/blink/renderer/core/html/parser/html_tokenizer.h"
#include "third_party/blink/renderer/core/style/computed_style_base_constants.h"
#include "third_party/blink/renderer/platform/text/segmented_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>

namespace blink {

namespace standalone_renderer_probe {
namespace {

struct HTMLTokenizerSummary {
  int token_count = 0;
  int start_tag_count = 0;
  int end_tag_count = 0;
  int character_token_count = 0;
  int atomic_token_count = 0;
  int atomic_attribute_count = 0;
  int atomic_valid_html_tag_count = 0;
  bool found_image_src = false;
  std::string visible_text;
  std::vector<std::string> start_tag_names;
  std::vector<std::string> image_sources;
  std::vector<std::string> style_blocks;
  std::vector<std::string> node_kinds;
  std::vector<std::string> node_names;
  std::vector<std::string> node_values;
  std::vector<html_names::HTMLTag> node_html_tags;
  std::vector<int> node_parent_indices;
  std::vector<int> node_depths;
  std::vector<int> node_ids;
  std::vector<int> node_first_child_indices;
  std::vector<int> node_next_sibling_indices;
  std::vector<int> node_child_counts;
  std::vector<bool> node_is_synthetic;
  std::vector<std::string> node_bridge_actions;
  int max_tree_depth = 0;
  int synthetic_node_count = 0;
  int tree_bridge_event_count = 0;
  int next_node_id = 1;
  int root_node_index = -1;
  int head_node_index = -1;
  int body_node_index = -1;
};

struct CSSTokenizerSummary {
  int token_count = 0;
  std::vector<std::string> urls;
};

struct CSSParserStreamSummary {
  int token_count = 0;
  int at_rule_count = 0;
  int block_start_count = 0;
  int block_end_count = 0;
  int function_count = 0;
};

struct CSSDeclarationSummary {
  std::vector<std::string> selectors;
  std::vector<std::string> property_names;
  std::vector<std::string> property_values;
};

bool IsASCIIAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool IsASCIIWhitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

bool StartsWithURLFunction(const std::string& css, size_t offset) {
  if (offset + 3 > css.size()) {
    return false;
  }
  const unsigned char u = static_cast<unsigned char>(css[offset]);
  const unsigned char r = static_cast<unsigned char>(css[offset + 1]);
  const unsigned char l = static_cast<unsigned char>(css[offset + 2]);
  if (std::tolower(u) != 'u' || std::tolower(r) != 'r' ||
      std::tolower(l) != 'l') {
    return false;
  }
  if (offset > 0 &&
      (IsASCIIAlpha(css[offset - 1]) || css[offset - 1] == '-' ||
       css[offset - 1] == '_')) {
    return false;
  }
  size_t cursor = offset + 3;
  while (cursor < css.size() && IsASCIIWhitespace(css[cursor])) {
    ++cursor;
  }
  return cursor < css.size() && css[cursor] == '(';
}

std::string EscapeCSSStringForURL(const std::string& value) {
  std::string escaped;
  escaped.reserve(value.size());
  for (const char c : value) {
    if (c == '"' || c == '\\') {
      escaped.push_back('\\');
    }
    escaped.push_back(c);
  }
  return escaped;
}

std::string NormalizeUnquotedURLFunctionsForCSSTokenizer(const char* css) {
  std::string input(css ? css : "");
  std::string output;
  output.reserve(input.size());

  for (size_t i = 0; i < input.size();) {
    if (!StartsWithURLFunction(input, i)) {
      output.push_back(input[i++]);
      continue;
    }

    output.append(input, i, 3);
    i += 3;
    while (i < input.size() && IsASCIIWhitespace(input[i])) {
      output.push_back(input[i++]);
    }
    if (i >= input.size() || input[i] != '(') {
      continue;
    }
    output.push_back(input[i++]);
    while (i < input.size() && IsASCIIWhitespace(input[i])) {
      output.push_back(input[i++]);
    }
    if (i >= input.size() || input[i] == '"' || input[i] == '\'') {
      continue;
    }

    const size_t value_start = i;
    while (i < input.size() && input[i] != ')' && input[i] != '(' &&
           input[i] != '"' && input[i] != '\'') {
      ++i;
    }
    size_t value_end = i;
    while (value_end > value_start && IsASCIIWhitespace(input[value_end - 1])) {
      --value_end;
    }
    if (i < input.size() && input[i] == ')') {
      output.push_back('"');
      output.append(
          EscapeCSSStringForURL(input.substr(value_start,
                                             value_end - value_start)));
      output.push_back('"');
      output.push_back(')');
      ++i;
    } else {
      output.append(input, value_start, i - value_start);
    }
  }

  return output;
}

bool EqualIgnoringASCIICase(const String& value, const char* literal) {
  return DeprecatedEqualIgnoringCase(value, String::FromUtf8(literal));
}

void AppendVisibleText(std::string& text, const std::string& chunk) {
  for (size_t i = 0; i < chunk.size(); ++i) {
    const unsigned char c = static_cast<unsigned char>(chunk[i]);
    if (c == 0xC2 && i + 1 < chunk.size() &&
        static_cast<unsigned char>(chunk[i + 1]) == 0xA0) {
      if (!text.empty() && text.back() != ' ') {
        text.push_back(' ');
      }
      ++i;
      continue;
    }
    if (std::isspace(c)) {
      if (!text.empty() && text.back() != ' ') {
        text.push_back(' ');
      }
      continue;
    }
    text.push_back(static_cast<char>(c));
  }
}

void AppendTagBoundarySpace(std::string& text) {
  if (!text.empty() && text.back() != ' ') {
    text.push_back(' ');
  }
}

void AppendHTMLNode(HTMLTokenizerSummary& summary,
                    std::string kind,
                    std::string name,
                    std::string value,
                    html_names::HTMLTag html_tag =
                        html_names::HTMLTag::kUnknown) {
  summary.node_kinds.push_back(std::move(kind));
  summary.node_names.push_back(std::move(name));
  summary.node_values.push_back(std::move(value));
  summary.node_html_tags.push_back(html_tag);
  summary.node_parent_indices.push_back(-1);
  summary.node_depths.push_back(0);
  summary.node_ids.push_back(summary.next_node_id++);
  summary.node_first_child_indices.push_back(-1);
  summary.node_next_sibling_indices.push_back(-1);
  summary.node_child_counts.push_back(0);
  summary.node_is_synthetic.push_back(false);
  summary.node_bridge_actions.push_back("source-token");
  ++summary.tree_bridge_event_count;
}

void InsertSyntheticHTMLNode(HTMLTokenizerSummary& summary,
                             size_t index,
                             std::string kind,
                             html_names::HTMLTag html_tag) {
  const std::string name =
      html_names::TagToQualifiedName(html_tag).LocalName().Utf8();
  summary.node_kinds.insert(summary.node_kinds.begin() + index,
                            std::move(kind));
  summary.node_names.insert(summary.node_names.begin() + index,
                            name);
  summary.node_values.insert(summary.node_values.begin() + index,
                             std::string());
  summary.node_html_tags.insert(summary.node_html_tags.begin() + index,
                                html_tag);
  summary.node_parent_indices.insert(summary.node_parent_indices.begin() +
                                         index,
                                     -1);
  summary.node_depths.insert(summary.node_depths.begin() + index, 0);
  summary.node_ids.insert(summary.node_ids.begin() + index,
                          summary.next_node_id++);
  summary.node_first_child_indices.insert(summary.node_first_child_indices.begin() +
                                             index,
                                         -1);
  summary.node_next_sibling_indices.insert(summary.node_next_sibling_indices.begin() +
                                              index,
                                          -1);
  summary.node_child_counts.insert(summary.node_child_counts.begin() + index,
                                   0);
  summary.node_is_synthetic.insert(summary.node_is_synthetic.begin() + index,
                                   true);
  summary.node_bridge_actions.insert(summary.node_bridge_actions.begin() +
                                         index,
                                     "parser-inserted");
  ++summary.synthetic_node_count;
  ++summary.tree_bridge_event_count;
}

bool HasStartElement(const HTMLTokenizerSummary& summary,
                     html_names::HTMLTag html_tag) {
  for (size_t i = 0; i < summary.node_kinds.size(); ++i) {
    if (summary.node_kinds[i] == "start" &&
        summary.node_html_tags[i] == html_tag) {
      return true;
    }
  }
  return false;
}

size_t FindFirstStartElement(const HTMLTokenizerSummary& summary,
                             html_names::HTMLTag html_tag) {
  for (size_t i = 0; i < summary.node_kinds.size(); ++i) {
    if (summary.node_kinds[i] == "start" &&
        summary.node_html_tags[i] == html_tag) {
      return i;
    }
  }
  return summary.node_kinds.size();
}

size_t FindLastEndElement(const HTMLTokenizerSummary& summary,
                          html_names::HTMLTag html_tag) {
  for (size_t i = summary.node_kinds.size(); i > 0; --i) {
    const size_t index = i - 1;
    if (summary.node_kinds[index] == "end" &&
        summary.node_html_tags[index] == html_tag) {
      return index;
    }
  }
  return summary.node_kinds.size();
}

bool IsBlinkInHeadStartTagForStandaloneBridge(html_names::HTMLTag tag) {
  using HTMLTag = html_names::HTMLTag;
  switch (tag) {
    case HTMLTag::kBase:
    case HTMLTag::kBasefont:
    case HTMLTag::kBgsound:
    case HTMLTag::kCommand:
    case HTMLTag::kLink:
    case HTMLTag::kMeta:
    case HTMLTag::kNoframes:
    case HTMLTag::kNoscript:
    case HTMLTag::kScript:
    case HTMLTag::kStyle:
    case HTMLTag::kTemplate:
    case HTMLTag::kTitle:
      return true;
    default:
      return false;
  }
}

bool IsStandaloneHeadContentNode(const HTMLTokenizerSummary& summary,
                                 size_t index) {
  if (index >= summary.node_kinds.size()) {
    return false;
  }
  const std::string& kind = summary.node_kinds[index];
  const html_names::HTMLTag tag = summary.node_html_tags[index];
  if (kind == "style" && tag == html_names::HTMLTag::kStyle) {
    return true;
  }
  if ((kind == "start" || kind == "end") &&
      IsBlinkInHeadStartTagForStandaloneBridge(tag)) {
    return true;
  }
  if (kind == "text") {
    const std::string& value = summary.node_values[index];
    return std::all_of(value.begin(), value.end(), IsASCIIWhitespace);
  }
  return false;
}

size_t FindImplicitHeadEndIndex(const HTMLTokenizerSummary& summary,
                                size_t scan_begin) {
  size_t index = scan_begin;
  while (index < summary.node_kinds.size()) {
    if (summary.node_kinds[index] == "end" &&
        summary.node_html_tags[index] == html_names::HTMLTag::kHTML) {
      break;
    }
    if (!IsStandaloneHeadContentNode(summary, index)) {
      break;
    }
    ++index;
  }
  return index;
}

void NormalizeStandaloneDocumentTree(HTMLTokenizerSummary& summary) {
  if (summary.node_kinds.empty()) {
    InsertSyntheticHTMLNode(summary, 0, "start", html_names::HTMLTag::kHTML);
    InsertSyntheticHTMLNode(summary, 1, "start", html_names::HTMLTag::kHead);
    InsertSyntheticHTMLNode(summary, 2, "end", html_names::HTMLTag::kHead);
    InsertSyntheticHTMLNode(summary, 3, "start", html_names::HTMLTag::kBody);
    InsertSyntheticHTMLNode(summary, 4, "end", html_names::HTMLTag::kBody);
    InsertSyntheticHTMLNode(summary, 5, "end", html_names::HTMLTag::kHTML);
    return;
  }

  if (!HasStartElement(summary, html_names::HTMLTag::kHTML)) {
    InsertSyntheticHTMLNode(summary, 0, "start", html_names::HTMLTag::kHTML);
    InsertSyntheticHTMLNode(summary, summary.node_kinds.size(), "end",
                            html_names::HTMLTag::kHTML);
  }

  if (!HasStartElement(summary, html_names::HTMLTag::kHead)) {
    size_t head_index = 1;
    const size_t html_index =
        FindFirstStartElement(summary, html_names::HTMLTag::kHTML);
    if (html_index != summary.node_kinds.size()) {
      head_index = html_index + 1;
    }
    const size_t head_end_index = FindImplicitHeadEndIndex(summary,
                                                           head_index);
    InsertSyntheticHTMLNode(summary, head_index, "start",
                            html_names::HTMLTag::kHead);
    InsertSyntheticHTMLNode(summary, head_end_index + 1, "end",
                            html_names::HTMLTag::kHead);
  }

  if (!HasStartElement(summary, html_names::HTMLTag::kBody)) {
    size_t body_index = FindLastEndElement(summary, html_names::HTMLTag::kHead);
    if (body_index != summary.node_kinds.size()) {
      ++body_index;
    } else {
      body_index = FindFirstStartElement(summary, html_names::HTMLTag::kHTML);
      body_index = body_index == summary.node_kinds.size() ? 0 : body_index + 1;
    }
    InsertSyntheticHTMLNode(summary, body_index, "start",
                            html_names::HTMLTag::kBody);
    size_t body_end_index = FindLastEndElement(summary, html_names::HTMLTag::kHTML);
    if (body_end_index == summary.node_kinds.size()) {
      body_end_index = summary.node_kinds.size();
    }
    InsertSyntheticHTMLNode(summary, body_end_index, "end",
                            html_names::HTMLTag::kBody);
  }
}

bool IsHTMLVoidElementForStandaloneTreeSink(html_names::HTMLTag tag) {
  using HTMLTag = html_names::HTMLTag;
  switch (tag) {
    case HTMLTag::kArea:
    case HTMLTag::kBase:
    case HTMLTag::kBr:
    case HTMLTag::kCol:
    case HTMLTag::kEmbed:
    case HTMLTag::kHr:
    case HTMLTag::kImg:
    case HTMLTag::kInput:
    case HTMLTag::kLink:
    case HTMLTag::kMeta:
    case HTMLTag::kParam:
    case HTMLTag::kSource:
    case HTMLTag::kTrack:
    case HTMLTag::kWbr:
      return true;
    default:
      return false;
  }
}

bool IsImpliedPEndBoundaryForStandaloneTreeSink(html_names::HTMLTag tag) {
  using HTMLTag = html_names::HTMLTag;
  switch (tag) {
    case HTMLTag::kAddress:
    case HTMLTag::kArticle:
    case HTMLTag::kAside:
    case HTMLTag::kBlockquote:
    case HTMLTag::kCenter:
    case HTMLTag::kDetails:
    case HTMLTag::kDialog:
    case HTMLTag::kDir:
    case HTMLTag::kDiv:
    case HTMLTag::kDl:
    case HTMLTag::kFieldset:
    case HTMLTag::kFigcaption:
    case HTMLTag::kFigure:
    case HTMLTag::kFooter:
    case HTMLTag::kH1:
    case HTMLTag::kH2:
    case HTMLTag::kH3:
    case HTMLTag::kH4:
    case HTMLTag::kH5:
    case HTMLTag::kH6:
    case HTMLTag::kHeader:
    case HTMLTag::kHgroup:
    case HTMLTag::kHr:
    case HTMLTag::kMain:
    case HTMLTag::kMenu:
    case HTMLTag::kNav:
    case HTMLTag::kOl:
    case HTMLTag::kP:
    case HTMLTag::kPre:
    case HTMLTag::kSearch:
    case HTMLTag::kSection:
    case HTMLTag::kSummary:
    case HTMLTag::kTable:
    case HTMLTag::kUl:
      return true;
    default:
      return false;
  }
}

bool HasBlinkImpliedEndTagForStandaloneBridge(html_names::HTMLTag tag) {
  using HTMLTag = html_names::HTMLTag;
  switch (tag) {
    case HTMLTag::kDd:
    case HTMLTag::kDt:
    case HTMLTag::kLi:
    case HTMLTag::kOption:
    case HTMLTag::kOptgroup:
    case HTMLTag::kP:
    case HTMLTag::kRb:
    case HTMLTag::kRp:
    case HTMLTag::kRt:
    case HTMLTag::kRTC:
      return true;
    default:
      return false;
  }
}

bool ShouldCloseOpenElementBeforeStart(html_names::HTMLTag open_tag,
                                       html_names::HTMLTag start_tag) {
  using HTMLTag = html_names::HTMLTag;
  (void)HasBlinkImpliedEndTagForStandaloneBridge(open_tag);
  if (open_tag == HTMLTag::kP &&
      (start_tag == HTMLTag::kP ||
       IsImpliedPEndBoundaryForStandaloneTreeSink(start_tag))) {
    return true;
  }
  if (open_tag == HTMLTag::kLi && start_tag == HTMLTag::kLi) {
    return true;
  }
  if ((open_tag == HTMLTag::kDt || open_tag == HTMLTag::kDd) &&
      (start_tag == HTMLTag::kDt || start_tag == HTMLTag::kDd)) {
    return true;
  }
  if (open_tag == HTMLTag::kOption && start_tag == HTMLTag::kOption) {
    return true;
  }
  if (open_tag == HTMLTag::kOptgroup &&
      (start_tag == HTMLTag::kOptgroup || start_tag == HTMLTag::kOption)) {
    return true;
  }
  if ((open_tag == HTMLTag::kRb || open_tag == HTMLTag::kRp ||
       open_tag == HTMLTag::kRt || open_tag == HTMLTag::kRTC) &&
      (start_tag == HTMLTag::kRb || start_tag == HTMLTag::kRp ||
       start_tag == HTMLTag::kRt || start_tag == HTMLTag::kRTC)) {
    return true;
  }
  if (open_tag == HTMLTag::kTr && start_tag == HTMLTag::kTr) {
    return true;
  }
  if ((open_tag == HTMLTag::kTd || open_tag == HTMLTag::kTh) &&
      (start_tag == HTMLTag::kTd || start_tag == HTMLTag::kTh ||
       start_tag == HTMLTag::kTr || start_tag == HTMLTag::kTbody ||
       start_tag == HTMLTag::kTfoot || start_tag == HTMLTag::kThead)) {
    return true;
  }
  if (open_tag == HTMLTag::kTr &&
      (start_tag == HTMLTag::kTbody || start_tag == HTMLTag::kTfoot ||
       start_tag == HTMLTag::kThead)) {
    return true;
  }
  return false;
}

class StandaloneHTMLTreeBridge {
  STACK_ALLOCATED();

 public:
  explicit StandaloneHTMLTreeBridge(HTMLTokenizerSummary& summary)
      : summary_(summary) {}

  void Build() {
    NormalizeStandaloneDocumentTree(summary_);
    AttachTreePositions();
  }

 private:
  void PopOpenElementAtOrAfter(std::vector<int>& open_elements,
                               size_t index) {
    if (index < open_elements.size()) {
      open_elements.erase(open_elements.begin() + index, open_elements.end());
      ++summary_.tree_bridge_event_count;
    }
  }

  void CloseElementsBeforeStart(std::vector<int>& open_elements,
                                html_names::HTMLTag start_tag) {
    while (!open_elements.empty()) {
      const html_names::HTMLTag open_tag =
          summary_.node_html_tags[static_cast<size_t>(open_elements.back())];
      if (!ShouldCloseOpenElementBeforeStart(open_tag, start_tag)) {
        return;
      }
      open_elements.pop_back();
      ++summary_.tree_bridge_event_count;
    }
  }

  void AttachTreePositions() {
    summary_.max_tree_depth = 0;
    summary_.root_node_index = -1;
    summary_.head_node_index = -1;
    summary_.body_node_index = -1;
    std::fill(summary_.node_first_child_indices.begin(),
              summary_.node_first_child_indices.end(), -1);
    std::fill(summary_.node_next_sibling_indices.begin(),
              summary_.node_next_sibling_indices.end(), -1);
    std::fill(summary_.node_child_counts.begin(),
              summary_.node_child_counts.end(), 0);
    std::vector<int> open_elements;
    std::vector<int> last_child_for_node(summary_.node_kinds.size(), -1);
    for (int i = 0; i < static_cast<int>(summary_.node_kinds.size()); ++i) {
      const std::string& kind = summary_.node_kinds[static_cast<size_t>(i)];
      const std::string& name = summary_.node_names[static_cast<size_t>(i)];
      const html_names::HTMLTag tag = summary_.node_html_tags[static_cast<size_t>(i)];
      if (kind == "end") {
        summary_.node_parent_indices[static_cast<size_t>(i)] =
            open_elements.empty() ? -1 : open_elements.back();
        summary_.node_depths[static_cast<size_t>(i)] =
            static_cast<int>(open_elements.size());
        for (auto it = open_elements.rbegin(); it != open_elements.rend();
             ++it) {
          if (summary_.node_html_tags[static_cast<size_t>(*it)] == tag) {
            PopOpenElementAtOrAfter(
                open_elements,
                static_cast<size_t>(std::next(it).base() -
                                    open_elements.begin()));
            break;
          }
        }
        summary_.max_tree_depth =
            std::max(summary_.max_tree_depth,
                     summary_.node_depths[static_cast<size_t>(i)]);
        summary_.node_bridge_actions[static_cast<size_t>(i)] +=
            "|close-element";
        continue;
      }

      if (kind == "start") {
        CloseElementsBeforeStart(open_elements, tag);
        if (tag == html_names::HTMLTag::kHTML && summary_.root_node_index < 0) {
          summary_.root_node_index = i;
        } else if (tag == html_names::HTMLTag::kHead &&
                   summary_.head_node_index < 0) {
          summary_.head_node_index = i;
        } else if (tag == html_names::HTMLTag::kBody &&
                   summary_.body_node_index < 0) {
          summary_.body_node_index = i;
        }
      }

      summary_.node_parent_indices[static_cast<size_t>(i)] =
          open_elements.empty() ? -1 : open_elements.back();
      summary_.node_depths[static_cast<size_t>(i)] =
          static_cast<int>(open_elements.size());
      if (!open_elements.empty()) {
        const int parent = open_elements.back();
        const size_t parent_index = static_cast<size_t>(parent);
        if (summary_.node_first_child_indices[parent_index] < 0) {
          summary_.node_first_child_indices[parent_index] = i;
        } else if (last_child_for_node[parent_index] >= 0) {
          summary_.node_next_sibling_indices[static_cast<size_t>(
              last_child_for_node[parent_index])] = i;
        }
        last_child_for_node[parent_index] = i;
        ++summary_.node_child_counts[parent_index];
      }
      summary_.max_tree_depth =
          std::max(summary_.max_tree_depth,
                   summary_.node_depths[static_cast<size_t>(i)]);

      if (kind == "start" && !IsHTMLVoidElementForStandaloneTreeSink(tag)) {
        open_elements.push_back(i);
        ++summary_.tree_bridge_event_count;
        summary_.node_bridge_actions[static_cast<size_t>(i)] +=
            "|open-element";
      } else if (kind == "text" || kind == "image" || kind == "style") {
        summary_.node_bridge_actions[static_cast<size_t>(i)] += "|insert";
      }
    }
  }

  HTMLTokenizerSummary& summary_;
};

void ApplyStandaloneHTMLTreeBridge(HTMLTokenizerSummary& summary) {
  StandaloneHTMLTreeBridge bridge(summary);
  bridge.Build();
}

std::string EscapeHTMLNodeAttributeField(const std::string& value) {
  std::string escaped;
  escaped.reserve(value.size());
  for (const char c : value) {
    if (c == '\\' || c == '\t' || c == '\n' || c == '\r') {
      escaped.push_back('\\');
      if (c == '\t') {
        escaped.push_back('t');
      } else if (c == '\n') {
        escaped.push_back('n');
      } else if (c == '\r') {
        escaped.push_back('r');
      } else {
        escaped.push_back('\\');
      }
      continue;
    }
    escaped.push_back(c);
  }
  return escaped;
}

void AppendSerializedAttribute(std::string& attributes,
                               const std::string& name,
                               const std::string& value) {
  if (name.empty()) {
    return;
  }
  attributes += EscapeHTMLNodeAttributeField(name);
  attributes.push_back('\t');
  attributes += EscapeHTMLNodeAttributeField(value);
  attributes.push_back('\n');
}

std::string SerializeAtomicHTMLAttributes(
    const Vector<Attribute, kAttributePrealloc>& attributes) {
  std::string serialized;
  for (const Attribute& attribute : attributes) {
    AppendSerializedAttribute(serialized, attribute.LocalName().Utf8(),
                              attribute.Value().Utf8());
  }
  return serialized;
}

std::string SerializeHTMLTokenAttributes(
    const HTMLToken::AttributeList& attributes) {
  std::string serialized;
  for (const HTMLToken::Attribute& attribute : attributes) {
    AppendSerializedAttribute(
        serialized, attribute.NameAttemptStaticStringCreation().Utf8(),
        attribute.Value().Utf8());
  }
  return serialized;
}

void CopyStringToBuffer(const std::string& value,
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

std::string TrimASCIIWhitespace(std::string value) {
  size_t begin = 0;
  while (begin < value.size() && IsASCIIWhitespace(value[begin])) {
    ++begin;
  }
  size_t end = value.size();
  while (end > begin && IsASCIIWhitespace(value[end - 1])) {
    --end;
  }
  return value.substr(begin, end - begin);
}

HTMLTokenizerSummary TokenizeHTMLForStandaloneRenderer(const char* html) {
  HTMLTokenizerSummary summary;
  if (!html || !html[0]) {
    return summary;
  }

  static bool html_names_initialized = [] {
    html_names::Init();
    return true;
  }();
  (void)html_names_initialized;

  HTMLParserOptions options(nullptr);
  options.scripting_flag = false;
  HTMLTokenizer tokenizer(options);
  SegmentedString source(String::FromUtf8(html));
  bool suppress_visible_text = false;
  bool collect_style_text = false;
  std::string current_style_text;

  while (HTMLToken* token = tokenizer.NextToken(source)) {
    ++summary.token_count;
    const HTMLToken::TokenType token_type = token->GetType();
    if (token_type == HTMLToken::kStartTag ||
        token_type == HTMLToken::kEndTag ||
        token_type == HTMLToken::kCharacter ||
        token_type == HTMLToken::kComment) {
      AtomicHTMLToken atomic_token(*token);
      ++summary.atomic_token_count;
      if (token_type == HTMLToken::kStartTag ||
          token_type == HTMLToken::kEndTag) {
        summary.atomic_attribute_count +=
            static_cast<int>(atomic_token.Attributes().size());
        if (atomic_token.IsValidHTMLTag()) {
          ++summary.atomic_valid_html_tag_count;
        }
      }

      if (token_type == HTMLToken::kStartTag) {
        ++summary.start_tag_count;
        const std::string tag_name = atomic_token.GetName().Utf8();
        const html_names::HTMLTag tag = atomic_token.GetHTMLTag();
        summary.start_tag_names.push_back(tag_name);
        AppendHTMLNode(summary, "start", tag_name,
                       SerializeAtomicHTMLAttributes(
                           atomic_token.Attributes()),
                       tag);
        if (tag == html_names::HTMLTag::kScript) {
          suppress_visible_text = true;
          tokenizer.UpdateStateFor(html_names::HTMLTag::kScript);
        } else if (tag == html_names::HTMLTag::kStyle) {
          suppress_visible_text = true;
          collect_style_text = true;
          current_style_text.clear();
          tokenizer.UpdateStateFor(html_names::HTMLTag::kStyle);
        } else if (tag == html_names::HTMLTag::kImg) {
          AppendTagBoundarySpace(summary.visible_text);
          for (const Attribute& attribute : atomic_token.Attributes()) {
            if (attribute.GetName() == html_names::kSrcAttr &&
              !attribute.Value().empty()) {
              summary.found_image_src = true;
              const std::string source = attribute.Value().Utf8();
              summary.image_sources.push_back(source);
              AppendHTMLNode(summary, "image", "img", source, tag);
            }
          }
        } else {
          AppendTagBoundarySpace(summary.visible_text);
        }
      } else if (token_type == HTMLToken::kEndTag) {
        ++summary.end_tag_count;
        const html_names::HTMLTag tag = atomic_token.GetHTMLTag();
        const std::string tag_name = atomic_token.GetName().Utf8();
        if (tag == html_names::HTMLTag::kScript ||
            tag == html_names::HTMLTag::kStyle) {
          if (tag == html_names::HTMLTag::kStyle && collect_style_text &&
              !current_style_text.empty()) {
            summary.style_blocks.push_back(std::move(current_style_text));
            AppendHTMLNode(summary, "style", "style",
                           summary.style_blocks.back(), tag);
            current_style_text.clear();
          }
          suppress_visible_text = false;
          collect_style_text = false;
        } else {
          AppendTagBoundarySpace(summary.visible_text);
        }
        AppendHTMLNode(summary, "end", tag_name, std::string(), tag);
      } else if (token_type == HTMLToken::kCharacter) {
        ++summary.character_token_count;
        if (collect_style_text) {
          current_style_text.append(atomic_token.Characters().Utf8());
        } else if (!suppress_visible_text) {
          const std::string text = atomic_token.Characters().Utf8();
          AppendVisibleText(summary.visible_text, text);
          AppendHTMLNode(summary, "text", std::string(), text);
        }
      }

      tokenizer.ClearToken();
      continue;
    }

    switch (token_type) {
      case HTMLToken::kStartTag: {
        ++summary.start_tag_count;
        const String tag_name = token->GetName().AsString();
        const std::string tag_name_utf8 = tag_name.Utf8();
        const html_names::HTMLTag html_tag =
            html_names::HTMLTag::kUnknown;
        summary.start_tag_names.push_back(tag_name_utf8);
        AppendHTMLNode(summary, "start", tag_name_utf8,
                       SerializeHTMLTokenAttributes(token->Attributes()),
                       html_tag);
        if (EqualIgnoringASCIICase(tag_name, "script")) {
          suppress_visible_text = true;
          tokenizer.UpdateStateFor(html_names::HTMLTag::kScript);
        } else if (EqualIgnoringASCIICase(tag_name, "style")) {
          suppress_visible_text = true;
          collect_style_text = true;
          current_style_text.clear();
          tokenizer.UpdateStateFor(html_names::HTMLTag::kStyle);
        } else if (EqualIgnoringASCIICase(tag_name, "img")) {
          AppendTagBoundarySpace(summary.visible_text);
          for (const HTMLToken::Attribute& attribute : token->Attributes()) {
            if (EqualIgnoringASCIICase(attribute.NameAttemptStaticStringCreation(),
                                      "src") &&
                !attribute.Value().empty()) {
              summary.found_image_src = true;
              const std::string source = attribute.Value().Utf8();
              summary.image_sources.push_back(source);
              AppendHTMLNode(summary, "image", "img", source, html_tag);
            }
          }
        } else {
          AppendTagBoundarySpace(summary.visible_text);
        }
        break;
      }
      case HTMLToken::kEndTag: {
        ++summary.end_tag_count;
        const String tag_name = token->GetName().AsString();
        if (EqualIgnoringASCIICase(tag_name, "script") ||
            EqualIgnoringASCIICase(tag_name, "style")) {
          if (EqualIgnoringASCIICase(tag_name, "style") &&
              collect_style_text && !current_style_text.empty()) {
            summary.style_blocks.push_back(std::move(current_style_text));
            AppendHTMLNode(summary, "style", "style",
                           summary.style_blocks.back(),
                           html_names::HTMLTag::kStyle);
            current_style_text.clear();
          }
          suppress_visible_text = false;
          collect_style_text = false;
        } else {
          AppendTagBoundarySpace(summary.visible_text);
        }
        AppendHTMLNode(summary, "end", tag_name.Utf8(), std::string(),
                       html_names::HTMLTag::kUnknown);
        break;
      }
      case HTMLToken::kCharacter:
        ++summary.character_token_count;
        if (collect_style_text) {
          current_style_text.append(token->Characters().AsString().Utf8());
        } else if (!suppress_visible_text) {
          const std::string text = token->Characters().AsString().Utf8();
          AppendVisibleText(summary.visible_text, text);
          AppendHTMLNode(summary, "text", std::string(), text);
        }
        break;
      default:
        break;
    }
    tokenizer.ClearToken();
  }

  if (!summary.visible_text.empty() && summary.visible_text.back() == ' ') {
    summary.visible_text.pop_back();
  }
  if (collect_style_text && !current_style_text.empty()) {
    summary.style_blocks.push_back(std::move(current_style_text));
    AppendHTMLNode(summary, "style", "style", summary.style_blocks.back(),
                   html_names::HTMLTag::kStyle);
  }
  ApplyStandaloneHTMLTreeBridge(summary);

  return summary;
}

CSSParserStreamSummary ParseCSSStreamForStandaloneRenderer(const char* css) {
  CSSParserStreamSummary summary;
  if (!css || !css[0]) {
    return summary;
  }

  const String css_text = String::FromUtf8(css);
  CSSParserTokenStream stream{StringView(css_text)};
  while (!stream.AtEnd()) {
    const CSSParserToken token = stream.ConsumeRaw();
    ++summary.token_count;
    if (token.GetType() == kAtKeywordToken) {
      ++summary.at_rule_count;
    }
    if (token.GetType() == kFunctionToken) {
      ++summary.function_count;
    }
    if (token.GetBlockType() == CSSParserToken::kBlockStart) {
      ++summary.block_start_count;
    } else if (token.GetBlockType() == CSSParserToken::kBlockEnd) {
      ++summary.block_end_count;
    }
  }
  return summary;
}

CSSDeclarationSummary ExtractCSSDeclarationsForStandaloneRenderer(
    const char* css) {
  CSSDeclarationSummary summary;
  if (!css || !css[0]) {
    return summary;
  }

  // Keep declaration extraction as source-span discovery for now. The Blink
  // CSS token stream remains probed separately; converting token payloads from
  // the reduced embedder is not stable enough yet.
  const std::string input(css);
  int brace_depth = 0;
  size_t declaration_start = 0;
  std::vector<std::string> selector_stack;
  size_t i = 0;
  while (i < input.size()) {
    const char c = input[i];
    if (c == '/' && i + 1 < input.size() && input[i + 1] == '*') {
      i += 2;
      while (i + 1 < input.size() &&
             !(input[i] == '*' && input[i + 1] == '/')) {
        ++i;
      }
      i = std::min(input.size(), i + 2);
      continue;
    }
    if (c == '"' || c == '\'') {
      const char quote = c;
      ++i;
      while (i < input.size()) {
        if (input[i] == '\\' && i + 1 < input.size()) {
          i += 2;
          continue;
        }
        if (input[i++] == quote) {
          break;
        }
      }
      continue;
    }
    if (c == '{') {
      ++brace_depth;
      const std::string selector =
          TrimASCIIWhitespace(input.substr(declaration_start,
                                           i - declaration_start));
      selector_stack.push_back(selector.rfind("@", 0) == 0 ? std::string()
                                                           : selector);
      declaration_start = i + 1;
      ++i;
      continue;
    }
    if (c == '}') {
      brace_depth = std::max(0, brace_depth - 1);
      if (!selector_stack.empty()) {
        selector_stack.pop_back();
      }
      declaration_start = i + 1;
      ++i;
      continue;
    }
    if (brace_depth <= 0) {
      ++i;
      continue;
    }

    int paren_depth = 0;
    int bracket_depth = 0;
    size_t colon = std::string::npos;
    size_t end = std::string::npos;
    bool advanced_into_nested_block = false;
    for (size_t cursor = declaration_start; cursor < input.size(); ++cursor) {
      const char scan = input[cursor];
      if (scan == '/' && cursor + 1 < input.size() && input[cursor + 1] == '*') {
        cursor += 2;
        while (cursor + 1 < input.size() &&
               !(input[cursor] == '*' && input[cursor + 1] == '/')) {
          ++cursor;
        }
        ++cursor;
        continue;
      }
      if (scan == '"' || scan == '\'') {
        const char quote = scan;
        ++cursor;
        while (cursor < input.size()) {
          if (input[cursor] == '\\' && cursor + 1 < input.size()) {
            cursor += 2;
            continue;
          }
          if (input[cursor] == quote) {
            break;
          }
          ++cursor;
        }
        continue;
      }
      if (scan == '(') {
        ++paren_depth;
      } else if (scan == ')' && paren_depth > 0) {
        --paren_depth;
      } else if (scan == '[') {
        ++bracket_depth;
      } else if (scan == ']' && bracket_depth > 0) {
        --bracket_depth;
      }
      if (paren_depth == 0 && bracket_depth == 0 && scan == '{' &&
          colon == std::string::npos) {
        ++brace_depth;
        const std::string selector =
            TrimASCIIWhitespace(input.substr(declaration_start,
                                             cursor - declaration_start));
        selector_stack.push_back(selector.rfind("@", 0) == 0 ? std::string()
                                                             : selector);
        declaration_start = cursor + 1;
        i = declaration_start;
        advanced_into_nested_block = true;
        break;
      }
      if (paren_depth == 0 && bracket_depth == 0 && scan == ':' &&
          colon == std::string::npos) {
        colon = cursor;
        continue;
      }
      if (paren_depth == 0 && bracket_depth == 0 &&
          (scan == ';' || scan == '}')) {
        end = cursor;
        break;
      }
    }
    if (advanced_into_nested_block) {
      continue;
    }
    if (end == std::string::npos) {
      end = input.size();
    }
    if (colon != std::string::npos && colon > declaration_start &&
        colon < end) {
      std::string property_name =
          TrimASCIIWhitespace(input.substr(declaration_start,
                                           colon - declaration_start));
      std::string property_value =
          TrimASCIIWhitespace(input.substr(colon + 1, end - colon - 1));
      if (!property_name.empty() && !property_value.empty()) {
        auto selector = std::find_if(
            selector_stack.rbegin(), selector_stack.rend(),
            [](const std::string& candidate) { return !candidate.empty(); });
        summary.selectors.push_back(selector == selector_stack.rend()
                                        ? std::string()
                                        : *selector);
        summary.property_names.push_back(std::move(property_name));
        summary.property_values.push_back(std::move(property_value));
      }
    }

    if (end < input.size() && input[end] == '}') {
      brace_depth = std::max(0, brace_depth - 1);
      if (!selector_stack.empty()) {
        selector_stack.pop_back();
      }
    }
    declaration_start = end + 1;
    i = declaration_start;
  }
  return summary;
}

CSSTokenizerSummary TokenizeCSSForStandaloneRenderer(const char* css) {
  CSSTokenizerSummary summary;
  if (!css || !css[0]) {
    return summary;
  }

  const std::string normalized_css =
      NormalizeUnquotedURLFunctionsForCSSTokenizer(css);
  const String css_text = String::FromUtf8(normalized_css.c_str());
  CSSTokenizer tokenizer{StringView(css_text)};
  bool pending_url_function = false;
  for (;;) {
    CSSParserToken token = tokenizer.TokenizeSingle();
    if (token.GetType() == kEOFToken) {
      break;
    }
    ++summary.token_count;
    if (token.GetType() == kUrlToken) {
      summary.urls.push_back(token.Value().ToString().Utf8());
      pending_url_function = false;
    } else if (token.GetType() == kFunctionToken &&
               EqualIgnoringAsciiCase(token.Value(), "url")) {
      pending_url_function = true;
    } else if (pending_url_function && token.GetType() == kStringToken) {
      summary.urls.push_back(token.Value().ToString().Utf8());
    } else if (token.GetType() == kRightParenthesisToken ||
               token.GetType() == kSemicolonToken ||
               token.GetType() == kLeftBraceToken ||
               token.GetType() == kRightBraceToken) {
      pending_url_function = false;
    }
  }
  return summary;
}

}  // namespace

bool HasDocumentLifecycleTypesForStandaloneRenderer() {
  return sizeof(Document*) > 0 && sizeof(DocumentInit*) > 0 &&
         sizeof(HTMLDocument*) > 0;
}

int ReducedCSSPropertyCountForStandaloneRenderer() {
  return kNumCSSProperties;
}

int ReducedCSSValueKeywordCountForStandaloneRenderer() {
  return kNumCSSValueKeywords;
}

int ReducedCSSTokenizerTokenCountForStandaloneRenderer(const char* css) {
  return TokenizeCSSForStandaloneRenderer(css).token_count;
}

int ReducedCSSParserTokenStreamTokenCountForStandaloneRenderer(const char* css) {
  return ParseCSSStreamForStandaloneRenderer(css).token_count;
}

int ReducedCSSParserTokenStreamAtRuleCountForStandaloneRenderer(
    const char* css) {
  return ParseCSSStreamForStandaloneRenderer(css).at_rule_count;
}

int ReducedCSSParserTokenStreamBlockStartCountForStandaloneRenderer(
    const char* css) {
  return ParseCSSStreamForStandaloneRenderer(css).block_start_count;
}

int ReducedCSSParserTokenStreamFunctionCountForStandaloneRenderer(
    const char* css) {
  return ParseCSSStreamForStandaloneRenderer(css).function_count;
}

int ReducedCSSDeclarationCountForStandaloneRenderer(const char* css) {
  return static_cast<int>(
      ExtractCSSDeclarationsForStandaloneRenderer(css).property_names.size());
}

void ReducedCSSDeclarationSelectorAtForStandaloneRenderer(
    const char* css,
    int index,
    char* output,
    int output_capacity) {
  const CSSDeclarationSummary summary =
      ExtractCSSDeclarationsForStandaloneRenderer(css);
  if (index < 0 || static_cast<size_t>(index) >= summary.selectors.size()) {
    CopyStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStringToBuffer(summary.selectors[static_cast<size_t>(index)], output,
                     output_capacity);
}

void ReducedCSSDeclarationPropertyAtForStandaloneRenderer(
    const char* css,
    int index,
    char* output,
    int output_capacity) {
  const CSSDeclarationSummary summary =
      ExtractCSSDeclarationsForStandaloneRenderer(css);
  if (index < 0 ||
      static_cast<size_t>(index) >= summary.property_names.size()) {
    CopyStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStringToBuffer(summary.property_names[static_cast<size_t>(index)],
                     output, output_capacity);
}

void ReducedCSSDeclarationValueAtForStandaloneRenderer(
    const char* css,
    int index,
    char* output,
    int output_capacity) {
  const CSSDeclarationSummary summary =
      ExtractCSSDeclarationsForStandaloneRenderer(css);
  if (index < 0 ||
      static_cast<size_t>(index) >= summary.property_values.size()) {
    CopyStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStringToBuffer(summary.property_values[static_cast<size_t>(index)],
                     output, output_capacity);
}

int ReducedCSSTokenizerUrlCountForStandaloneRenderer(const char* css) {
  return static_cast<int>(TokenizeCSSForStandaloneRenderer(css).urls.size());
}

void ReducedCSSTokenizerUrlAtForStandaloneRenderer(const char* css,
                                                   int index,
                                                   char* output,
                                                   int output_capacity) {
  const std::vector<std::string> urls =
      TokenizeCSSForStandaloneRenderer(css).urls;
  if (index < 0 || index >= static_cast<int>(urls.size())) {
    CopyStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStringToBuffer(urls[static_cast<size_t>(index)], output,
                     output_capacity);
}

bool HasStyleEnumsForStandaloneRenderer() {
  return sizeof(EDisplay) > 0 && sizeof(EPosition) > 0 &&
         sizeof(EVisibility) > 0;
}

int ReducedHTMLTokenizerTokenCountForStandaloneRenderer(const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).token_count;
}

int ReducedHTMLTokenizerStartTagCountForStandaloneRenderer(const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).start_tag_count;
}

int ReducedHTMLTokenizerEndTagCountForStandaloneRenderer(const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).end_tag_count;
}

int ReducedHTMLTokenizerCharacterTokenCountForStandaloneRenderer(
    const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).character_token_count;
}

bool ReducedHTMLTokenizerFindsImageSourceForStandaloneRenderer(
    const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).found_image_src;
}

int ReducedAtomicHTMLTokenCountForStandaloneRenderer(const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).atomic_token_count;
}

int ReducedAtomicHTMLTokenAttributeCountForStandaloneRenderer(
    const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).atomic_attribute_count;
}

int ReducedAtomicHTMLTokenValidTagCountForStandaloneRenderer(const char* html) {
  return TokenizeHTMLForStandaloneRenderer(html).atomic_valid_html_tag_count;
}

int ReducedHTMLTokenizerVisibleTextLengthForStandaloneRenderer(
    const char* html) {
  return static_cast<int>(
      TokenizeHTMLForStandaloneRenderer(html).visible_text.size());
}

void ReducedHTMLTokenizerVisibleTextForStandaloneRenderer(
    const char* html,
    char* output,
    int output_capacity) {
  CopyStringToBuffer(TokenizeHTMLForStandaloneRenderer(html).visible_text,
                     output, output_capacity);
}

int ReducedHTMLTokenizerImageSourceCountForStandaloneRenderer(
    const char* html) {
  return static_cast<int>(
      TokenizeHTMLForStandaloneRenderer(html).image_sources.size());
}

void ReducedHTMLTokenizerImageSourceAtForStandaloneRenderer(
    const char* html,
    int index,
    char* output,
    int output_capacity) {
  const HTMLTokenizerSummary summary = TokenizeHTMLForStandaloneRenderer(html);
  if (index < 0 ||
      static_cast<size_t>(index) >= summary.image_sources.size()) {
    CopyStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStringToBuffer(summary.image_sources[static_cast<size_t>(index)], output,
                     output_capacity);
}

int ReducedHTMLTokenizerStartTagNameCountForStandaloneRenderer(
    const char* html) {
  return static_cast<int>(
      TokenizeHTMLForStandaloneRenderer(html).start_tag_names.size());
}

void ReducedHTMLTokenizerStartTagNameAtForStandaloneRenderer(
    const char* html,
    int index,
    char* output,
    int output_capacity) {
  const HTMLTokenizerSummary summary = TokenizeHTMLForStandaloneRenderer(html);
  if (index < 0 ||
      static_cast<size_t>(index) >= summary.start_tag_names.size()) {
    CopyStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStringToBuffer(summary.start_tag_names[static_cast<size_t>(index)],
                     output, output_capacity);
}

int ReducedHTMLTokenizerStyleBlockCountForStandaloneRenderer(const char* html) {
  return static_cast<int>(
      TokenizeHTMLForStandaloneRenderer(html).style_blocks.size());
}

int ReducedHTMLTokenizerStyleBlockLengthForStandaloneRenderer(const char* html,
                                                              int index) {
  const HTMLTokenizerSummary summary = TokenizeHTMLForStandaloneRenderer(html);
  if (index < 0 || static_cast<size_t>(index) >= summary.style_blocks.size()) {
    return 0;
  }
  return static_cast<int>(summary.style_blocks[static_cast<size_t>(index)]
                              .size());
}

void ReducedHTMLTokenizerStyleBlockAtForStandaloneRenderer(
    const char* html,
    int index,
    char* output,
    int output_capacity) {
  const HTMLTokenizerSummary summary = TokenizeHTMLForStandaloneRenderer(html);
  if (index < 0 || static_cast<size_t>(index) >= summary.style_blocks.size()) {
    CopyStringToBuffer(std::string(), output, output_capacity);
    return;
  }
  CopyStringToBuffer(summary.style_blocks[static_cast<size_t>(index)], output,
                     output_capacity);
}

}  // namespace standalone_renderer_probe
}  // namespace blink
