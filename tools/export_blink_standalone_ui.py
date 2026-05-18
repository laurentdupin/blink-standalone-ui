#!/usr/bin/env python3
"""Export the current standalone Blink renderer cut into a new source tree.

The export intentionally preserves Chromium-relative paths under
`upstream/chromium/` so every copied source can be traced back to its origin.
The generated manifest is the contract for later updates and for replacing
the current command-dump based build with CMake or Visual Studio projects.
"""

from __future__ import annotations

import argparse
import ast
import hashlib
import json
import os
import pathlib
import re
import shutil
import sys
from dataclasses import dataclass
from typing import Iterable


CHROMIUM_ROOT = pathlib.Path(__file__).resolve().parents[2]
DEFAULT_DESTINATION = CHROMIUM_ROOT.parent / "blink-standalone-ui"

SKIP_DIR_NAMES = {
    ".git",
    "__pycache__",
    "_pydeps",
    "node_modules",
}

SKIP_SUFFIXES = {
    ".exe",
    ".dll",
    ".ilk",
    ".lib",
    ".obj",
    ".pdb",
    ".pyc",
    ".rlib",
}

TEXT_EXTENSIONS = {
    ".c",
    ".cc",
    ".cpp",
    ".cxx",
    ".h",
    ".hh",
    ".hpp",
    ".hxx",
    ".inc",
    ".inl",
    ".ipp",
    ".gn",
    ".gni",
    ".isolate",
    ".json",
    ".md",
    ".mojom",
    ".py",
    ".txt",
    ".typemap",
    ".yml",
}

ROOT_COPY_DIRS = (
    "standalone_renderer/include",
    "standalone_renderer/src",
    "standalone_renderer/stubs",
    "standalone_renderer/examples",
    "standalone_renderer/tools",
    "third_party/blink/renderer/core",
    "third_party/blink/renderer/bindings",
    "third_party/blink/renderer/platform",
    "third_party/blink/common",
    "third_party/blink/public/common",
    "third_party/blink/public/platform",
    "third_party/blink/public/web",
    "third_party/blink/public/mojom",
    "cc/animation",
    "cc/base",
    "cc/benchmarks",
    "cc/debug",
    "cc/input",
    "cc/layers",
    "cc/metrics",
    "cc/paint",
    "cc/resources",
    "cc/scheduler",
    "cc/tiles",
    "cc/trees",
    "cc/view_transition",
    "url",
    "ui/base",
    "ui/accessibility",
    "ui/color",
    "ui/display",
    "ui/events",
    "ui/gfx",
    "ui/latency",
    "ui/native_theme",
    "base",
    "components/content_settings/core/common",
    "components/performance_manager/public/mojom",
    "components/subresource_filter/core/common",
    "components/shared_highlighting/core/common",
    "components/viz/common",
    "net/base",
    "net/cert",
    "net/cookies",
    "net/dns/public",
    "net/first_party_sets",
    "net/filter",
    "net/http",
    "net/nqe",
    "net/storage_access_api",
    "net/ssl",
    "services/network/public/cpp",
    "services/metrics/public/cpp",
    "services/viz/public/mojom",
    "device/base/synchronization",
    "gin",
    "gpu/command_buffer/common",
    "ipc",
    "media/audio",
    "media/base",
    "skia/ext",
    "skia/public/mojom",
    "mojo/public/c",
    "mojo/public/cpp",
    "mojo/public/mojom",
    "third_party/abseil-cpp/absl",
    "third_party/boringssl/src/include",
    "third_party/boringssl/src/pki",
    "third_party/googletest/src/googletest/include",
    "third_party/highway/src",
    "third_party/icu/source/common",
    "third_party/icu/source/i18n",
    "third_party/liburlpattern",
    "third_party/libxml/src/include",
    "third_party/libxml/win32/include",
    "third_party/modp_b64",
    "third_party/ots/include",
    "third_party/perfetto/include",
    "third_party/perfetto/protos",
    "third_party/perfetto/src/base/include",
    "third_party/perfetto/src/tracing",
    "third_party/rapidhash",
    "third_party/skia",
    "third_party/simdutf",
    "third_party/zlib",
    "testing/gtest/include",
    "v8/include",
    "build",
    "buildtools/third_party/libc++",
)

ROOT_COPY_FILES = (
    "cc/cc_export.h",
    "ui/gl/angle_implementation.h",
)

GENERATED_COPY_DIRS = (
    "gen/build",
    "gen/base",
    "gen/cc",
    "gen/components/performance_manager",
    "gen/device",
    "gen/mojo",
    "gen/net",
    "gen/services/network",
    "gen/services/metrics",
    "gen/services/viz",
    "gen/skia",
    "gen/third_party/blink",
    "gen/third_party/perfetto",
    "gen/ui",
    "gen/v8",
)

COMMAND_DUMPS = (
    "generated/blink_live/html_css_renderer_blink_cli.commands.txt",
    "generated/blink_live/blink_tree_builder_link_probe.commands.txt",
    "generated/blink_live/blink_dom_link_probe.commands.txt",
    "generated/blink_live/standalone_blink_sdl.commands.txt",
    "generated/blink_live/live_frame_bridge_link_probe.rsp",
)

EXTRA_LIVE_SOURCES = (
    "base/synchronization/lock.cc",
    "base/synchronization/atomic_flag.cc",
    "base/threading/platform_thread_ref.cc",
    "cc/base/features.cc",
    "cc/base/region.cc",
    "cc/paint/draw_looper.cc",
    "cc/paint/element_id.cc",
    "cc/paint/filter_operation.cc",
    "cc/paint/filter_operations.cc",
    "cc/paint/paint_flags.cc",
    "cc/paint/paint_filter.cc",
    "cc/paint/paint_image.cc",
    "cc/paint/paint_image_builder.cc",
    "cc/paint/paint_op.cc",
    "cc/paint/paint_op_buffer.cc",
    "cc/paint/paint_op_buffer_iterator.cc",
    "cc/paint/paint_op_reader.cc",
    "cc/paint/paint_op_writer.cc",
    "cc/paint/paint_record.cc",
    "cc/paint/paint_recorder.cc",
    "cc/paint/paint_shader.cc",
    "cc/paint/path_effect.cc",
    "cc/paint/record_paint_canvas.cc",
    "cc/paint/render_surface_filters.cc",
    "cc/paint/skia_paint_canvas.cc",
    "cc/paint/skia_paint_image_generator.cc",
    "cc/paint/paint_worklet_input.cc",
    "cc/paint/display_item_list.cc",
    "cc/paint/color_filter.cc",
    "cc/paint/decode_stashing_image_provider.cc",
    "cc/paint/decoded_draw_image.cc",
    "cc/paint/draw_image.cc",
    "cc/paint/image_provider.cc",
    "cc/paint/paint_image_generator.cc",
    "cc/paint/scoped_raster_flags.cc",
    "cc/paint/skottie_serialization_history.cc",
    "cc/paint/skottie_text_property_value.cc",
    "cc/paint/tone_map_util.cc",
    "mojo/public/cpp/bindings/lib/buffer.cc",
    "generated/blink_live/gen/third_party/blink/renderer/core/style/computed_style_base.cc",
    "generated/blink_live/gen/third_party/blink/renderer/core/style/computed_style_base_constants.cc",
    "generated/blink_live/gen/third_party/blink/renderer/core/style_property_shorthand.cc",
    "generated/blink_live/gen/third_party/blink/renderer/core/css/properties/css_property_instances.cc",
    "generated/blink_live/gen/third_party/blink/renderer/core/css/properties/longhands.cc",
    "generated/blink_live/gen/third_party/blink/renderer/core/css/properties/shorthands.cc",
    "ui/gfx/animation/keyframe/timing_function.cc",
    "ui/gfx/geometry/point.cc",
    "ui/gfx/geometry/point_conversions.cc",
    "ui/gfx/geometry/rrect_f.cc",
    "ui/gfx/geometry/skia_conversions.cc",
    "ui/gfx/geometry/size.cc",
    "ui/gfx/geometry/size_conversions.cc",
    "third_party/blink/renderer/core/animation/animation_time_delta.cc",
    "third_party/blink/renderer/core/animation/css/css_animation_data.cc",
    "third_party/blink/renderer/core/animation/css/css_timing_data.cc",
    "third_party/blink/renderer/core/animation/css/css_transition_data.cc",
    "third_party/blink/renderer/core/css/css_color.cc",
    "third_party/blink/renderer/core/css/css_gradient_value.cc",
    "third_party/blink/renderer/core/css/css_axis_value.cc",
    "third_party/blink/renderer/core/css/css_basic_shape_values.cc",
    "third_party/blink/renderer/core/css/css_border_image.cc",
    "third_party/blink/renderer/core/css/css_border_image_slice_value.cc",
    "third_party/blink/renderer/core/css/css_bracketed_value_list.cc",
    "third_party/blink/renderer/core/css/css_content_distribution_value.cc",
    "third_party/blink/renderer/core/css/css_custom_ident_value.cc",
    "third_party/blink/renderer/core/css/css_inherited_value.cc",
    "third_party/blink/renderer/core/css/css_length_resolver.cc",
    "third_party/blink/renderer/core/css/css_markup.cc",
    "third_party/blink/renderer/core/css/css_math_expression_node.cc",
    "third_party/blink/renderer/core/css/css_math_function_value.cc",
    "third_party/blink/renderer/core/css/css_math_operator.cc",
    "third_party/blink/renderer/core/css/css_numeric_literal_value.cc",
    "third_party/blink/renderer/core/css/css_primitive_value.cc",
    "third_party/blink/renderer/core/css/css_property_name.cc",
    "third_party/blink/renderer/core/css/css_ray_value.cc",
    "third_party/blink/renderer/core/css/css_ratio_value.cc",
    "third_party/blink/renderer/core/css/css_repeat_style_value.cc",
    "third_party/blink/renderer/core/css/css_repeat_value.cc",
    "third_party/blink/renderer/core/css/css_revert_layer_value.cc",
    "third_party/blink/renderer/core/css/css_revert_rule_value.cc",
    "third_party/blink/renderer/core/css/css_revert_value.cc",
    "third_party/blink/renderer/core/css/css_scroll_value.cc",
    "third_party/blink/renderer/core/css/css_string_value.cc",
    "third_party/blink/renderer/core/css/css_syntax_definition.cc",
    "third_party/blink/renderer/core/css/css_to_length_conversion_data.cc",
    "third_party/blink/renderer/core/css/css_unset_value.cc",
    "third_party/blink/renderer/core/css/css_uri_value.cc",
    "third_party/blink/renderer/core/css/css_variable_data.cc",
    "third_party/blink/renderer/core/css/css_value_list.cc",
    "third_party/blink/renderer/core/css/css_view_value.cc",
    "third_party/blink/renderer/core/css/css_value_clamping_utils.cc",
    "third_party/blink/renderer/core/css/css_gap_decoration_property_utils.cc",
    "third_party/blink/renderer/core/css/cssom_utils.cc",
    "third_party/blink/renderer/core/css/cssom/css_keyword_value.cc",
    "third_party/blink/renderer/core/css/cssom/css_unsupported_color.cc",
    "third_party/blink/renderer/core/css/cssom/css_paint_worklet_input.cc",
    "third_party/blink/renderer/core/css/cssom/cross_thread_color_value.cc",
    "third_party/blink/renderer/core/css/cssom/cross_thread_keyword_value.cc",
    "third_party/blink/renderer/core/css/properties/computed_style_utils.cc",
    "third_party/blink/renderer/core/css/properties/css_color_function_parser.cc",
    "third_party/blink/renderer/core/css/properties/css_direction_aware_resolver.cc",
    "third_party/blink/renderer/core/css/properties/css_property.cc",
    "third_party/blink/renderer/core/css/property_registry.cc",
    "third_party/blink/renderer/core/css/parser/css_parser_fast_paths.cc",
    "third_party/blink/renderer/core/css/parser/css_parser_local_context.cc",
    "third_party/blink/renderer/core/css/resolver/css_to_style_map.cc",
    "third_party/blink/renderer/core/css/resolver/style_builder_converter.cc",
    "third_party/blink/renderer/core/css/resolver/transform_builder.cc",
    "third_party/blink/renderer/core/css/properties/shorthands/shorthands_custom.cc",
    "third_party/blink/renderer/core/css/style_color.cc",
    "third_party/blink/renderer/core/css/style_change_reason.cc",
    "third_party/blink/renderer/core/css/style_property_shorthand_custom.cc",
    "third_party/blink/renderer/core/dom/text_link_colors.cc",
    "third_party/blink/renderer/core/html/html_script_element.cc",
    "third_party/blink/renderer/core/layout/layout_box_model_object.cc",
    "third_party/blink/renderer/core/layout/geometry/physical_rect.cc",
    "third_party/blink/renderer/core/layout/layout_invalidation_reason.cc",
    "third_party/blink/renderer/core/layout/min_max_sizes.cc",
    "third_party/blink/renderer/core/layout/logical_fragment_link.cc",
    "third_party/blink/renderer/core/layout/layout_object_hot.cc",
    "third_party/blink/renderer/core/layout/flex/flex_child_iterator.cc",
    "third_party/blink/renderer/core/layout/flex/flex_gap_accumulator.cc",
    "third_party/blink/renderer/core/layout/flex/flex_item_iterator.cc",
    "third_party/blink/renderer/core/layout/flex/flex_layout_algorithm.cc",
    "third_party/blink/renderer/core/layout/flex/flex_line_breaker.cc",
    "third_party/blink/renderer/core/layout/flex/layout_flexible_box.cc",
    "third_party/blink/renderer/core/layout/flex/line_flexer.cc",
    "third_party/blink/renderer/core/layout/gap/cross_gap.cc",
    "third_party/blink/renderer/core/layout/gap/gap_geometry.cc",
    "third_party/blink/renderer/core/layout/gap/gap_utils.cc",
    "third_party/blink/renderer/core/layout/gap/main_gap.cc",
    "third_party/blink/renderer/core/layout/grid/grid_item.cc",
    "third_party/blink/renderer/core/layout/grid/grid_layout_algorithm.cc",
    "third_party/blink/renderer/core/layout/grid/grid_layout_utils.cc",
    "third_party/blink/renderer/core/layout/grid/grid_line_resolver.cc",
    "third_party/blink/renderer/core/layout/grid/grid_named_line_collection.cc",
    "third_party/blink/renderer/core/layout/grid/grid_node.cc",
    "third_party/blink/renderer/core/layout/grid/grid_placement.cc",
    "third_party/blink/renderer/core/layout/grid/grid_sizing_tree.cc",
    "third_party/blink/renderer/core/layout/grid/grid_track_collection.cc",
    "third_party/blink/renderer/core/layout/grid/grid_track_sizing_algorithm.cc",
    "third_party/blink/renderer/core/layout/grid/layout_grid.cc",
    "third_party/blink/renderer/core/layout/grid_lanes/grid_lanes_layout_algorithm.cc",
    "third_party/blink/renderer/core/layout/grid_lanes/grid_lanes_node.cc",
    "third_party/blink/renderer/core/layout/grid_lanes/grid_lanes_running_positions.cc",
    "third_party/blink/renderer/core/layout/grid_lanes/layout_grid_lanes.cc",
    "third_party/blink/renderer/core/style/filter_operations.cc",
    "third_party/blink/renderer/core/style/fill_layer.cc",
    "third_party/blink/renderer/core/style/applied_text_decoration.cc",
    "third_party/blink/renderer/core/style/anchor_specifier_value.cc",
    "third_party/blink/renderer/core/style/computed_grid_template_areas.cc",
    "third_party/blink/renderer/core/style/content_data.cc",
    "third_party/blink/renderer/core/style/grid_track_list.cc",
    "third_party/blink/renderer/core/style/nine_piece_image.cc",
    "third_party/blink/renderer/core/style/style_aspect_ratio.cc",
    "third_party/blink/renderer/core/style/style_initial_data.cc",
    "third_party/blink/renderer/core/style/style_initial_letter.cc",
    "third_party/blink/renderer/core/style/list_style_type_data.cc",
    "third_party/blink/renderer/core/style/position_try_fallbacks.cc",
    "third_party/blink/renderer/core/style/reference_clip_path_operation.cc",
    "third_party/blink/renderer/core/style/style_highlight_data.cc",
    "third_party/blink/renderer/core/style/style_scrollbar_color.cc",
    "third_party/blink/renderer/core/style/style_svg_resource.cc",
    "third_party/blink/renderer/core/style/style_variables.cc",
    "third_party/blink/renderer/core/style/style_generated_image.cc",
    "third_party/blink/renderer/core/style/svg_paint.cc",
    "third_party/blink/renderer/core/style/text_decoration_thickness.cc",
    "third_party/blink/renderer/platform/fonts/font_description.cc",
    "third_party/blink/renderer/platform/fonts/font_fallback_map.cc",
    "third_party/blink/renderer/platform/fonts/font_family.cc",
    "third_party/blink/renderer/platform/fonts/font_optical_sizing.cc",
    "third_party/blink/renderer/platform/fonts/font_orientation.cc",
    "third_party/blink/renderer/platform/fonts/font_palette.cc",
    "third_party/blink/renderer/platform/fonts/font_selection_types.cc",
    "third_party/blink/renderer/platform/fonts/generic_font_family_settings.cc",
    "third_party/blink/renderer/platform/fonts/font_smoothing_mode.cc",
    "third_party/blink/renderer/platform/fonts/font_size_adjust.cc",
    "third_party/blink/renderer/platform/fonts/font_selector.cc",
    "third_party/blink/renderer/platform/fonts/simple_font_data.cc",
    "third_party/blink/renderer/platform/fonts/font_variant_emoji.cc",
    "third_party/blink/renderer/platform/fonts/font_variant_east_asian.cc",
    "third_party/blink/renderer/platform/fonts/font_variant_numeric.cc",
    "third_party/blink/renderer/platform/fonts/font_width_variant.cc",
    "third_party/blink/renderer/platform/fonts/opentype/font_settings.cc",
    "third_party/blink/renderer/platform/fonts/resolved_font_features.cc",
    "third_party/blink/renderer/platform/fonts/text_rendering_mode.cc",
    "third_party/blink/renderer/platform/animation/timing_function.cc",
    "third_party/blink/renderer/platform/geometry/calculation_value.cc",
    "third_party/blink/renderer/platform/geometry/calculation_expression_node.cc",
    "third_party/blink/renderer/platform/geometry/length.cc",
    "third_party/blink/renderer/platform/geometry/length_functions.cc",
    "third_party/blink/renderer/platform/geometry/math_functions.cc",
    "third_party/blink/renderer/platform/graphics/color.cc",
    "third_party/blink/renderer/platform/text/quotes_data.cc",
    "third_party/blink/renderer/platform/text/writing_direction_mode.cc",
    "third_party/blink/renderer/core/svg/svg_parser_utilities.cc",
    "third_party/perfetto/src/tracing/internal/checked_scope.cc",
    "third_party/harfbuzz/src/src/harfbuzz.cc",
    "third_party/simdutf/simdutf.cpp",
    "skia/ext/skcms_ext.cc",
    "generated/blink_live/gen/third_party/blink/renderer/platform/font_family_names.cc",
    "third_party/skia/src/base/SkBuffer.cpp",
    "third_party/skia/src/base/SkContainers.cpp",
    "third_party/skia/src/base/SkDebug.cpp",
    "third_party/skia/src/base/SkDeque.cpp",
    "third_party/skia/src/base/SkMalloc.cpp",
    "third_party/skia/src/base/SkTDArray.cpp",
    "third_party/skia/src/base/SkUTF.cpp",
    "third_party/skia/src/base/SkUtils.cpp",
    "third_party/skia/src/core/SkBitmap.cpp",
    "third_party/skia/src/core/SkBitmapDevice.cpp",
    "third_party/skia/src/core/SkBlendMode.cpp",
    "third_party/skia/src/core/SkBlendModeBlender.cpp",
    "third_party/skia/src/core/SkColor.cpp",
    "third_party/skia/src/core/SkColorFilter.cpp",
    "third_party/skia/src/core/SkColorSpace.cpp",
    "third_party/skia/src/core/SkColorSpaceXformSteps.cpp",
    "third_party/skia/src/core/SkColorTable.cpp",
    "third_party/skia/src/core/SkConvertPixels.cpp",
    "third_party/skia/src/core/SkCanvas.cpp",
    "third_party/skia/src/core/SkCanvas_Raster.cpp",
    "third_party/skia/src/core/SkCanvasPriv.cpp",
    "third_party/skia/src/core/SkBlitter.cpp",
    "third_party/skia/src/core/SkContourMeasure.cpp",
    "third_party/skia/src/core/SkCPURecorder.cpp",
    "third_party/skia/src/core/SkData.cpp",
    "third_party/skia/src/core/SkDescriptor.cpp",
    "third_party/skia/src/core/SkEdgeClipper.cpp",
    "third_party/skia/src/core/SkFont.cpp",
    "third_party/skia/src/core/SkFont_serial.cpp",
    "third_party/skia/src/core/SkFontDescriptor.cpp",
    "third_party/skia/src/core/SkFontMgr.cpp",
    "third_party/skia/src/core/SkFontStream.cpp",
    "third_party/skia/src/core/SkGlyph.cpp",
    "third_party/skia/src/core/SkGlyphRunPainter.cpp",
    "third_party/skia/src/core/SkMatrix.cpp",
    "third_party/skia/src/core/SkM44.cpp",
    "third_party/skia/src/core/SkImageInfo.cpp",
    "third_party/skia/src/core/SkImageFilter.cpp",
    "third_party/skia/src/core/SkImageFilterCache.cpp",
    "third_party/skia/src/core/SkImageFilterTypes.cpp",
    "third_party/skia/src/core/SkGeometry.cpp",
    "third_party/skia/src/core/SkPath.cpp",
    "third_party/skia/src/core/SkPathBuilder.cpp",
    "third_party/skia/src/core/SkPathData.cpp",
    "third_party/skia/src/core/SkPathIter.cpp",
    "third_party/skia/src/core/SkPathMeasure.cpp",
    "third_party/skia/src/core/SkPathPriv.cpp",
    "third_party/skia/src/core/SkPathRawShapes.cpp",
    "third_party/skia/src/core/SkPathUtils.cpp",
    "third_party/skia/src/core/SkPaint.cpp",
    "third_party/skia/src/core/SkPoint.cpp",
    "third_party/skia/src/core/SkMallocPixelRef.cpp",
    "third_party/skia/src/core/SkMask.cpp",
    "third_party/skia/src/core/SkMasks.cpp",
    "third_party/skia/src/core/SkPicture.cpp",
    "third_party/skia/src/core/SkPictureData.cpp",
    "third_party/skia/src/core/SkPictureFlat.cpp",
    "third_party/skia/src/core/SkPicturePlayback.cpp",
    "third_party/skia/src/core/SkPictureRecord.cpp",
    "third_party/skia/src/core/SkPictureRecorder.cpp",
    "third_party/skia/src/core/SkPtrRecorder.cpp",
    "third_party/skia/src/core/SkPixmap.cpp",
    "third_party/skia/src/core/SkPixelRef.cpp",
    "third_party/skia/src/core/SkReadBuffer.cpp",
    "third_party/skia/src/core/SkRect.cpp",
    "third_party/skia/src/core/SkRegion.cpp",
    "third_party/skia/src/core/SkRegion_path.cpp",
    "third_party/skia/src/core/SkRRect.cpp",
    "third_party/skia/src/core/SkString.cpp",
    "third_party/skia/src/core/SkStringUtils.cpp",
    "third_party/skia/src/core/SkTextBlob.cpp",
    "third_party/skia/src/core/SkTypeface.cpp",
    "third_party/skia/src/core/SkVertices.cpp",
    "third_party/skia/src/core/SkTypefaceCache.cpp",
    "third_party/skia/src/core/SkScalerContext.cpp",
    "third_party/skia/src/core/SkScan.cpp",
    "third_party/skia/src/core/SkScan_AAAPath.cpp",
    "third_party/skia/src/core/SkScan_AntiPath.cpp",
    "third_party/skia/src/core/SkScan_Antihair.cpp",
    "third_party/skia/src/core/SkScan_Hairline.cpp",
    "third_party/skia/src/core/SkScan_Path.cpp",
    "third_party/skia/src/core/SkStream.cpp",
    "third_party/skia/src/core/SkStrike.cpp",
    "third_party/skia/src/core/SkStrikeCache.cpp",
    "third_party/skia/src/core/SkStrikeSpec.cpp",
    "third_party/skia/src/core/SkWritePixelsRec.cpp",
    "third_party/skia/src/core/SkWriteBuffer.cpp",
    "third_party/skia/src/core/SkBlurMaskFilterImpl.cpp",
    "third_party/skia/src/core/SkBlurMask.cpp",
    "third_party/skia/src/core/SkCachedData.cpp",
    "third_party/skia/src/core/SkDevice.cpp",
    "third_party/skia/src/core/SkFlattenable.cpp",
    "third_party/skia/src/core/SkImageGenerator.cpp",
    "third_party/skia/src/core/SkMaskFilter.cpp",
    "third_party/skia/src/core/SkMaskFilterBase.cpp",
    "third_party/skia/src/core/SkPaintPriv.cpp",
    "third_party/skia/src/core/SkResourceCache.cpp",
    "third_party/skia/src/core/SkSpecialImage.cpp",
    "third_party/skia/src/core/SkLocalMatrixImageFilter.cpp",
    "third_party/skia/src/effects/colorfilters/SkBlendModeColorFilter.cpp",
    "third_party/skia/src/effects/colorfilters/SkColorFilterBase.cpp",
    "third_party/skia/src/effects/colorfilters/SkColorSpaceXformColorFilter.cpp",
    "third_party/skia/src/effects/colorfilters/SkComposeColorFilter.cpp",
    "third_party/skia/src/effects/colorfilters/SkMatrixColorFilter.cpp",
    "third_party/skia/src/effects/colorfilters/SkTableColorFilter.cpp",
    "third_party/skia/src/effects/SkCornerPathEffect.cpp",
    "third_party/skia/src/effects/SkDashPathEffect.cpp",
    "third_party/skia/src/effects/imagefilters/SkBlurImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkBlendImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkColorFilterImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkComposeImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkCropImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkDisplacementMapImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkDropShadowImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkImageImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkLightingImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkMagnifierImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkMatrixConvolutionImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkMatrixTransformImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkMergeImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkMorphologyImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkPictureImageFilter.cpp",
    "third_party/skia/src/effects/imagefilters/SkShaderImageFilter.cpp",
    "third_party/skia/src/image/SkSurface.cpp",
    "third_party/skia/src/image/SkSurface_Base.cpp",
    "third_party/skia/src/image/SkImage.cpp",
    "third_party/skia/src/image/SkImage_Lazy.cpp",
    "third_party/skia/src/image/SkImage_LazyFactories.cpp",
    "third_party/skia/src/image/SkImage_Raster.cpp",
    "third_party/skia/src/image/SkImage_RasterFactories.cpp",
    "third_party/skia/src/image/SkTiledImageUtils.cpp",
    "third_party/skia/src/core/SkAnnotation.cpp",
    "third_party/skia/src/pdf/SkDocument_PDF_None.cpp",
    "third_party/skia/src/shaders/SkImageShader.cpp",
    "third_party/skia/src/shaders/SkBlendShader.cpp",
    "third_party/skia/src/shaders/SkColorShader.cpp",
    "third_party/skia/src/shaders/SkEmptyShader.cpp",
    "third_party/skia/src/shaders/SkPerlinNoiseShaderImpl.cpp",
    "third_party/skia/src/shaders/SkPictureShader.cpp",
    "third_party/skia/src/shaders/SkShaderBase.cpp",
    "third_party/skia/src/shaders/SkShader.cpp",
    "third_party/skia/src/shaders/SkLocalMatrixShader.cpp",
    "third_party/skia/src/shaders/SkTransformShader.cpp",
    "third_party/skia/src/shaders/SkTriColorShader.cpp",
    "third_party/skia/src/shaders/gradients/SkConicalGradient.cpp",
    "third_party/skia/src/shaders/gradients/SkGradientBaseShader.cpp",
    "third_party/skia/src/shaders/gradients/SkLinearGradient.cpp",
    "third_party/skia/src/shaders/gradients/SkRadialGradient.cpp",
    "third_party/skia/src/shaders/gradients/SkSweepGradient.cpp",
    "skia/ext/legacy_display_globals.cc",
    "third_party/skia/modules/skcms/skcms.cc",
    "third_party/skia/modules/skcms/src/skcms_TransformBaseline.cc",
    "third_party/skia/src/text/GlyphRun.cpp",
    "third_party/skia/src/text/StrikeForGPU.cpp",
    "third_party/skia/src/base/SkArenaAlloc.cpp",
    "third_party/skia/src/base/SkBezierCurves.cpp",
    "third_party/skia/src/base/SkBlockAllocator.cpp",
    "third_party/skia/src/base/SkCubics.cpp",
    "third_party/skia/src/base/SkQuads.cpp",
    "third_party/skia/src/pathops/SkAddIntersections.cpp",
    "third_party/skia/src/pathops/SkDCubicLineIntersection.cpp",
    "third_party/skia/src/pathops/SkDConicLineIntersection.cpp",
    "third_party/skia/src/pathops/SkDLineIntersection.cpp",
    "third_party/skia/src/pathops/SkDQuadLineIntersection.cpp",
    "third_party/skia/src/pathops/SkIntersections.cpp",
    "third_party/skia/src/pathops/SkOpAngle.cpp",
    "third_party/skia/src/pathops/SkOpBuilder.cpp",
    "third_party/skia/src/pathops/SkOpCoincidence.cpp",
    "third_party/skia/src/pathops/SkOpContour.cpp",
    "third_party/skia/src/pathops/SkOpCubicHull.cpp",
    "third_party/skia/src/pathops/SkOpEdgeBuilder.cpp",
    "third_party/skia/src/pathops/SkOpSegment.cpp",
    "third_party/skia/src/pathops/SkOpSpan.cpp",
    "third_party/skia/src/pathops/SkPathOpsAsWinding.cpp",
    "third_party/skia/src/pathops/SkPathOpsCommon.cpp",
    "third_party/skia/src/pathops/SkPathOpsConic.cpp",
    "third_party/skia/src/pathops/SkPathOpsCubic.cpp",
    "third_party/skia/src/pathops/SkPathOpsCurve.cpp",
    "third_party/skia/src/pathops/SkPathOpsDebug.cpp",
    "third_party/skia/src/pathops/SkPathOpsLine.cpp",
    "third_party/skia/src/pathops/SkPathOpsOp.cpp",
    "third_party/skia/src/pathops/SkPathOpsQuad.cpp",
    "third_party/skia/src/pathops/SkPathOpsRect.cpp",
    "third_party/skia/src/pathops/SkPathOpsSimplify.cpp",
    "third_party/skia/src/pathops/SkPathOpsTightBounds.cpp",
    "third_party/skia/src/pathops/SkPathOpsTSect.cpp",
    "third_party/skia/src/pathops/SkPathOpsTypes.cpp",
    "third_party/skia/src/pathops/SkPathOpsWinding.cpp",
    "third_party/skia/src/pathops/SkPathWriter.cpp",
    "third_party/skia/src/pathops/SkReduceOrder.cpp",
    "third_party/skia/src/utils/SkParse.cpp",
    "third_party/skia/src/utils/SkParsePath.cpp",
    "third_party/skia/src/utils/SkNullCanvas.cpp",
    "third_party/skia/src/utils/SkMatrix22.cpp",
    "third_party/skia/src/utils/SkCustomTypeface.cpp",
    "third_party/skia/src/utils/SkDashPath.cpp",
    "third_party/skia/src/utils/SkShadowTessellator.cpp",
    "third_party/skia/src/utils/SkShadowUtils.cpp",
    "third_party/skia/src/base/SkSemaphore.cpp",
    "third_party/skia/src/base/SkSafeMath.cpp",
    "third_party/skia/src/base/SkFloatingPoint.cpp",
    "third_party/skia/src/ports/SkMemory_malloc.cpp",
    "third_party/skia/src/ports/SkLog_win.cpp",
    "third_party/skia/src/core/SkBlitMask_opts.cpp",
    "third_party/skia/src/core/SkBlitRow_D32.cpp",
    "third_party/skia/src/core/SkMemset_opts.cpp",
    "third_party/skia/src/core/SkBitmapCache.cpp",
    "third_party/skia/src/core/SkAutoPixmapStorage.cpp",
    "third_party/skia/src/core/SkBigPicture.cpp",
    "third_party/skia/src/core/SkCompressedDataUtils.cpp",
    "third_party/skia/src/core/SkCPUContext.cpp",
    "third_party/skia/src/core/SkDrawable.cpp",
    "third_party/skia/src/core/SkRecord.cpp",
    "third_party/skia/src/core/SkRecordCanvas.cpp",
    "third_party/skia/src/core/SkRecordDraw.cpp",
    "third_party/skia/src/core/SkRecordedDrawable.cpp",
    "third_party/skia/src/core/SkRecordOpts.cpp",
    "third_party/skia/src/core/SkRecords.cpp",
    "third_party/skia/src/core/SkWriter32.cpp",
    "third_party/skia/src/core/SkIDChangeListener.cpp",
    "third_party/skia/src/core/SkAAClip.cpp",
    "third_party/skia/src/core/SkAlphaRuns.cpp",
    "third_party/skia/src/core/SkAnalyticEdge.cpp",
    "third_party/skia/src/core/SkBlurEngine.cpp",
    "third_party/skia/src/core/SkCubicClipper.cpp",
    "third_party/skia/src/core/SkEdge.cpp",
    "third_party/skia/src/core/SkEdgeBuilder.cpp",
    "third_party/skia/src/core/SkGraphics.cpp",
    "third_party/skia/src/core/SkLineClipper.cpp",
    "third_party/skia/src/core/SkMaskGamma.cpp",
    "third_party/skia/src/core/SkOpts.cpp",
    "third_party/skia/src/core/SkPathEffect.cpp",
    "third_party/skia/src/core/SkPathRaw.cpp",
    "third_party/skia/src/core/SkPath_serial.cpp",
    "third_party/skia/src/core/SkPixelStorage.cpp",
    "third_party/skia/src/core/SkScalar.cpp",
    "third_party/skia/src/core/SkSwizzler_opts.cpp",
    "third_party/skia/src/core/SkSpriteBlitter_ARGB32.cpp",
    "third_party/skia/src/core/SkStroke.cpp",
    "third_party/skia/src/core/SkVertState.cpp",
    "third_party/skia/src/core/SkLatticeIter.cpp",
    "third_party/skia/src/core/SkMatrixInvert.cpp",
    "third_party/skia/src/core/SkMipmap.cpp",
    "third_party/skia/src/core/SkMipmapAccessor.cpp",
    "third_party/skia/src/core/SkMipmapBuilder.cpp",
    "third_party/skia/src/core/SkPixmapDraw.cpp",
    "third_party/skia/src/core/SkYUVAPixmaps.cpp",
    "third_party/skia/src/core/SkYUVAInfo.cpp",
    "third_party/skia/src/core/SkYUVPlanesCache.cpp",
    "third_party/skia/src/image/SkImage_Base.cpp",
    "third_party/skia/src/image/SkImage_Picture.cpp",
    "third_party/skia/src/image/SkImage_Raster.cpp",
    "third_party/skia/src/text/SlugFromBuffer.cpp",
    "third_party/skia/src/image/SkSurface_Raster.cpp",
    "third_party/skia/src/effects/colorfilters/SkWorkingFormatColorFilter.cpp",
    "skia/ext/switches.cc",
    "third_party/skia/src/core/SkBlitRow_opts.cpp",
    "third_party/skia/src/core/SkCapabilities.cpp",
    "third_party/skia/src/core/SkCpu.cpp",
    "third_party/skia/src/core/SkFlattenable.cpp",
    "third_party/skia/src/core/SkGlobalInitialization_core.cpp",
    "third_party/skia/src/core/SkGaussFilter.cpp",
    "third_party/skia/src/core/SkMaskBlurFilter.cpp",
    "third_party/skia/src/core/SkMipmapHQDownSampler.cpp",
    "third_party/skia/src/core/SkRSXform.cpp",
    "third_party/skia/src/core/SkDrawShadowInfo.cpp",
    "third_party/skia/src/core/SkResourceCache.cpp",
    "third_party/skia/src/core/SkStrokerPriv.cpp",
    "third_party/skia/src/core/SkSynchronizedResourceCache.cpp",
    "third_party/skia/src/image/SkRescaleAndReadPixels.cpp",
    "third_party/skia/src/core/SkBitmapProcState_opts.cpp",
    "third_party/skia/src/core/SkBitmapProcState_matrixProcs.cpp",
    "third_party/skia/src/image/SkPictureImageGenerator.cpp",
    "third_party/skia/src/core/SkImageGenerator.cpp",
    "third_party/skia/src/shaders/SkColorFilterShader.cpp",
    "third_party/skia/src/shaders/SkWorkingColorSpaceShader.cpp",
    "third_party/skia/src/utils/SkNWayCanvas.cpp",
    "third_party/skia/src/utils/SkPatchUtils.cpp",
    "cc/paint/deferred_paint_record.cc",
    "cc/base/simple_enclosed_region.cc",
    "cc/base/math_util.cc",
    "cc/paint/discardable_image_map.cc",
    "cc/paint/solid_color_analyzer.cc",
    "cc/paint/paint_cache.cc",
    "cc/paint/clear_for_opaque_raster.cc",
    "cc/paint/paint_op_buffer_serializer.cc",
    "cc/paint/shader_transfer_cache_entry.cc",
    "cc/paint/transfer_cache_serialize_helper.cc",
)

EXTRA_LIVE_SOURCE_GLOBS = (
    "third_party/icu/source/common/*.cpp",
    "third_party/icu/source/i18n/*.cpp",
    "third_party/blink/renderer/core/css/css_*_value.cc",
)


@dataclass(frozen=True)
class CopiedFile:
    source: str
    destination: str
    size: int
    sha256: str
    category: str


def normalize_rel(path: pathlib.Path | str) -> str:
    return pathlib.Path(path).as_posix().lstrip("./")


def should_copy(path: pathlib.Path) -> bool:
    if path.name in {".gitignore", ".gitattributes", "package-lock.json"}:
        return False
    if any(part in SKIP_DIR_NAMES for part in path.parts):
        return False
    suffix = path.suffix.lower()
    if suffix in SKIP_SUFFIXES:
        return False
    return suffix in TEXT_EXTENSIONS or suffix == ""


def file_sha256(path: pathlib.Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        for chunk in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def copy_one(
    relative: str,
    destination_root: pathlib.Path,
    category: str,
    manifest: dict[str, CopiedFile],
) -> None:
    relative = normalize_rel(relative)
    source = CHROMIUM_ROOT / relative
    if not source.exists() or not source.is_file() or not should_copy(source):
        return
    destination = destination_root / "upstream" / "chromium" / relative
    destination.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(source, destination)
    manifest[relative] = CopiedFile(
        source=relative,
        destination=destination.relative_to(destination_root).as_posix(),
        size=source.stat().st_size,
        sha256=file_sha256(source),
        category=category,
    )


def copy_tree(
    relative_dir: str,
    destination_root: pathlib.Path,
    category: str,
    manifest: dict[str, CopiedFile],
) -> None:
    root = CHROMIUM_ROOT / relative_dir
    if not root.exists():
        return
    for path in root.rglob("*"):
        if path.is_file() and should_copy(path):
            copy_one(path.relative_to(CHROMIUM_ROOT).as_posix(),
                     destination_root, category, manifest)


def prune_exported_tree(relative_dir: str, destination_root: pathlib.Path) -> None:
    relative_dir = normalize_rel(relative_dir)
    destination = destination_root / "upstream" / "chromium" / relative_dir
    if destination.exists():
        shutil.rmtree(destination)


def extract_string_collections(script: pathlib.Path) -> set[str]:
    tree = ast.parse(script.read_text(encoding="utf-8"))
    result: set[str] = set()
    interesting_prefixes = (
        "LIVE_",
        "TEMPLATE_",
        "RUNTIME_",
        "SMOKE_",
    )
    for node in tree.body:
        if not isinstance(node, ast.Assign):
            continue
        if not node.targets or not isinstance(node.targets[0], ast.Name):
            continue
        name = node.targets[0].id
        if not name.startswith(interesting_prefixes):
            continue
        for child in ast.walk(node.value):
            if isinstance(child, ast.Constant) and isinstance(child.value, str):
                value = child.value
                if (
                    value.endswith((".cc", ".h", ".inc", ".mojom"))
                    or "/" in value
                    or value.startswith("gen/")
                ):
                    result.add(value)
    return result


def resolve_source_reference(reference: str) -> str | None:
    normalized = normalize_rel(reference)
    if normalized.startswith("../../"):
        normalized = normalized.removeprefix("../../")
    if normalized.startswith("core/"):
        normalized = "third_party/blink/renderer/" + normalized
    if normalized.startswith("platform/"):
        normalized = "third_party/blink/renderer/" + normalized
    if normalized.startswith("gen/"):
        normalized = "generated/blink_live/" + normalized
    if (CHROMIUM_ROOT / normalized).exists():
        return normalized
    return None


def extract_command_sources(command_dump: pathlib.Path) -> set[str]:
    if not command_dump.exists():
        return set()
    data = command_dump.read_text(encoding="utf-8-sig", errors="replace")
    candidates = set(re.findall(r"(?:(?:\.\./\.\./)?[\w./+-]+?\.(?:cc|c|cpp|h|inc|mojom))", data))
    resolved: set[str] = set()
    for candidate in candidates:
        source = resolve_source_reference(candidate)
        if source:
            resolved.add(source)
    return resolved


def write_support_files(destination: pathlib.Path,
                        manifest: dict[str, CopiedFile]) -> None:
    (destination / "manifest").mkdir(parents=True, exist_ok=True)
    (destination / "docs").mkdir(parents=True, exist_ok=True)
    (destination / "cmake").mkdir(parents=True, exist_ok=True)

    gitignore = """# Local build products
/build/
/out/
/cmake-build-*/
/.vs/
/.vscode/

# The exported tree keeps only the generated files and command metadata from
# Chromium's out directory. Local object files and executables must stay out.
/upstream/chromium/out/**
!/upstream/chromium/generated/blink_live/
!/upstream/chromium/generated/blink_live/gen/
!/upstream/chromium/generated/blink_live/gen/**
!/upstream/chromium/generated/blink_live/*.rsp
!/upstream/chromium/generated/blink_live/*.commands.txt

# Compiler/linker products
*.obj
*.o
*.lib
*.a
*.dll
*.dylib
*.so
*.exe
*.pdb
*.ilk
*.exp
*.idb
*.ipdb
*.iobj

# Generated local scratch files
*.log
*.tmp
*.rsp
!upstream/chromium/generated/blink_live/*.rsp
*.commands.txt
!upstream/chromium/generated/blink_live/*.commands.txt

# Python/tool caches
__pycache__/
*.py[cod]
.pytest_cache/
.mypy_cache/

# Editor/OS noise
.DS_Store
Thumbs.db
*.swp
*~
"""
    if not (destination / ".gitignore").exists():
        (destination / ".gitignore").write_text(gitignore, encoding="utf-8")
    if not (destination / ".gitattributes").exists():
        (destination / ".gitattributes").write_text(
            "# Auto detect text files and perform LF normalization\n"
            "* text=auto\n",
            encoding="utf-8",
        )

    readme = """# blink-standalone-ui

This repository is an exported source snapshot of the current standalone
HTML/CSS renderer cut from Chromium/Blink.

The upstream Chromium paths are preserved under `upstream/chromium/` so each
file can be compared or refreshed from a Chromium checkout. The first exported
goal is traceability and a stable source tree; the next goal is replacing the
Chromium command-dump build with a focused CMake or Visual Studio build.

Current pipeline:

`HTML/CSS input -> live Blink DummyPageHolder/Document/style/layout/paint lifecycle -> PaintArtifact metadata -> retained draw commands -> SDL demo`

Known limitations:

- Text draw payload extraction is not complete; the current SDL path uses live
  PaintArtifact metadata and a transitional text bridge.
- Blink animation time is not wired to standalone `FrameInput` yet.
- The CMake file is a skeleton. It records the intended target shape but does
  not yet replace the command-dump build.
"""
    if not (destination / "README.md").exists():
        (destination / "README.md").write_text(readme, encoding="utf-8")

    live_sources = []
    for entry in sorted(manifest.values(), key=lambda item: item.source):
        if entry.category not in {"live-bridge-explicit", "command-source"}:
            continue
        if not entry.source.endswith((".cc", ".c", ".cpp")):
            continue
        if entry.source.startswith("standalone_renderer/examples/"):
            continue
        if entry.source.startswith("standalone_renderer/tests/"):
            continue
        if entry.source == (
                "third_party/blink/renderer/core/"
                "standalone_renderer_probe_base_shim.cc"):
            continue
        if entry.source == (
                "third_party/blink/renderer/core/"
                "standalone_tree_builder_dom_shim.cc"):
            continue
        live_sources.append(
            "${BLINK_STANDALONE_CHROMIUM_ROOT}/" + entry.source)
    seen_live_sources = set(live_sources)
    for pattern in EXTRA_LIVE_SOURCE_GLOBS:
        for path in sorted(CHROMIUM_ROOT.glob(pattern)):
            source = "${BLINK_STANDALONE_CHROMIUM_ROOT}/" + normalize_rel(
                path.relative_to(CHROMIUM_ROOT))
            if source not in seen_live_sources:
                live_sources.append(source)
                seen_live_sources.add(source)
    for source in EXTRA_LIVE_SOURCES:
        cmake_source = "${BLINK_STANDALONE_CHROMIUM_ROOT}/" + source
        if cmake_source not in seen_live_sources:
            live_sources.append(cmake_source)
            seen_live_sources.add(cmake_source)
    live_sources_text = "\n".join(f"  {source}" for source in live_sources)
    (destination / "cmake" / "live_blink_sources.cmake").write_text(
        "set(BLINK_STANDALONE_LIVE_SOURCES\n"
        f"{live_sources_text}\n"
        ")\n",
        encoding="utf-8",
    )

    cmake = """cmake_minimum_required(VERSION 3.26)
project(blink_standalone_ui LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BLINK_STANDALONE_CHROMIUM_ROOT
  ${CMAKE_CURRENT_SOURCE_DIR}/upstream/chromium
)
set(BLINK_STANDALONE_RENDERER_ROOT
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer
)

  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/live_blink_sources.cmake)

  add_library(blink_live_modp_b64 OBJECT
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/modp_b64/modp_b64.cc
  )
  target_include_directories(blink_live_modp_b64 PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}
  )

  add_library(blink_live_compiler_rt_atomic OBJECT
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/compiler-rt/src/lib/builtins/atomic.c
  )
  target_include_directories(blink_live_compiler_rt_atomic PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/compiler-rt/src/lib/builtins
  )

  add_executable(blink_live_bridge_probe
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/tests/live_frame_bridge_link_probe.cc
    ${BLINK_STANDALONE_LIVE_SOURCES}
    $<TARGET_OBJECTS:blink_live_modp_b64>
    $<TARGET_OBJECTS:blink_live_compiler_rt_atomic>
  )

  target_include_directories(blink_live_bridge_probe PRIVATE
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs
    ${BLINK_STANDALONE_CHROMIUM_ROOT}
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/partition_allocator/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/base/allocator/partition_allocator/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/build_config
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/abseil-cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/harfbuzz/src/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/highway/src
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/src/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libxml/win32/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/v8/include
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/buildtools/third_party/libc++/src/include
  )

  target_compile_definitions(blink_live_bridge_probe PRIVATE
    BLINK_CORE_IMPLEMENTATION=1
    BLINK_IMPLEMENTATION=1
    INSIDE_BLINK=1
    STANDALONE_RENDERER_GN_PROBE=1
    HTML_CSS_RENDERER_STANDALONE=1
    HTML_CSS_RENDERER_HAS_REDUCED_BLINK_PLATFORM=1
    DCHECK_ALWAYS_ON=1
    WTF_IMPLEMENTATION=1
    USE_AURA=1
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_NONSTDC_NO_WARNINGS
    _CRT_SECURE_NO_DEPRECATE
    _SCL_SECURE_NO_DEPRECATE
    _WINSOCK_DEPRECATED_NO_WARNINGS
    UNICODE
    _UNICODE
    U_STATIC_IMPLEMENTATION
    U_COMMON_IMPLEMENTATION
    U_I18N_IMPLEMENTATION
    SKCMS_DISABLE_HSW=1
    SKCMS_DISABLE_SKX=1
    SK_ENABLE_OPTIMIZE_SIZE=1
  )

  if(MSVC)
    target_compile_options(blink_live_bridge_probe PRIVATE
      /FI${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/stubs/standalone_network_namespace_forwards.h
      /bigobj
      /MP8
      /permissive-
      /Zc:__cplusplus
      /wd4005
      /wd4068
      /wd4100
      /wd4127
      /wd4251
      /wd4267
      /wd4275
      /wd4324
      /wd4800
      /wd4996
    )
  endif()
"""
    if not (destination / "CMakeLists.txt").exists():
        (destination / "CMakeLists.txt").write_text(cmake, encoding="utf-8")

    manifest_json = {
        "schema": 1,
        "chromium_root": str(CHROMIUM_ROOT),
        "layout": "upstream/chromium/<chromium-relative-path>",
        "file_count": len(manifest),
        "files": [entry.__dict__ for entry in sorted(
            manifest.values(), key=lambda item: item.source)],
    }
    (destination / "manifest" / "origin_manifest.json").write_text(
        json.dumps(manifest_json, indent=2), encoding="utf-8")

    copied_paths = "\n".join(sorted(manifest))
    (destination / "manifest" / "copied_files.txt").write_text(
        copied_paths + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--destination", type=pathlib.Path,
                        default=DEFAULT_DESTINATION)
    parser.add_argument("--clean", action="store_true")
    parser.add_argument("--skip-large-roots", action="store_true")
    args = parser.parse_args()

    destination = args.destination.resolve()
    if args.clean and destination.exists():
        shutil.rmtree(destination)
    destination.mkdir(parents=True, exist_ok=True)

    manifest: dict[str, CopiedFile] = {}

    root_dirs = ROOT_COPY_DIRS
    if args.skip_large_roots:
        root_dirs = tuple(
            path for path in ROOT_COPY_DIRS
            if path not in {"third_party/skia", "base", "build"}
        )

    for relative_dir in root_dirs:
        print(f"copy tree {relative_dir}")
        prune_exported_tree(relative_dir, destination)
        copy_tree(relative_dir, destination, "source-root", manifest)
    for relative_file in ROOT_COPY_FILES:
        copy_one(relative_file, destination, "source-root", manifest)

    for relative_dir in GENERATED_COPY_DIRS:
        print(f"copy generated tree generated/blink_live/{relative_dir}")
        prune_exported_tree("generated/blink_live/" + relative_dir, destination)
        copy_tree("generated/blink_live/" + relative_dir, destination,
                  "generated", manifest)

    live_script = CHROMIUM_ROOT / "standalone_renderer/tools/compile_live_frame_bridge_probe.py"
    for reference in sorted(extract_string_collections(live_script)):
        resolved = resolve_source_reference(reference)
        if resolved:
            copy_one(resolved, destination, "live-bridge-explicit", manifest)

    for command_dump in COMMAND_DUMPS:
        path = CHROMIUM_ROOT / command_dump
        copy_one(command_dump, destination, "build-metadata", manifest)
        for source in sorted(extract_command_sources(path)):
            copy_one(source, destination, "command-source", manifest)

    write_support_files(destination, manifest)
    print(f"exported {len(manifest)} files to {destination}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
