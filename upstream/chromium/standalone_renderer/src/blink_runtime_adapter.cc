#include "html_css_renderer/blink_adapter.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "html_css_renderer/blink_runtime_environment.h"
#include "html_css_renderer/render_policy.h"
#include "html_css_renderer/retained_scene.h"
#if defined(HTML_CSS_RENDERER_HAS_BLINK_TREE_BUILDER_BRIDGE)
#include "html_css_renderer/blink_tree_bridge_probe.h"
#endif
#include "incremental_damage.h"

#if defined(HTML_CSS_RENDERER_HAS_LIVE_BLINK_RUNTIME)
namespace blink::standalone_renderer_probe {
void StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(int width,
                                                                    int height);
int StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgePaintChunkMetadataAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* x,
    int* y,
    int* width,
    int* height,
    int* begin_display_item_index,
    int* end_display_item_index,
    int* has_text);
int StandaloneBlinkLiveFrameBridgeExportedDrawOpCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeArtifactAuditLineCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeArtifactAuditLineAtForStandaloneRenderer(
    const char* body_html,
    int line_index,
    char* buffer,
    int buffer_size);
int StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonSizeForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonForStandaloneRenderer(
    const char* body_html,
    char* buffer,
    int buffer_size);
int StandaloneBlinkLiveFrameBridgeExportedDrawOpAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* type,
    float* x,
    float* y,
    float* width,
    float* height,
    float* r,
    float* g,
    float* b,
    float* a,
    float* font_size,
    float* radius_x,
    float* radius_y,
    int* glyph_count);
int StandaloneBlinkLiveFrameBridgeExportedGlyphAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int glyph_index,
    uint32_t* glyph_id,
    float* x,
    float* y);
int StandaloneBlinkLiveFrameBridgeExportedRRectRadiiAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    float* top_left_x,
    float* top_left_y,
    float* top_right_x,
    float* top_right_y,
    float* bottom_right_x,
    float* bottom_right_y,
    float* bottom_left_x,
    float* bottom_left_y);
int StandaloneBlinkLiveFrameBridgeExportedTextMaskInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* width,
    int* height,
    int* byte_count);
int StandaloneBlinkLiveFrameBridgeExportedTextMaskBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size);
int StandaloneBlinkLiveFrameBridgeExportedPathInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count);
int StandaloneBlinkLiveFrameBridgeExportedPathBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size);
int StandaloneBlinkLiveFrameBridgeExportedTextBlobInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count);
int StandaloneBlinkLiveFrameBridgeExportedTextBlobBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size);
int StandaloneBlinkLiveFrameBridgeExportedDebugLabelAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    char* buffer,
    int buffer_size);
int StandaloneBlinkLiveFrameBridgeExportedShaderInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count);
int StandaloneBlinkLiveFrameBridgeExportedShaderBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size);
int StandaloneBlinkLiveFrameBridgePaintChunkPropertyStateAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    uint64_t* state_hash,
    float* transform16,
    int* has_clip_rect,
    float* clip_x,
    float* clip_y,
    float* clip_width,
    float* clip_height);
int StandaloneBlinkLiveFrameBridgeExportedBitmapInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* width,
    int* height,
    int* byte_count);
int StandaloneBlinkLiveFrameBridgeExportedBitmapBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size);
}  // namespace blink::standalone_renderer_probe
#endif

namespace blink::standalone_renderer_probe {
bool HasDocumentLifecycleTypesForStandaloneRenderer();
int ReducedCSSPropertyCountForStandaloneRenderer();
int ReducedCSSValueKeywordCountForStandaloneRenderer();
int ReducedCSSTokenizerTokenCountForStandaloneRenderer(const char* css);
int ReducedCSSParserTokenStreamTokenCountForStandaloneRenderer(const char* css);
int ReducedCSSParserTokenStreamAtRuleCountForStandaloneRenderer(
    const char* css);
int ReducedCSSParserTokenStreamBlockStartCountForStandaloneRenderer(
    const char* css);
int ReducedCSSParserTokenStreamFunctionCountForStandaloneRenderer(
    const char* css);
int ReducedCSSDeclarationCountForStandaloneRenderer(const char* css);
void ReducedCSSDeclarationSelectorAtForStandaloneRenderer(
    const char* css,
    int index,
    char* output,
    int output_capacity);
void ReducedCSSDeclarationPropertyAtForStandaloneRenderer(
    const char* css,
    int index,
    char* output,
    int output_capacity);
void ReducedCSSDeclarationValueAtForStandaloneRenderer(const char* css,
                                                       int index,
                                                       char* output,
                                                       int output_capacity);
int ReducedCSSTokenizerUrlCountForStandaloneRenderer(const char* css);
void ReducedCSSTokenizerUrlAtForStandaloneRenderer(const char* css,
                                                   int index,
                                                   char* output,
                                                   int output_capacity);
bool HasStyleEnumsForStandaloneRenderer();
int ReducedHTMLTokenizerTokenCountForStandaloneRenderer(const char* html);
int ReducedHTMLTokenizerStartTagCountForStandaloneRenderer(const char* html);
int ReducedHTMLTokenizerEndTagCountForStandaloneRenderer(const char* html);
int ReducedHTMLTokenizerCharacterTokenCountForStandaloneRenderer(
    const char* html);
bool ReducedHTMLTokenizerFindsImageSourceForStandaloneRenderer(
    const char* html);
int ReducedAtomicHTMLTokenCountForStandaloneRenderer(const char* html);
int ReducedAtomicHTMLTokenAttributeCountForStandaloneRenderer(
    const char* html);
int ReducedAtomicHTMLTokenValidTagCountForStandaloneRenderer(const char* html);
int ReducedHTMLTokenizerVisibleTextLengthForStandaloneRenderer(
    const char* html);
void ReducedHTMLTokenizerVisibleTextForStandaloneRenderer(
    const char* html,
    char* output,
    int output_capacity);
int ReducedHTMLTokenizerImageSourceCountForStandaloneRenderer(const char* html);
void ReducedHTMLTokenizerImageSourceAtForStandaloneRenderer(
    const char* html,
    int index,
    char* output,
    int output_capacity);
int ReducedHTMLTokenizerStartTagNameCountForStandaloneRenderer(
    const char* html);
void ReducedHTMLTokenizerStartTagNameAtForStandaloneRenderer(
    const char* html,
    int index,
    char* output,
    int output_capacity);
int ReducedHTMLTokenizerStyleBlockCountForStandaloneRenderer(const char* html);
int ReducedHTMLTokenizerStyleBlockLengthForStandaloneRenderer(const char* html,
                                                              int index);
void ReducedHTMLTokenizerStyleBlockAtForStandaloneRenderer(
    const char* html,
    int index,
    char* output,
    int output_capacity);
}  // namespace blink::standalone_renderer_probe

namespace html_css_renderer {
namespace {

namespace fs = std::filesystem;

#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
namespace blink_core_probe = ::blink::standalone_renderer_probe;
#endif
#if defined(HTML_CSS_RENDERER_HAS_BLINK_TREE_BUILDER_BRIDGE)
namespace blink_tree_probe = ::blink::standalone_renderer_probe;
#endif

constexpr const char* kRuntimeSeedFiles[] = {
    "third_party/blink/renderer/core/testing/dummy_page_holder.h",
    "third_party/blink/renderer/core/testing/dummy_page_holder.cc",
    "third_party/blink/renderer/core/standalone_live_frame_bridge_probe.cc",
};

constexpr const char* kRequiredGeneratedFiles[] = {
    "third_party/blink/public/mojom/frame/policy_container.mojom-blink.h",
    "third_party/blink/public/mojom/frame/frame.mojom-blink-forward.h",
    "third_party/blink/public/mojom/navigation/navigation_params.mojom-blink-forward.h",
    "third_party/blink/public/mojom/page/page.mojom-blink-forward.h",
    "third_party/blink/public/mojom/loader/content_security_notifier.mojom-blink.h",
    "third_party/blink/renderer/bindings/buildflags.h",
    "third_party/blink/public/public_buildflags.h",
    "services/network/public/mojom/url_loader_factory.mojom-shared.h",
    "services/network/public/mojom/content_security_policy.mojom-blink-forward.h",
};

bool IsDrawableDrawCommand(DrawCommandType type) {
  return type == DrawCommandType::kFillRect ||
         type == DrawCommandType::kStrokeRect ||
         type == DrawCommandType::kFillRectShader ||
         type == DrawCommandType::kFillRRect ||
         type == DrawCommandType::kStrokeRRect ||
         type == DrawCommandType::kFillRRectShader ||
         type == DrawCommandType::kFillPath ||
         type == DrawCommandType::kDrawImage ||
         type == DrawCommandType::kDrawGlyphRun ||
         type == DrawCommandType::kDrawTextBlob ||
         type == DrawCommandType::kDrawText;
}

Rect DrawCommandBounds(const DrawCommand& command) {
  if (command.type == DrawCommandType::kDrawGlyphRun &&
      !command.glyph_run.positions.empty()) {
    Rect bounds{command.glyph_run.positions.front().x,
                command.glyph_run.positions.front().y,
                command.glyph_run.font_size,
                command.glyph_run.font_size};
    for (const Point position : command.glyph_run.positions) {
      bounds = UnionRectBounds(
          bounds,
          Rect{position.x, position.y, command.glyph_run.font_size,
               command.glyph_run.font_size});
    }
    return bounds;
  }
  if (command.type == DrawCommandType::kDrawText) {
    const float width = command.text.empty()
                            ? command.glyph_run.font_size
                            : command.glyph_run.font_size *
                                  0.5f * static_cast<float>(command.text.size());
    return Rect{command.rect.x, command.rect.y, width,
                command.glyph_run.font_size};
  }
  if (command.type == DrawCommandType::kDrawTextBlob) {
    return Rect{command.rect.x, command.rect.y, 1.0f, 1.0f};
  }
  return command.rect;
}

Rect DrawCommandListBounds(const DrawCommandList& commands,
                           const RendererSnapshot& snapshot) {
  Rect bounds;
  for (const DrawCommand& command : commands) {
    if (IsDrawableDrawCommand(command.type)) {
      bounds = UnionRectBounds(bounds, DrawCommandBounds(command));
    }
  }
  if (bounds.width <= 0.0f || bounds.height <= 0.0f) {
    return Rect{0.0f, 0.0f, snapshot.viewport.width, snapshot.viewport.height};
  }
  return bounds;
}

Point SnapshotDocumentScrollOffset(const RendererSnapshot& snapshot) {
  const auto document_scroll =
      snapshot.scroll_offsets_by_element_id.find("document");
  if (document_scroll != snapshot.scroll_offsets_by_element_id.end()) {
    return document_scroll->second;
  }
  const auto body_scroll = snapshot.scroll_offsets_by_element_id.find("body");
  if (body_scroll != snapshot.scroll_offsets_by_element_id.end()) {
    return body_scroll->second;
  }
  return Point{};
}

void ApplyRetainedScenePlan(RenderResult& result,
                            const RetainedScene& current_scene,
                            const LoadCommandList& load_commands,
                            const RetainedScene* previous_scene,
                            const RendererSnapshot& previous_snapshot,
                            Point current_scroll_offset,
                            Point previous_scroll_offset) {
  const PresentationUpdatePlan plan = PlanPresentationUpdate(
      current_scene, previous_scene, result.successor_snapshot.viewport,
      current_scroll_offset, previous_scroll_offset);
  result.frame = BuildRenderFrame(current_scene, load_commands, plan);
  result.damage_rects = plan.dirty_rects;
  result.damage_bounds = Rect{};
  for (const Rect dirty_rect : result.damage_rects) {
    result.damage_bounds = UnionRectBounds(result.damage_bounds, dirty_rect);
  }
  result.requires_full_redraw = plan.requires_full_redraw;
  if (plan.allows_scroll_translation_reuse) {
    result.diagnostics.push_back(
        "reduced Blink retained presentation allows scroll translation reuse");
  }
  if (!plan.requires_full_redraw && plan.dirty_rects.empty() &&
      (previous_snapshot.focused_element_id !=
           result.successor_snapshot.focused_element_id ||
       previous_snapshot.hovered_element_id !=
           result.successor_snapshot.hovered_element_id ||
       previous_snapshot.active_element_id !=
           result.successor_snapshot.active_element_id ||
       !SameStringMap(previous_snapshot.form_values_by_element_id,
                      result.successor_snapshot.form_values_by_element_id))) {
    ApplyIncrementalDamage(previous_snapshot, result,
                           "reduced Blink retained state incremental render");
  } else if (!plan.requires_full_redraw && plan.dirty_rects.empty()) {
    result.frame = RenderFrame{};
    result.frame.requires_full_redraw = false;
    result.diagnostics.push_back(
        "reduced Blink retained presentation has no visual damage");
  }
  result.diagnostics.push_back(
      "reduced Blink RenderFrame routed through retained scene presentation plan");
}

bool ReducedBlinkCoreIsReachable() {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  return blink_core_probe::HasDocumentLifecycleTypesForStandaloneRenderer();
#else
  return false;
#endif
}

std::string ReducedBlinkCoreCSSDiagnostic() {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  if (!blink_core_probe::HasStyleEnumsForStandaloneRenderer()) {
    return "reduced Blink core CSS/style metadata is not reachable";
  }
  return "reduced Blink core CSS metadata reachable: " +
         std::to_string(
             blink_core_probe::ReducedCSSPropertyCountForStandaloneRenderer()) +
         " CSS properties, " +
         std::to_string(blink_core_probe::
                            ReducedCSSValueKeywordCountForStandaloneRenderer()) +
         " CSS value keywords";
#else
  return "reduced Blink core CSS/style metadata is not linked";
#endif
}

std::string RealBlinkPaintBridgeDiagnostic() {
#if defined(HTML_CSS_RENDERER_HAS_BLINK_TREE_BUILDER_BRIDGE)
  if (!blink_tree_probe::
          StandaloneBlinkRealPaintBridgeSurfaceReachableForStandaloneRenderer()) {
    return "real Blink paint bridge surface is not linked";
  }
  return blink_tree_probe::
                 StandaloneBlinkRealPaintBridgeRequiresPaintCleanForStandaloneRenderer()
             ? "real Blink paint bridge contract selected: "
               "LocalFrameView::GetPaintArtifact after PaintClean lifecycle"
             : "real Blink paint bridge contract selected";
#else
  return "real Blink paint bridge surface is not linked";
#endif
}

std::string ReducedBlinkHTMLTokenizerDiagnostic(const std::string& html) {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  return "reduced Blink HTML tokenizer parsed current document: " +
         std::to_string(
             blink_core_probe::ReducedHTMLTokenizerTokenCountForStandaloneRenderer(
                 html.c_str())) +
         " tokens, " +
         std::to_string(blink_core_probe::
                            ReducedHTMLTokenizerStartTagCountForStandaloneRenderer(
                                html.c_str())) +
         " start tags, " +
         std::to_string(blink_core_probe::
                            ReducedHTMLTokenizerEndTagCountForStandaloneRenderer(
                                html.c_str())) +
         " end tags, " +
         std::to_string(
             blink_core_probe::
                 ReducedHTMLTokenizerCharacterTokenCountForStandaloneRenderer(
                     html.c_str())) +
         " character tokens, " +
         std::to_string(
             blink_core_probe::ReducedHTMLTokenizerStyleBlockCountForStandaloneRenderer(
                 html.c_str())) +
         " style blocks, " +
         std::to_string(
             blink_core_probe::ReducedAtomicHTMLTokenCountForStandaloneRenderer(
                 html.c_str())) +
         " atomic tokens, " +
         std::to_string(
             blink_core_probe::
                 ReducedAtomicHTMLTokenAttributeCountForStandaloneRenderer(
                     html.c_str())) +
         " atomic attributes, " +
         std::to_string(
             blink_core_probe::ReducedAtomicHTMLTokenValidTagCountForStandaloneRenderer(
                 html.c_str())) +
         " valid HTML tags, image src " +
         (blink_core_probe::ReducedHTMLTokenizerFindsImageSourceForStandaloneRenderer(
              html.c_str())
              ? "seen"
              : "not seen");
#else
  return "reduced Blink HTML tokenizer is not linked";
#endif
}

std::string ReducedBlinkHTMLStartTagSequence(const std::string& html) {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  const int count =
      blink_core_probe::ReducedHTMLTokenizerStartTagNameCountForStandaloneRenderer(
          html.c_str());
  if (count <= 0) {
    return "reduced Blink HTML parser start tag sequence: <none>";
  }
  std::string sequence = "reduced Blink HTML parser start tag sequence:";
  for (int i = 0; i < count; ++i) {
    char buffer[128] = {};
    blink_core_probe::ReducedHTMLTokenizerStartTagNameAtForStandaloneRenderer(
        html.c_str(), i, buffer, static_cast<int>(sizeof(buffer)));
    if (buffer[0] != '\0') {
      sequence += i == 0 ? " " : " > ";
      sequence += buffer;
    }
  }
  return sequence;
#else
  return "reduced Blink HTML parser start tag sequence unavailable";
#endif
}

std::string ReducedBlinkCSSParserStreamDiagnostic(
    const std::vector<Stylesheet>& stylesheets) {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  int stylesheet_count = 0;
  int token_count = 0;
  int at_rule_count = 0;
  int block_count = 0;
  int function_count = 0;
  for (const Stylesheet& stylesheet : stylesheets) {
    const bool has_url_function =
        stylesheet.css.find("url(") != std::string::npos ||
        stylesheet.css.find("URL(") != std::string::npos;
    if (has_url_function) {
      continue;
    }
    ++stylesheet_count;
    token_count +=
        blink_core_probe::ReducedCSSParserTokenStreamTokenCountForStandaloneRenderer(
            stylesheet.css.c_str());
    at_rule_count +=
        blink_core_probe::
            ReducedCSSParserTokenStreamAtRuleCountForStandaloneRenderer(
                stylesheet.css.c_str());
    block_count +=
        blink_core_probe::
            ReducedCSSParserTokenStreamBlockStartCountForStandaloneRenderer(
                stylesheet.css.c_str());
    function_count +=
        blink_core_probe::
            ReducedCSSParserTokenStreamFunctionCountForStandaloneRenderer(
                stylesheet.css.c_str());
  }
  return "reduced Blink CSS parser token stream parsed " +
         std::to_string(stylesheet_count) + " stylesheet(s): " +
         std::to_string(token_count) + " tokens, " +
         std::to_string(at_rule_count) + " at-rules, " +
         std::to_string(block_count) + " blocks, " +
         std::to_string(function_count) + " functions";
#else
  (void)stylesheets;
  return "reduced Blink CSS parser token stream is not linked";
#endif
}

std::string ReducedBlinkCSSDeclarationDiagnostic(
    const std::vector<Stylesheet>& stylesheets) {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  int stylesheet_count = 0;
  int declaration_count = 0;
  std::vector<std::string> samples;
  for (const Stylesheet& stylesheet : stylesheets) {
    ++stylesheet_count;
    const int count =
        blink_core_probe::ReducedCSSDeclarationCountForStandaloneRenderer(
            stylesheet.css.c_str());
    declaration_count += count;
    for (int i = 0; i < count && samples.size() < 4; ++i) {
      char selector[128] = {};
      char property[128] = {};
      char value[256] = {};
      blink_core_probe::ReducedCSSDeclarationSelectorAtForStandaloneRenderer(
          stylesheet.css.c_str(), i, selector, static_cast<int>(sizeof(selector)));
      blink_core_probe::ReducedCSSDeclarationPropertyAtForStandaloneRenderer(
          stylesheet.css.c_str(), i, property, static_cast<int>(sizeof(property)));
      blink_core_probe::ReducedCSSDeclarationValueAtForStandaloneRenderer(
          stylesheet.css.c_str(), i, value, static_cast<int>(sizeof(value)));
      if (property[0] != '\0' && value[0] != '\0') {
        std::string sample;
        if (selector[0] != '\0') {
          sample += selector;
          sample += " -> ";
        }
        sample += std::string(property) + ": " + value;
        samples.push_back(std::move(sample));
      }
    }
  }

  std::string diagnostic = "reduced Blink CSS declaration spans parsed " +
                           std::to_string(stylesheet_count) +
                           " stylesheet(s): " +
                           std::to_string(declaration_count) +
                           " declaration(s)";
  if (!samples.empty()) {
    diagnostic += " [";
    for (size_t i = 0; i < samples.size(); ++i) {
      if (i > 0) {
        diagnostic += "; ";
      }
      diagnostic += samples[i];
    }
    diagnostic += "]";
  }
  return diagnostic;
#else
  (void)stylesheets;
  return "reduced Blink CSS declaration spans are not linked";
#endif
}

struct ParsedDocument {
  using AttributeList = std::vector<std::pair<std::string, std::string>>;

  struct Node {
    std::string kind;
    std::string name;
    std::string value;
    AttributeList attributes;
    int node_id = 0;
    int parent_index = -1;
    int depth = 0;
    int first_child_index = -1;
    int next_sibling_index = -1;
    int child_count = 0;
    bool has_tree_position = false;
    bool synthetic = false;
    std::string bridge_action;
    std::vector<int> children;
  };

  struct LayoutBox {
    int node_index = -1;
    Rect bounds;
    std::string role;
  };

  struct ArtifactChunk {
    std::string chunk_id;
    int node_index = -1;
    Rect bounds;
    std::string role;
    std::string op;
  };

  std::string sanitized_html;
  std::string visible_text;
  std::vector<std::string> start_tag_sequence;
  std::vector<std::string> end_tag_sequence;
  std::vector<std::string> image_sources;
  std::vector<Stylesheet> inline_styles;
  std::vector<Node> nodes;
  std::vector<LayoutBox> layout_boxes;
  std::vector<ArtifactChunk> artifact_chunks;
  int start_tag_attribute_count = 0;
  int max_tree_depth = 0;
  int synthetic_node_count = 0;
  int tree_bridge_event_count = 0;
  int root_node_index = -1;
  int head_node_index = -1;
  int body_node_index = -1;
  int element_node_count = 0;
  int text_node_count = 0;
  int bridge_child_relation_count = 0;
  int linked_dom_node_count = 0;
  int linked_dom_max_depth = 0;
};

std::optional<std::string> AttributeValue(
    const ParsedDocument::Node& node,
    const std::string& name) {
  for (const auto& attribute : node.attributes) {
    if (attribute.first == name) {
      return attribute.second;
    }
  }
  return std::nullopt;
}

void AttachParsedDocumentTreeRelationships(ParsedDocument& document) {
  const int bridge_root_index = document.root_node_index;
  const int bridge_head_index = document.head_node_index;
  const int bridge_body_index = document.body_node_index;
  document.root_node_index = bridge_root_index;
  document.head_node_index = bridge_head_index;
  document.body_node_index = bridge_body_index;
  document.element_node_count = 0;
  document.text_node_count = 0;
  document.bridge_child_relation_count = 0;
  for (ParsedDocument::Node& node : document.nodes) {
    node.children.clear();
  }
  for (int i = 0; i < static_cast<int>(document.nodes.size()); ++i) {
    ParsedDocument::Node& node = document.nodes[static_cast<size_t>(i)];
    if (node.kind == "start") {
      ++document.element_node_count;
      if (node.name == "html" && document.root_node_index < 0) {
        document.root_node_index = i;
      } else if (node.name == "head" && document.head_node_index < 0) {
        document.head_node_index = i;
      } else if (node.name == "body" && document.body_node_index < 0) {
        document.body_node_index = i;
      }
    } else if (node.kind == "text") {
      ++document.text_node_count;
    }
    if (node.parent_index >= 0 &&
        node.parent_index < static_cast<int>(document.nodes.size())) {
      ParsedDocument::Node& parent =
          document.nodes[static_cast<size_t>(node.parent_index)];
      if (parent.first_child_index < 0 || parent.children.empty()) {
        parent.children.clear();
        for (int child = parent.first_child_index;
             child >= 0 && child < static_cast<int>(document.nodes.size());
             child =
                 document.nodes[static_cast<size_t>(child)].next_sibling_index) {
          parent.children.push_back(child);
          ++document.bridge_child_relation_count;
          if (static_cast<int>(parent.children.size()) > parent.child_count &&
              parent.child_count > 0) {
            break;
          }
        }
      }
    }
  }
}

const ParsedDocument::LayoutBox* LayoutBoxForNode(
    const ParsedDocument& document,
    int node_index,
    const std::string& role = std::string()) {
  for (const ParsedDocument::LayoutBox& box : document.layout_boxes) {
    if (box.node_index == node_index && (role.empty() || box.role == role)) {
      return &box;
    }
  }
  return nullptr;
}

void ImportBlinkTokenizerResourceMetadata(const std::string& html,
                                          ParsedDocument& document) {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  const int image_count =
      blink_core_probe::ReducedHTMLTokenizerImageSourceCountForStandaloneRenderer(
          html.c_str());
  for (int i = 0; i < image_count; ++i) {
    std::string value(1024, '\0');
    blink_core_probe::ReducedHTMLTokenizerImageSourceAtForStandaloneRenderer(
        html.c_str(), i, value.data(), static_cast<int>(value.size()));
    value.resize(std::char_traits<char>::length(value.c_str()));
    if (!value.empty()) {
      document.image_sources.push_back(std::move(value));
    }
  }

  int inline_style_index = 0;
  const int style_count =
      blink_core_probe::ReducedHTMLTokenizerStyleBlockCountForStandaloneRenderer(
          html.c_str());
  for (int i = 0; i < style_count; ++i) {
    const int style_length =
        blink_core_probe::ReducedHTMLTokenizerStyleBlockLengthForStandaloneRenderer(
            html.c_str(), i);
    if (style_length <= 0) {
      continue;
    }
    std::string css(static_cast<size_t>(style_length) + 1, '\0');
    blink_core_probe::ReducedHTMLTokenizerStyleBlockAtForStandaloneRenderer(
        html.c_str(), i, css.data(), static_cast<int>(css.size()));
    css.resize(std::char_traits<char>::length(css.c_str()));
    if (!css.empty()) {
      document.inline_styles.push_back(
          {"blink-inline-style-" + std::to_string(inline_style_index++),
           std::move(css)});
    }
  }
#else
  (void)html;
  (void)document;
#endif
}

bool ParseDocumentWithBlinkTreeBuilder(const std::string& html,
                                       ParsedDocument& document) {
#if defined(HTML_CSS_RENDERER_HAS_BLINK_TREE_BUILDER_BRIDGE)
  blink_tree_probe::ResetStandaloneHTMLTreeBuilderRecordingForStandaloneRenderer();
  blink_tree_probe::StandaloneHTMLTreeBuilderParseHTMLForStandaloneRenderer(
      html.c_str());
  const int recorded_node_count =
      blink_tree_probe::StandaloneHTMLTreeBuilderRecordedNodeCountForStandaloneRenderer();
  const int dom_snapshot_node_count =
      blink_tree_probe::StandaloneHTMLTreeBuilderDOMSnapshotNodeCountForStandaloneRenderer();
  const bool use_dom_snapshot = dom_snapshot_node_count > 0;
  const int node_count =
      use_dom_snapshot ? dom_snapshot_node_count : recorded_node_count;
  if (node_count <= 0) {
    return false;
  }

  document.nodes.reserve(static_cast<size_t>(node_count));
  for (int i = 0; i < node_count; ++i) {
    std::string kind(32, '\0');
    std::string name(128, '\0');
    std::string value(4096, '\0');
    if (use_dom_snapshot) {
      blink_tree_probe::StandaloneHTMLTreeBuilderDOMSnapshotNodeKindAtForStandaloneRenderer(
          i, kind.data(), static_cast<int>(kind.size()));
      blink_tree_probe::StandaloneHTMLTreeBuilderDOMSnapshotNodeNameAtForStandaloneRenderer(
          i, name.data(), static_cast<int>(name.size()));
      blink_tree_probe::StandaloneHTMLTreeBuilderDOMSnapshotNodeValueAtForStandaloneRenderer(
          i, value.data(), static_cast<int>(value.size()));
    } else {
      blink_tree_probe::StandaloneHTMLTreeBuilderRecordedNodeKindAtForStandaloneRenderer(
          i, kind.data(), static_cast<int>(kind.size()));
      blink_tree_probe::StandaloneHTMLTreeBuilderRecordedNodeNameAtForStandaloneRenderer(
          i, name.data(), static_cast<int>(name.size()));
      blink_tree_probe::StandaloneHTMLTreeBuilderRecordedNodeValueAtForStandaloneRenderer(
          i, value.data(), static_cast<int>(value.size()));
    }
    kind.resize(std::char_traits<char>::length(kind.c_str()));
    name.resize(std::char_traits<char>::length(name.c_str()));
    value.resize(std::char_traits<char>::length(value.c_str()));
    if (kind.empty()) {
      continue;
    }

    ParsedDocument::Node node;
    node.kind = kind == "element" ? "start" : kind;
    node.name = std::move(name);
    node.value = std::move(value);
    node.node_id = i + 1;
    node.parent_index =
        use_dom_snapshot
            ? blink_tree_probe::
                  StandaloneHTMLTreeBuilderDOMSnapshotParentAtForStandaloneRenderer(
                      i)
            : blink_tree_probe::
                  StandaloneHTMLTreeBuilderRecordedParentAtForStandaloneRenderer(
                      i);
    node.depth =
        use_dom_snapshot
            ? blink_tree_probe::
                  StandaloneHTMLTreeBuilderDOMSnapshotDepthAtForStandaloneRenderer(
                      i)
            : blink_tree_probe::
                  StandaloneHTMLTreeBuilderRecordedDepthAtForStandaloneRenderer(
                      i);
    node.first_child_index =
        use_dom_snapshot
            ? blink_tree_probe::
                  StandaloneHTMLTreeBuilderDOMSnapshotFirstChildAtForStandaloneRenderer(
                      i)
            : blink_tree_probe::
                  StandaloneHTMLTreeBuilderRecordedFirstChildAtForStandaloneRenderer(
                      i);
    node.next_sibling_index =
        use_dom_snapshot
            ? blink_tree_probe::
                  StandaloneHTMLTreeBuilderDOMSnapshotNextSiblingAtForStandaloneRenderer(
                      i)
            : blink_tree_probe::
                  StandaloneHTMLTreeBuilderRecordedNextSiblingAtForStandaloneRenderer(
                      i);
    node.child_count =
        use_dom_snapshot
            ? blink_tree_probe::
                  StandaloneHTMLTreeBuilderDOMSnapshotChildCountAtForStandaloneRenderer(
                      i)
            : blink_tree_probe::
                  StandaloneHTMLTreeBuilderRecordedChildCountAtForStandaloneRenderer(
                      i);
    node.has_tree_position = true;
    if (i == 0 && node.kind == "start" && node.name == "html" &&
        node.parent_index < 0) {
      node.kind = "document";
      node.name = "#document";
      node.synthetic = true;
    }
    node.bridge_action =
        use_dom_snapshot ? "blink-dom-snapshot" : "blink-tree-builder";
    document.nodes.push_back(std::move(node));
  }

  document.tree_bridge_event_count = recorded_node_count;
  document.linked_dom_node_count =
      blink_tree_probe::StandaloneHTMLTreeBuilderDOMLinkedNodeCountForStandaloneRenderer();
  document.linked_dom_max_depth =
      blink_tree_probe::StandaloneHTMLTreeBuilderDOMLinkedMaxDepthForStandaloneRenderer();
  const int layout_box_count =
      blink_tree_probe::StandaloneHTMLTreeBuilderLayoutSnapshotBoxCountForStandaloneRenderer();
  document.layout_boxes.reserve(
      layout_box_count > 0 ? static_cast<size_t>(layout_box_count) : 0);
  for (int i = 0; i < layout_box_count; ++i) {
    std::string role(32, '\0');
    blink_tree_probe::StandaloneHTMLTreeBuilderLayoutSnapshotRoleAtForStandaloneRenderer(
        i, role.data(), static_cast<int>(role.size()));
    role.resize(std::char_traits<char>::length(role.c_str()));
    ParsedDocument::LayoutBox box;
    box.node_index =
        blink_tree_probe::StandaloneHTMLTreeBuilderLayoutSnapshotNodeAtForStandaloneRenderer(
            i);
    box.bounds = Rect{
        blink_tree_probe::StandaloneHTMLTreeBuilderLayoutSnapshotXAtForStandaloneRenderer(
            i),
        blink_tree_probe::StandaloneHTMLTreeBuilderLayoutSnapshotYAtForStandaloneRenderer(
            i),
        blink_tree_probe::
            StandaloneHTMLTreeBuilderLayoutSnapshotWidthAtForStandaloneRenderer(
                i),
        blink_tree_probe::
            StandaloneHTMLTreeBuilderLayoutSnapshotHeightAtForStandaloneRenderer(
                i)};
    box.role = std::move(role);
    document.layout_boxes.push_back(std::move(box));
  }
  const int artifact_chunk_count =
      blink_tree_probe::
          StandaloneHTMLTreeBuilderPaintArtifactChunkCountForStandaloneRenderer();
  document.artifact_chunks.reserve(
      artifact_chunk_count > 0 ? static_cast<size_t>(artifact_chunk_count)
                               : 0);
  for (int i = 0; i < artifact_chunk_count; ++i) {
    std::string chunk_id(128, '\0');
    std::string role(32, '\0');
    std::string op(32, '\0');
    blink_tree_probe::
        StandaloneHTMLTreeBuilderPaintArtifactChunkIdAtForStandaloneRenderer(
            i, chunk_id.data(), static_cast<int>(chunk_id.size()));
    blink_tree_probe::
        StandaloneHTMLTreeBuilderPaintArtifactChunkRoleAtForStandaloneRenderer(
            i, role.data(), static_cast<int>(role.size()));
    blink_tree_probe::
        StandaloneHTMLTreeBuilderPaintArtifactChunkOpAtForStandaloneRenderer(
            i, op.data(), static_cast<int>(op.size()));
    chunk_id.resize(std::char_traits<char>::length(chunk_id.c_str()));
    role.resize(std::char_traits<char>::length(role.c_str()));
    op.resize(std::char_traits<char>::length(op.c_str()));
    ParsedDocument::ArtifactChunk chunk;
    chunk.chunk_id = std::move(chunk_id);
    chunk.node_index =
        blink_tree_probe::
            StandaloneHTMLTreeBuilderPaintArtifactChunkNodeAtForStandaloneRenderer(
                i);
    chunk.bounds = Rect{
        blink_tree_probe::
            StandaloneHTMLTreeBuilderPaintArtifactChunkXAtForStandaloneRenderer(
                i),
        blink_tree_probe::
            StandaloneHTMLTreeBuilderPaintArtifactChunkYAtForStandaloneRenderer(
                i),
        blink_tree_probe::
            StandaloneHTMLTreeBuilderPaintArtifactChunkWidthAtForStandaloneRenderer(
                i),
        blink_tree_probe::
            StandaloneHTMLTreeBuilderPaintArtifactChunkHeightAtForStandaloneRenderer(
                i)};
    chunk.role = std::move(role);
    chunk.op = std::move(op);
    document.artifact_chunks.push_back(std::move(chunk));
  }
  document.visible_text.clear();
  for (const ParsedDocument::Node& node : document.nodes) {
    if (node.kind == "start" && !node.name.empty()) {
      document.start_tag_sequence.push_back(node.name);
    } else if (node.kind == "text") {
      document.visible_text += node.value;
    }
    document.max_tree_depth = std::max(document.max_tree_depth, node.depth);
  }
  ImportBlinkTokenizerResourceMetadata(html, document);
  AttachParsedDocumentTreeRelationships(document);
  return true;
#else
  (void)html;
  (void)document;
  return false;
#endif
}

ParsedDocument ParseDocumentWithReducedBlink(const std::string& html) {
  ParsedDocument document;
  document.sanitized_html = html;
  if (ParseDocumentWithBlinkTreeBuilder(html, document)) {
    return document;
  }
  return document;
}

std::string ParsedDocumentSummaryDiagnostic(const ParsedDocument& document) {
  return "ParsedDocument from Blink tree source: " +
         std::to_string(document.nodes.size()) + " node(s), " +
         std::to_string(document.start_tag_sequence.size()) + " element start(s), " +
         std::to_string(document.end_tag_sequence.size()) + " element end(s), " +
         std::to_string(document.start_tag_attribute_count) + " start attribute(s), " +
         std::to_string(document.image_sources.size()) + " image reference(s), " +
         std::to_string(document.inline_styles.size()) + " inline style block(s), " +
         std::to_string(document.visible_text.size()) + " visible text byte(s), " +
         "standalone tree sink max depth " +
         std::to_string(document.max_tree_depth) + ", " +
         std::to_string(document.synthetic_node_count) +
         " parser-inserted node(s), " +
         std::to_string(document.tree_bridge_event_count) +
         " tree bridge event(s), " +
         std::to_string(document.element_node_count) +
         " DOM-like element node(s), " +
         std::to_string(document.text_node_count) +
         " DOM-like text node(s), root/head/body indices " +
         std::to_string(document.root_node_index) + "/" +
         std::to_string(document.head_node_index) + "/" +
         std::to_string(document.body_node_index) + ", " +
         std::to_string(document.bridge_child_relation_count) +
         " bridge child relation(s), Blink DOM links " +
         std::to_string(document.linked_dom_node_count) +
         " node(s) at max depth " +
         std::to_string(document.linked_dom_max_depth) + ", " +
         std::to_string(document.layout_boxes.size()) +
         " Blink layout snapshot box(es), " +
         std::to_string(document.artifact_chunks.size()) +
         " Blink paint artifact chunk probe(s)";
}

std::string ParsedDocumentNodeSequenceDiagnostic(
    const ParsedDocument& document) {
  std::string sequence = "Blink tree node sequence:";
  if (document.nodes.empty()) {
    return sequence + " <empty>";
  }
  const size_t limit = std::min<size_t>(document.nodes.size(), 16);
  for (size_t i = 0; i < limit; ++i) {
    const ParsedDocument::Node& node = document.nodes[i];
    sequence += i == 0 ? " " : " > ";
    sequence += node.kind;
    if (node.node_id > 0) {
      sequence += "#";
      sequence += std::to_string(node.node_id);
    }
    if (!node.name.empty()) {
      sequence += ":";
      sequence += node.name;
    } else if (node.kind == "text" && !node.value.empty()) {
      sequence += ":text";
    }
    if (node.has_tree_position) {
      sequence += "@d";
      sequence += std::to_string(node.depth);
    }
    if (node.synthetic) {
      sequence += "*";
    }
    if (!node.bridge_action.empty()) {
      sequence += "{";
      sequence += node.bridge_action;
      sequence += "}";
    }
  }
  if (document.nodes.size() > limit) {
    sequence += " > ...";
  }
  return sequence;
}

std::vector<Stylesheet> StylesheetsWithBlinkInlineStyles(
    const ParsedDocument& document,
    const std::vector<Stylesheet>& stylesheets) {
  std::vector<Stylesheet> combined = stylesheets;
  combined.insert(combined.end(), document.inline_styles.begin(),
                  document.inline_styles.end());
  return combined;
}

std::vector<ResourceReference> ReducedBlinkCSSResourceReferences(
    const std::vector<Stylesheet>& stylesheets) {
  std::vector<ResourceReference> references;
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  for (const Stylesheet& stylesheet : stylesheets) {
    const bool has_url_function =
        stylesheet.css.find("url(") != std::string::npos ||
        stylesheet.css.find("URL(") != std::string::npos;
    if (!has_url_function) {
      (void)blink_core_probe::
          ReducedCSSParserTokenStreamTokenCountForStandaloneRenderer(
              stylesheet.css.c_str());
    }
  }
#else
  (void)stylesheets;
#endif
  references = ExtractResourceReferences(std::string(), stylesheets);
  return references;
}

std::optional<Color> ParseDeclarationHexColor(const std::string& value) {
  const size_t hash = value.find('#');
  if (hash == std::string::npos || hash + 6 >= value.size()) {
    return std::nullopt;
  }

  auto parse_byte = [](const std::string& text) -> std::optional<int> {
    int parsed = 0;
    for (char c : text) {
      parsed *= 16;
      if (c >= '0' && c <= '9') {
        parsed += c - '0';
      } else if (c >= 'a' && c <= 'f') {
        parsed += 10 + c - 'a';
      } else if (c >= 'A' && c <= 'F') {
        parsed += 10 + c - 'A';
      } else {
        return std::nullopt;
      }
    }
    return parsed;
  };

  const auto red = parse_byte(value.substr(hash + 1, 2));
  const auto green = parse_byte(value.substr(hash + 3, 2));
  const auto blue = parse_byte(value.substr(hash + 5, 2));
  if (!red || !green || !blue) {
    return std::nullopt;
  }
  return Color::Rgba(*red / 255.0f, *green / 255.0f, *blue / 255.0f, 1.0f);
}

struct DeclarationPaintHints {
  std::optional<Color> background_color;
  std::optional<Color> text_color;
  int declaration_count = 0;
};

struct CSSDeclarationSpan {
  std::string stylesheet_id;
  std::string selector;
  std::string property;
  std::string value;
  int source_order = 0;
};

std::vector<CSSDeclarationSpan> ExtractDeclarationSpans(
    const std::vector<Stylesheet>& stylesheets) {
  std::vector<CSSDeclarationSpan> spans;
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  int source_order = 0;
  for (const Stylesheet& stylesheet : stylesheets) {
    const int count =
        blink_core_probe::ReducedCSSDeclarationCountForStandaloneRenderer(
            stylesheet.css.c_str());
    for (int i = 0; i < count; ++i) {
      char selector_buffer[128] = {};
      char property_buffer[128] = {};
      char value_buffer[256] = {};
      blink_core_probe::ReducedCSSDeclarationSelectorAtForStandaloneRenderer(
          stylesheet.css.c_str(), i, selector_buffer,
          static_cast<int>(sizeof(selector_buffer)));
      blink_core_probe::ReducedCSSDeclarationPropertyAtForStandaloneRenderer(
          stylesheet.css.c_str(), i, property_buffer,
          static_cast<int>(sizeof(property_buffer)));
      blink_core_probe::ReducedCSSDeclarationValueAtForStandaloneRenderer(
          stylesheet.css.c_str(), i, value_buffer,
          static_cast<int>(sizeof(value_buffer)));
      if (property_buffer[0] == '\0' || value_buffer[0] == '\0') {
        continue;
      }
      spans.push_back({stylesheet.id, selector_buffer,
                       ToLowerAscii(property_buffer), value_buffer,
                       source_order++});
    }
  }
#else
  (void)stylesheets;
#endif
  return spans;
}

bool SelectorCanAffectCurrentDocumentPaint(const std::string& selector) {
  if (selector.empty()) {
    return true;
  }
  const std::string lower = ToLowerAscii(selector);
  return lower.find("body") != std::string::npos ||
         lower.find("html") != std::string::npos ||
         lower.find("main") != std::string::npos ||
         lower.find("p") != std::string::npos ||
         lower.find("h1") != std::string::npos ||
         lower.find("*") != std::string::npos;
}

DeclarationPaintHints ExtractDeclarationPaintHints(
    const std::vector<Stylesheet>& stylesheets) {
  DeclarationPaintHints hints;
  const std::vector<CSSDeclarationSpan> spans =
      ExtractDeclarationSpans(stylesheets);
  hints.declaration_count = static_cast<int>(spans.size());
  for (const CSSDeclarationSpan& span : spans) {
    if (!SelectorCanAffectCurrentDocumentPaint(span.selector)) {
      continue;
    }
    if (span.property == "background" ||
        span.property == "background-color") {
      if (auto parsed = ParseDeclarationHexColor(span.value)) {
        hints.background_color = *parsed;
      }
    } else if (span.property == "color") {
      if (auto parsed = ParseDeclarationHexColor(span.value)) {
        hints.text_color = *parsed;
      }
    }
  }
  return hints;
}

void ApplyDeclarationPaintHints(PaintArtifact& paint_artifact,
                                Size viewport,
                                std::vector<std::string>& diagnostics,
                                const DeclarationPaintHints& hints) {
  bool applied_background = false;
  bool applied_text = false;
  for (PaintArtifactChunk& chunk : paint_artifact.chunks) {
    for (PaintRecordOp& op : chunk.paint_record_ops) {
      if (hints.background_color &&
          (op.type == PaintRecordOpType::kDrawRect ||
           op.type == PaintRecordOpType::kDrawIRect) &&
          op.rect.x == 0.0f && op.rect.y == 0.0f &&
          op.rect.width == viewport.width &&
          op.rect.height == viewport.height) {
        op.color = *hints.background_color;
        applied_background = true;
      }
      if (hints.text_color && op.type == PaintRecordOpType::kDrawTextBlob) {
        op.glyph_run.color = *hints.text_color;
        applied_text = true;
      }
    }
  }

  if (applied_background || applied_text) {
    std::string diagnostic =
        "Blink declaration paint bridge applied " +
        std::to_string(hints.declaration_count) + " parsed declaration span(s)";
    if (applied_background) {
      diagnostic += ", background color";
    }
    if (applied_text) {
      diagnostic += ", text color";
    }
    diagnostics.push_back(std::move(diagnostic));
  }
}

void AddPaintArtifactChunk(PaintArtifact& artifact,
                           std::string chunk_id,
                           Rect bounds,
                           PaintRecordOp op) {
  PaintArtifactChunk chunk;
  chunk.chunk_id = std::move(chunk_id);
  chunk.bounds = bounds;
  chunk.paint_record_ops.push_back(std::move(op));
  artifact.chunks.push_back(std::move(chunk));
}

void AddEmptyPaintArtifactChunk(PaintArtifact& artifact,
                                std::string chunk_id,
                                Rect bounds) {
  PaintArtifactChunk chunk;
  chunk.chunk_id = std::move(chunk_id);
  chunk.bounds = bounds;
  artifact.chunks.push_back(std::move(chunk));
}

bool HasTextBackend(FontProvider* font_provider,
                    TextShaper* text_shaper,
                    GlyphRasterizer* glyph_rasterizer) {
  return font_provider && text_shaper && glyph_rasterizer;
}

std::optional<GlyphRun> ShapeAndRasterizeTextForBlinkBridge(
    const std::string& text,
    Point origin,
    Color color,
    const std::string& font_id,
    TextShaper* text_shaper,
    GlyphRasterizer* glyph_rasterizer,
    LoadCommandList* load_commands,
    std::vector<std::string>* diagnostics) {
  if (text.empty() || font_id.empty() || !text_shaper || !glyph_rasterizer) {
    return std::nullopt;
  }

  TextShapeInput shape_input;
  shape_input.text = text;
  shape_input.font_id = font_id;
  shape_input.font_size = 16.0f;
  shape_input.direction = TextDirection::kLeftToRight;
  shape_input.origin = origin;
  shape_input.color = color;
  TextShapeResult shaped = text_shaper->ShapeText(shape_input);
  diagnostics->insert(diagnostics->end(), shaped.diagnostics.begin(),
                      shaped.diagnostics.end());
  if (shaped.glyph_run.glyph_ids.empty()) {
    return std::nullopt;
  }

  GlyphRasterInput raster_input;
  raster_input.glyph_run = shaped.glyph_run;
  raster_input.atlas_id = "blink-text-atlas";
  GlyphRasterResult rasterized =
      glyph_rasterizer->RasterizeGlyphs(raster_input);
  for (const GlyphAtlasUpdate& update : rasterized.atlas_updates) {
    load_commands->push_back(LoadCommand::UpdateGlyphAtlas(update));
  }
  diagnostics->insert(diagnostics->end(), rasterized.diagnostics.begin(),
                      rasterized.diagnostics.end());
  diagnostics->push_back("Blink bridge shaped text with font asset: " +
                         font_id);
  return shaped.glyph_run;
}

bool RasterizeGlyphRunForBlinkBridge(const GlyphRun& glyph_run,
                                     GlyphRasterizer* glyph_rasterizer,
                                     LoadCommandList* load_commands,
                                     std::vector<std::string>* diagnostics) {
  if (!glyph_rasterizer || glyph_run.font_id.empty() ||
      glyph_run.glyph_ids.empty()) {
    return false;
  }
  GlyphRasterInput raster_input;
  raster_input.glyph_run = glyph_run;
  raster_input.atlas_id = "blink-text-atlas";
  GlyphRasterResult rasterized =
      glyph_rasterizer->RasterizeGlyphs(raster_input);
  for (const GlyphAtlasUpdate& update : rasterized.atlas_updates) {
    load_commands->push_back(LoadCommand::UpdateGlyphAtlas(update));
  }
  diagnostics->insert(diagnostics->end(), rasterized.diagnostics.begin(),
                      rasterized.diagnostics.end());
  return !rasterized.atlas_updates.empty();
}

std::string BuildLiveBlinkProbeHtml(const std::string& html,
                                    const std::vector<Stylesheet>& stylesheets) {
  const auto lower_ascii = [](std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char c) {
                     return static_cast<char>(std::tolower(c));
                   });
    return value;
  };
  const auto extract_style_blocks = [&](const std::string& input) {
    std::string styles;
    const std::string lower = lower_ascii(input);
    size_t search_offset = 0;
    while (true) {
      const size_t open = lower.find("<style", search_offset);
      if (open == std::string::npos) {
        break;
      }
      const size_t open_end = lower.find('>', open);
      if (open_end == std::string::npos) {
        break;
      }
      const size_t close = lower.find("</style>", open_end + 1);
      if (close == std::string::npos) {
        break;
      }
      styles += "<style>";
      styles += input.substr(open_end + 1, close - open_end - 1);
      styles += "</style>";
      search_offset = close + 8;
    }
    return styles;
  };
  const auto remove_style_blocks = [&](const std::string& input) {
    std::string output;
    const std::string lower = lower_ascii(input);
    size_t search_offset = 0;
    while (true) {
      const size_t open = lower.find("<style", search_offset);
      if (open == std::string::npos) {
        output += input.substr(search_offset);
        break;
      }
      const size_t open_end = lower.find('>', open);
      if (open_end == std::string::npos) {
        output += input.substr(search_offset);
        break;
      }
      const size_t close = lower.find("</style>", open_end + 1);
      if (close == std::string::npos) {
        output += input.substr(search_offset);
        break;
      }
      output += input.substr(search_offset, open - search_offset);
      search_offset = close + 8;
    }
    return output;
  };

  std::string stylesheet_html;
  for (const Stylesheet& stylesheet : stylesheets) {
    stylesheet_html += "<style>";
    stylesheet_html += stylesheet.css;
    stylesheet_html += "</style>";
  }

  const bool has_head = html.find("<head") != std::string::npos ||
                        html.find("<HEAD") != std::string::npos;
  const bool has_body = html.find("<body") != std::string::npos ||
                        html.find("<BODY") != std::string::npos;
  const bool has_html = html.find("<html") != std::string::npos ||
                        html.find("<HTML") != std::string::npos;
  if (has_head) {
    std::string output = html;
    const size_t head_close = output.find("</head>");
    const size_t head_close_upper = output.find("</HEAD>");
    const size_t insert_at =
        head_close != std::string::npos ? head_close : head_close_upper;
    if (insert_at != std::string::npos) {
      output.insert(insert_at, stylesheet_html);
      return output;
    }
    return stylesheet_html + output;
  }
  if (has_body || has_html) {
    return "<head>" + stylesheet_html + "</head>" + html;
  }
  return "<head>" + stylesheet_html + extract_style_blocks(html) +
         "</head><body>" + remove_style_blocks(html) + "</body>";
}

std::string NormalizeBlinkTextNodeValue(const std::string& value) {
  std::string normalized;
  normalized.reserve(value.size());
  bool pending_space = false;
  for (const unsigned char c : value) {
    if (std::isspace(c)) {
      pending_space = !normalized.empty();
      continue;
    }
    if (pending_space) {
      normalized.push_back(' ');
      pending_space = false;
    }
    normalized.push_back(static_cast<char>(c));
  }
  return normalized;
}

int SourceElementDepthForNode(const ParsedDocument& document,
                              const ParsedDocument::Node& node) {
  int depth = 0;
  int parent_index = node.parent_index;
  while (parent_index >= 0 &&
         parent_index < static_cast<int>(document.nodes.size())) {
    const ParsedDocument::Node& parent =
        document.nodes[static_cast<size_t>(parent_index)];
    if (parent.kind == "start" && !parent.synthetic &&
        parent.name != "html" && parent.name != "head" &&
        parent.name != "body") {
      ++depth;
    }
    parent_index = parent.parent_index;
  }
  return depth;
}

std::string NearestElementIdForNode(const ParsedDocument& document,
                                    const ParsedDocument::Node& node) {
  int parent_index = node.parent_index;
  while (parent_index >= 0 &&
         parent_index < static_cast<int>(document.nodes.size())) {
    const ParsedDocument::Node& parent =
        document.nodes[static_cast<size_t>(parent_index)];
    if (parent.kind == "start") {
      if (const std::optional<std::string> id = AttributeValue(parent, "id")) {
        return *id;
      }
    }
    parent_index = parent.parent_index;
  }
  return std::string();
}

int FindFirstElementNode(const ParsedDocument& document,
                         const std::string& name) {
  for (int i = 0; i < static_cast<int>(document.nodes.size()); ++i) {
    const ParsedDocument::Node& node = document.nodes[static_cast<size_t>(i)];
    if (node.kind == "start" && node.name == name) {
      return i;
    }
  }
  return -1;
}

PaintArtifact BuildPaintArtifactFromBlinkExport(const ParsedDocument& document,
                                                Size viewport,
                                                Color text_color) {
  PaintArtifact artifact;
  for (const ParsedDocument::ArtifactChunk& chunk :
       document.artifact_chunks) {
    const std::string chunk_id =
        chunk.chunk_id.empty() ? "blink-paint-artifact:anonymous"
                               : chunk.chunk_id;
    if (chunk.op == "DrawRect") {
      const Color color = chunk.role == "background"
                              ? Color::Rgba(1.0f, 1.0f, 1.0f, 1.0f)
                              : Color::Rgba(0.0f, 0.0f, 0.0f, 0.0f);
      AddPaintArtifactChunk(artifact, chunk_id, chunk.bounds,
                            PaintRecordDrawRect(chunk.bounds, color));
      continue;
    }
    if (chunk.op == "DrawTextBlob" && chunk.node_index >= 0 &&
        chunk.node_index < static_cast<int>(document.nodes.size())) {
      const ParsedDocument::Node& node =
          document.nodes[static_cast<size_t>(chunk.node_index)];
      const std::string text = NormalizeBlinkTextNodeValue(node.value);
      if (!text.empty()) {
        AddEmptyPaintArtifactChunk(artifact, chunk_id, chunk.bounds);
        continue;
      }
    }
    AddEmptyPaintArtifactChunk(artifact, chunk_id, chunk.bounds);
  }

  if (artifact.chunks.empty()) {
    AddPaintArtifactChunk(
        artifact, "blink-artifact:viewport-background",
        Rect{0.0f, 0.0f, viewport.width, viewport.height},
        PaintRecordDrawRect(Rect{0.0f, 0.0f, viewport.width, viewport.height},
                            Color::Rgba(1.0f, 1.0f, 1.0f, 1.0f)));
  }
  return artifact;
}

struct BlinkTreeFrameBuildResult {
  LoadCommandList load_commands;
  PaintArtifact paint_artifact;
  BlinkPaintArtifactSource paint_source = BlinkPaintArtifactSource::kNone;
  DrawCommandList draw_commands;
  std::vector<HitTestEntry> hit_test_entries;
  std::vector<std::string> missing_resources;
  std::vector<std::string> diagnostics;
};

BlinkTreeFrameBuildResult BuildBlinkTreeFrameOutput(
    const ParsedDocument& document,
    const std::vector<Stylesheet>& stylesheets,
    AssetProvider* asset_provider,
    Size viewport,
    Color text_color,
    FontProvider* font_provider,
    TextShaper* text_shaper,
    GlyphRasterizer* glyph_rasterizer) {
  BlinkTreeFrameBuildResult output;
  const bool use_blink_exported_artifact = !document.artifact_chunks.empty();
  if (use_blink_exported_artifact) {
    output.paint_artifact =
        BuildPaintArtifactFromBlinkExport(document, viewport, text_color);
    output.paint_source = BlinkPaintArtifactSource::kReducedBlinkExport;
  } else {
    AddPaintArtifactChunk(
        output.paint_artifact, "blink-artifact:viewport-background",
        Rect{0.0f, 0.0f, viewport.width, viewport.height},
        PaintRecordDrawRect(Rect{0.0f, 0.0f, viewport.width, viewport.height},
                            Color::Rgba(1.0f, 1.0f, 1.0f, 1.0f)));
    output.paint_source = BlinkPaintArtifactSource::kStandaloneSnapshot;
  }
  std::vector<ResourceReference> inline_style_references =
      ReducedBlinkCSSResourceReferences(stylesheets);
  if (inline_style_references.empty()) {
    inline_style_references = ExtractResourceReferences(std::string(),
                                                        stylesheets);
  }
  int resource_reference_count =
      static_cast<int>(inline_style_references.size());
  std::string active_font_id;

  const auto apply_resolution = [&](const ResourceResolution& resolution,
                                    float y,
                                    float x = 16.0f) -> bool {
    if (!resolution.asset) {
      output.missing_resources.push_back(resolution.reference.id);
      output.diagnostics.push_back(resolution.diagnostic);
      return false;
    }

    if (resolution.reference.element_kind == "font") {
      FontLoadInfo font;
      font.font_id = resolution.reference.id;
      font.resource_id = resolution.reference.id;
      font.mime_type = resolution.asset->mime_type;
      font.byte_count = resolution.asset->bytes.size();
      font.bytes_hash = HashBytes(resolution.asset->bytes);
      output.load_commands.push_back(LoadCommand::LoadFont(std::move(font)));
      active_font_id = resolution.reference.id;
      if (font_provider) {
        FontAsset font_asset;
        font_asset.font_id = resolution.reference.id;
        font_asset.resource_id = resolution.reference.id;
        font_asset.mime_type = resolution.asset->mime_type;
        font_asset.bytes = resolution.asset->bytes;
        if (font_provider->RegisterFont(font_asset)) {
          output.diagnostics.push_back(
              "Blink bridge registered font asset for text backend: " +
              resolution.reference.id);
        } else {
          output.diagnostics.push_back(
              "Blink bridge failed to register font asset for text backend: " +
              resolution.reference.id);
          active_font_id.clear();
        }
      }
      output.diagnostics.push_back(
          "Blink inline style resource policy resolved font asset: " +
          resolution.reference.id);
      return true;
    }

    ImageLoadInfo image;
    image.image_id = resolution.reference.id;
    image.resource_id = resolution.reference.id;
    image.mime_type = resolution.asset->mime_type;
    image.byte_count = resolution.asset->bytes.size();
    image.bytes_hash = HashBytes(resolution.asset->bytes);
    output.load_commands.push_back(LoadCommand::LoadImage(std::move(image)));
    if (resolution.reference.element_kind == "image") {
      const Rect image_bounds{x, y, 96.0f, 72.0f};
      AddPaintArtifactChunk(
          output.paint_artifact,
          "blink-artifact:image:" + resolution.reference.id, image_bounds,
          PaintRecordDrawImageRect(resolution.reference.id,
                                   Rect{0.0f, 0.0f, 0.0f, 0.0f},
                                   image_bounds));
      output.hit_test_entries.push_back({resolution.reference.id,
                                         image_bounds});
    } else {
      output.diagnostics.push_back(
          "Blink inline style resource policy resolved image-like asset: " +
          resolution.reference.id);
    }
    return true;
  };

  for (const ResourceResolution& resolution :
       ResolveResourceReferences(inline_style_references, asset_provider)) {
    (void)apply_resolution(resolution, 0.0f);
  }
  float y = 24.0f;
  bool emitted_text = false;
  int text_node_count = 0;
  int rendered_tree_node_count = 0;
  std::vector<std::string> rendered_image_sources;

  const auto render_node = [&](const auto& self, int node_index) -> void {
    if (node_index < 0 ||
        node_index >= static_cast<int>(document.nodes.size())) {
      return;
    }
    const ParsedDocument::Node& node =
        document.nodes[static_cast<size_t>(node_index)];
    if (node.kind == "start") {
      if (node.name == "head" || node.name == "script" ||
          node.name == "style") {
        return;
      }
      ++rendered_tree_node_count;
      for (const int child_index : node.children) {
        self(self, child_index);
      }
      return;
    }
    if (node.kind == "end" || node.kind == "style") {
      return;
    }
    if (node.kind == "image" && !node.value.empty()) {
      ++resource_reference_count;
      rendered_image_sources.push_back(node.value);
      const float x = 16.0f + 12.0f *
                                  static_cast<float>(
                                      SourceElementDepthForNode(document,
                                                                node));
      const std::vector<ResourceResolution> resolutions =
          ResolveResourceReferences({ResourceReference{node.value, "image"}},
                                    asset_provider);
      if (!resolutions.empty() && apply_resolution(resolutions.front(), y, x)) {
        y += 84.0f;
      }
      return;
    }
    if (node.kind != "text") {
      return;
    }
    const std::string text = NormalizeBlinkTextNodeValue(node.value);
    if (text.empty()) {
      return;
    }
    ++text_node_count;
    const ParsedDocument::LayoutBox* layout_box =
        LayoutBoxForNode(document, node_index, "text");
    const float x = layout_box
                        ? layout_box->bounds.x
                        : 16.0f + 12.0f *
                                      static_cast<float>(
                                          SourceElementDepthForNode(document,
                                                                    node));
    const float text_y = layout_box ? layout_box->bounds.y : y;
    std::string element_id = NearestElementIdForNode(document, node);
    if (element_id.empty()) {
      element_id = text_node_count == 1
                       ? std::string("document-text")
                       : "document-text-" + std::to_string(text_node_count);
    }
    const Rect text_bounds =
        layout_box ? layout_box->bounds
                   : Rect{x, y - 16.0f,
                          8.0f * static_cast<float>(text.size()), 24.0f};
    if (!use_blink_exported_artifact) {
      std::optional<GlyphRun> shaped;
      if (HasTextBackend(font_provider, text_shaper, glyph_rasterizer)) {
        shaped = ShapeAndRasterizeTextForBlinkBridge(
            text, Point{x, text_y}, text_color, active_font_id, text_shaper,
            glyph_rasterizer, &output.load_commands, &output.diagnostics);
      }
      if (shaped) {
        AddPaintArtifactChunk(output.paint_artifact,
                              "blink-artifact:text:" + element_id, text_bounds,
                              PaintRecordDrawTextBlob(std::move(*shaped)));
      } else {
        output.diagnostics.push_back(
            "Blink bridge skipped text because shaping failed: " + element_id);
      }
    }
    output.hit_test_entries.push_back({element_id, text_bounds});
    emitted_text = true;
    y = layout_box ? std::max(y, layout_box->bounds.y +
                                     layout_box->bounds.height)
                   : y + 24.0f;
  };

  const int body_index = document.body_node_index >= 0
                             ? document.body_node_index
                             : FindFirstElementNode(document, "body");
  if (body_index >= 0) {
    render_node(render_node, body_index);
  } else if (document.root_node_index >= 0) {
    render_node(render_node, document.root_node_index);
  } else {
    for (int i = 0; i < static_cast<int>(document.nodes.size()); ++i) {
      const ParsedDocument::Node& node = document.nodes[static_cast<size_t>(i)];
      if (node.parent_index < 0) {
        render_node(render_node, i);
      }
    }
  }

  for (const std::string& image_source : document.image_sources) {
    if (image_source.empty() ||
        std::find(rendered_image_sources.begin(), rendered_image_sources.end(),
                  image_source) != rendered_image_sources.end()) {
      continue;
    }
    ++resource_reference_count;
    const std::vector<ResourceResolution> resolutions =
        ResolveResourceReferences({ResourceReference{image_source, "image"}},
                                  asset_provider);
    if (!resolutions.empty() && apply_resolution(resolutions.front(), y)) {
      y += 84.0f;
    }
  }

  if (!use_blink_exported_artifact && !emitted_text &&
      !document.visible_text.empty()) {
    const Rect text_bounds{
        16.0f, y - 16.0f,
        8.0f * static_cast<float>(document.visible_text.size()), 24.0f};
    std::optional<GlyphRun> shaped;
    if (HasTextBackend(font_provider, text_shaper, glyph_rasterizer)) {
      shaped = ShapeAndRasterizeTextForBlinkBridge(
          document.visible_text, Point{16.0f, y}, text_color, active_font_id,
          text_shaper, glyph_rasterizer, &output.load_commands,
          &output.diagnostics);
    }
    if (shaped) {
      AddPaintArtifactChunk(output.paint_artifact,
                            "blink-artifact:text:document-text", text_bounds,
                            PaintRecordDrawTextBlob(std::move(*shaped)));
      output.hit_test_entries.push_back({"document-text", text_bounds});
    } else {
      output.diagnostics.push_back(
          "Blink bridge skipped visible text because shaping failed");
    }
  }

  output.diagnostics.push_back(
      "Blink tree node stream drives current RenderFrame package: " +
      std::to_string(document.nodes.size()) + " node(s), " +
      std::to_string(resource_reference_count) + " resource reference(s), " +
      std::to_string(text_node_count) + " text node(s), " +
      std::to_string(rendered_tree_node_count) +
      " rendered DOM-like subtree node(s), " +
      std::to_string(document.layout_boxes.size()) +
      " Blink layout snapshot box(es), " +
      std::to_string(output.paint_artifact.chunks.size()) +
      (use_blink_exported_artifact
           ? " Blink-exported paint artifact chunk(s)"
           : " synthesized paint artifact chunk(s)"));
  if (!document.inline_styles.empty()) {
    output.diagnostics.push_back(
        "Blink CSS parser token stream imported; inline url(...) resource "
        "policy handles current CSS");
  }
  return output;
}

#if defined(HTML_CSS_RENDERER_HAS_LIVE_BLINK_RUNTIME)
class LiveBlinkPageEmbedder final : public BlinkPageEmbedder {
 public:
  explicit LiveBlinkPageEmbedder(BlinkPageEmbedderCreateInfo create_info) {
    snapshot_.html = create_info.renderer.html;
    snapshot_.stylesheets = create_info.renderer.stylesheets;
    snapshot_.viewport = create_info.renderer.viewport;
    snapshot_.device_scale_factor = create_info.renderer.device_scale_factor;
    snapshot_.asset_namespace = create_info.renderer.asset_namespace;
    snapshot_.features = create_info.renderer.features;
  }

  BlinkLifecycleReport Initialize() override {
    BlinkLifecycleReport report;
    report.used_blink_runtime = true;
    report.diagnostics.push_back(
        "live Blink runtime adapter is linked");
    AppendLivePaintDiagnostics(snapshot_.html, snapshot_.stylesheets,
                               snapshot_.viewport,
                               report.diagnostics);
    return report;
  }

  RenderResult AdvanceAndRender(const FrameInput& input) override {
    const RendererSnapshot previous_snapshot = Snapshot();
    ApplyInput(input);
    RenderResult result;
    result.successor_snapshot = snapshot_;
    AppendLivePaintDiagnostics(result.successor_snapshot.html,
                               result.successor_snapshot.stylesheets,
                               result.successor_snapshot.viewport,
                               result.diagnostics);
    TryReplaceWithLivePaintArtifactScene(result, previous_snapshot, false,
                                         snapshot_.html, snapshot_.stylesheets);
    return result;
  }

  RenderResult AdvanceAndRenderIncremental(const FrameInput& input) override {
    const RendererSnapshot previous_snapshot = Snapshot();
    ApplyInput(input);
    RenderResult result;
    result.successor_snapshot = snapshot_;
    AppendLivePaintDiagnostics(result.successor_snapshot.html,
                               result.successor_snapshot.stylesheets,
                               result.successor_snapshot.viewport,
                               result.diagnostics);
    TryReplaceWithLivePaintArtifactScene(result, previous_snapshot, true,
                                         snapshot_.html, snapshot_.stylesheets);
    return result;
  }

  RendererSnapshot Snapshot() const override { return snapshot_; }

 private:
  void ApplyInput(const FrameInput& input) {
    snapshot_.timeline_time_seconds =
        input.timeline_time_seconds > 0.0
            ? input.timeline_time_seconds
            : snapshot_.timeline_time_seconds + input.delta_time_seconds;
    if (input.viewport) {
      snapshot_.viewport = *input.viewport;
    }
    snapshot_.scroll_offsets_by_element_id = input.scroll_offsets_by_element_id;
    snapshot_.focused_element_id = input.focused_element_id;
    snapshot_.hovered_element_id = input.hovered_element_id;
    snapshot_.active_element_id = input.active_element_id;
    snapshot_.form_values_by_element_id = input.form_values_by_element_id;
  }

  static void AppendLivePaintDiagnostics(
      const std::string& html,
      const std::vector<Stylesheet>& stylesheets,
      Size viewport,
      std::vector<std::string>& diagnostics) {
    namespace live_probe = ::blink::standalone_renderer_probe;
    const std::string probe_html = BuildLiveBlinkProbeHtml(html, stylesheets);
    live_probe::StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(
        static_cast<int>(viewport.width), static_cast<int>(viewport.height));
    diagnostics.push_back(
        "live Blink bridge recipe version: " +
        std::to_string(live_probe::
                           StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer()));
    if (!live_probe::
            StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer() ||
        !live_probe::
            StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer()) {
      diagnostics.push_back(
          "live Blink bridge is linked but does not expose the expected "
          "DummyPageHolder/LocalFrameView PaintArtifact path");
      return;
    }
    const int reached_paint_clean =
        live_probe::StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
            probe_html.c_str());
    const int chunk_count =
        live_probe::StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
            probe_html.c_str());
    const int display_item_count =
        live_probe::
            StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
                probe_html.c_str());
    const int exported_draw_op_count =
        live_probe::
            StandaloneBlinkLiveFrameBridgeExportedDrawOpCountForStandaloneRenderer(
                probe_html.c_str());
    diagnostics.push_back(
        "live Blink PaintArtifact probe: PaintClean=" +
        std::to_string(reached_paint_clean) + ", chunks=" +
        std::to_string(chunk_count) + ", display items=" +
        std::to_string(display_item_count) + ", exported draw ops=" +
        std::to_string(exported_draw_op_count));
    if (chunk_count > 0) {
      int x = 0;
      int y = 0;
      int width = 0;
      int height = 0;
      int begin = 0;
      int end = 0;
      int has_text = 0;
      if (live_probe::
              StandaloneBlinkLiveFrameBridgePaintChunkMetadataAtForStandaloneRenderer(
                  probe_html.c_str(), 0, &x, &y, &width, &height, &begin,
                  &end, &has_text)) {
        diagnostics.push_back(
            "live Blink PaintArtifact first chunk: bounds=(" +
            std::to_string(x) + "," + std::to_string(y) + " " +
            std::to_string(width) + "x" + std::to_string(height) +
            "), display item range=[" + std::to_string(begin) + "," +
            std::to_string(end) + "), has_text=" +
            std::to_string(has_text));
      }
    }
  }

  void TryReplaceWithLivePaintArtifactScene(
      RenderResult& result,
      const RendererSnapshot& previous_snapshot,
      bool incremental,
      const std::string& html,
      const std::vector<Stylesheet>& stylesheets) {
    namespace live_probe = ::blink::standalone_renderer_probe;
    const std::string probe_html = BuildLiveBlinkProbeHtml(html, stylesheets);
    live_probe::StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(
        static_cast<int>(result.successor_snapshot.viewport.width),
        static_cast<int>(result.successor_snapshot.viewport.height));
    if (!live_probe::
            StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer() ||
        !live_probe::
            StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer()) {
      return;
    }
    if (!live_probe::StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
            probe_html.c_str())) {
      result.diagnostics.push_back(
          "real Blink PaintArtifact bridge did not reach PaintClean");
      return;
    }

    const int chunk_count =
        live_probe::StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
            probe_html.c_str());
    const int raw_audit_json_size =
        live_probe::
            StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonSizeForStandaloneRenderer(
                probe_html.c_str());
    if (raw_audit_json_size > 0) {
      std::string raw_json(static_cast<size_t>(raw_audit_json_size) + 1, '\0');
      const int copied =
          live_probe::
              StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonForStandaloneRenderer(
                  probe_html.c_str(), raw_json.data(),
                  static_cast<int>(raw_json.size()));
      if (copied > 0) {
        raw_json.resize(static_cast<size_t>(copied));
        result.raw_paint_artifact_audit_json = std::move(raw_json);
      }
    }
    if (chunk_count <= 0) {
      result.diagnostics.push_back("real Blink PaintArtifact bridge produced no chunks");
      return;
    }
    const int exported_draw_op_count =
        live_probe::StandaloneBlinkLiveFrameBridgeExportedDrawOpCountForStandaloneRenderer(
            probe_html.c_str());
    if (exported_draw_op_count <= 0) {
      result.diagnostics.push_back(
          "real Blink PaintArtifact bridge produced no exported draw ops");
      return;
    }

    RetainedScene current_scene;
    DrawCommandList commands;
    DrawCommandList chunk_commands;
    DrawCommandList* active_commands = &commands;
    std::string active_chunk_key;
    Rect active_chunk_bounds;
    PaintPropertyStateSnapshot active_chunk_property_state;
    int active_chunk_debug_index = -1;
    bool inside_chunk = false;
    LoadCommandList load_commands;

    const int audit_line_count =
        live_probe::
            StandaloneBlinkLiveFrameBridgeArtifactAuditLineCountForStandaloneRenderer(
                probe_html.c_str());
    for (int i = 0; i < audit_line_count && i < 128; ++i) {
      std::array<char, 4096> line{};
      if (live_probe::
              StandaloneBlinkLiveFrameBridgeArtifactAuditLineAtForStandaloneRenderer(
                  probe_html.c_str(), i, line.data(),
                  static_cast<int>(line.size())) > 0) {
        result.diagnostics.push_back(line.data());
      }
    }
    int translated_command_count = 0;
    for (int i = 0; i < exported_draw_op_count; ++i) {
      int type = 0;
      float x = 0.0f;
      float y = 0.0f;
      float width = 0.0f;
      float height = 0.0f;
      float r = 0.0f;
      float g = 0.0f;
      float b = 0.0f;
      float a = 1.0f;
      float font_size = 0.0f;
      float radius_x = 0.0f;
      float radius_y = 0.0f;
      int glyph_count = 0;
      if (!live_probe::
              StandaloneBlinkLiveFrameBridgeExportedDrawOpAtForStandaloneRenderer(
                  probe_html.c_str(), i, &type, &x, &y, &width, &height, &r,
                  &g, &b, &a, &font_size, &radius_x, &radius_y,
                  &glyph_count)) {
        continue;
      }
      auto normalize_component = [](float value) {
        return value > 1.0f ? value / 255.0f : value;
      };
      const Color color =
          Color::Rgba(normalize_component(r), normalize_component(g),
                      normalize_component(b), normalize_component(a));
      if (type == 12) {
        if (inside_chunk) {
          current_scene.chunks.push_back(MakeRetainedPaintChunk(
              active_chunk_key, RetainedChunkKind::kDocument,
              active_chunk_bounds, active_chunk_property_state,
              std::move(chunk_commands)));
          current_scene.chunks.back().debug_index = active_chunk_debug_index;
          current_scene.chunks.back().stable_key = active_chunk_key;
          current_scene.chunks.back().chunk_id_string = active_chunk_key;
          chunk_commands.clear();
        }
        inside_chunk = true;
        const int chunk_index = static_cast<int>(font_size);
        active_chunk_debug_index = chunk_index;
        active_chunk_bounds = Rect{x, y, width, height};
        active_chunk_property_state = PaintPropertyStateSnapshot{};
        uint64_t property_state_hash = 0;
        std::array<float, 16> transform_to_root{};
        int has_clip_rect = 0;
        float clip_x = 0.0f;
        float clip_y = 0.0f;
        float clip_width = 0.0f;
        float clip_height = 0.0f;
        if (live_probe::
                StandaloneBlinkLiveFrameBridgePaintChunkPropertyStateAtForStandaloneRenderer(
                    probe_html.c_str(), chunk_index, &property_state_hash,
                    transform_to_root.data(), &has_clip_rect, &clip_x, &clip_y,
                    &clip_width, &clip_height)) {
          active_chunk_property_state.state_hash = property_state_hash;
          active_chunk_property_state.transform_to_root.values =
              transform_to_root;
          const bool identity_or_translation =
              transform_to_root[0] == 1.0f && transform_to_root[1] == 0.0f &&
              transform_to_root[4] == 0.0f && transform_to_root[5] == 1.0f;
          active_chunk_property_state.transform_is_2d = true;
          active_chunk_property_state.transform_has_perspective = false;
          active_chunk_property_state.transform_has_non_translation =
              !identity_or_translation;
          active_chunk_property_state.transform_node_id = property_state_hash;
          active_chunk_property_state.transform_chain_depth = 1;
          active_chunk_property_state.has_clip_rect = has_clip_rect != 0;
          active_chunk_property_state.clip_rect =
              Rect{clip_x, clip_y, clip_width, clip_height};
          active_chunk_property_state.clip_node_id =
              property_state_hash ^ 0x9e3779b97f4a7c15ull;
          active_chunk_property_state.clip_chain_depth =
              active_chunk_property_state.has_clip_rect ? 1u : 0u;
          active_chunk_property_state.effect_node_id =
              property_state_hash ^ 0xc2b2ae3d27d4eb4full;
          active_chunk_property_state.effect_chain_depth = 1;
        }
        active_chunk_key = "blink-chunk:fingerprint=chunk-" +
                           std::to_string(chunk_index) + "-state-" +
                           std::to_string(
                               active_chunk_property_state.state_hash) +
                           ":state=" +
                           std::to_string(
                               active_chunk_property_state.state_hash) +
                           ":debug-index=" + std::to_string(chunk_index);
        active_commands = &chunk_commands;
      } else if (type == 13) {
        if (inside_chunk) {
          current_scene.chunks.push_back(MakeRetainedPaintChunk(
              active_chunk_key, RetainedChunkKind::kDocument,
              active_chunk_bounds, active_chunk_property_state,
              std::move(chunk_commands)));
          current_scene.chunks.back().debug_index = active_chunk_debug_index;
          current_scene.chunks.back().stable_key = active_chunk_key;
          current_scene.chunks.back().chunk_id_string = active_chunk_key;
          chunk_commands.clear();
        }
        inside_chunk = false;
        active_chunk_key.clear();
        active_chunk_bounds = Rect{};
        active_chunk_property_state = PaintPropertyStateSnapshot{};
        active_chunk_debug_index = -1;
        active_commands = &commands;
      } else if (type == 1) {
        active_commands->push_back(
            DrawCommand::FillRect(Rect{x, y, width, height}, color));
        ++translated_command_count;
      } else if (type == 4) {
        active_commands->push_back(DrawCommand::StrokeRect(
            Rect{x, y, width, height}, color,
            font_size > 0.0f ? font_size : 1.0f));
        ++translated_command_count;
      } else if (type == 5) {
        active_commands->push_back(
            DrawCommand::FillRRect(Rect{x, y, width, height}, radius_x,
                                   radius_y, color));
        ++translated_command_count;
      } else if (type == 6) {
        active_commands->push_back(DrawCommand::StrokeRRect(
            Rect{x, y, width, height}, radius_x, radius_y, color,
            font_size > 0.0f ? font_size : 1.0f));
        ++translated_command_count;
      } else if (type == 7) {
        std::array<char, 128> debug_label{};
        live_probe::
            StandaloneBlinkLiveFrameBridgeExportedDebugLabelAtForStandaloneRenderer(
                probe_html.c_str(), i, debug_label.data(),
                static_cast<int>(debug_label.size()));
        std::string diagnostic =
            "diagnostic_bitmap_fallback fallback_rasterized=true "
            "fallback_reason=unsupported_retained_resource original_paint_op="
            "bitmap-backed source_chunk=" + active_chunk_key +
            " source_display_item=unknown op " + std::to_string(i);
        if (debug_label[0] != '\0') {
          diagnostic += " source=";
          diagnostic += debug_label.data();
        }
        result.diagnostics.push_back(std::move(diagnostic));
        int bitmap_width = 0;
        int bitmap_height = 0;
        int byte_count = 0;
        if (!live_probe::
                StandaloneBlinkLiveFrameBridgeExportedBitmapInfoAtForStandaloneRenderer(
                    probe_html.c_str(), i, &bitmap_width, &bitmap_height,
                    &byte_count) ||
            bitmap_width <= 0 || bitmap_height <= 0 || byte_count <= 0) {
          result.diagnostics.push_back(
              "real Blink PaintArtifact bitmap resource missing for op " +
              std::to_string(i));
          continue;
        }
        std::vector<uint8_t> rgba_pixels(static_cast<size_t>(byte_count));
        const int copied =
            live_probe::
                StandaloneBlinkLiveFrameBridgeExportedBitmapBytesAtForStandaloneRenderer(
                    probe_html.c_str(), i, rgba_pixels.data(), byte_count);
        if (copied != byte_count) {
          result.diagnostics.push_back(
              "real Blink PaintArtifact bitmap copy failed for op " +
              std::to_string(i));
          continue;
        }
        const uint64_t pixel_hash = HashBytes(rgba_pixels);
        ImageLoadInfo image;
        image.image_id =
            "blink-paint-bitmap-" + std::to_string(pixel_hash);
        image.resource_id = image.image_id;
        image.mime_type = "image/x-raw-rgba";
        image.decoded_format = PixelFormat::kRgba8888;
        image.decoded_size = Size{static_cast<float>(bitmap_width),
                                  static_cast<float>(bitmap_height)};
        image.decoded_pixels = std::move(rgba_pixels);
        image.byte_count = image.decoded_pixels.size();
        image.bytes_hash = pixel_hash;
        active_commands->push_back(
            DrawCommand::DrawImage(image.image_id, Rect{x, y, width, height}));
        load_commands.push_back(LoadCommand::LoadImage(std::move(image)));
        ++translated_command_count;
      } else if (type == 8) {
        active_commands->push_back(DrawCommand::Save());
        ++translated_command_count;
      } else if (type == 9) {
        active_commands->push_back(DrawCommand::Restore());
        ++translated_command_count;
      } else if (type == 10) {
        active_commands->push_back(
            DrawCommand::ClipRect(Rect{x, y, width, height}));
        ++translated_command_count;
      } else if (type == 15) {
        std::array<Point, 4> corner_radii = {
            Point{radius_x, radius_y},
            Point{radius_x, radius_y},
            Point{radius_x, radius_y},
            Point{radius_x, radius_y},
        };
        float top_left_x = 0.0f;
        float top_left_y = 0.0f;
        float top_right_x = 0.0f;
        float top_right_y = 0.0f;
        float bottom_right_x = 0.0f;
        float bottom_right_y = 0.0f;
        float bottom_left_x = 0.0f;
        float bottom_left_y = 0.0f;
        if (blink::standalone_renderer_probe::
                StandaloneBlinkLiveFrameBridgeExportedRRectRadiiAtForStandaloneRenderer(
                    probe_html.c_str(), static_cast<int>(i), &top_left_x,
                    &top_left_y, &top_right_x, &top_right_y, &bottom_right_x,
                    &bottom_right_y, &bottom_left_x, &bottom_left_y)) {
          corner_radii = {
              Point{top_left_x, top_left_y},
              Point{top_right_x, top_right_y},
              Point{bottom_right_x, bottom_right_y},
              Point{bottom_left_x, bottom_left_y},
          };
        }
        active_commands->push_back(
            DrawCommand::ClipRRect(Rect{x, y, width, height}, corner_radii,
                                   font_size > 0.5f));
        ++translated_command_count;
      } else if (type == 16) {
        active_commands->push_back(
            DrawCommand::SaveLayer(Rect{x, y, width, height}, font_size));
        ++translated_command_count;
      } else if (type == 17) {
        int byte_count = 0;
        if (live_probe::
                StandaloneBlinkLiveFrameBridgeExportedPathInfoAtForStandaloneRenderer(
                    probe_html.c_str(), i, &byte_count) &&
            byte_count > 0) {
          std::vector<uint8_t> path_bytes(static_cast<size_t>(byte_count));
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgeExportedPathBytesAtForStandaloneRenderer(
                      probe_html.c_str(), i, path_bytes.data(), byte_count) ==
              byte_count) {
            active_commands->push_back(
                DrawCommand::ClipPath(std::move(path_bytes),
                                      font_size > 0.5f));
            ++translated_command_count;
          }
        }
      } else if (type == 18) {
        int byte_count = 0;
        if (live_probe::
                StandaloneBlinkLiveFrameBridgeExportedTextBlobInfoAtForStandaloneRenderer(
                    probe_html.c_str(), i, &byte_count) &&
            byte_count > 0) {
          std::vector<uint8_t> blob_bytes(static_cast<size_t>(byte_count));
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgeExportedTextBlobBytesAtForStandaloneRenderer(
                      probe_html.c_str(), i, blob_bytes.data(), byte_count) ==
              byte_count) {
            active_commands->push_back(DrawCommand::DrawTextBlob(
                std::move(blob_bytes), Point{x, y}, color));
            ++translated_command_count;
          }
        }
      } else if (type == 19 || type == 20) {
        int byte_count = 0;
        if (live_probe::
                StandaloneBlinkLiveFrameBridgeExportedShaderInfoAtForStandaloneRenderer(
                    probe_html.c_str(), i, &byte_count) &&
            byte_count > 0) {
          std::vector<uint8_t> shader_bytes(static_cast<size_t>(byte_count));
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgeExportedShaderBytesAtForStandaloneRenderer(
                      probe_html.c_str(), i, shader_bytes.data(),
                      byte_count) == byte_count) {
            if (type == 19) {
              active_commands->push_back(DrawCommand::FillRectShader(
                  Rect{x, y, width, height}, std::move(shader_bytes), color));
            } else {
              active_commands->push_back(DrawCommand::FillRRectShader(
                  Rect{x, y, width, height}, radius_x, radius_y,
                  std::move(shader_bytes), color));
            }
            ++translated_command_count;
          }
        }
      } else if (type == 21) {
        int path_byte_count = 0;
        if (live_probe::
                StandaloneBlinkLiveFrameBridgeExportedPathInfoAtForStandaloneRenderer(
                    probe_html.c_str(), i, &path_byte_count) &&
            path_byte_count > 0) {
          std::vector<uint8_t> path_bytes(
              static_cast<size_t>(path_byte_count));
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgeExportedPathBytesAtForStandaloneRenderer(
                      probe_html.c_str(), i, path_bytes.data(),
                      path_byte_count) == path_byte_count) {
            std::vector<uint8_t> shader_bytes;
            int shader_byte_count = 0;
            if (live_probe::
                    StandaloneBlinkLiveFrameBridgeExportedShaderInfoAtForStandaloneRenderer(
                        probe_html.c_str(), i, &shader_byte_count) &&
                shader_byte_count > 0) {
              shader_bytes.resize(static_cast<size_t>(shader_byte_count));
              if (live_probe::
                      StandaloneBlinkLiveFrameBridgeExportedShaderBytesAtForStandaloneRenderer(
                          probe_html.c_str(), i, shader_bytes.data(),
                          shader_byte_count) != shader_byte_count) {
                shader_bytes.clear();
              }
            }
            active_commands->push_back(DrawCommand::FillPath(
                std::move(path_bytes), color,
                font_size > 0.0f ? font_size : 0.0f,
                std::move(shader_bytes)));
            active_commands->back().rect = Rect{x, y, width, height};
            ++translated_command_count;
          }
        }
      } else if (type == 11) {
        Matrix4 matrix;
        matrix.values[12] = x;
        matrix.values[13] = y;
        active_commands->push_back(DrawCommand::Transform(matrix));
        ++translated_command_count;
      } else if (type == 14) {
        Matrix4 matrix;
        matrix.values[0] = x;
        matrix.values[4] = y;
        matrix.values[12] = width;
        matrix.values[1] = height;
        matrix.values[5] = r;
        matrix.values[13] = g;
        active_commands->push_back(DrawCommand::Transform(matrix));
        ++translated_command_count;
      } else {
        result.diagnostics.push_back(
            "real Blink PaintArtifact unexpected non-oracle exported op type " +
            std::to_string(type));
      }
    }
    if (inside_chunk) {
      current_scene.chunks.push_back(MakeRetainedPaintChunk(
          active_chunk_key, RetainedChunkKind::kDocument, active_chunk_bounds,
          active_chunk_property_state, std::move(chunk_commands)));
      current_scene.chunks.back().debug_index = active_chunk_debug_index;
      current_scene.chunks.back().stable_key = active_chunk_key;
      current_scene.chunks.back().chunk_id_string = active_chunk_key;
      chunk_commands.clear();
      inside_chunk = false;
      active_commands = &commands;
    }
    if (translated_command_count == 0) {
      result.diagnostics.push_back(
          "real Blink PaintArtifact bridge produced no translated draw commands");
      return;
    }
    if (!commands.empty() || current_scene.chunks.empty()) {
      current_scene.chunks.push_back(MakeRetainedPaintChunk(
          "live-blink-paint-artifact", RetainedChunkKind::kDocument,
          DrawCommandListBounds(commands, result.successor_snapshot),
          std::move(commands)));
    }
    result.diagnostics.push_back(
        "retained Blink PaintChunk scene chunks=" +
        std::to_string(current_scene.chunks.size()));
    ApplyRetainedScenePlan(
        result, current_scene, load_commands,
        incremental && previous_retained_scene_ ? &*previous_retained_scene_
                                                : nullptr,
        previous_snapshot, SnapshotDocumentScrollOffset(result.successor_snapshot),
        SnapshotDocumentScrollOffset(previous_snapshot));
    previous_retained_scene_ = std::move(current_scene);
    result.diagnostics.push_back(
        "paint artifact source: real Blink PaintArtifact; "
        "extractor=real_blink_paint_artifact_extractor");
    result.diagnostics.push_back(
        "real Blink PaintArtifact exported through retained PaintOp commands");
  }

  RendererSnapshot snapshot_;
  std::optional<RetainedScene> previous_retained_scene_;
};
#endif

}  // namespace

BlinkRuntimeAdapterStatus InspectBlinkRuntimeAdapterStatus(
    const std::string& chromium_root,
    bool live_runtime_enabled) {
  BlinkRuntimeAdapterStatus status;
  status.live_runtime_enabled = live_runtime_enabled;
  status.required_replacements = RequiredBlinkBoundaryReplacements();
  status.required_shims = RequiredBlinkRuntimeShims();

  const fs::path root =
      chromium_root.empty() ? fs::current_path() : fs::path(chromium_root);
  for (const char* seed : kRuntimeSeedFiles) {
    status.seed_files.push_back(seed);
    if (!fs::exists(root / fs::path(seed))) {
      status.diagnostics.push_back(std::string("missing Blink runtime seed: ") +
                                   seed);
    }
  }

  for (const char* generated : kRequiredGeneratedFiles) {
    status.required_generated_files.push_back(generated);
    if (!fs::exists(root / fs::path(generated))) {
      status.missing_generated_files.push_back(generated);
    }
  }

  if (!status.missing_generated_files.empty()) {
    status.diagnostics.push_back(
        "live Blink runtime compile is blocked by missing generated GN/mojom/buildflag artifacts");
  }
  status.diagnostics.push_back(
      "DummyPageHolder currently crosses loader, URLLoaderMockFactory, Mojo, V8 header, and generated mojom boundaries");
  status.diagnostics.push_back(
      "standalone_live_frame_bridge_probe.cc pins the intended full-Blink path: "
      "DummyPageHolder -> Document body mutation -> "
      "LocalFrameView::UpdateAllLifecyclePhasesForTest -> "
      "LocalFrameView::GetPaintArtifact");
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_PLATFORM)
  status.diagnostics.push_back(
      "reduced Blink platform slice is linked: WTF strings, geometry, transforms, and paint property metadata");
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  status.diagnostics.push_back(
      "reduced Blink core slice is linked: Document, DocumentInit, HTMLDocument, generated style/name tables, and paint result types");
  status.diagnostics.push_back(ReducedBlinkCoreCSSDiagnostic());
  status.diagnostics.push_back(ReducedBlinkHTMLTokenizerDiagnostic(
      "<main><img src='asset.png'><p>Blink tree builder</p></main>"));
#endif
  status.diagnostics.push_back(
      "CreateLiveBlinkPageEmbedder can render through the reduced standalone lifecycle while full LocalFrame wiring remains blocked");
#else
  status.diagnostics.push_back(
      "reduced Blink platform slice is not linked into this adapter build");
#endif
  status.diagnostics.push_back(
      "next live step is replacing DummyPageHolder clients with standalone AssetProvider, null script, null browser-interface, and deterministic scheduler shims");

  BlinkRuntimeEnvironmentCreateInfo environment_info;
  environment_info.renderer.viewport = {800.0f, 600.0f};
  environment_info.snapshot.viewport = environment_info.renderer.viewport;
  BlinkRuntimeEnvironment environment(std::move(environment_info));
  const BlinkFrameIslandPlan frame_island_plan =
      environment.BuildFrameIslandPlan();
  status.diagnostics.insert(status.diagnostics.end(),
                            frame_island_plan.diagnostics.begin(),
                            frame_island_plan.diagnostics.end());
  status.diagnostics.push_back(
      "Blink frame island pending required step count: " +
      std::to_string(frame_island_plan.PendingRequiredStepCount()));

  int pending_required_shims = 0;
  for (const BlinkRuntimeShim& shim : status.required_shims) {
    if (shim.required_for_live_runtime && !shim.implemented) {
      ++pending_required_shims;
    }
  }
  if (pending_required_shims > 0) {
    status.diagnostics.push_back(
        "live Blink runtime compile is blocked by pending standalone runtime shims");
  }

  status.can_attempt_compile = live_runtime_enabled &&
                               status.missing_generated_files.empty() &&
                               pending_required_shims == 0 &&
                               !status.seed_files.empty();
  if (!live_runtime_enabled) {
    status.diagnostics.push_back(
        "live Blink runtime compile is opt-in; configure with HTML_CSS_RENDERER_ENABLE_LIVE_BLINK_RUNTIME once shims are ready");
  }
  return status;
}

std::unique_ptr<BlinkPageEmbedder> CreateLiveBlinkPageEmbedder(
    BlinkPageEmbedderCreateInfo create_info) {
#if defined(HTML_CSS_RENDERER_HAS_LIVE_BLINK_RUNTIME)
  return std::make_unique<LiveBlinkPageEmbedder>(std::move(create_info));
#else
  return CreateNoOpBlinkPageEmbedder(std::move(create_info));
#endif
}

}  // namespace html_css_renderer
