#!/usr/bin/env python3
"""Rebuild the standalone Blink tree-builder probe without running Ninja.

The Chromium checkout is incomplete enough that normal GN/Ninja iteration is
expensive and sometimes hangs on this machine. This helper consumes a
previously generated `ninja -t commands` dump for `blink_tree_builder_link_probe`,
recompiles selected sources, links a filtered executable, and optionally runs it.
"""

from __future__ import annotations

import argparse
import ctypes
import pathlib
import subprocess
import sys
from ctypes import wintypes


DEFAULT_COMPILE_FILTERS = (
    "core/html/parser/html_element_stack.cc",
    "core/html/parser/html_construction_site.cc",
    "core/html/parser/html_tree_builder.cc",
    "core/css/properties/css_property.cc",
    "core/css/properties/computed_style_utils.cc",
    "core/css/properties/css_direction_aware_resolver.cc",
    "core/css/properties/longhands/longhands_custom.cc",
    "core/css/properties/shorthands/shorthands_custom.cc",
    "core/css/css_to_length_conversion_data.cc",
    "core/css/css_length_resolver.cc",
    "core/css/css_gap_decoration_property_utils.cc",
    "core/css/parser/css_parser_fast_paths.cc",
    "core/css/parser/css_parser_local_context.cc",
    "core/css/properties/css_parsing_utils.cc",
    "core/css/properties/css_color_function_parser.cc",
    "core/css/style_change_reason.cc",
    "core/css/style_property_shorthand_custom.cc",
    "core/css/resolver/css_to_style_map.cc",
    "core/css/resolver/font_builder.cc",
    "core/css/resolver/style_builder_converter.cc",
    "core/css/resolver/transform_builder.cc",
    "core/css/css_alternate_value.cc",
    "core/css/css_axis_value.cc",
    "core/css/css_basic_shape_values.cc",
    "core/css/css_border_image.cc",
    "core/css/css_border_image_slice_value.cc",
    "core/css/css_bracketed_value_list.cc",
    "core/css/css_color_mix_value.cc",
    "core/css/css_color.cc",
    "core/css/css_content_distribution_value.cc",
    "core/css/css_cursor_image_value.cc",
    "core/css/css_custom_ident_value.cc",
    "core/css/css_font_variation_value.cc",
    "core/css/css_grid_template_areas_value.cc",
    "core/css/css_identifier_value.cc",
    "core/css/css_layout_function_value.cc",
    "core/css/css_font_feature_value.cc",
    "core/css/css_font_family_value.cc",
    "core/css/css_function_value.cc",
    "core/css/css_gradient_value.cc",
    "core/css/css_grid_integer_repeat_value.cc",
    "core/css/css_inherited_value.cc",
    "core/css/cssom/cross_thread_color_value.cc",
    "core/css/cssom/cross_thread_keyword_value.cc",
    "core/css/cssom/css_keyword_value.cc",
    "core/css/cssom/css_unsupported_color.cc",
    "core/css/cssom_utils.cc",
    "core/css/css_markup.cc",
    "core/css/css_math_function_value.cc",
    "core/css/css_math_expression_node.cc",
    "core/css/css_math_operator.cc",
    "core/css/css_numeric_literal_value.cc",
    "core/css/css_pending_system_font_value.cc",
    "core/css/css_path_value.cc",
    "core/css/css_primitive_value.cc",
    "core/css/css_progress_value.cc",
    "core/css/css_ray_value.cc",
    "core/css/css_ratio_value.cc",
    "core/css/css_relative_color_value.cc",
    "core/css/css_repeat_style_value.cc",
    "core/css/css_repeat_value.cc",
    "core/css/css_revert_layer_value.cc",
    "core/css/css_revert_rule_value.cc",
    "core/css/css_revert_value.cc",
    "core/css/css_scroll_value.cc",
    "core/css/css_shadow_value.cc",
    "core/css/css_string_value.cc",
    "core/css/css_syntax_definition.cc",
    "core/css/css_uri_value.cc",
    "core/css/css_unset_value.cc",
    "core/css/css_unresolved_color_value.cc",
    "core/css/css_value_list.cc",
    "core/css/css_value_clamping_utils.cc",
    "core/css/css_view_value.cc",
    "core/css/css_variable_data.cc",
    "core/css/css_property_name.cc",
    "core/css/property_registry.cc",
    "core/css/style_color.cc",
    "core/dom/text_link_colors.cc",
    "core/layout/geometry/physical_rect.cc",
    "core/layout/layout_block.cc",
    "core/layout/layout_block_flow.cc",
    "core/layout/layout_box.cc",
    "core/layout/layout_box_model_object.cc",
    "core/layout/layout_inline.cc",
    "core/layout/layout_object_hot.cc",
    "core/layout/layout_object.cc",
    "core/layout/layout_object_child_list.cc",
    "core/layout/layout_text.cc",
    "core/layout/layout_invalidation_reason.cc",
    "core/animation/animation_time_delta.cc",
    "core/animation/css/css_animation_data.cc",
    "core/animation/css/css_timing_data.cc",
    "core/animation/css/css_transition_data.cc",
    "core/style/applied_text_decoration.cc",
    "core/style/anchor_specifier_value.cc",
    "core/style/style_highlight_data.cc",
    "core/style/content_data.cc",
    "core/style/fill_layer.cc",
    "core/style/filter_operations.cc",
    "core/style/nine_piece_image.cc",
    "core/style/position_try_fallbacks.cc",
    "core/style/reference_clip_path_operation.cc",
    "core/style/style_aspect_ratio.cc",
    "core/style/style_initial_data.cc",
    "core/style/style_initial_letter.cc",
    "core/style/computed_grid_template_areas.cc",
    "core/style/grid_track_list.cc",
    "core/style/list_style_type_data.cc",
    "core/style/style_generated_image.cc",
    "core/style/style_path.cc",
    "core/style/style_scrollbar_color.cc",
    "core/style/style_svg_resource.cc",
    "core/style/text_decoration_thickness.cc",
    "core/style/style_variables.cc",
    "core/style/svg_paint.cc",
    "core/svg/svg_path_byte_stream_builder.cc",
    "core/svg/svg_path_byte_stream_source.cc",
    "core/svg/svg_path_parser.cc",
    "core/svg/svg_path_builder.cc",
    "core/svg/svg_parser_utilities.cc",
    "core/svg/svg_path_string_builder.cc",
    "core/svg/svg_path_string_source.cc",
    "core/svg/svg_path_utilities.cc",
    "core/standalone_renderer_probe_css_parser_context_shim.cc",
    "core/standalone_layout_link_stubs.cc",
    "core/standalone_tree_builder_dom_shim.cc",
    "gen/third_party/blink/renderer/core/css/properties/css_property_instances.cc",
    "gen/third_party/blink/renderer/core/css/properties/longhands.cc",
    "gen/third_party/blink/renderer/core/css/properties/shorthands.cc",
    "gen/third_party/blink/renderer/core/style_property_shorthand.cc",
    "gen/third_party/blink/renderer/core/style/computed_style_base.cc",
    "gen/third_party/blink/renderer/core/style/computed_style_base_constants.cc",
    "platform/geometry/length_functions.cc",
    "platform/geometry/math_functions.cc",
    "platform/geometry/path.cc",
    "platform/geometry/path_builder.cc",
    "platform/geometry/calculation_expression_node.cc",
    "platform/geometry/length.cc",
    "platform/geometry/physical_offset.cc",
    "platform/geometry/physical_size.cc",
    "platform/geometry/calculation_value.cc",
    "platform/animation/timing_function.cc",
    "platform/fonts/font_description.cc",
    "platform/fonts/font_family.cc",
    "platform/fonts/font_optical_sizing.cc",
    "platform/fonts/font_orientation.cc",
    "platform/fonts/font_palette.cc",
    "platform/fonts/font_selection_types.cc",
    "platform/fonts/font_size_adjust.cc",
    "platform/fonts/font_smoothing_mode.cc",
    "platform/fonts/font_variant_east_asian.cc",
    "platform/fonts/font_variant_emoji.cc",
    "platform/fonts/font_variant_numeric.cc",
    "platform/fonts/font_width_variant.cc",
    "platform/fonts/opentype/font_settings.cc",
    "platform/fonts/resolved_font_features.cc",
    "platform/fonts/text_rendering_mode.cc",
    "platform/fonts/generic_font_family_settings.cc",
    "platform/text/quotes_data.cc",
    "platform/wtf/text/text_offset_map.cc",
    "platform/text/writing_direction_mode.cc",
    "platform/graphics/color.cc",
    "platform/transforms/affine_transform.cc",
    "platform/transforms/interpolated_transform_operation.cc",
    "platform/transforms/rotation.cc",
    "platform/transforms/matrix_3d_transform_operation.cc",
    "platform/transforms/matrix_transform_operation.cc",
    "platform/transforms/perspective_transform_operation.cc",
    "platform/transforms/rotate_transform_operation.cc",
    "platform/transforms/scale_transform_operation.cc",
    "platform/transforms/skew_transform_operation.cc",
    "platform/transforms/translate_transform_operation.cc",
    "platform/transforms/transform_operations.cc",
    "standalone_renderer/tests/blink_tree_builder_link_probe.cc",
)

SYNTHESIZED_COMPILE_SOURCES = {
    "core/css/properties/css_property.cc",
    "core/css/properties/computed_style_utils.cc",
    "core/css/properties/css_direction_aware_resolver.cc",
    "core/css/properties/longhands/longhands_custom.cc",
    "core/css/properties/shorthands/shorthands_custom.cc",
    "core/css/css_to_length_conversion_data.cc",
    "core/css/css_length_resolver.cc",
    "core/css/css_gap_decoration_property_utils.cc",
    "core/css/parser/css_parser_fast_paths.cc",
    "core/css/parser/css_parser_local_context.cc",
    "core/css/properties/css_parsing_utils.cc",
    "core/css/properties/css_color_function_parser.cc",
    "core/css/style_change_reason.cc",
    "core/css/style_property_shorthand_custom.cc",
    "core/css/resolver/css_to_style_map.cc",
    "core/css/resolver/font_builder.cc",
    "core/css/resolver/style_builder_converter.cc",
    "core/css/resolver/transform_builder.cc",
    "core/css/css_alternate_value.cc",
    "core/css/css_axis_value.cc",
    "core/css/css_basic_shape_values.cc",
    "core/css/css_border_image.cc",
    "core/css/css_border_image_slice_value.cc",
    "core/css/css_bracketed_value_list.cc",
    "core/css/css_color_mix_value.cc",
    "core/css/css_color.cc",
    "core/css/css_content_distribution_value.cc",
    "core/css/css_cursor_image_value.cc",
    "core/css/css_custom_ident_value.cc",
    "core/css/css_font_variation_value.cc",
    "core/css/css_grid_template_areas_value.cc",
    "core/css/css_identifier_value.cc",
    "core/css/css_layout_function_value.cc",
    "core/css/css_font_feature_value.cc",
    "core/css/css_font_family_value.cc",
    "core/css/css_function_value.cc",
    "core/css/css_gradient_value.cc",
    "core/css/css_grid_integer_repeat_value.cc",
    "core/css/css_inherited_value.cc",
    "core/css/cssom/cross_thread_color_value.cc",
    "core/css/cssom/cross_thread_keyword_value.cc",
    "core/css/cssom/css_keyword_value.cc",
    "core/css/cssom/css_unsupported_color.cc",
    "core/css/cssom_utils.cc",
    "core/css/css_markup.cc",
    "core/css/css_math_function_value.cc",
    "core/css/css_math_expression_node.cc",
    "core/css/css_math_operator.cc",
    "core/css/css_numeric_literal_value.cc",
    "core/css/css_pending_system_font_value.cc",
    "core/css/css_path_value.cc",
    "core/css/css_primitive_value.cc",
    "core/css/css_progress_value.cc",
    "core/css/css_ray_value.cc",
    "core/css/css_ratio_value.cc",
    "core/css/css_relative_color_value.cc",
    "core/css/css_repeat_style_value.cc",
    "core/css/css_repeat_value.cc",
    "core/css/css_revert_layer_value.cc",
    "core/css/css_revert_rule_value.cc",
    "core/css/css_revert_value.cc",
    "core/css/css_scroll_value.cc",
    "core/css/css_shadow_value.cc",
    "core/css/css_string_value.cc",
    "core/css/css_syntax_definition.cc",
    "core/css/css_uri_value.cc",
    "core/css/css_unset_value.cc",
    "core/css/css_unresolved_color_value.cc",
    "core/css/css_value_list.cc",
    "core/css/css_value_clamping_utils.cc",
    "core/css/css_view_value.cc",
    "core/css/css_variable_data.cc",
    "core/css/css_property_name.cc",
    "core/css/property_registry.cc",
    "core/css/style_color.cc",
    "core/dom/text_link_colors.cc",
    "core/layout/geometry/physical_rect.cc",
    "core/layout/layout_block.cc",
    "core/layout/layout_block_flow.cc",
    "core/layout/layout_box.cc",
    "core/layout/layout_box_model_object.cc",
    "core/layout/layout_inline.cc",
    "core/layout/layout_object_hot.cc",
    "core/layout/layout_object.cc",
    "core/layout/layout_object_child_list.cc",
    "core/layout/layout_text.cc",
    "core/layout/layout_invalidation_reason.cc",
    "core/animation/animation_time_delta.cc",
    "core/animation/css/css_animation_data.cc",
    "core/animation/css/css_timing_data.cc",
    "core/animation/css/css_transition_data.cc",
    "core/style/applied_text_decoration.cc",
    "core/style/anchor_specifier_value.cc",
    "core/style/style_highlight_data.cc",
    "core/style/content_data.cc",
    "core/style/fill_layer.cc",
    "core/style/filter_operations.cc",
    "core/style/nine_piece_image.cc",
    "core/style/position_try_fallbacks.cc",
    "core/style/reference_clip_path_operation.cc",
    "core/style/style_aspect_ratio.cc",
    "core/style/style_initial_data.cc",
    "core/style/style_initial_letter.cc",
    "core/style/computed_grid_template_areas.cc",
    "core/style/grid_track_list.cc",
    "core/style/list_style_type_data.cc",
    "core/style/style_generated_image.cc",
    "core/style/style_path.cc",
    "core/style/style_scrollbar_color.cc",
    "core/style/style_svg_resource.cc",
    "core/style/text_decoration_thickness.cc",
    "core/style/style_variables.cc",
    "core/style/svg_paint.cc",
    "core/svg/svg_path_byte_stream_builder.cc",
    "core/svg/svg_path_byte_stream_source.cc",
    "core/svg/svg_path_parser.cc",
    "core/svg/svg_path_builder.cc",
    "core/svg/svg_parser_utilities.cc",
    "core/svg/svg_path_string_builder.cc",
    "core/svg/svg_path_string_source.cc",
    "core/svg/svg_path_utilities.cc",
    "core/standalone_renderer_probe_css_parser_context_shim.cc",
    "core/standalone_layout_link_stubs.cc",
    "gen/third_party/blink/renderer/core/css/properties/css_property_instances.cc",
    "gen/third_party/blink/renderer/core/css/properties/longhands.cc",
    "gen/third_party/blink/renderer/core/css/properties/shorthands.cc",
    "gen/third_party/blink/renderer/core/style_property_shorthand.cc",
    "gen/third_party/blink/renderer/core/style/computed_style_base.cc",
    "gen/third_party/blink/renderer/core/style/computed_style_base_constants.cc",
    "platform/geometry/length_functions.cc",
    "platform/geometry/math_functions.cc",
    "platform/geometry/path.cc",
    "platform/geometry/path_builder.cc",
    "platform/geometry/calculation_expression_node.cc",
    "platform/geometry/length.cc",
    "platform/geometry/physical_offset.cc",
    "platform/geometry/physical_size.cc",
    "platform/geometry/calculation_value.cc",
    "platform/animation/timing_function.cc",
    "platform/fonts/font_description.cc",
    "platform/fonts/font_family.cc",
    "platform/fonts/font_optical_sizing.cc",
    "platform/fonts/font_orientation.cc",
    "platform/fonts/font_palette.cc",
    "platform/fonts/font_selection_types.cc",
    "platform/fonts/font_size_adjust.cc",
    "platform/fonts/font_smoothing_mode.cc",
    "platform/fonts/font_variant_east_asian.cc",
    "platform/fonts/font_variant_emoji.cc",
    "platform/fonts/font_variant_numeric.cc",
    "platform/fonts/font_width_variant.cc",
    "platform/fonts/opentype/font_settings.cc",
    "platform/fonts/resolved_font_features.cc",
    "platform/fonts/text_rendering_mode.cc",
    "platform/fonts/generic_font_family_settings.cc",
    "platform/text/quotes_data.cc",
    "platform/wtf/text/text_offset_map.cc",
    "platform/text/writing_direction_mode.cc",
    "platform/graphics/color.cc",
    "platform/transforms/affine_transform.cc",
    "platform/transforms/interpolated_transform_operation.cc",
    "platform/transforms/rotation.cc",
    "platform/transforms/matrix_3d_transform_operation.cc",
    "platform/transforms/matrix_transform_operation.cc",
    "platform/transforms/perspective_transform_operation.cc",
    "platform/transforms/rotate_transform_operation.cc",
    "platform/transforms/scale_transform_operation.cc",
    "platform/transforms/skew_transform_operation.cc",
    "platform/transforms/translate_transform_operation.cc",
    "platform/transforms/transform_operations.cc",
}

FILTERED_LINK_INPUT_SUBSTRINGS = (
    "standalone_paint_probe",
    "standalone_geometry_probe",
    "platform/wtf/minimal_probe",
    "platform\\wtf\\minimal_probe",
    "core_css_css_path_value.obj",
    "core_style_style_path.obj",
    "core_svg_svg_path",
    "platform/platform/path.obj",
    "platform\\platform\\path.obj",
    "platform/platform/path_builder.obj",
    "platform\\platform\\path_builder.obj",
    "libc++/exception.obj",
    "libc++\\exception.obj",
    "libc++/future.obj",
    "libc++\\future.obj",
    "libc++/thread.obj",
    "libc++\\thread.obj",
    "libc++/condition_variable.obj",
    "libc++\\condition_variable.obj",
    "libc++/mutex.obj",
    "libc++\\mutex.obj",
    "libc++/shared_mutex.obj",
    "libc++\\shared_mutex.obj",
)

WTF_MINIMAL_EXCLUDED_OBJECTS = {
    "date_math.obj",
    "text_offset_map.obj",
    "uuid.obj",
}

EXTRA_LINK_INPUTS = (
    "obj/ui/gfx/animation/keyframe/keyframe.lib",
    "obj/third_party/blink/renderer/platform/platform/affine_transform.obj",
    "obj/third_party/blink/renderer/platform/platform/matrix_3d_transform_operation.obj",
    "obj/third_party/blink/renderer/platform/platform/matrix_transform_operation.obj",
    "obj/third_party/blink/renderer/platform/platform/perspective_transform_operation.obj",
    "obj/third_party/blink/renderer/platform/platform/physical_offset.obj",
    "obj/third_party/blink/renderer/platform/platform/physical_size.obj",
    "obj/third_party/blink/renderer/platform/platform/rotate_transform_operation.obj",
    "obj/third_party/blink/renderer/platform/platform/rotation.obj",
    "obj/third_party/blink/renderer/platform/platform/scale_transform_operation.obj",
    "obj/third_party/blink/renderer/platform/platform/skew_transform_operation.obj",
    "obj/third_party/blink/renderer/platform/platform/translate_transform_operation.obj",
    "obj/base/third_party/double_conversion/double_conversion.lib",
    "obj/third_party/modp_b64/modp_b64.lib",
    "../../third_party/llvm-build/Release+Asserts/lib/clang/23/lib/windows/"
    "clang_rt.builtins-x86_64.lib",
)


def split_command_line(command: str) -> list[str]:
    argv_to_command_line = ctypes.windll.shell32.CommandLineToArgvW
    argv_to_command_line.argtypes = [
        wintypes.LPCWSTR,
        ctypes.POINTER(ctypes.c_int),
    ]
    argv_to_command_line.restype = ctypes.POINTER(wintypes.LPWSTR)
    argc = ctypes.c_int()
    argv = argv_to_command_line(command, ctypes.byref(argc))
    if not argv:
        raise ctypes.WinError()
    try:
        return [argv[index] for index in range(argc.value)]
    finally:
        ctypes.windll.kernel32.LocalFree(argv)


def resolve_executable(out_dir: pathlib.Path, value: str) -> pathlib.Path:
    executable = pathlib.Path(value)
    if executable.is_absolute():
        return executable
    return (out_dir / executable).resolve()


def read_commands(path: pathlib.Path) -> list[str]:
    return path.read_text(encoding="utf-8-sig", errors="replace").splitlines()


def compile_sources(
    out_dir: pathlib.Path,
    commands: list[str],
    source_filters: tuple[str, ...],
    timeout: int,
) -> int:
    for source_filter in source_filters:
        normalized_filter = source_filter.replace("\\", "/")
        matches = [
            command
            for command in commands
            if "clang-cl.exe" in command
            and normalized_filter in command.replace("\\", "/")
        ]
        if not matches:
            if normalized_filter not in SYNTHESIZED_COMPILE_SOURCES:
                print(f"missing compile command for {source_filter}")
                return 2
            template_matches = [
                command
                for command in commands
                if "clang-cl.exe" in command
                and "core/standalone_tree_builder_dom_shim.cc"
                in command.replace("\\", "/")
            ]
            if not template_matches:
                print(f"missing compile command for {source_filter}")
                return 2
            if normalized_filter.startswith("gen/"):
                replacement_source = normalized_filter
            else:
                replacement_source = (
                    f"../../third_party/blink/renderer/{normalized_filter}"
                )
            obj_name = normalized_filter.replace("/", "_").replace(".cc", ".obj")
            matches = [
                template_matches[0]
                .replace(
                    "../../third_party/blink/renderer/core/"
                    "standalone_tree_builder_dom_shim.cc",
                    replacement_source,
                )
                .replace(
                    "obj/third_party/blink/renderer/core/"
                    "standalone_core_tree_builder_probe/"
                    "standalone_tree_builder_dom_shim.obj",
                    "obj/third_party/blink/renderer/core/"
                    f"standalone_core_tree_builder_probe/{obj_name}",
                )
            ]

        args = [
            arg
            for arg in split_command_line(matches[0])
            if not arg.lower().startswith("/showincludes")
        ]
        forced_include = (
            "/FI../../standalone_renderer/stubs/"
            "standalone_network_namespace_forwards.h"
        )
        if forced_include not in args:
            args.insert(1, forced_include)
        needs_standalone_define = (
            normalized_filter.startswith("core/")
            or normalized_filter.startswith("gen/third_party/blink/renderer/core/")
        )
        if needs_standalone_define and "/DSTANDALONE_RENDERER_GN_PROBE=1" not in args:
            args.append("/DSTANDALONE_RENDERER_GN_PROBE=1")
        executable = resolve_executable(out_dir, args[0])
        rsp_path = out_dir / (
            "direct.recompile." + pathlib.Path(source_filter).stem + ".rsp"
        )
        rsp_path.write_text(subprocess.list2cmdline(args[1:]), encoding="utf-8")
        result = subprocess.run(
            [str(executable), "@" + str(rsp_path)],
            cwd=out_dir,
            shell=False,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors="replace",
            timeout=timeout,
        )
        print(f"{source_filter} EXIT {result.returncode}")
        if result.stdout:
            print(result.stdout[-12000:])
        if result.returncode:
            return result.returncode
    return 0


def collect_link_inputs(out_dir: pathlib.Path, commands: list[str]) -> list[str]:
    inputs: list[str] = []
    for command in commands:
        if "clang-cl.exe" not in command:
            continue
        for arg in split_command_line(command):
            if not arg.startswith("/Fo"):
                continue
            obj = arg[3:].strip('"')
            if any(skip in obj for skip in FILTERED_LINK_INPUT_SUBSTRINGS):
                continue
            if obj not in inputs and (out_dir / obj).exists():
                inputs.append(obj)

    wtf_dir = out_dir / "obj/third_party/blink/renderer/platform/wtf/minimal_probe"
    for path in sorted(wtf_dir.glob("*.obj")):
        if path.name in WTF_MINIMAL_EXCLUDED_OBJECTS:
            continue
        relative = str(path.relative_to(out_dir)).replace("\\", "/")
        if relative not in inputs:
            inputs.append(relative)

    for item in EXTRA_LINK_INPUTS:
        path = (out_dir / item).resolve() if item.startswith("../") else out_dir / item
        if item not in inputs and path.exists():
            inputs.append(item)
    for source in SYNTHESIZED_COMPILE_SOURCES:
        obj_name = source.replace("/", "_").replace(".cc", ".obj")
        item = (
            "obj/third_party/blink/renderer/core/"
            f"standalone_core_tree_builder_probe/{obj_name}"
        )
        if any(skip in item for skip in FILTERED_LINK_INPUT_SUBSTRINGS):
            continue
        if item not in inputs and (out_dir / item).exists():
            inputs.append(item)
    return inputs


def link_probe(
    out_dir: pathlib.Path,
    commands: list[str],
    timeout: int,
    allow_unresolved: bool,
) -> int:
    link_commands = [
        command
        for command in commands
        if "lld-link.exe" in command and "blink_tree_builder_link_probe.exe" in command
    ]
    if not link_commands:
        print("missing link command for blink_tree_builder_link_probe.exe")
        return 2

    args = split_command_line(link_commands[-1])
    executable = resolve_executable(out_dir, args[0])
    link_args = [arg for arg in args[1:] if not arg.startswith("@")]
    inputs = collect_link_inputs(out_dir, commands)
    rsp_path = out_dir / "blink_tree_builder_link_probe.nopaint_minruntime.rsp"
    rsp_path.write_text(subprocess.list2cmdline(inputs), encoding="utf-8")
    if allow_unresolved:
        link_args.append("/force:unresolved")
    result = subprocess.run(
        [str(executable)] + link_args + ["@" + str(rsp_path), "/errorlimit:0"],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    if result.stdout:
        print(result.stdout[-40000:])
    print(f"LINK EXIT {result.returncode}")
    return result.returncode


def run_probe(out_dir: pathlib.Path, timeout: int) -> int:
    executable = out_dir / "blink_tree_builder_link_probe.exe"
    result = subprocess.run(
        [str(executable)],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    if result.stdout:
        print(result.stdout)
    print(f"RUN EXIT {result.returncode}")
    return result.returncode


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out-dir", type=pathlib.Path, default="generated/blink_live")
    parser.add_argument(
        "--commands",
        type=pathlib.Path,
        default="generated/blink_live/blink_tree_builder_link_probe.commands.txt",
    )
    parser.add_argument("--compile-timeout", type=int, default=120)
    parser.add_argument("--link-timeout", type=int, default=120)
    parser.add_argument("--run-timeout", type=int, default=10)
    parser.add_argument("--no-run", action="store_true")
    parser.add_argument("--skip-compile", action="store_true")
    parser.add_argument("--allow-unresolved", action="store_true")
    parser.add_argument(
        "--source-filter",
        action="append",
        help="Recompile only matching source. Defaults to the current probe files.",
    )
    args = parser.parse_args()

    out_dir = args.out_dir.resolve()
    commands = read_commands(args.commands.resolve())
    source_filters = tuple(args.source_filter or DEFAULT_COMPILE_FILTERS)
    if not args.skip_compile:
        exit_code = compile_sources(
            out_dir,
            commands,
            source_filters,
            args.compile_timeout,
        )
        if exit_code:
            return exit_code
    exit_code = link_probe(
        out_dir,
        commands,
        args.link_timeout,
        args.allow_unresolved,
    )
    if exit_code or args.no_run:
        return exit_code
    return run_probe(out_dir, args.run_timeout)


if __name__ == "__main__":
    sys.exit(main())
