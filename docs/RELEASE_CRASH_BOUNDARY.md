# Release Crash Boundary

This records the post-`1640521e` rerun of the old 8-page image/resource crash set. The purpose is to close the Release crash boundary, not to accept `/Od` as a solution.

## Crash Set

- `14g_image_inside_overflow_clip`
- `14i_image_inside_rounded_overflow_clip`
- `14j_image_rounded_overflow_document_scroll`
- `18h_css_bg_data_png_rounded_clip`
- `18j_external_css_png_background`
- `43s_incremental_attr_rounded_svg_image_basic`
- `49a_ui_visual_effects_resource_cards`
- `49c_ui_opacity_resource_cards`

## Results

| Build configuration | Output directory | Pages | Failures | Correctness failures | Timeouts |
| --- | --- | ---: | ---: | ---: | ---: |
| `x64-Perf` all optimized, restored | `build/perf/release-crash-boundary/all-optimized-restored` | 8 | 0 | 0 | 0 |
| `x64-Perf`, `BLINK_STANDALONE_OPTIMIZE_BOUNDARY=OFF` | `build/perf/release-crash-boundary/boundary-off` | 8 | 0 | 0 | 0 |
| `x64-Perf`, `BLINK_STANDALONE_OPTIMIZE_CODECS=OFF` | `build/perf/release-crash-boundary/codecs-off` | 8 | 0 | 0 | 0 |
| `x64-Perf`, `BLINK_STANDALONE_OPTIMIZE_CHROMIUM=OFF` | `build/perf/release-crash-boundary/chromium-off` | 8 | 0 | 0 | 0 |

## Boundary Status

The old Release crash issue did not reproduce in any of the four post-`1640521e` runs. The primary perf build was restored to:

- `BLINK_STANDALONE_OPTIMIZE_CHROMIUM=ON`
- `BLINK_STANDALONE_OPTIMIZE_CODECS=ON`
- `BLINK_STANDALONE_OPTIMIZE_BOUNDARY=ON`
- `BLINK_STANDALONE_OPTIMIZE_APP=ON`

The `/Od` runs remain diagnostic evidence only.
