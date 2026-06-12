#include "html_css_renderer/blink_adapter.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdio>
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
        "live Blink retained presentation allows scroll translation reuse");
  }
  if (!plan.requires_full_redraw && plan.dirty_rects.empty() &&
      !SameStringMap(previous_snapshot.element_attributes_by_id_and_name,
                     result.successor_snapshot.element_attributes_by_id_and_name)) {
    ApplyIncrementalDamage(previous_snapshot, result,
                           "live Blink retained attribute incremental render");
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
                           "live Blink retained state incremental render");
  } else if (!plan.requires_full_redraw && plan.dirty_rects.empty()) {
    result.frame = RenderFrame{};
    result.frame.requires_full_redraw = false;
    result.diagnostics.push_back(
        "live Blink retained presentation has no visual damage");
  }
  result.diagnostics.push_back(
      "live Blink RenderFrame routed through retained scene presentation plan");
}

std::string DiagnosticBlinkCoreCSSInventoryDiagnostic() {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  if (!blink_core_probe::HasStyleEnumsForStandaloneRenderer()) {
    return "diagnostic Blink core CSS/style inventory is not reachable";
  }
  return "diagnostic Blink core CSS inventory reachable: " +
         std::to_string(
             blink_core_probe::ReducedCSSPropertyCountForStandaloneRenderer()) +
         " CSS properties, " +
         std::to_string(blink_core_probe::
                            ReducedCSSValueKeywordCountForStandaloneRenderer()) +
         " CSS value keywords";
#else
  return "diagnostic Blink core CSS/style inventory is not linked";
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

std::string DiagnosticBlinkHTMLTokenizerInventoryDiagnostic(
    const std::string& html) {
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  return "diagnostic Blink HTML tokenizer inventory parsed current document: " +
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
  return "diagnostic Blink HTML tokenizer inventory is not linked";
#endif
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

bool SameRendererSnapshotForNoChangeFrame(const RendererSnapshot& left,
                                          const RendererSnapshot& right) {
  return left.html == right.html &&
         SameStylesheets(left.stylesheets, right.stylesheets) &&
         SameSize(left.viewport, right.viewport) &&
         std::abs(left.device_scale_factor - right.device_scale_factor) <=
             0.001f &&
         left.asset_namespace == right.asset_namespace &&
         std::abs(left.timeline_time_seconds - right.timeline_time_seconds) <=
             0.000001 &&
         SameStringMap(left.element_attributes_by_id_and_name,
                       right.element_attributes_by_id_and_name) &&
         SamePoint(SnapshotDocumentScrollOffset(left),
                   SnapshotDocumentScrollOffset(right)) &&
         SameNonDocumentScrollOffsets(left.scroll_offsets_by_element_id,
                                      right.scroll_offsets_by_element_id) &&
         left.focused_element_id == right.focused_element_id &&
         left.hovered_element_id == right.hovered_element_id &&
         left.active_element_id == right.active_element_id &&
         SameStringMap(left.form_values_by_element_id,
                       right.form_values_by_element_id);
}

bool FrameHasRasterDamage(const RenderFrame& frame) {
  return frame.requires_full_redraw || !frame.damage_rects.empty();
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

void TranslateScrollableElementEntries(
    std::vector<ScrollableElementEntry>& entries,
    Point delta) {
  if (SamePoint(delta, Point{})) {
    return;
  }
  for (ScrollableElementEntry& entry : entries) {
    entry.bounds.x += delta.x;
    entry.bounds.y += delta.y;
  }
}

class LiveBlinkPageEmbedder final : public BlinkPageEmbedder {
 public:
  explicit LiveBlinkPageEmbedder(BlinkPageEmbedderCreateInfo create_info) {
    enable_paint_artifact_audit_ = create_info.enable_paint_artifact_audit;
    trace_stages_ = create_info.trace_stages;
    debug_text_blob_replay_ = create_info.debug_text_blob_replay;
    lifecycle_stop_ = create_info.lifecycle_stop;
    SetTextBlobReplayDiagnosticsEnabled(debug_text_blob_replay_);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetDisableRetainedExtractionForStandaloneRenderer(
            0);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
            enable_paint_artifact_audit_ ? 1 : 0);
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
    MarkFullLifecycleWorkScheduled(result, previous_snapshot);
    TryReplaceWithLivePaintArtifactScene(result, previous_snapshot, input, false,
                                         snapshot_.html, snapshot_.stylesheets);
    FinalizeFrameWorkNeeds(result);
    return result;
  }

  RenderResult AdvanceAndRenderIncremental(const FrameInput& input) override {
    const RendererSnapshot previous_snapshot = Snapshot();
    ApplyInput(input);
    RenderResult result;
    result.successor_snapshot = snapshot_;
    if (TryRenderNoChangeFromRetainedFrame(result, previous_snapshot, input)) {
      FinalizeFrameWorkNeeds(result);
      return result;
    }
    if (TryRenderDocumentScrollOnlyFromRetainedScene(result, previous_snapshot,
                                                    input)) {
      FinalizeFrameWorkNeeds(result);
      return result;
    }
    MarkFullLifecycleWorkScheduled(result, previous_snapshot);
    TryReplaceWithLivePaintArtifactScene(result, previous_snapshot, input, true,
                                         snapshot_.html, snapshot_.stylesheets);
    FinalizeFrameWorkNeeds(result);
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

  void MarkFullLifecycleWorkScheduled(
      RenderResult& result,
      const RendererSnapshot& previous_snapshot) const {
    FrameWorkDiagnostics& work = result.frame_work;
    const bool document_changed =
        !previous_retained_scene_ || snapshot_.html != previous_snapshot.html ||
        !SameStylesheets(snapshot_.stylesheets, previous_snapshot.stylesheets);
    work.needs_document_commit = document_changed;
    work.needs_style = true;
    work.needs_layout = true;
    work.needs_prepaint = true;
    work.needs_paint = true;
    work.needs_composite_translation = true;
    work.document_commit_count = document_changed ? 1 : 0;
    work.style_update_count = 1;
    work.layout_count = 1;
    work.prepaint_count = 1;
    work.paint_count = 1;
  }

  void FinalizeFrameWorkNeeds(RenderResult& result) const {
    result.frame_work.needs_begin_frame = result.needs_begin_frame;
    result.frame_work.needs_raster = FrameHasRasterDamage(result.frame);
    result.frame_work.needs_present = result.frame_work.needs_raster;
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
    if (source_summary.clip_or_mask_rule_count > 0 &&
        !document_scroll_unchanged) {
      push_diagnostic(
          "document scroll fast path ineligible: clip or mask rules require "
          "Blink lifecycle");
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

  bool CanUseNoChangeFastPath(const RendererSnapshot& previous_snapshot,
                              const FrameInput& input,
                              std::vector<std::string>* diagnostics) const {
    const auto push_diagnostic = [&](const std::string& diagnostic) {
      if (diagnostics) {
        diagnostics->push_back(diagnostic);
      }
    };
    if (!previous_retained_scene_) {
      push_diagnostic("no-change fast path ineligible: no retained scene");
      return false;
    }
    if (input.wheel || !input.pointers.empty() ||
        !input.keyboard.pressed_key_codes.empty()) {
      push_diagnostic("no-change fast path ineligible: input event pending");
      return false;
    }
    if (previous_needs_begin_frame_) {
      push_diagnostic(
          "no-change fast path ineligible: previous Blink frame requested "
          "begin frame");
      return false;
    }
    if (!SameRendererSnapshotForNoChangeFrame(snapshot_, previous_snapshot)) {
      push_diagnostic("no-change fast path ineligible: snapshot changed");
      return false;
    }
    push_diagnostic(
        "no-change fast path eligible: retained scene and Blink begin-frame "
        "state are unchanged");
    return true;
  }

  bool TryRenderNoChangeFromRetainedFrame(
      RenderResult& result,
      const RendererSnapshot& previous_snapshot,
      const FrameInput& input) {
    if (!CanUseNoChangeFastPath(previous_snapshot, input,
                                &result.diagnostics)) {
      return false;
    }
    result.successor_snapshot = snapshot_;
    result.frame = RenderFrame{};
    result.frame.requires_full_redraw = false;
    result.damage_bounds = Rect{};
    result.damage_rects.clear();
    result.requires_full_redraw = false;
    result.needs_begin_frame = false;
    result.hit_test_entries = previous_hit_test_entries_;
    result.scrollable_element_entries = previous_scrollable_element_entries_;
    if (previous_document_max_scroll_offset_) {
      result.document_max_scroll_offset = *previous_document_max_scroll_offset_;
    }
    if (enable_paint_artifact_audit_) {
      result.raw_paint_artifact_audit_json = previous_raw_paint_artifact_audit_json_;
    }
    result.frame_work.no_change_fast_path = true;
    result.diagnostics.push_back(
        "standalone frame scheduler returned no-change frame without Blink "
        "lifecycle, PaintArtifact translation, raster, or presentation damage");
    result.diagnostics.push_back(
        "paint artifact source: real Blink PaintArtifact; "
        "extractor=real_blink_paint_artifact_extractor; "
        "reuse=no_change_retained_frame");
    result.diagnostics.push_back(
        "real Blink PaintArtifact retained state preserved from previous "
        "frame");
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
    result.frame_work.retained_scene_plan_count = 1;
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
    auto trace_stage = [&](const char* stage) {
      if (!trace_stages_) {
        return;
      }
      std::fprintf(stderr, "live_adapter.stage=%s\n", stage);
      std::fflush(stderr);
    };
    ResetTypefaceResourceRegistryForFrame();
    trace_stage("before invalidate cache");
    SetTextBlobReplayDiagnosticsEnabled(debug_text_blob_replay_);
    live_probe::StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer();
    trace_stage("after invalidate cache");
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
            0);
    live_probe::
        StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
            enable_paint_artifact_audit_ ? 1 : 0);
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
      trace_stage("before raw paint artifact audit size");
      const int raw_audit_json_size =
          live_probe::
              StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonSizeForStandaloneRenderer(
                  probe_html.c_str());
      trace_stage("after raw paint artifact audit size");
      if (raw_audit_json_size <= 0) {
        return;
      }
      std::string raw_json(static_cast<size_t>(raw_audit_json_size) + 1, '\0');
      trace_stage("before raw paint artifact audit copy");
      const int copied =
          live_probe::
              StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonForStandaloneRenderer(
                  probe_html.c_str(), raw_json.data(),
                  static_cast<int>(raw_json.size()));
      trace_stage("after raw paint artifact audit copy");
      if (copied > 0) {
        raw_json.resize(static_cast<size_t>(copied));
        result.raw_paint_artifact_audit_json = std::move(raw_json);
      }
    };
    trace_stage("before reaches PaintClean");
    if (!live_probe::StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
            probe_html.c_str())) {
      result.diagnostics.push_back(
          "real Blink PaintArtifact bridge did not reach PaintClean");
      return;
    }
    trace_stage("after reaches PaintClean");
    float applied_scroll_x = 0.0f;
    float applied_scroll_y = 0.0f;
    float max_scroll_x = 0.0f;
    float max_scroll_y = 0.0f;
    trace_stage("before document scroll query");
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
    trace_stage("after document scroll query");
    const bool prior_needs_begin_frame = previous_needs_begin_frame_;
    trace_stage("before needs begin frame query");
    result.needs_begin_frame =
        live_probe::
            StandaloneBlinkLiveFrameBridgeNeedsBeginFrameForStandaloneRenderer(
                probe_html.c_str()) != 0;
    trace_stage("after needs begin frame query");
    previous_needs_begin_frame_ = result.needs_begin_frame;
    std::array<char, 256> observed_hovered_element_id{};
    std::array<char, 256> observed_active_element_id{};
    trace_stage("before pointer observed query");
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
    trace_stage("after pointer observed query");
    trace_stage("before hit test import");
    ImportLiveHitTestEntriesForStandaloneRenderer(probe_html, result);
    trace_stage("after hit test import");
    trace_stage("before scrollable element import");
    ImportLiveScrollableElementEntriesForStandaloneRenderer(probe_html, result);
    trace_stage("after scrollable element import");
    PersistObservedScrollableElementOffsetsForStandaloneRenderer(result);
    snapshot_.scroll_offsets_by_element_id =
        result.successor_snapshot.scroll_offsets_by_element_id;

    trace_stage("before paint chunk count");
    const int chunk_count =
        live_probe::StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
            probe_html.c_str());
    trace_stage("after paint chunk count");
    copy_raw_paint_artifact_audit_json();
    if (chunk_count <= 0) {
      result.diagnostics.push_back("real Blink PaintArtifact bridge produced no chunks");
      return;
    }
    trace_stage("before exported draw op count");
    const int exported_draw_op_count =
        live_probe::StandaloneBlinkLiveFrameBridgeExportedDrawOpCountForStandaloneRenderer(
            probe_html.c_str());
    trace_stage("after exported draw op count");
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
      if (trace_stages_ && i < 16) {
        std::fprintf(stderr, "live_adapter.stage=before exported draw op %d\n", i);
        std::fflush(stderr);
      }
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
      if (trace_stages_ && i < 16) {
        std::fprintf(stderr, "live_adapter.stage=after exported draw op %d\n", i);
        std::fflush(stderr);
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
      } else if (type == 7) {
        std::array<char, 128> debug_label{};
        live_probe::
            StandaloneBlinkLiveFrameBridgeExportedDebugLabelAtForStandaloneRenderer(
                probe_html.c_str(), i, debug_label.data(),
                static_cast<int>(debug_label.size()));
        std::string diagnostic =
            "unsupported retained PaintOp requires Chromium "
            "PaintArtifactCompositor/cc source_chunk=" + active_chunk_key +
            " source_display_item=unknown op=" + std::to_string(i);
        if (debug_label[0] != '\0') {
          diagnostic += " source=";
          diagnostic += debug_label.data();
        }
        result.diagnostics.push_back(std::move(diagnostic));
        continue;
      } else if (type == 22) {
        std::array<char, 128> debug_label{};
        live_probe::
            StandaloneBlinkLiveFrameBridgeExportedDebugLabelAtForStandaloneRenderer(
                probe_html.c_str(), i, debug_label.data(),
                static_cast<int>(debug_label.size()));
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
        image.image_id = "blink-paint-image-" + std::to_string(pixel_hash);
        image.resource_id = image.image_id;
        image.mime_type = "image/x-blink-paint-image-rgba";
        image.decoded_format = PixelFormat::kRgba8888;
        image.decoded_size = Size{static_cast<float>(bitmap_width),
                                  static_cast<float>(bitmap_height)};
        image.decoded_pixels = std::move(rgba_pixels);
        image.byte_count = image.decoded_pixels.size();
        image.bytes_hash = pixel_hash;
        Rect src_rect{0.0f, 0.0f, static_cast<float>(bitmap_width),
                      static_cast<float>(bitmap_height)};
        std::string sampling_options = "filter=nearest,mipmap=none";
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
        const std::string image_id = image.image_id;
        active_commands->push_back(DrawCommand::DrawImageRect(
            image_id, src_rect, Rect{x, y, width, height}, sampling_options));
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
    result.frame_work.paint_artifact_translation_count = 1;
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
    result.frame_work.retained_scene_plan_count = 1;
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
    previous_raw_paint_artifact_audit_json_ = result.raw_paint_artifact_audit_json;
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
  bool enable_paint_artifact_audit_ = false;
  bool trace_stages_ = false;
  bool debug_text_blob_replay_ = false;
  std::string lifecycle_stop_;
  bool last_pointer_pressed_ = false;
  std::optional<PointerState> previous_primary_pointer_state_;
  bool previous_needs_begin_frame_ = false;
  std::optional<Point> previous_document_max_scroll_offset_;
  std::optional<RetainedScene> previous_retained_scene_;
  std::vector<ResourceCommand> previous_resource_commands_;
  std::vector<HitTestEntry> previous_hit_test_entries_;
  std::vector<ScrollableElementEntry> previous_scrollable_element_entries_;
  std::string previous_raw_paint_artifact_audit_json_;
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
      "diagnostic Blink platform inventory slice is linked: WTF strings, geometry, transforms, and paint property metadata");
#if defined(HTML_CSS_RENDERER_HAS_REDUCED_BLINK_CORE)
  status.diagnostics.push_back(
      "diagnostic Blink core inventory slice is linked: Document, DocumentInit, HTMLDocument, generated style/name tables, and paint result types");
  status.diagnostics.push_back(DiagnosticBlinkCoreCSSInventoryDiagnostic());
  status.diagnostics.push_back(DiagnosticBlinkHTMLTokenizerInventoryDiagnostic(
      "<main><img src='asset.png'><p>Blink tree builder</p></main>"));
#endif
  status.diagnostics.push_back(
      "CreateLiveBlinkPageEmbedder requires the live DummyPageHolder/"
      "LocalFrameView PaintArtifact bridge; standalone lifecycle renderer "
      "is not exposed");
#else
  status.diagnostics.push_back(
      "diagnostic Blink platform inventory slice is not linked into this adapter build");
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
