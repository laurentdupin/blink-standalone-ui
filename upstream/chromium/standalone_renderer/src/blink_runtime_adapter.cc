#include "html_css_renderer/blink_adapter.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <iterator>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "html_css_renderer/blink_runtime_environment.h"
#include "html_css_renderer/render_policy.h"
#include "html_css_renderer/retained_scene.h"
#include "html_css_renderer/typeface_resource_registry.h"
#include "html_css_renderer/blink_tree_bridge_probe.h"
#include "incremental_damage.h"

namespace blink::standalone_renderer_probe {
void StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(int width,
                                                                    int height);
void StandaloneBlinkLiveFrameBridgeSetDocumentScrollOffsetForStandaloneRenderer(
    float x,
    float y);
void StandaloneBlinkLiveFrameBridgeSetElementScrollOffsetsForStandaloneRenderer(
    const char* serialized_offsets);
void StandaloneBlinkLiveFrameBridgeSetAnimationTimeForStandaloneRenderer(
    double time_ms);
void StandaloneBlinkLiveFrameBridgeSetElementAttributesForStandaloneRenderer(
    const char* serialized_attributes);
void StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
    const char* hovered_element_id,
    const char* active_element_id);
void StandaloneBlinkLiveFrameBridgeSetPointerStateForStandaloneRenderer(
    float x,
    float y,
    int pressed,
    int event_type,
    int requested);
int StandaloneBlinkLiveFrameBridgePointerObservedStateForStandaloneRenderer(
    const char* body_html,
    char* hovered_element_id,
    int hovered_element_id_capacity,
    char* active_element_id,
    int active_element_id_capacity);
void StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
    float x,
    float y,
    float delta_x,
    float delta_y,
    int requested);
void StandaloneBlinkLiveFrameBridgeSetDisableRetainedExtractionForStandaloneRenderer(
    int disabled);
void StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetForceOracleBitmapForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
    const char* lifecycle_stop);
int StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer();
void StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeNeedsBeginFrameForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeDocumentScrollOffsetForStandaloneRenderer(
    const char* body_html,
    float* x,
    float* y,
    float* max_x,
    float* max_y);
int StandaloneBlinkLiveFrameBridgeHitTestEntryCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeHitTestEntryAtForStandaloneRenderer(
    const char* body_html,
    int index,
    char* element_id,
    int element_id_capacity,
    float* x,
    float* y,
    float* width,
    float* height);
int StandaloneBlinkLiveFrameBridgeScrollableElementEntryCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeScrollableElementEntryAtForStandaloneRenderer(
    const char* body_html,
    int index,
    char* element_id,
    int element_id_capacity,
    float* x,
    float* y,
    float* width,
    float* height,
    float* scroll_x,
    float* scroll_y,
    float* max_scroll_x,
    float* max_scroll_y,
    int* can_scroll_x,
    int* can_scroll_y);
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
int StandaloneBlinkLiveFrameBridgePaintChunkDrawableBoundsAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* x,
    int* y,
    int* width,
    int* height);
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
int StandaloneBlinkLiveFrameBridgeChunkStableKeyAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    char* buffer,
    int buffer_size);
int StandaloneBlinkLiveFrameBridgeChunkIdStringAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    char* buffer,
    int buffer_size);
int StandaloneBlinkLiveFrameBridgeFinerCacheUnitCountForStandaloneRenderer(
    const char* body_html,
    int chunk_index);
int StandaloneBlinkLiveFrameBridgeFinerCacheUnitAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int unit_index,
    int* exported_unit_index,
    int* begin_display_item_index,
    int* end_display_item_index,
    uint64_t* display_item_client_id,
    int* display_item_client_id_valid,
    float* visual_x,
    float* visual_y,
    float* visual_width,
    float* visual_height,
    uint64_t* content_hash,
    uint64_t* resource_signal_hash,
    int* display_item_count,
    int* drawing_item_count,
    int* paint_op_count,
    int* recursive_paint_op_count,
    int* visual_op_count,
    int* conservative_candidate,
    int* has_save_layer_ops,
    int* has_non_rect_clip_ops,
    int* has_non_translation_transform,
    int* has_effect_opacity,
    int* has_shader_ops,
    int* has_image_ops,
    int* has_path_ops,
    int* has_filter_ops,
    int* has_path_effect_ops,
    char* stable_key_buffer,
    int stable_key_buffer_size);
int StandaloneBlinkLiveFrameBridgePaintChunkPropertyMetadataAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    uint64_t* transform_node_id,
    uint64_t* transform_parent_id,
    uint32_t* transform_chain_depth,
    uint64_t* scroll_node_id,
    uint32_t* clip_chain_depth,
    uint32_t* effect_chain_depth,
    uint64_t* effect_node_id,
    uint64_t* effect_parent_id,
    float* effect_opacity,
    int* effect_has_non_default_opacity,
    int* effect_has_filter,
    int* effect_has_backdrop_filter,
    int* effect_has_blend_mode,
    int* effect_blend_mode,
    uint64_t* effect_output_clip_id);
int StandaloneBlinkLiveFrameBridgePaintChunkFilterOperationCountForStandaloneRenderer(
    const char* body_html,
    int chunk_index);
int StandaloneBlinkLiveFrameBridgePaintChunkHasUnsupportedFilterForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* has_unsupported_filter);
int StandaloneBlinkLiveFrameBridgePaintChunkFilterOperationAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int operation_index,
    int* type,
    float* amount,
    float* offset_x,
    float* offset_y,
    float* color_r,
    float* color_g,
    float* color_b,
    float* color_a,
    float* matrix20);
int StandaloneBlinkLiveFrameBridgePaintChunkRoundedClipAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* has_rounded_clip,
    float* clip_x,
    float* clip_y,
    float* clip_width,
    float* clip_height,
    float* top_left_x,
    float* top_left_y,
    float* top_right_x,
    float* top_right_y,
    float* bottom_right_x,
    float* bottom_right_y,
    float* bottom_left_x,
    float* bottom_left_y);
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
    int* stroke_cap,
    int* stroke_join,
    float* stroke_miter,
    float* radius_x,
    float* radius_y,
    int* glyph_count);
int StandaloneBlinkLiveFrameBridgeExportedDrawOpSourceAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* source_chunk_index,
    int* source_display_item_index,
    uint64_t* source_display_item_client_id,
    int* source_display_item_client_id_valid);
int StandaloneBlinkLiveFrameBridgeExportedGlyphAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int glyph_index,
    uint32_t* glyph_id,
    float* x,
    float* y);
int StandaloneBlinkLiveFrameBridgeExportedDrawLooperLayerCountForStandaloneRenderer(
    const char* body_html,
    int op_index);
int StandaloneBlinkLiveFrameBridgeExportedDrawLooperLayerAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int layer_index,
    float* offset_x,
    float* offset_y,
    float* blur_sigma,
    float* r,
    float* g,
    float* b,
    float* a,
    uint32_t* flags);
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
int StandaloneBlinkLiveFrameBridgeExportedPathEffectInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count);
int StandaloneBlinkLiveFrameBridgeExportedPathEffectBytesAtForStandaloneRenderer(
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
int StandaloneBlinkLiveFrameBridgeExportedSaveLayerBoundsUnsetAtForStandaloneRenderer(
    const char* body_html,
    int op_index);
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
int StandaloneBlinkLiveFrameBridgeExportedImageSourceRectAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    float* src_x,
    float* src_y,
    float* src_width,
    float* src_height);
int StandaloneBlinkLiveFrameBridgeExportedImageSamplingOptionsAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    char* buffer,
    int buffer_size);
}  // namespace blink::standalone_renderer_probe

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
namespace blink_tree_probe = ::blink::standalone_renderer_probe;

std::optional<FilterOperationKind> FilterOperationKindFromBridgeType(int type) {
  switch (type) {
    case 0:
      return FilterOperationKind::kGrayscale;
    case 1:
      return FilterOperationKind::kSepia;
    case 2:
      return FilterOperationKind::kSaturate;
    case 3:
      return FilterOperationKind::kHueRotate;
    case 4:
      return FilterOperationKind::kInvert;
    case 5:
      return FilterOperationKind::kBrightness;
    case 6:
      return FilterOperationKind::kContrast;
    case 7:
      return FilterOperationKind::kOpacity;
    case 8:
      return FilterOperationKind::kBlur;
    case 9:
      return FilterOperationKind::kDropShadow;
    case 10:
      return FilterOperationKind::kColorMatrix;
    default:
      return std::nullopt;
  }
}

void PopulateFilterOperationsFromLiveProbe(
    const std::string& probe_html,
    int chunk_index,
    PaintPropertyStateSnapshot& property_state) {
  int has_unsupported_filter = 0;
  if (::blink::standalone_renderer_probe::
          StandaloneBlinkLiveFrameBridgePaintChunkHasUnsupportedFilterForStandaloneRenderer(
              probe_html.c_str(), chunk_index, &has_unsupported_filter)) {
    property_state.effect_has_unsupported_filter =
        has_unsupported_filter != 0;
  }

  const int operation_count = ::blink::standalone_renderer_probe::
      StandaloneBlinkLiveFrameBridgePaintChunkFilterOperationCountForStandaloneRenderer(
          probe_html.c_str(), chunk_index);
  property_state.effect_filter_operations.clear();
  property_state.effect_filter_operations.reserve(
      static_cast<size_t>(std::max(0, operation_count)));
  for (int operation_index = 0; operation_index < operation_count;
       ++operation_index) {
    int bridge_type = 0;
    float amount = 0.0f;
    float offset_x = 0.0f;
    float offset_y = 0.0f;
    float color_r = 0.0f;
    float color_g = 0.0f;
    float color_b = 0.0f;
    float color_a = 1.0f;
    std::array<float, 20> matrix{};
    if (!::blink::standalone_renderer_probe::
            StandaloneBlinkLiveFrameBridgePaintChunkFilterOperationAtForStandaloneRenderer(
                probe_html.c_str(), chunk_index, operation_index, &bridge_type,
                &amount, &offset_x, &offset_y, &color_r, &color_g, &color_b,
                &color_a, matrix.data())) {
      property_state.effect_has_unsupported_filter = true;
      continue;
    }
    std::optional<FilterOperationKind> kind =
        FilterOperationKindFromBridgeType(bridge_type);
    if (!kind) {
      property_state.effect_has_unsupported_filter = true;
      continue;
    }
    FilterOperationSnapshot operation;
    operation.kind = *kind;
    operation.amount = amount;
    operation.offset = Point{offset_x, offset_y};
    operation.color = Color::Rgba(color_r, color_g, color_b, color_a);
    operation.matrix = matrix;
    property_state.effect_filter_operations.push_back(operation);
  }
}

std::vector<FinerCacheUnitDescriptor> ImportFinerCacheUnitDescriptors(
    const std::string& probe_html,
    int chunk_index,
    const std::string& chunk_stable_key) {
  const int unit_count = ::blink::standalone_renderer_probe::
      StandaloneBlinkLiveFrameBridgeFinerCacheUnitCountForStandaloneRenderer(
          probe_html.c_str(), chunk_index);
  std::vector<FinerCacheUnitDescriptor> descriptors;
  descriptors.reserve(static_cast<size_t>(std::max(0, unit_count)));
  for (int unit_probe_index = 0; unit_probe_index < unit_count;
       ++unit_probe_index) {
    FinerCacheUnitDescriptor descriptor;
    uint64_t client_id = 0;
    uint64_t content_hash = 0;
    uint64_t resource_signal_hash = 0;
    int client_id_valid = 0;
    int conservative_candidate = 0;
    int has_save_layer_ops = 0;
    int has_non_rect_clip_ops = 0;
    int has_non_translation_transform = 0;
    int has_effect_opacity = 0;
    int has_shader_ops = 0;
    int has_image_ops = 0;
    int has_path_ops = 0;
    int has_filter_ops = 0;
    int has_path_effect_ops = 0;
    float visual_x = 0.0f;
    float visual_y = 0.0f;
    float visual_width = 0.0f;
    float visual_height = 0.0f;
    std::array<char, 1024> stable_key_buffer{};
    if (!::blink::standalone_renderer_probe::
            StandaloneBlinkLiveFrameBridgeFinerCacheUnitAtForStandaloneRenderer(
                probe_html.c_str(), chunk_index, unit_probe_index,
                &descriptor.unit_index,
                &descriptor.begin_display_item_index,
                &descriptor.end_display_item_index, &client_id,
                &client_id_valid, &visual_x, &visual_y, &visual_width,
                &visual_height, &content_hash, &resource_signal_hash,
                &descriptor.display_item_count, &descriptor.drawing_item_count,
                &descriptor.paint_op_count,
                &descriptor.recursive_paint_op_count,
                &descriptor.visual_op_count, &conservative_candidate,
                &has_save_layer_ops, &has_non_rect_clip_ops,
                &has_non_translation_transform, &has_effect_opacity,
                &has_shader_ops, &has_image_ops, &has_path_ops,
                &has_filter_ops, &has_path_effect_ops,
                stable_key_buffer.data(),
                static_cast<int>(stable_key_buffer.size()))) {
      continue;
    }
    descriptor.parent_chunk_debug_index = chunk_index;
    descriptor.parent_chunk_stable_key = chunk_stable_key;
    descriptor.display_item_client_id = client_id;
    descriptor.display_item_client_id_valid = client_id_valid != 0;
    descriptor.visual_bounds =
        Rect{visual_x, visual_y, visual_width, visual_height};
    descriptor.content_hash = content_hash;
    descriptor.resource_signal_hash = resource_signal_hash;
    descriptor.conservative_candidate = conservative_candidate != 0;
    descriptor.has_save_layer_ops = has_save_layer_ops != 0;
    descriptor.has_non_rect_clip_ops = has_non_rect_clip_ops != 0;
    descriptor.has_non_translation_transform =
        has_non_translation_transform != 0;
    descriptor.has_effect_opacity = has_effect_opacity != 0;
    descriptor.has_shader_ops = has_shader_ops != 0;
    descriptor.has_image_ops = has_image_ops != 0;
    descriptor.has_path_ops = has_path_ops != 0;
    descriptor.has_filter_ops = has_filter_ops != 0;
    descriptor.has_path_effect_ops = has_path_effect_ops != 0;
    descriptor.stable_key = stable_key_buffer[0] != '\0'
                                ? std::string(stable_key_buffer.data())
                                : chunk_stable_key + ":unit=" +
                                      std::to_string(descriptor.unit_index);
    descriptors.push_back(std::move(descriptor));
  }
  return descriptors;
}

FinerCacheUnitDescriptor* FindFinerCacheUnitForDisplayItem(
    std::vector<FinerCacheUnitDescriptor>& descriptors,
    int chunk_index,
    int display_item_index) {
  if (chunk_index < 0 || display_item_index < 0) {
    return nullptr;
  }
  for (FinerCacheUnitDescriptor& descriptor : descriptors) {
    if (descriptor.parent_chunk_debug_index != chunk_index) {
      continue;
    }
    if (descriptor.begin_display_item_index <= display_item_index &&
        display_item_index < descriptor.end_display_item_index) {
      return &descriptor;
    }
  }
  return nullptr;
}

void RecordFinerCacheUnitCommandSpan(FinerCacheUnitDescriptor& descriptor,
                                     size_t translated_command_index) {
  const int index = static_cast<int>(translated_command_index);
  if (!descriptor.translated_command_span_available ||
      descriptor.translated_command_begin_index < 0 ||
      index < descriptor.translated_command_begin_index) {
    descriptor.translated_command_begin_index = index;
  }
  if (!descriptor.translated_command_span_available ||
      descriptor.translated_command_end_index < index + 1) {
    descriptor.translated_command_end_index = index + 1;
  }
  descriptor.translated_command_span_available = true;
}

void AnnotateTranslatedCommandsFromSource(
    DrawCommandList& commands,
    size_t begin_index,
    int source_chunk_index,
    int source_display_item_index,
    uint64_t source_display_item_client_id,
    bool source_display_item_client_id_valid,
    std::vector<FinerCacheUnitDescriptor>& descriptors) {
  if (source_chunk_index < 0 || source_display_item_index < 0 ||
      begin_index >= commands.size()) {
    return;
  }
  FinerCacheUnitDescriptor* descriptor =
      FindFinerCacheUnitForDisplayItem(descriptors, source_chunk_index,
                                       source_display_item_index);
  for (size_t command_index = begin_index; command_index < commands.size();
       ++command_index) {
    DrawCommand& command = commands[command_index];
    command.source.available = true;
    command.source.chunk_debug_index = source_chunk_index;
    command.source.display_item_index = source_display_item_index;
    command.source.display_item_client_id = source_display_item_client_id;
    command.source.display_item_client_id_valid =
        source_display_item_client_id_valid;
    command.source.translated_command_index =
        static_cast<int>(command_index);
    if (descriptor) {
      command.source.finer_cache_unit_index = descriptor->unit_index;
      command.source.finer_cache_unit_stable_key = descriptor->stable_key;
      RecordFinerCacheUnitCommandSpan(*descriptor, command_index);
    }
  }
}

int EntryLocalSaveDepthForCommandSpan(const DrawCommandList& commands,
                                      int begin_index) {
  if (begin_index <= 0) {
    return 0;
  }
  int save_depth = 0;
  const size_t limit = std::min(commands.size(),
                                static_cast<size_t>(begin_index));
  for (size_t command_index = 0; command_index < limit; ++command_index) {
    switch (commands[command_index].type) {
      case DrawCommandType::kSave:
      case DrawCommandType::kSaveLayer:
        ++save_depth;
        break;
      case DrawCommandType::kRestore:
        if (save_depth > 0) {
          --save_depth;
        }
        break;
      default:
        break;
    }
  }
  return save_depth;
}

void PopulateFinerCacheUnitEntryStateSummaries(
    std::vector<FinerCacheUnitDescriptor>& descriptors,
    const DrawCommandList& commands) {
  for (FinerCacheUnitDescriptor& descriptor : descriptors) {
    if (!descriptor.translated_command_span_available ||
        descriptor.translated_command_begin_index < 0) {
      descriptor.entry_state_status =
          "unavailable_no_translated_command_span";
      continue;
    }
    descriptor.entry_local_save_depth_available = true;
    descriptor.entry_local_save_depth =
        EntryLocalSaveDepthForCommandSpan(commands,
                                          descriptor.translated_command_begin_index);
    descriptor.entry_clip_bounds_available = false;
    descriptor.entry_transform_available = false;
    descriptor.entry_effect_layer_depth_available = false;
    descriptor.entry_state_status =
        "partial_local_save_depth_only_canvas_clip_transform_unavailable";
  }
}

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

float ScrollClipEdgeDamageThickness(const RetainedScene& scene) {
  float thickness = 0.0f;
  for (const RetainedPaintChunk& chunk : scene.chunks) {
    if (chunk.property_state.clip_has_rounded_clip ||
        chunk.property_state.clip_has_path_clip) {
      thickness = std::max(thickness, 4.0f);
    }
    for (const DrawCommand& command : chunk.commands) {
      switch (command.type) {
        case DrawCommandType::kClipRRect:
        case DrawCommandType::kClipPath:
        case DrawCommandType::kFillRRect:
        case DrawCommandType::kFillRRectShader:
          thickness = std::max(thickness, 2.0f);
          break;
        case DrawCommandType::kStrokeRRect:
          thickness = std::max(thickness, command.stroke_width);
          break;
        case DrawCommandType::kFillPath:
          thickness = std::max(thickness, std::max(command.stroke_width, 2.0f));
          break;
        default:
          break;
      }
    }
  }
  return std::min(std::ceil(thickness), 32.0f);
}

void AppendDamageRect(RenderResult& result, Rect damage) {
  if (damage.width <= 0.0f || damage.height <= 0.0f) {
    return;
  }
  result.damage_rects.push_back(damage);
  result.damage_bounds = UnionRectBounds(result.damage_bounds, damage);
  result.frame.damage_rects = result.damage_rects;
  result.frame.damage_bounds = result.damage_bounds;
}

void AddScrollClipEdgeDamage(RenderResult& result,
                             const RetainedScene& scene,
                             Point current_scroll_offset,
                             Point previous_scroll_offset) {
  const float thickness = ScrollClipEdgeDamageThickness(scene);
  if (thickness <= 0.0f) {
    return;
  }
  const Size viewport = result.successor_snapshot.viewport;
  const float delta_x = current_scroll_offset.x - previous_scroll_offset.x;
  const float delta_y = current_scroll_offset.y - previous_scroll_offset.y;
  if (std::abs(delta_y) > 0.0f) {
    const float height = std::min(thickness, viewport.height);
    AppendDamageRect(result,
                     delta_y > 0.0f
                         ? Rect{0.0f, 0.0f, viewport.width, height}
                         : Rect{0.0f, viewport.height - height,
                                viewport.width, height});
  }
  if (std::abs(delta_x) > 0.0f) {
    const float width = std::min(thickness, viewport.width);
    AppendDamageRect(result,
                     delta_x > 0.0f
                         ? Rect{0.0f, 0.0f, width, viewport.height}
                         : Rect{viewport.width - width, 0.0f,
                                width, viewport.height});
  }
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

void SetSnapshotDocumentScrollOffset(RendererSnapshot& snapshot,
                                     Point scroll_offset) {
  snapshot.scroll_offsets_by_element_id["document"] = scroll_offset;
}

std::string SerializeElementScrollOffsetsForStandaloneRenderer(
    const std::unordered_map<std::string, Point>& scroll_offsets) {
  std::vector<std::pair<std::string, Point>> ordered;
  ordered.reserve(scroll_offsets.size());
  for (const auto& [key, value] : scroll_offsets) {
    if (key == "document" || key == "body") {
      continue;
    }
    ordered.push_back({key, value});
  }
  std::sort(ordered.begin(), ordered.end(),
            [](const auto& lhs, const auto& rhs) {
              return lhs.first < rhs.first;
            });
  std::ostringstream out;
  for (const auto& [key, value] : ordered) {
    out << key << "=" << value.x << "," << value.y << "\n";
  }
  return out.str();
}

std::string SerializeElementAttributesForStandaloneRenderer(
    const std::unordered_map<std::string, std::string>& attributes) {
  std::vector<std::pair<std::string, std::string>> ordered(attributes.begin(),
                                                            attributes.end());
  std::sort(ordered.begin(), ordered.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });
  std::ostringstream out;
  for (const auto& [key, value] : ordered) {
    out << key << "=" << value << "\n";
  }
  return out.str();
}

void ImportLiveHitTestEntriesForStandaloneRenderer(
    const std::string& probe_html,
    RenderResult& result) {
  namespace live_probe = ::blink::standalone_renderer_probe;
  result.hit_test_entries.clear();
  const int entry_count =
      live_probe::StandaloneBlinkLiveFrameBridgeHitTestEntryCountForStandaloneRenderer(
          probe_html.c_str());
  for (int i = 0; i < entry_count && i < 4096; ++i) {
    std::array<char, 256> element_id{};
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    if (!live_probe::StandaloneBlinkLiveFrameBridgeHitTestEntryAtForStandaloneRenderer(
            probe_html.c_str(), i, element_id.data(),
            static_cast<int>(element_id.size()), &x, &y, &width, &height)) {
      continue;
    }
    const size_t id_length = std::char_traits<char>::length(element_id.data());
    if (id_length == 0 || width <= 0.0f || height <= 0.0f) {
      continue;
    }
    result.hit_test_entries.push_back(
        {std::string(element_id.data(), id_length), Rect{x, y, width, height}});
  }
}

void ImportLiveScrollableElementEntriesForStandaloneRenderer(
    const std::string& probe_html,
    RenderResult& result) {
  namespace live_probe = ::blink::standalone_renderer_probe;
  result.scrollable_element_entries.clear();
  const int entry_count =
      live_probe::
          StandaloneBlinkLiveFrameBridgeScrollableElementEntryCountForStandaloneRenderer(
              probe_html.c_str());
  for (int i = 0; i < entry_count && i < 512; ++i) {
    std::array<char, 256> element_id{};
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float scroll_x = 0.0f;
    float scroll_y = 0.0f;
    float max_scroll_x = 0.0f;
    float max_scroll_y = 0.0f;
    int can_scroll_x = 0;
    int can_scroll_y = 0;
    if (!live_probe::
            StandaloneBlinkLiveFrameBridgeScrollableElementEntryAtForStandaloneRenderer(
                probe_html.c_str(), i, element_id.data(),
                static_cast<int>(element_id.size()), &x, &y, &width, &height,
                &scroll_x, &scroll_y, &max_scroll_x, &max_scroll_y,
                &can_scroll_x, &can_scroll_y)) {
      continue;
    }
    const size_t id_length = std::char_traits<char>::length(element_id.data());
    if (id_length == 0 || width <= 0.0f || height <= 0.0f ||
        (!can_scroll_x && !can_scroll_y)) {
      continue;
    }
    result.scrollable_element_entries.push_back(
        {std::string(element_id.data(), id_length),
         Rect{x, y, width, height},
         Point{scroll_x, scroll_y},
         Point{max_scroll_x, max_scroll_y},
         can_scroll_x != 0,
         can_scroll_y != 0});
  }
}

void PersistObservedScrollableElementOffsetsForStandaloneRenderer(
    RenderResult& result) {
  for (const ScrollableElementEntry& entry :
       result.scrollable_element_entries) {
    if (entry.element_id.empty() || entry.element_id == "document" ||
        entry.element_id == "body") {
      continue;
    }
    const bool offset_is_nonzero =
        std::abs(entry.scroll_offset.x) > 0.001f ||
        std::abs(entry.scroll_offset.y) > 0.001f;
    const bool already_tracked =
        result.successor_snapshot.scroll_offsets_by_element_id.find(
            entry.element_id) !=
        result.successor_snapshot.scroll_offsets_by_element_id.end();
    if (!offset_is_nonzero && !already_tracked) {
      continue;
    }
    result.successor_snapshot.scroll_offsets_by_element_id[entry.element_id] =
        entry.scroll_offset;
  }
}

void ApplyRetainedScenePlan(RenderResult& result,
                            const RetainedScene& current_scene,
                            const LoadCommandList& load_commands,
                            const RetainedScene* previous_scene,
                            const RendererSnapshot& previous_snapshot,
                            Point current_scroll_offset,
                            Point previous_scroll_offset,
                            bool force_full_redraw_for_active_animation_change =
                                false) {
  PresentationUpdatePlan plan = PlanPresentationUpdate(
      current_scene, previous_scene, result.successor_snapshot.viewport,
      current_scroll_offset, previous_scroll_offset);
  if (force_full_redraw_for_active_animation_change &&
      !plan.requires_full_redraw) {
    plan.requires_full_redraw = true;
    plan.allows_scroll_translation_reuse = false;
    plan.scroll_translation_delta = Point{};
    plan.scroll_exposed_rects.clear();
    plan.dirty_rects.clear();
    plan.dirty_rects.push_back(plan.viewport_bounds);
    result.diagnostics.push_back(
        "disabled retained partial presentation because Blink requested "
        "another begin frame while viewport or scroll state changed");
  }
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
      !SameStringMap(previous_snapshot.element_attributes_by_id_and_name,
                     result.successor_snapshot.element_attributes_by_id_and_name)) {
    ApplyIncrementalDamage(previous_snapshot, result,
                           "reduced Blink retained attribute incremental render");
  } else if (!plan.requires_full_redraw && plan.dirty_rects.empty() &&
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
  if (!blink_tree_probe::
          StandaloneBlinkRealPaintBridgeSurfaceReachableForStandaloneRenderer()) {
    return "real Blink paint bridge surface is not linked";
  }
  return blink_tree_probe::
                 StandaloneBlinkRealPaintBridgeRequiresPaintCleanForStandaloneRenderer()
             ? "real Blink paint bridge contract selected: "
               "LocalFrameView::GetPaintArtifact after PaintClean lifecycle"
             : "real Blink paint bridge contract selected";
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

std::string LowerAscii(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return value;
}

std::string TrimAscii(std::string value) {
  const auto first = std::find_if_not(value.begin(), value.end(),
                                      [](unsigned char c) {
                                        return std::isspace(c) != 0;
                                      });
  const auto last = std::find_if_not(value.rbegin(), value.rend(),
                                     [](unsigned char c) {
                                       return std::isspace(c) != 0;
                                     }).base();
  if (first >= last) {
    return {};
  }
  return std::string(first, last);
}

std::vector<std::string> SplitSelectors(std::string selector_text) {
  std::vector<std::string> selectors;
  size_t start = 0;
  while (start < selector_text.size()) {
    const size_t comma = selector_text.find(',', start);
    selectors.push_back(TrimAscii(selector_text.substr(
        start, comma == std::string::npos ? std::string::npos : comma - start)));
    if (comma == std::string::npos) {
      break;
    }
    start = comma + 1;
  }
  return selectors;
}

bool HtmlContainsClassToken(const std::string& html, const std::string& token) {
  size_t class_pos = 0;
  while ((class_pos = html.find("class", class_pos)) != std::string::npos) {
    const size_t equals = html.find('=', class_pos + 5);
    if (equals == std::string::npos) {
      break;
    }
    const size_t value_start = html.find_first_not_of(" \t\r\n", equals + 1);
    if (value_start == std::string::npos) {
      break;
    }
    const char quote = html[value_start];
    size_t value_end = std::string::npos;
    size_t content_start = value_start;
    if (quote == '"' || quote == '\'') {
      content_start = value_start + 1;
      value_end = html.find(quote, content_start);
    } else {
      value_end = html.find_first_of(" \t\r\n>", content_start);
    }
    if (value_end == std::string::npos) {
      value_end = html.size();
    }
    const std::string classes = html.substr(content_start,
                                           value_end - content_start);
    size_t token_pos = 0;
    while ((token_pos = classes.find(token, token_pos)) != std::string::npos) {
      const bool left_ok =
          token_pos == 0 ||
          std::isspace(static_cast<unsigned char>(classes[token_pos - 1]));
      const size_t token_end = token_pos + token.size();
      const bool right_ok =
          token_end >= classes.size() ||
          std::isspace(static_cast<unsigned char>(classes[token_end]));
      if (left_ok && right_ok) {
        return true;
      }
      token_pos = token_end;
    }
    class_pos = value_end;
  }
  return false;
}

bool HtmlContainsIdToken(const std::string& html, const std::string& token) {
  return html.find("id=\"" + token + "\"") != std::string::npos ||
         html.find("id='" + token + "'") != std::string::npos ||
         html.find("id=" + token) != std::string::npos;
}

bool SelectorMayMatchHtml(const std::string& selector,
                          const std::string& html) {
  if (selector.empty() || selector.find('@') != std::string::npos) {
    return true;
  }
  bool saw_specific_token = false;
  for (size_t i = 0; i + 1 < selector.size(); ++i) {
    if (selector[i] != '.' && selector[i] != '#') {
      continue;
    }
    const char prefix = selector[i];
    size_t end = i + 1;
    while (end < selector.size() &&
           (std::isalnum(static_cast<unsigned char>(selector[end])) ||
            selector[end] == '_' || selector[end] == '-')) {
      ++end;
    }
    if (end == i + 1) {
      continue;
    }
    saw_specific_token = true;
    const std::string token = selector.substr(i + 1, end - i - 1);
    if (prefix == '#' && HtmlContainsIdToken(html, token)) {
      return true;
    }
    if (prefix == '.' && HtmlContainsClassToken(html, token)) {
      return true;
    }
    i = end - 1;
  }
  if (saw_specific_token) {
    return false;
  }
  size_t start = 0;
  while (start < selector.size() &&
         !std::isalpha(static_cast<unsigned char>(selector[start]))) {
    ++start;
  }
  size_t end = start;
  while (end < selector.size() &&
         (std::isalnum(static_cast<unsigned char>(selector[end])) ||
          selector[end] == '-')) {
    ++end;
  }
  if (end == start) {
    return true;
  }
  const std::string tag = selector.substr(start, end - start);
  return tag == "html" || tag == "body" ||
         html.find("<" + tag) != std::string::npos;
}

struct ScrollLifecycleSourceSummary {
  int fixed_rule_count = 0;
  int sticky_rule_count = 0;
  int active_sticky_rule_count = 0;
  int filter_rule_count = 0;
  int clip_or_mask_rule_count = 0;
  int overflow_scroll_rule_count = 0;
  std::vector<std::string> active_sticky_selectors;
};

bool DeclarationHasPropertyValue(const std::string& declarations,
                                 const std::string& property,
                                 const std::string& value) {
  const size_t property_pos = declarations.find(property);
  if (property_pos == std::string::npos) {
    return false;
  }
  const size_t value_pos = declarations.find(value, property_pos);
  if (value_pos == std::string::npos) {
    return false;
  }
  const size_t semicolon = declarations.find(';', property_pos);
  return semicolon == std::string::npos || value_pos < semicolon;
}

ScrollLifecycleSourceSummary SummarizeScrollLifecycleSource(
    const std::string& html,
    const std::vector<Stylesheet>& stylesheets) {
  const std::string lower_html = LowerAscii(html);
  ScrollLifecycleSourceSummary summary;
  if (lower_html.find("position: sticky") != std::string::npos ||
      lower_html.find("position:sticky") != std::string::npos) {
    summary.active_sticky_rule_count++;
    summary.active_sticky_selectors.push_back("inline-style");
  }
  auto inspect_css = [&](const std::string& css_input) {
    const std::string css = LowerAscii(css_input);
    size_t block_start = 0;
    while ((block_start = css.find('{', block_start)) != std::string::npos) {
      const size_t block_end = css.find('}', block_start + 1);
      if (block_end == std::string::npos) {
        break;
      }
      const size_t selector_start =
          css.rfind('}', block_start) == std::string::npos
              ? 0
              : css.rfind('}', block_start) + 1;
      const std::string selector_text =
          css.substr(selector_start, block_start - selector_start);
      const std::string declarations =
          css.substr(block_start + 1, block_end - block_start - 1);
      if (DeclarationHasPropertyValue(declarations, "position", "fixed")) {
        summary.fixed_rule_count++;
      }
      if (DeclarationHasPropertyValue(declarations, "position", "sticky")) {
        summary.sticky_rule_count++;
        for (const std::string& selector : SplitSelectors(selector_text)) {
          if (SelectorMayMatchHtml(selector, lower_html)) {
            summary.active_sticky_rule_count++;
            if (summary.active_sticky_selectors.size() < 4) {
              summary.active_sticky_selectors.push_back(selector);
            }
            break;
          }
        }
      }
      if (declarations.find("filter") != std::string::npos) {
        summary.filter_rule_count++;
      }
      if (declarations.find("clip-path") != std::string::npos ||
          declarations.find("mask") != std::string::npos) {
        summary.clip_or_mask_rule_count++;
      }
      if ((declarations.find("overflow") != std::string::npos) &&
          (declarations.find("auto") != std::string::npos ||
           declarations.find("scroll") != std::string::npos)) {
        summary.overflow_scroll_rule_count++;
      }
      block_start = block_end + 1;
    }
  };
  inspect_css(html);
  for (const Stylesheet& stylesheet : stylesheets) {
    inspect_css(stylesheet.css);
  }
  return summary;
}

std::string ScrollLifecycleSummaryDiagnostic(
    const ScrollLifecycleSourceSummary& summary) {
  std::ostringstream out;
  out << "document scroll fast path source summary: fixed_rules="
      << summary.fixed_rule_count << " sticky_rules="
      << summary.sticky_rule_count << " active_sticky_rules="
      << summary.active_sticky_rule_count << " filter_rules="
      << summary.filter_rule_count << " clip_or_mask_rules="
      << summary.clip_or_mask_rule_count << " overflow_scroll_rules="
      << summary.overflow_scroll_rule_count;
  if (!summary.active_sticky_selectors.empty()) {
    out << " active_sticky_selectors=";
    for (size_t i = 0; i < summary.active_sticky_selectors.size(); ++i) {
      if (i > 0) {
        out << "|";
      }
      out << summary.active_sticky_selectors[i];
    }
  }
  return out.str();
}

bool SameSize(Size left, Size right) {
  return std::abs(left.width - right.width) <= 0.001f &&
         std::abs(left.height - right.height) <= 0.001f;
}

bool SamePoint(Point left, Point right) {
  return std::abs(left.x - right.x) <= 0.001f &&
         std::abs(left.y - right.y) <= 0.001f;
}

bool SameStylesheets(const std::vector<Stylesheet>& left,
                     const std::vector<Stylesheet>& right) {
  if (left.size() != right.size()) {
    return false;
  }
  for (size_t i = 0; i < left.size(); ++i) {
    if (left[i].id != right[i].id || left[i].css != right[i].css) {
      return false;
    }
  }
  return true;
}

bool SameFeatures(const RendererFeatureFlags& left,
                  const RendererFeatureFlags& right) {
  return left.enable_css_animations == right.enable_css_animations &&
         left.enable_css_transitions == right.enable_css_transitions &&
         left.enable_forms_visual_state == right.enable_forms_visual_state &&
         left.enable_svg == right.enable_svg &&
         left.enable_mathml == right.enable_mathml;
}

bool IsDocumentScrollKey(const std::string& key) {
  return key == "document" || key == "body";
}

bool SameNonDocumentScrollOffsets(
    const std::unordered_map<std::string, Point>& left,
    const std::unordered_map<std::string, Point>& right) {
  for (const auto& [key, value] : left) {
    if (IsDocumentScrollKey(key)) {
      continue;
    }
    const auto found = right.find(key);
    if (found == right.end() || !SamePoint(value, found->second)) {
      return false;
    }
  }
  for (const auto& [key, value] : right) {
    if (IsDocumentScrollKey(key)) {
      continue;
    }
    const auto found = left.find(key);
    if (found == left.end() || !SamePoint(value, found->second)) {
      return false;
    }
  }
  return true;
}

void TranslateHitTestEntries(std::vector<HitTestEntry>& entries, Point delta) {
  if (SamePoint(delta, Point{})) {
    return;
  }
  for (HitTestEntry& entry : entries) {
    entry.bounds.x += delta.x;
    entry.bounds.y += delta.y;
  }
}

void TranslateScrollableElementEntries(std::vector<ScrollableElementEntry>& entries,
                                       Point delta) {
  if (SamePoint(delta, Point{})) {
    return;
  }
  for (ScrollableElementEntry& entry : entries) {
    entry.bounds.x += delta.x;
    entry.bounds.y += delta.y;
  }
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

class LiveBlinkPageEmbedder final : public BlinkPageEmbedder {
 public:
  explicit LiveBlinkPageEmbedder(BlinkPageEmbedderCreateInfo create_info) {
    disable_retained_extraction_ = create_info.disable_retained_extraction;
    enable_paint_artifact_audit_ = create_info.enable_paint_artifact_audit;
    trace_stages_ = create_info.trace_stages;
    debug_text_blob_replay_ = create_info.debug_text_blob_replay;
    force_paint_oracle_bitmap_ = create_info.force_paint_oracle_bitmap;
    lifecycle_stop_ = create_info.lifecycle_stop;
    SetTextBlobReplayDiagnosticsEnabled(debug_text_blob_replay_);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetDisableRetainedExtractionForStandaloneRenderer(
            disable_retained_extraction_ ? 1 : 0);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
            enable_paint_artifact_audit_ ? 1 : 0);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetForceOracleBitmapForStandaloneRenderer(
            force_paint_oracle_bitmap_ ? 1 : 0);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
            trace_stages_ ? 1 : 0);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
            lifecycle_stop_.empty() ? nullptr : lifecycle_stop_.c_str());
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
    report.diagnostics.push_back(
        "live Blink paint diagnostics are emitted during frame render");
    return report;
  }

  RenderResult AdvanceAndRender(const FrameInput& input) override {
    const RendererSnapshot previous_snapshot = Snapshot();
    ApplyInput(input);
    RenderResult result;
    result.successor_snapshot = snapshot_;
    TryReplaceWithLivePaintArtifactScene(result, previous_snapshot, input, false,
                                         snapshot_.html, snapshot_.stylesheets);
    return result;
  }

  RenderResult AdvanceAndRenderIncremental(const FrameInput& input) override {
    const RendererSnapshot previous_snapshot = Snapshot();
    ApplyInput(input);
    RenderResult result;
    result.successor_snapshot = snapshot_;
    if (TryRenderDocumentScrollOnlyFromRetainedScene(result, previous_snapshot,
                                                    input)) {
      return result;
    }
    TryReplaceWithLivePaintArtifactScene(result, previous_snapshot, input, true,
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
    if (input.html_override) {
      snapshot_.html = *input.html_override;
    }
    if (input.stylesheets_override) {
      snapshot_.stylesheets = *input.stylesheets_override;
    }
    snapshot_.element_attributes_by_id_and_name =
        input.element_attributes_by_id_and_name;
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
      Point document_scroll_offset,
      const std::unordered_map<std::string, Point>& scroll_offsets,
      double timeline_time_seconds,
      const std::unordered_map<std::string, std::string>& element_attributes,
      const std::string& hovered_element_id,
      const std::string& active_element_id,
      std::vector<std::string>& diagnostics) {
    namespace live_probe = ::blink::standalone_renderer_probe;
    const std::string probe_html = BuildLiveBlinkProbeHtml(html, stylesheets);
    live_probe::StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(
        static_cast<int>(viewport.width), static_cast<int>(viewport.height));
    live_probe::StandaloneBlinkLiveFrameBridgeSetDocumentScrollOffsetForStandaloneRenderer(
        document_scroll_offset.x, document_scroll_offset.y);
    const std::string serialized_scroll_offsets =
        SerializeElementScrollOffsetsForStandaloneRenderer(scroll_offsets);
    live_probe::StandaloneBlinkLiveFrameBridgeSetElementScrollOffsetsForStandaloneRenderer(
        serialized_scroll_offsets.c_str());
    live_probe::StandaloneBlinkLiveFrameBridgeSetAnimationTimeForStandaloneRenderer(
        timeline_time_seconds * 1000.0);
    const std::string serialized_attributes =
        SerializeElementAttributesForStandaloneRenderer(element_attributes);
    live_probe::StandaloneBlinkLiveFrameBridgeSetElementAttributesForStandaloneRenderer(
        serialized_attributes.c_str());
    live_probe::StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
        hovered_element_id.c_str(), active_element_id.c_str());
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

  bool CanUseDocumentScrollOnlyFastPath(
      const RendererSnapshot& previous_snapshot,
      std::vector<std::string>* diagnostics) const {
    const auto push_diagnostic = [&](const std::string& diagnostic) {
      if (diagnostics) {
        diagnostics->push_back(diagnostic);
      }
    };
    if (!previous_retained_scene_) {
      push_diagnostic(
          "document scroll fast path ineligible: no retained scene");
      return false;
    }
    const bool document_scroll_unchanged =
        SamePoint(SnapshotDocumentScrollOffset(snapshot_),
                  SnapshotDocumentScrollOffset(previous_snapshot));
    const ScrollLifecycleSourceSummary source_summary =
        SummarizeScrollLifecycleSource(snapshot_.html, snapshot_.stylesheets);
    push_diagnostic(ScrollLifecycleSummaryDiagnostic(source_summary));
    if (snapshot_.html != previous_snapshot.html) {
      push_diagnostic("document scroll fast path ineligible: html changed");
      return false;
    }
    if (!SameStylesheets(snapshot_.stylesheets, previous_snapshot.stylesheets)) {
      push_diagnostic(
          "document scroll fast path ineligible: stylesheets changed");
      return false;
    }
    if (!SameSize(snapshot_.viewport, previous_snapshot.viewport)) {
      push_diagnostic("document scroll fast path ineligible: viewport changed");
      return false;
    }
    if (std::abs(snapshot_.device_scale_factor -
                 previous_snapshot.device_scale_factor) > 0.001f) {
      push_diagnostic(
          "document scroll fast path ineligible: device scale changed");
      return false;
    }
    if (snapshot_.asset_namespace != previous_snapshot.asset_namespace) {
      push_diagnostic(
          "document scroll fast path ineligible: asset namespace changed");
      return false;
    }
    if (!SameFeatures(snapshot_.features, previous_snapshot.features)) {
      push_diagnostic("document scroll fast path ineligible: features changed");
      return false;
    }
    if (snapshot_.timeline_time_seconds !=
        previous_snapshot.timeline_time_seconds) {
      if (previous_needs_begin_frame_) {
        push_diagnostic("document scroll fast path ineligible: time changed");
        return false;
      }
      push_diagnostic(
          "document scroll fast path allowed time change because previous "
          "Blink frame did not request begin frame");
    }
    if (!SameStringMap(snapshot_.element_attributes_by_id_and_name,
                       previous_snapshot.element_attributes_by_id_and_name)) {
      push_diagnostic("document scroll fast path ineligible: attrs changed");
      return false;
    }
    if (snapshot_.focused_element_id != previous_snapshot.focused_element_id ||
        snapshot_.hovered_element_id != previous_snapshot.hovered_element_id ||
        snapshot_.active_element_id != previous_snapshot.active_element_id) {
      push_diagnostic(
          "document scroll fast path ineligible: interaction state changed");
      return false;
    }
    if (!SameStringMap(snapshot_.form_values_by_element_id,
                       previous_snapshot.form_values_by_element_id)) {
      push_diagnostic(
          "document scroll fast path ineligible: form state changed");
      return false;
    }
    if (source_summary.active_sticky_rule_count > 0 &&
        !document_scroll_unchanged) {
      push_diagnostic(
          "document scroll fast path ineligible: active sticky position "
          "requires Blink lifecycle");
      return false;
    }
    if (!SameNonDocumentScrollOffsets(
            snapshot_.scroll_offsets_by_element_id,
            previous_snapshot.scroll_offsets_by_element_id)) {
      push_diagnostic(
          "document scroll fast path ineligible: element scroll changed");
      return false;
    }
    if (document_scroll_unchanged) {
      push_diagnostic(
          "document scroll fast path using retained no-op because document "
          "scroll is unchanged");
    }
    return true;
  }

  bool TryRenderDocumentScrollOnlyFromRetainedScene(
      RenderResult& result,
      const RendererSnapshot& previous_snapshot,
      const FrameInput& input) {
    if (input.wheel || !input.pointers.empty() ||
        !input.keyboard.pressed_key_codes.empty()) {
      return false;
    }
    const RendererSnapshot unclamped_snapshot = snapshot_;
    bool clamped_to_previous_max = false;
    if (previous_document_max_scroll_offset_) {
      const Point requested_scroll = SnapshotDocumentScrollOffset(snapshot_);
      const Point maximum = *previous_document_max_scroll_offset_;
      const Point clamped_scroll{
          std::clamp(requested_scroll.x, 0.0f, std::max(0.0f, maximum.x)),
          std::clamp(requested_scroll.y, 0.0f, std::max(0.0f, maximum.y))};
      if (!SamePoint(requested_scroll, clamped_scroll)) {
        SetSnapshotDocumentScrollOffset(snapshot_, clamped_scroll);
        result.successor_snapshot = snapshot_;
        clamped_to_previous_max = true;
      }
    }
    if (!CanUseDocumentScrollOnlyFastPath(previous_snapshot,
                                         &result.diagnostics)) {
      if (clamped_to_previous_max) {
        snapshot_ = unclamped_snapshot;
        result.successor_snapshot = snapshot_;
      }
      return false;
    }
    const Point current_scroll_offset = SnapshotDocumentScrollOffset(snapshot_);
    const Point previous_scroll_offset =
        SnapshotDocumentScrollOffset(previous_snapshot);
    ApplyRetainedScenePlan(result, *previous_retained_scene_,
                           LoadCommandList{}, &*previous_retained_scene_,
                           previous_snapshot, current_scroll_offset,
                           previous_scroll_offset);
    AddScrollClipEdgeDamage(result, *previous_retained_scene_,
                            current_scroll_offset, previous_scroll_offset);
    result.frame.resource_commands = previous_resource_commands_;
    result.hit_test_entries = previous_hit_test_entries_;
    result.scrollable_element_entries = previous_scrollable_element_entries_;
    if (previous_document_max_scroll_offset_) {
      result.document_max_scroll_offset = *previous_document_max_scroll_offset_;
    }
    result.needs_begin_frame = previous_needs_begin_frame_;
    const Point scroll_delta{previous_scroll_offset.x - current_scroll_offset.x,
                             previous_scroll_offset.y - current_scroll_offset.y};
    TranslateHitTestEntries(result.hit_test_entries, scroll_delta);
    TranslateScrollableElementEntries(result.scrollable_element_entries,
                                      scroll_delta);
    result.diagnostics.push_back(
        "live Blink document scroll-only fast path reused retained scene");
    if (clamped_to_previous_max) {
      result.diagnostics.push_back(
          "live Blink document scroll-only fast path clamped to previous "
          "Blink-reported maximum scroll offset");
    }
    result.diagnostics.push_back(
        "paint artifact source: real Blink PaintArtifact; "
        "extractor=real_blink_paint_artifact_extractor; "
        "reuse=document_scroll_only_retained_scene");
    result.diagnostics.push_back(
        "real Blink PaintArtifact exported through retained PaintOp commands");
    return true;
  }

  void TryReplaceWithLivePaintArtifactScene(
      RenderResult& result,
      const RendererSnapshot& previous_snapshot,
      const FrameInput& input,
      bool incremental,
      const std::string& html,
      const std::vector<Stylesheet>& stylesheets) {
    namespace live_probe = ::blink::standalone_renderer_probe;
    const std::string probe_html = BuildLiveBlinkProbeHtml(html, stylesheets);
    ResetTypefaceResourceRegistryForFrame();
    SetTextBlobReplayDiagnosticsEnabled(debug_text_blob_replay_);
    live_probe::StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer();
    live_probe::StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(
        static_cast<int>(result.successor_snapshot.viewport.width),
        static_cast<int>(result.successor_snapshot.viewport.height));
    live_probe::StandaloneBlinkLiveFrameBridgeSetDocumentScrollOffsetForStandaloneRenderer(
        SnapshotDocumentScrollOffset(result.successor_snapshot).x,
        SnapshotDocumentScrollOffset(result.successor_snapshot).y);
    const std::string serialized_scroll_offsets =
        SerializeElementScrollOffsetsForStandaloneRenderer(
            result.successor_snapshot.scroll_offsets_by_element_id);
    live_probe::StandaloneBlinkLiveFrameBridgeSetElementScrollOffsetsForStandaloneRenderer(
        serialized_scroll_offsets.c_str());
    live_probe::StandaloneBlinkLiveFrameBridgeSetAnimationTimeForStandaloneRenderer(
        result.successor_snapshot.timeline_time_seconds * 1000.0);
    const std::string serialized_attributes =
        SerializeElementAttributesForStandaloneRenderer(
            result.successor_snapshot.element_attributes_by_id_and_name);
    live_probe::StandaloneBlinkLiveFrameBridgeSetElementAttributesForStandaloneRenderer(
        serialized_attributes.c_str());
    const bool primary_pointer_state_changed =
        PrimaryPointerStateChangedForStandaloneRenderer(input);
    if (input.pointers.empty()) {
      live_probe::StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
          result.successor_snapshot.hovered_element_id.c_str(),
          result.successor_snapshot.active_element_id.c_str());
    } else {
      live_probe::StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
          nullptr, nullptr);
    }
    if (input.wheel) {
      live_probe::StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
          input.wheel->position.x, input.wheel->position.y,
          input.wheel->delta.x, input.wheel->delta.y, 1);
    } else {
      live_probe::StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
          0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    if (!input.pointers.empty()) {
      const PointerState& pointer = input.pointers.front();
      int pointer_event_type = 0;
      if (!last_pointer_pressed_ && pointer.pressed) {
        pointer_event_type = 1;
      } else if (last_pointer_pressed_ && !pointer.pressed) {
        pointer_event_type = 2;
      }
      live_probe::StandaloneBlinkLiveFrameBridgeSetPointerStateForStandaloneRenderer(
          pointer.position.x, pointer.position.y, pointer.pressed ? 1 : 0,
          pointer_event_type, primary_pointer_state_changed ? 1 : 0);
      last_pointer_pressed_ = pointer.pressed;
    } else {
      live_probe::StandaloneBlinkLiveFrameBridgeSetPointerStateForStandaloneRenderer(
          0.0f, 0.0f, 0, 0, 0);
      last_pointer_pressed_ = false;
    }
    live_probe::
        StandaloneBlinkLiveFrameBridgeSetDisableRetainedExtractionForStandaloneRenderer(
            disable_retained_extraction_ ? 1 : 0);
    live_probe::
        StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
            enable_paint_artifact_audit_ ? 1 : 0);
    live_probe::StandaloneBlinkLiveFrameBridgeSetForceOracleBitmapForStandaloneRenderer(
        force_paint_oracle_bitmap_ ? 1 : 0);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
            lifecycle_stop_.empty() ? nullptr : lifecycle_stop_.c_str());
    if (!live_probe::
            StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer() ||
        !live_probe::
            StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer()) {
      return;
    }
    auto copy_raw_paint_artifact_audit_json = [&]() {
      const int raw_audit_json_size =
          live_probe::
              StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonSizeForStandaloneRenderer(
                  probe_html.c_str());
      if (raw_audit_json_size <= 0) {
        return;
      }
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
    };
    if (!live_probe::StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
            probe_html.c_str())) {
      result.diagnostics.push_back(
          "real Blink PaintArtifact bridge did not reach PaintClean");
      return;
    }
    float applied_scroll_x = 0.0f;
    float applied_scroll_y = 0.0f;
    float max_scroll_x = 0.0f;
    float max_scroll_y = 0.0f;
    if (live_probe::StandaloneBlinkLiveFrameBridgeDocumentScrollOffsetForStandaloneRenderer(
            probe_html.c_str(), &applied_scroll_x, &applied_scroll_y,
            &max_scroll_x, &max_scroll_y)) {
      Point& document_scroll =
          result.successor_snapshot.scroll_offsets_by_element_id["document"];
      document_scroll.x = applied_scroll_x;
      document_scroll.y = applied_scroll_y;
      result.document_max_scroll_offset = Point{max_scroll_x, max_scroll_y};
      previous_document_max_scroll_offset_ = result.document_max_scroll_offset;
      snapshot_.scroll_offsets_by_element_id =
          result.successor_snapshot.scroll_offsets_by_element_id;
    }
    const bool prior_needs_begin_frame = previous_needs_begin_frame_;
    result.needs_begin_frame =
        live_probe::
            StandaloneBlinkLiveFrameBridgeNeedsBeginFrameForStandaloneRenderer(
                probe_html.c_str()) != 0;
    previous_needs_begin_frame_ = result.needs_begin_frame;
    std::array<char, 256> observed_hovered_element_id{};
    std::array<char, 256> observed_active_element_id{};
    if (live_probe::
            StandaloneBlinkLiveFrameBridgePointerObservedStateForStandaloneRenderer(
                probe_html.c_str(), observed_hovered_element_id.data(),
                static_cast<int>(observed_hovered_element_id.size()),
                observed_active_element_id.data(),
                static_cast<int>(observed_active_element_id.size()))) {
      result.successor_snapshot.hovered_element_id =
          observed_hovered_element_id.data();
      result.successor_snapshot.active_element_id =
          observed_active_element_id.data();
      snapshot_.hovered_element_id =
          result.successor_snapshot.hovered_element_id;
      snapshot_.active_element_id = result.successor_snapshot.active_element_id;
    }
    ImportLiveHitTestEntriesForStandaloneRenderer(probe_html, result);
    ImportLiveScrollableElementEntriesForStandaloneRenderer(probe_html, result);
    PersistObservedScrollableElementOffsetsForStandaloneRenderer(result);
    snapshot_.scroll_offsets_by_element_id =
        result.successor_snapshot.scroll_offsets_by_element_id;

    const int chunk_count =
        live_probe::StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
            probe_html.c_str());
    copy_raw_paint_artifact_audit_json();
    if (chunk_count <= 0) {
      result.diagnostics.push_back("real Blink PaintArtifact bridge produced no chunks");
      return;
    }
    if (disable_retained_extraction_) {
      result.diagnostics.push_back(
          "real Blink PaintArtifact retained extraction disabled by caller");
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
    std::string active_chunk_id_string;
    Rect active_chunk_bounds;
    Rect active_chunk_drawable_bounds;
    PaintPropertyStateSnapshot active_chunk_property_state;
    int active_chunk_debug_index = -1;
    std::vector<FinerCacheUnitDescriptor> active_chunk_finer_cache_units;
    bool inside_chunk = false;
    LoadCommandList load_commands;
    std::vector<ResourceCommand> explicit_resource_commands;

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
    auto nearly_equal = [](float left, float right) {
      return std::abs(left - right) <= 0.01f;
    };
    auto nearly_equal_root_space_origin = [](float left, float right) {
      return std::abs(left - right) <= 1.5f;
    };
    auto nearly_equal_rect = [&](Rect left, Rect right) {
      return nearly_equal(left.x, right.x) && nearly_equal(left.y, right.y) &&
             nearly_equal(left.width, right.width) &&
             nearly_equal(left.height, right.height);
    };
    auto duplicates_chunk_property_clip =
        [&](Rect clip, const PaintPropertyStateSnapshot& state) {
          return (state.has_clip_rect &&
                  nearly_equal_rect(clip, state.clip_rect)) ||
                 (state.has_clip_rrect &&
                 nearly_equal_rect(clip, state.clip_rrect));
        };
    auto chunk_property_transform_replayed_by_retained_scene = [&]() {
      const Matrix4& matrix =
          active_chunk_property_state.transform_to_root;
      const bool has_non_identity_transform =
          active_chunk_property_state.transform_has_non_translation ||
          !nearly_equal(matrix.values[12], 0.0f) ||
          !nearly_equal(matrix.values[13], 0.0f);
      return active_chunk_property_state.transform_is_2d &&
             !active_chunk_property_state.transform_has_perspective &&
             active_chunk_property_state.scroll_node_id == 0 &&
             active_chunk_property_state.clip_chain_depth == 0 &&
             !active_chunk_property_state.has_clip_rect &&
             !active_chunk_property_state.has_clip_rrect &&
             active_chunk_property_state.effect_chain_depth == 0 &&
             !active_chunk_property_state.effect_has_non_default_opacity &&
             !active_chunk_property_state.effect_has_filter &&
             !active_chunk_property_state.effect_has_backdrop_filter &&
             !active_chunk_property_state.effect_has_blend_mode &&
             active_chunk_bounds.width > 0.0f &&
             active_chunk_bounds.height > 0.0f &&
             has_non_identity_transform;
    };
    auto matrix_matches_active_chunk_property_transform =
        [&](float m00, float m01, float tx, float m10, float m11, float ty) {
          const Matrix4& matrix =
              active_chunk_property_state.transform_to_root;
          return nearly_equal(m00, matrix.values[0]) &&
                 nearly_equal(m01, matrix.values[4]) &&
                 nearly_equal(tx, matrix.values[12]) &&
                 nearly_equal(m10, matrix.values[1]) &&
                 nearly_equal(m11, matrix.values[5]) &&
                 nearly_equal(ty, matrix.values[13]);
        };
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
      int stroke_cap = 0;
      int stroke_join = 0;
      float stroke_miter = 4.0f;
      float radius_x = 0.0f;
      float radius_y = 0.0f;
      int glyph_count = 0;
      if (!live_probe::
              StandaloneBlinkLiveFrameBridgeExportedDrawOpAtForStandaloneRenderer(
                  probe_html.c_str(), i, &type, &x, &y, &width, &height, &r,
                  &g, &b, &a, &font_size, &stroke_cap, &stroke_join,
                  &stroke_miter, &radius_x, &radius_y, &glyph_count)) {
        continue;
      }
      DrawCommandList* source_annotation_commands = active_commands;
      const size_t source_annotation_begin =
          source_annotation_commands ? source_annotation_commands->size() : 0;
      int source_chunk_index = -1;
      int source_display_item_index = -1;
      uint64_t source_display_item_client_id = 0;
      int source_display_item_client_id_valid = 0;
      live_probe::
          StandaloneBlinkLiveFrameBridgeExportedDrawOpSourceAtForStandaloneRenderer(
              probe_html.c_str(), i, &source_chunk_index,
              &source_display_item_index, &source_display_item_client_id,
              &source_display_item_client_id_valid);
      auto normalize_component = [](float value) {
        return value > 1.0f ? value / 255.0f : value;
      };
      const Color color =
          Color::Rgba(normalize_component(r), normalize_component(g),
                      normalize_component(b), normalize_component(a));
      auto append_draw_looper_layers = [&](DrawCommand& command) {
        const int layer_count =
            live_probe::
                StandaloneBlinkLiveFrameBridgeExportedDrawLooperLayerCountForStandaloneRenderer(
                    probe_html.c_str(), i);
        for (int layer_index = 0; layer_index < layer_count; ++layer_index) {
          float layer_offset_x = 0.0f;
          float layer_offset_y = 0.0f;
          float layer_blur_sigma = 0.0f;
          float layer_r = 0.0f;
          float layer_g = 0.0f;
          float layer_b = 0.0f;
          float layer_a = 1.0f;
          uint32_t layer_flags = 0;
          if (!live_probe::
                  StandaloneBlinkLiveFrameBridgeExportedDrawLooperLayerAtForStandaloneRenderer(
                      probe_html.c_str(), i, layer_index, &layer_offset_x,
                      &layer_offset_y, &layer_blur_sigma, &layer_r, &layer_g,
                      &layer_b, &layer_a, &layer_flags)) {
            continue;
          }
          DrawLooperLayer layer;
          layer.offset_x = layer_offset_x;
          layer.offset_y = layer_offset_y;
          layer.blur_sigma = layer_blur_sigma;
          layer.color = Color::Rgba(normalize_component(layer_r),
                                    normalize_component(layer_g),
                                    normalize_component(layer_b),
                                    normalize_component(layer_a));
          layer.flags = layer_flags;
          command.draw_looper_layers.push_back(layer);
        }
      };
      auto exported_rrect_radii = [&]() {
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
        return corner_radii;
      };
      auto append_path_effect_bytes = [&](DrawCommand& command) {
        int byte_count = 0;
        if (!live_probe::
                StandaloneBlinkLiveFrameBridgeExportedPathEffectInfoAtForStandaloneRenderer(
                    probe_html.c_str(), i, &byte_count) ||
            byte_count <= 0) {
          return;
        }
        std::vector<uint8_t> bytes(static_cast<size_t>(byte_count));
        if (live_probe::
                StandaloneBlinkLiveFrameBridgeExportedPathEffectBytesAtForStandaloneRenderer(
                    probe_html.c_str(), i, bytes.data(), byte_count) !=
            byte_count) {
          return;
        }
        command.path_effect_bytes = std::move(bytes);
      };
      if (type == 12) {
        if (inside_chunk) {
          current_scene.chunks.push_back(MakeRetainedPaintChunk(
              active_chunk_key, RetainedChunkKind::kDocument,
              active_chunk_bounds, active_chunk_property_state,
              std::move(chunk_commands)));
          current_scene.chunks.back().debug_index = active_chunk_debug_index;
          if (active_chunk_drawable_bounds.width > 0.0f &&
              active_chunk_drawable_bounds.height > 0.0f) {
            current_scene.chunks.back().placement_bounds =
                active_chunk_drawable_bounds;
          }
          current_scene.chunks.back().stable_key = active_chunk_key;
          current_scene.chunks.back().chunk_id_string =
              active_chunk_id_string.empty() ? active_chunk_key
                                             : active_chunk_id_string;
          PopulateFinerCacheUnitEntryStateSummaries(
              active_chunk_finer_cache_units, chunk_commands);
          current_scene.chunks.back().finer_cache_units =
              std::move(active_chunk_finer_cache_units);
          chunk_commands.clear();
        }
        inside_chunk = true;
        const int chunk_index = static_cast<int>(font_size);
        active_chunk_debug_index = chunk_index;
        active_chunk_bounds = Rect{x, y, width, height};
        active_chunk_drawable_bounds = Rect{};
        int drawable_x = 0;
        int drawable_y = 0;
        int drawable_width = 0;
        int drawable_height = 0;
        if (live_probe::
                StandaloneBlinkLiveFrameBridgePaintChunkDrawableBoundsAtForStandaloneRenderer(
                    probe_html.c_str(), chunk_index, &drawable_x, &drawable_y,
                    &drawable_width, &drawable_height)) {
          active_chunk_drawable_bounds =
              Rect{static_cast<float>(drawable_x),
                   static_cast<float>(drawable_y),
                   static_cast<float>(drawable_width),
                   static_cast<float>(drawable_height)};
        }
        active_chunk_property_state = PaintPropertyStateSnapshot{};
        std::array<char, 1024> chunk_key_buffer{};
        std::array<char, 512> chunk_id_buffer{};
        if (live_probe::
                StandaloneBlinkLiveFrameBridgeChunkStableKeyAtForStandaloneRenderer(
                    probe_html.c_str(), chunk_index, chunk_key_buffer.data(),
                    static_cast<int>(chunk_key_buffer.size())) <= 0) {
          chunk_key_buffer[0] = '\0';
        }
        if (live_probe::
                StandaloneBlinkLiveFrameBridgeChunkIdStringAtForStandaloneRenderer(
                    probe_html.c_str(), chunk_index, chunk_id_buffer.data(),
                    static_cast<int>(chunk_id_buffer.size())) <= 0) {
          chunk_id_buffer[0] = '\0';
        }
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
          uint64_t transform_node_id = 0;
          uint64_t transform_parent_id = 0;
          uint32_t transform_chain_depth = 0;
          uint64_t scroll_node_id = 0;
          uint32_t clip_chain_depth = 0;
          uint32_t effect_chain_depth = 0;
          uint64_t effect_node_id = 0;
          uint64_t effect_parent_id = 0;
          float effect_opacity = 1.0f;
          int effect_has_non_default_opacity = 0;
          int effect_has_filter = 0;
          int effect_has_backdrop_filter = 0;
          int effect_has_blend_mode = 0;
          int effect_blend_mode = 3;
          uint64_t effect_output_clip_id = 0;
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgePaintChunkPropertyMetadataAtForStandaloneRenderer(
                      probe_html.c_str(), chunk_index, &transform_node_id,
                      &transform_parent_id, &transform_chain_depth,
                      &scroll_node_id, &clip_chain_depth, &effect_chain_depth,
                      &effect_node_id, &effect_parent_id, &effect_opacity,
                      &effect_has_non_default_opacity, &effect_has_filter,
                      &effect_has_backdrop_filter, &effect_has_blend_mode,
                      &effect_blend_mode, &effect_output_clip_id)) {
            active_chunk_property_state.transform_node_id = transform_node_id;
            active_chunk_property_state.transform_parent_id =
                transform_parent_id;
            active_chunk_property_state.transform_chain_depth =
                transform_chain_depth;
            active_chunk_property_state.scroll_node_id = scroll_node_id;
            active_chunk_property_state.clip_chain_depth = clip_chain_depth;
            active_chunk_property_state.effect_chain_depth = effect_chain_depth;
            active_chunk_property_state.effect_node_id = effect_node_id;
            active_chunk_property_state.effect_parent_id = effect_parent_id;
            active_chunk_property_state.effect_opacity = effect_opacity;
            active_chunk_property_state.effect_has_non_default_opacity =
                effect_has_non_default_opacity != 0;
            active_chunk_property_state.effect_has_filter =
                effect_has_filter != 0;
            active_chunk_property_state.effect_has_backdrop_filter =
                effect_has_backdrop_filter != 0;
            active_chunk_property_state.effect_has_blend_mode =
                effect_has_blend_mode != 0;
            active_chunk_property_state.effect_blend_mode = effect_blend_mode;
            active_chunk_property_state.effect_output_clip_id =
                effect_output_clip_id;
          }
          PopulateFilterOperationsFromLiveProbe(
              probe_html, chunk_index, active_chunk_property_state);
          int has_rounded_clip = 0;
          float rounded_clip_x = 0.0f;
          float rounded_clip_y = 0.0f;
          float rounded_clip_width = 0.0f;
          float rounded_clip_height = 0.0f;
          float top_left_x = 0.0f;
          float top_left_y = 0.0f;
          float top_right_x = 0.0f;
          float top_right_y = 0.0f;
          float bottom_right_x = 0.0f;
          float bottom_right_y = 0.0f;
          float bottom_left_x = 0.0f;
          float bottom_left_y = 0.0f;
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgePaintChunkRoundedClipAtForStandaloneRenderer(
                      probe_html.c_str(), chunk_index, &has_rounded_clip,
                      &rounded_clip_x, &rounded_clip_y, &rounded_clip_width,
                      &rounded_clip_height, &top_left_x, &top_left_y,
                      &top_right_x, &top_right_y, &bottom_right_x,
                      &bottom_right_y, &bottom_left_x, &bottom_left_y) &&
              has_rounded_clip != 0) {
            active_chunk_property_state.has_clip_rrect = true;
            active_chunk_property_state.clip_rrect =
                Rect{rounded_clip_x, rounded_clip_y, rounded_clip_width,
                     rounded_clip_height};
            active_chunk_property_state.clip_rrect_radii = {
                Point{top_left_x, top_left_y},
                Point{top_right_x, top_right_y},
                Point{bottom_right_x, bottom_right_y},
                Point{bottom_left_x, bottom_left_y},
            };
          }
        }
        active_chunk_key =
            chunk_key_buffer[0] != '\0'
                ? std::string(chunk_key_buffer.data())
                : "blink-chunk:fingerprint=chunk-" +
                      std::to_string(chunk_index) + "-state-" +
                      std::to_string(active_chunk_property_state.state_hash) +
                      ":state=" +
                      std::to_string(active_chunk_property_state.state_hash) +
                      ":debug-index=" + std::to_string(chunk_index);
        active_chunk_id_string =
            chunk_id_buffer[0] != '\0' ? std::string(chunk_id_buffer.data())
                                       : active_chunk_key;
        active_chunk_finer_cache_units = ImportFinerCacheUnitDescriptors(
            probe_html, chunk_index, active_chunk_key);
        active_commands = &chunk_commands;
      } else if (type == 13) {
        if (inside_chunk) {
          current_scene.chunks.push_back(MakeRetainedPaintChunk(
              active_chunk_key, RetainedChunkKind::kDocument,
              active_chunk_bounds, active_chunk_property_state,
              std::move(chunk_commands)));
          current_scene.chunks.back().debug_index = active_chunk_debug_index;
          if (active_chunk_drawable_bounds.width > 0.0f &&
              active_chunk_drawable_bounds.height > 0.0f) {
            current_scene.chunks.back().placement_bounds =
                active_chunk_drawable_bounds;
          }
          current_scene.chunks.back().stable_key = active_chunk_key;
          current_scene.chunks.back().chunk_id_string =
              active_chunk_id_string.empty() ? active_chunk_key
                                             : active_chunk_id_string;
          PopulateFinerCacheUnitEntryStateSummaries(
              active_chunk_finer_cache_units, chunk_commands);
          current_scene.chunks.back().finer_cache_units =
              std::move(active_chunk_finer_cache_units);
          chunk_commands.clear();
        }
        inside_chunk = false;
        active_chunk_key.clear();
        active_chunk_id_string.clear();
        active_chunk_bounds = Rect{};
        active_chunk_drawable_bounds = Rect{};
        active_chunk_property_state = PaintPropertyStateSnapshot{};
        active_chunk_debug_index = -1;
        active_chunk_finer_cache_units.clear();
        active_commands = &commands;
      } else if (type == 1) {
        DrawCommand command = DrawCommand::FillRect(
            Rect{x, y, width, height}, color);
        append_draw_looper_layers(command);
        active_commands->push_back(std::move(command));
        ++translated_command_count;
      } else if (type == 4) {
        DrawCommand command = DrawCommand::StrokeRect(
            Rect{x, y, width, height}, color,
            font_size > 0.0f ? font_size : 1.0f);
        command.stroke_cap = stroke_cap;
        command.stroke_join = stroke_join;
        command.stroke_miter = stroke_miter;
        append_draw_looper_layers(command);
        append_path_effect_bytes(command);
        active_commands->push_back(std::move(command));
        ++translated_command_count;
      } else if (type == 5) {
        DrawCommand command =
            DrawCommand::FillRRect(Rect{x, y, width, height},
                                   exported_rrect_radii(), color);
        append_draw_looper_layers(command);
        active_commands->push_back(std::move(command));
        ++translated_command_count;
      } else if (type == 6) {
        DrawCommand command =
            DrawCommand::StrokeRRect(Rect{x, y, width, height},
                                     exported_rrect_radii(), color,
                                     font_size > 0.0f ? font_size : 1.0f);
        command.stroke_cap = stroke_cap;
        command.stroke_join = stroke_join;
        command.stroke_miter = stroke_miter;
        append_draw_looper_layers(command);
        append_path_effect_bytes(command);
        active_commands->push_back(std::move(command));
        ++translated_command_count;
      } else if (type == 7 || type == 22) {
        std::array<char, 128> debug_label{};
        live_probe::
            StandaloneBlinkLiveFrameBridgeExportedDebugLabelAtForStandaloneRenderer(
                probe_html.c_str(), i, debug_label.data(),
                static_cast<int>(debug_label.size()));
        if (type == 7) {
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
        }
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
            std::string(type == 22 ? "blink-paint-image-"
                                   : "blink-paint-bitmap-") +
            std::to_string(pixel_hash);
        image.resource_id = image.image_id;
        image.mime_type = type == 22 ? "image/x-blink-paint-image-rgba"
                                     : "image/x-raw-rgba";
        image.decoded_format = PixelFormat::kRgba8888;
        image.decoded_size = Size{static_cast<float>(bitmap_width),
                                  static_cast<float>(bitmap_height)};
        image.decoded_pixels = std::move(rgba_pixels);
        image.byte_count = image.decoded_pixels.size();
        image.bytes_hash = pixel_hash;
        Rect src_rect{0.0f, 0.0f, static_cast<float>(bitmap_width),
                      static_cast<float>(bitmap_height)};
        std::string sampling_options = "filter=nearest,mipmap=none";
        if (type == 22) {
          float src_x = 0.0f;
          float src_y = 0.0f;
          float src_width = 0.0f;
          float src_height = 0.0f;
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgeExportedImageSourceRectAtForStandaloneRenderer(
                      probe_html.c_str(), i, &src_x, &src_y, &src_width,
                      &src_height) &&
              src_width > 0.0f && src_height > 0.0f) {
            src_rect = Rect{src_x, src_y, src_width, src_height};
          }
          std::array<char, 128> sampling_buffer{};
          if (live_probe::
                  StandaloneBlinkLiveFrameBridgeExportedImageSamplingOptionsAtForStandaloneRenderer(
                      probe_html.c_str(), i, sampling_buffer.data(),
                      static_cast<int>(sampling_buffer.size())) > 0) {
            sampling_options = sampling_buffer.data();
          }
          result.diagnostics.push_back(
              std::string("retained_image_resource source_raw_op=") +
              (debug_label[0] != '\0' ? debug_label.data()
                                      : "DrawImageRectOp") +
              " source_chunk=" + active_chunk_key + " op=" +
              std::to_string(i) + " resource_id=" + image.image_id);
        }
        const std::string image_id = image.image_id;
        active_commands->push_back(
            type == 22 ? DrawCommand::DrawImageRect(
                             image_id, src_rect, Rect{x, y, width, height},
                             sampling_options)
                       : DrawCommand::DrawImage(image_id,
                                                Rect{x, y, width, height}));
        load_commands.push_back(LoadCommand::LoadImage(std::move(image)));
        ++translated_command_count;
      } else if (type == 8) {
        active_commands->push_back(DrawCommand::Save());
        ++translated_command_count;
      } else if (type == 9) {
        active_commands->push_back(DrawCommand::Restore());
        ++translated_command_count;
      } else if (type == 10) {
        Rect clip_rect{x, y, width, height};
        if (inside_chunk && active_chunk_property_state.scroll_node_id != 0 &&
            active_chunk_property_state.transform_is_2d &&
            !active_chunk_property_state.transform_has_non_translation &&
            duplicates_chunk_property_clip(clip_rect,
                                           active_chunk_property_state)) {
          continue;
        }
        active_commands->push_back(DrawCommand::ClipRect(clip_rect));
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
        DrawCommand save_layer =
            DrawCommand::SaveLayer(Rect{x, y, width, height}, font_size);
        save_layer.save_layer_bounds_unset =
            live_probe::
                StandaloneBlinkLiveFrameBridgeExportedSaveLayerBoundsUnsetAtForStandaloneRenderer(
                    probe_html.c_str(), i) != 0;
        active_commands->push_back(std::move(save_layer));
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
            const uint64_t text_blob_resource_id =
                static_cast<uint64_t>(i) + 1u;
            std::vector<uint64_t> typeface_ids;
            for (const TypefaceResource& resource :
                 SnapshotTypefaceResources()) {
              typeface_ids.push_back(resource.id);
            }
            explicit_resource_commands.push_back(ResourceCommand::LoadTextBlob(
                text_blob_resource_id, blob_bytes, typeface_ids,
                Rect{x, y, width, height}, "same_process_only"));
            DrawCommand command =
                DrawCommand::DrawTextBlob(std::move(blob_bytes), Point{x, y},
                                          color);
            command.rect.width = width;
            command.rect.height = height;
            append_draw_looper_layers(command);
            active_commands->push_back(std::move(command));
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
                  Rect{x, y, width, height}, exported_rrect_radii(),
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
            DrawCommand command = DrawCommand::FillPath(
                std::move(path_bytes), color,
                font_size > 0.0f ? font_size : 0.0f,
                std::move(shader_bytes));
            command.rect = Rect{x, y, width, height};
            command.stroke_cap = stroke_cap;
            command.stroke_join = stroke_join;
            command.stroke_miter = stroke_miter;
            append_draw_looper_layers(command);
            append_path_effect_bytes(command);
            active_commands->push_back(std::move(command));
            ++translated_command_count;
          }
        }
      } else if (type == 11) {
        if (chunk_property_transform_replayed_by_retained_scene() &&
            matrix_matches_active_chunk_property_transform(1.0f, 0.0f, x,
                                                          0.0f, 1.0f, y)) {
          result.diagnostics.push_back(
              "real Blink PaintArtifact skipped duplicate chunk property "
              "translation transform for chunk " + active_chunk_key);
          continue;
        }
        Matrix4 matrix;
        matrix.values[12] = x;
        matrix.values[13] = y;
        active_commands->push_back(DrawCommand::Transform(matrix));
        ++translated_command_count;
      } else if (type == 14) {
        const bool pure_translation =
            nearly_equal(x, 1.0f) && nearly_equal(y, 0.0f) &&
            nearly_equal(height, 0.0f) && nearly_equal(r, 1.0f);
        const bool conservative_property_state =
            active_chunk_property_state.transform_chain_depth <= 4 &&
            active_chunk_property_state.scroll_node_id == 0 &&
            !active_chunk_property_state.has_clip_rect &&
            active_chunk_property_state.clip_chain_depth == 0 &&
            active_chunk_property_state.effect_chain_depth <= 1;
        const bool chunk_root_space_paint_offset_translation =
            pure_translation && conservative_property_state &&
            nearly_equal(x,
                         active_chunk_property_state.transform_to_root.values[0]) &&
            nearly_equal(y,
                         active_chunk_property_state.transform_to_root.values[4]) &&
            nearly_equal(width,
                         active_chunk_property_state.transform_to_root.values[12]) &&
            nearly_equal(height,
                         active_chunk_property_state.transform_to_root.values[1]) &&
            nearly_equal(r,
                         active_chunk_property_state.transform_to_root.values[5]) &&
            nearly_equal(g,
                         active_chunk_property_state.transform_to_root.values[13]) &&
            (std::abs(width) > 0.01f || std::abs(g) > 0.01f);
        const bool duplicates_chunk_root_space_origin =
            chunk_root_space_paint_offset_translation &&
            nearly_equal_root_space_origin(width, active_chunk_bounds.x) &&
            nearly_equal_root_space_origin(g, active_chunk_bounds.y);
        const bool duplicates_document_scroll_presentation_transform =
            pure_translation &&
            active_chunk_property_state.scroll_node_id != 0 &&
            active_chunk_property_state.transform_chain_depth <= 2 &&
            !active_chunk_property_state.transform_has_non_translation &&
            nearly_equal(x,
                         active_chunk_property_state.transform_to_root.values[0]) &&
            nearly_equal(y,
                         active_chunk_property_state.transform_to_root.values[4]) &&
            nearly_equal(width,
                         active_chunk_property_state.transform_to_root.values[12]) &&
            nearly_equal(height,
                         active_chunk_property_state.transform_to_root.values[1]) &&
            nearly_equal(r,
                         active_chunk_property_state.transform_to_root.values[5]) &&
            nearly_equal(g,
                         active_chunk_property_state.transform_to_root.values[13]) &&
            (std::abs(width) > 0.01f || std::abs(g) > 0.01f);
        const bool matches_scroll_chunk_transform =
            pure_translation &&
            active_chunk_property_state.scroll_node_id != 0 &&
            !duplicates_document_scroll_presentation_transform &&
            !active_chunk_property_state.transform_has_non_translation &&
            (width < -0.01f || g < -0.01f) &&
            (active_chunk_property_state.transform_chain_depth > 2 ||
             active_chunk_property_state.clip_chain_depth > 0) &&
            nearly_equal(x,
                         active_chunk_property_state.transform_to_root.values[0]) &&
            nearly_equal(y,
                         active_chunk_property_state.transform_to_root.values[4]) &&
            nearly_equal(width,
                         active_chunk_property_state.transform_to_root.values[12]) &&
            nearly_equal(height,
                         active_chunk_property_state.transform_to_root.values[1]) &&
            nearly_equal(r,
                         active_chunk_property_state.transform_to_root.values[5]) &&
            nearly_equal(g,
                         active_chunk_property_state.transform_to_root.values[13]);
        const bool duplicates_replayed_chunk_property_transform =
            chunk_property_transform_replayed_by_retained_scene() &&
            matrix_matches_active_chunk_property_transform(x, y, width, height,
                                                          r, g);
        if (duplicates_chunk_root_space_origin ||
            duplicates_document_scroll_presentation_transform ||
            duplicates_replayed_chunk_property_transform) {
          Matrix4 skipped_matrix;
          skipped_matrix.values[0] = x;
          skipped_matrix.values[4] = y;
          skipped_matrix.values[12] = width;
          skipped_matrix.values[1] = height;
          skipped_matrix.values[5] = r;
          skipped_matrix.values[13] = g;
          SkippedTransformDiagnostic skipped;
          skipped.matrix = skipped_matrix;
          skipped.chunk_bounds = active_chunk_bounds;
          skipped.transform_node_id =
              active_chunk_property_state.transform_node_id;
          skipped.transform_parent_id =
              active_chunk_property_state.transform_parent_id;
          skipped.transform_chain_depth =
              active_chunk_property_state.transform_chain_depth;
          skipped.scroll_node_id = active_chunk_property_state.scroll_node_id;
          skipped.clip_chain_depth =
              active_chunk_property_state.clip_chain_depth;
          skipped.effect_chain_depth =
              active_chunk_property_state.effect_chain_depth;
          skipped.source_chunk_key = active_chunk_key;
          skipped.reason =
              duplicates_document_scroll_presentation_transform
                  ? "duplicate_document_scroll_presentation_transform"
                  : duplicates_replayed_chunk_property_transform
                        ? "duplicate_chunk_property_transform"
                        : "duplicate_root_space_pure_translation";
          result.skipped_transform_diagnostics.push_back(std::move(skipped));
          result.diagnostics.push_back(
              "real Blink PaintArtifact skipped duplicate chunk "
              "translation transform for chunk " + active_chunk_key +
              " reason=" +
              (duplicates_document_scroll_presentation_transform
                   ? std::string("record_document_scroll_presented_by_retained_plan")
                   : duplicates_replayed_chunk_property_transform
                         ? std::string("record_chunk_property_transform_replayed_by_retained_scene")
                   : std::string("record_geometry_already_root_space")) +
              " transform_node_id=" +
              std::to_string(active_chunk_property_state.transform_node_id) +
              " transform_parent_id=" +
              std::to_string(active_chunk_property_state.transform_parent_id) +
              " transform_chain_depth=" +
              std::to_string(
                  active_chunk_property_state.transform_chain_depth) +
              " scroll_node_id=" +
              std::to_string(active_chunk_property_state.scroll_node_id) +
              " matrix=[1,0,0," + std::to_string(width) +
              ",0,1,0," + std::to_string(g) +
              ",0,0,1,0,0,0,0,1]"
              " chunk_bounds=[" +
              std::to_string(active_chunk_bounds.x) + "," +
              std::to_string(active_chunk_bounds.y) + "," +
              std::to_string(active_chunk_bounds.width) + "," +
              std::to_string(active_chunk_bounds.height) + "]"
              " transform_node_classification=provisional_root_space_paint_offset_translation"
              " is_paint_offset_translation=unknown"
              " is_fixed_position_translation=unknown");
          continue;
        }
        if (!pure_translation) {
          result.diagnostics.push_back(
              "real Blink PaintArtifact kept non-translation transform for "
              "chunk " + active_chunk_key);
        }
        Matrix4 matrix;
        matrix.values[0] = x;
        matrix.values[4] = y;
        matrix.values[12] =
            (matches_scroll_chunk_transform ||
             chunk_root_space_paint_offset_translation)
                ? width - active_chunk_bounds.x
                : width;
        matrix.values[1] = height;
        matrix.values[5] = r;
        matrix.values[13] =
            (matches_scroll_chunk_transform ||
             chunk_root_space_paint_offset_translation)
                ? g - active_chunk_bounds.y
                : g;
        if ((!matches_scroll_chunk_transform &&
             !chunk_root_space_paint_offset_translation) ||
            std::abs(matrix.values[12]) > 0.01f ||
            std::abs(matrix.values[13]) > 0.01f) {
          active_commands->push_back(DrawCommand::Transform(matrix));
          ++translated_command_count;
        }
      } else {
        result.diagnostics.push_back(
            "real Blink PaintArtifact unexpected non-oracle exported op type " +
            std::to_string(type));
      }
      if (type != 12 && type != 13 && source_annotation_commands) {
        AnnotateTranslatedCommandsFromSource(
            *source_annotation_commands, source_annotation_begin,
            source_chunk_index, source_display_item_index,
            source_display_item_client_id,
            source_display_item_client_id_valid != 0,
            active_chunk_finer_cache_units);
      }
    }
    if (inside_chunk) {
      current_scene.chunks.push_back(MakeRetainedPaintChunk(
          active_chunk_key, RetainedChunkKind::kDocument, active_chunk_bounds,
          active_chunk_property_state, std::move(chunk_commands)));
      current_scene.chunks.back().debug_index = active_chunk_debug_index;
      if (active_chunk_drawable_bounds.width > 0.0f &&
          active_chunk_drawable_bounds.height > 0.0f) {
        current_scene.chunks.back().placement_bounds =
            active_chunk_drawable_bounds;
      }
      current_scene.chunks.back().stable_key = active_chunk_key;
      current_scene.chunks.back().chunk_id_string =
          active_chunk_id_string.empty() ? active_chunk_key
                                         : active_chunk_id_string;
      PopulateFinerCacheUnitEntryStateSummaries(
          active_chunk_finer_cache_units, chunk_commands);
      current_scene.chunks.back().finer_cache_units =
          std::move(active_chunk_finer_cache_units);
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
    const Point current_document_scroll =
        SnapshotDocumentScrollOffset(result.successor_snapshot);
    const Point previous_document_scroll =
        SnapshotDocumentScrollOffset(previous_snapshot);
    const bool viewport_changed =
        !SameSize(result.successor_snapshot.viewport, previous_snapshot.viewport);
    const bool document_scroll_changed =
        !SamePoint(current_document_scroll, previous_document_scroll);
    const bool element_scroll_changed = !SameNonDocumentScrollOffsets(
        result.successor_snapshot.scroll_offsets_by_element_id,
        previous_snapshot.scroll_offsets_by_element_id);
    const bool force_full_redraw_for_active_animation_change =
        (prior_needs_begin_frame || result.needs_begin_frame) &&
        (viewport_changed || document_scroll_changed || element_scroll_changed);
    const bool force_full_redraw_for_pointer_state_change =
        primary_pointer_state_changed && !input.pointers.empty();
    if (force_full_redraw_for_pointer_state_change) {
      result.diagnostics.push_back(
          "live Blink raw pointer state changed; using conservative full "
          "viewport redraw for Blink-owned pseudo-state invalidation");
    }
    ApplyRetainedScenePlan(
        result, current_scene, load_commands,
        incremental && previous_retained_scene_ ? &*previous_retained_scene_
                                                : nullptr,
        previous_snapshot, current_document_scroll, previous_document_scroll,
        force_full_redraw_for_active_animation_change ||
            force_full_redraw_for_pointer_state_change);
    RememberPrimaryPointerStateForStandaloneRenderer(input);
    previous_retained_scene_ = std::move(current_scene);
    result.diagnostics.push_back(
        "paint artifact source: real Blink PaintArtifact; "
        "extractor=real_blink_paint_artifact_extractor");
    result.diagnostics.push_back(
        "real Blink PaintArtifact exported through retained PaintOp commands");
    std::vector<ResourceCommand> typeface_resource_commands;
    for (const TypefaceResource& resource : SnapshotTypefaceResources()) {
      typeface_resource_commands.push_back(ResourceCommand::LoadTypeface(
          resource.id, resource.family_name, resource.weight, resource.width,
          resource.slant == SkFontStyle::kItalic_Slant
              ? "italic"
              : resource.slant == SkFontStyle::kOblique_Slant ? "oblique"
                                                              : "upright",
          resource.same_process_only, resource.portable_font_data_available));
    }
    // Typeface resources must precede dependent text blob resources in strict
    // replay; otherwise SkTextBlob deserialization cannot resolve BSTF ids.
    result.frame.resource_commands.insert(result.frame.resource_commands.end(),
                                          typeface_resource_commands.begin(),
                                          typeface_resource_commands.end());
    result.frame.resource_commands.insert(result.frame.resource_commands.end(),
                                          explicit_resource_commands.begin(),
                                          explicit_resource_commands.end());
    FreezeTypefaceResourcesForReplay();
    previous_resource_commands_ = result.frame.resource_commands;
    previous_hit_test_entries_ = result.hit_test_entries;
    previous_scrollable_element_entries_ = result.scrollable_element_entries;
  }

  bool PrimaryPointerStateChangedForStandaloneRenderer(
      const FrameInput& input) const {
    if (input.pointers.empty()) {
      return previous_primary_pointer_state_.has_value();
    }
    const PointerState& pointer = input.pointers.front();
    if (!previous_primary_pointer_state_) {
      return true;
    }
    const PointerState& previous = *previous_primary_pointer_state_;
    return pointer.id != previous.id || pointer.position.x != previous.position.x ||
           pointer.position.y != previous.position.y ||
           pointer.pressed != previous.pressed;
  }

  void RememberPrimaryPointerStateForStandaloneRenderer(
      const FrameInput& input) {
    if (input.pointers.empty()) {
      previous_primary_pointer_state_.reset();
      return;
    }
    previous_primary_pointer_state_ = input.pointers.front();
  }

  RendererSnapshot snapshot_;
  bool disable_retained_extraction_ = false;
  bool enable_paint_artifact_audit_ = false;
  bool trace_stages_ = false;
  bool debug_text_blob_replay_ = false;
  bool force_paint_oracle_bitmap_ = false;
  std::string lifecycle_stop_;
  bool last_pointer_pressed_ = false;
  std::optional<PointerState> previous_primary_pointer_state_;
  bool previous_needs_begin_frame_ = false;
  std::optional<Point> previous_document_max_scroll_offset_;
  std::optional<RetainedScene> previous_retained_scene_;
  std::vector<ResourceCommand> previous_resource_commands_;
  std::vector<HitTestEntry> previous_hit_test_entries_;
  std::vector<ScrollableElementEntry> previous_scrollable_element_entries_;
};

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
  return std::make_unique<LiveBlinkPageEmbedder>(std::move(create_info));
}

}  // namespace html_css_renderer
