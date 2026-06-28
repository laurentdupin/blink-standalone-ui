# Blink Standalone C API Contract

This document describes the supported embedder-facing contract for the
`blink_standalone_renderer_*` C API declared in
`upstream/chromium/standalone_renderer/include/html_css_renderer/renderer_c_api.h`.
It is intended for Godot-style embedders that want HTML/CSS layout, paint, form
controls, native callbacks, and raw CPU frames without exposing JavaScript.

The API is a public C ABI over the standalone Blink/cc/Viz renderer path. It is
not a browser embedding API and does not expose V8, JavaScript execution, DOM
scripting, network navigation, media playback, or DevTools.

## Lifecycle

The normal lifecycle is:

1. Create a renderer with `blink_standalone_renderer_create`.
2. Set or replace the document with `blink_standalone_renderer_set_document_html`.
3. Set the logical CSS viewport and device scale with
   `blink_standalone_renderer_set_viewport`.
4. Queue input or mutations as needed.
5. Call `blink_standalone_renderer_advance_frame`.
6. Read `blink_standalone_renderer_get_latest_output` and metadata/form state.
7. Call `blink_standalone_renderer_release_latest_output` when pixel bytes are no
   longer needed.
8. Destroy the renderer with `blink_standalone_renderer_destroy`.

Multiple renderer handles may exist at the same time. Each owns an independent
Blink page/document/viewport/output state. Process-global Chromium, Skia, ANGLE,
and ICU runtime resources still exist, but page state, raw frame buffers,
metadata, form state, and queued mutations are renderer-local.

## Raw Output

The C API viewport width and height are logical CSS/view dimensions. The device
scale factor controls physical raw output size. For example,
`set_viewport(renderer, 256, 128, 2.0f)` produces a `512x256` raw frame while
hit metadata and input coordinates remain in logical coordinates.

Raw output is returned as RGBA8 or BGRA8. Embedders must inspect
`pixel_format`, `stride`, `width`, `height`, and `premultiplied_alpha`; rows are
not guaranteed to be tightly packed. Pixel pointers and dirty rect pointers are
owned by the renderer and remain valid until the latest output is released, the
renderer advances/mutates again, or the renderer is destroyed.

Transparent output is preserved when the document opts into transparency, for
example with transparent `html`/`body` backgrounds. Opaque document backgrounds
produce opaque raw pixels.

## Backdrop Filter Metadata

Ordinary CSS `filter` effects, such as `filter: blur(...)`, are rendered by
Blink into the raw HTML output. CSS `backdrop-filter` is different: Blink does
not receive, sample, or blur host-scene pixels behind the HTML surface. Instead,
the standalone C API exposes backdrop-filter regions as metadata so the embedder
can blur its own framebuffer or backbuffer behind the raw HTML output.

Use `blink_standalone_renderer_backdrop_filter_region_count` and
`blink_standalone_renderer_get_backdrop_filter_region` after
`advance_frame`. Region bounds and corner radii are logical CSS px, matching hit
metadata and input coordinates even when the raw output is DSF-scaled.

Each region exposes an ordered `filter_ops` chain for supported backdrop-filter
operations: `blur`, `brightness`, `contrast`, `saturate`, `grayscale`, `sepia`,
`invert`, `hue-rotate`, and `opacity`. Units are CSS px for blur, degrees for
hue-rotate, multipliers for brightness/contrast/saturate, and normalized
fractions for grayscale/sepia/invert/opacity. `blur_radius_css_px` remains a
compatibility shortcut for the largest exported blur operation.

Unsupported flags mark regions that exist but should not be treated as an exact
supported chain, including complex clips, non-translation transforms,
unsupported filter operations such as drop-shadow/reference filters/color
matrices, masks, blend modes, or operation chains longer than
`BLINK_STANDALONE_MAX_BACKDROP_FILTER_OPS`. `element_id` may be empty when
Blink's PaintArtifact/effect metadata cannot attribute the region reliably.

## Input

Mouse, wheel, keyboard, and text input are queued through the C API and applied
by the next `blink_standalone_renderer_advance_frame` call. Mouse and wheel
coordinates use logical CSS/view coordinates. Text input is UTF-8 and is routed
through Blink editing/form-control behavior; it is not a custom text widget
state.

## No-Script And No-Network Profile

The public product profile is HTML/CSS plus native callbacks. With
`no_script_profile` enabled, the C API rejects or makes inert executable content
surfaces including:

- `<script>` input.
- Inline event handler attributes such as `onclick`.
- `javascript:` URLs.
- Executable embedded surfaces such as iframe/object/embed.

The API does not advertise arbitrary JavaScript, WASM, navigation, or network
behavior. Local/static resources are the intended resource model.

## Resource Provider

Embedders that need to own document resource loading can install a per-renderer
resource provider with `blink_standalone_renderer_set_resource_provider`.
Provider callbacks receive the requested URL, document/base URL, resource type
hint, initiator hint, and accepted MIME types. Response bytes are copied into
renderer-owned storage before the callback release hook is invoked.

When `BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL` and
`BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK` are set, non-data
external resources fail closed through the provider callback. The standalone
filesystem `resource_root` fallback is not used for those requests. Data URLs
remain internally handled memory-only resources unless callback-for-data routing
is explicitly enabled.

Currently provider-backed resource coverage includes:

- Image resources used by elements and CSS image values.
- CSS background-image resources.
- Linked stylesheets via `<link rel="stylesheet" href="...">`.
- Simple CSS imports from provider-loaded stylesheets, including
  `@import url(...)` and quoted `@import "..."` forms.

Linked stylesheets and CSS imports are routed through the provider because the
standalone probe strips stylesheet link elements before constructing the live
Blink frame. Provider-loaded stylesheet text is injected into the existing
Blink stylesheet path and then parsed by Blink.

By default, `data:` URLs remain internally decoded memory-only resources and do
not call the provider. With
`BLINK_STANDALONE_RESOURCE_PROVIDER_CALLBACK_FOR_DATA_URLS`, data URLs that
reach the standalone provider-backed fetch seam are routed through the callback;
today this is validated for `<img src="data:...">` image resources and CSS image
values such as `background-image: url(data:...)`, including data URLs inside
provider-loaded linked stylesheets. If the callback blocks or fails those data
URLs, the request fails closed and does not fall back to internal data decoding.
The callback currently covers data URLs that are observed by the standalone
resource fetch seam; new resource classes should add explicit smoke coverage
before being advertised as provider-routable.

CSS `@font-face` resource URLs are routed through the provider as
`BLINK_STANDALONE_RESOURCE_TYPE_FONT` with
`BLINK_STANDALONE_RESOURCE_INITIATOR_FONT_FACE`. This is request routing only:
downloadable web-font decoding and rendering remain unsupported in this
standalone build. The CSS-only rule path can ask the provider for font bytes and
blocked or missing font resources fail closed, but `FontFace::Create(...)` does
not install a live CSS font face and `web_font_decoder_phase1_unsupported.cc`
still rejects web-font decoding. The JavaScript `FontFace` constructor/API,
promises, and events remain unsupported.

Media and audio playback remain unsupported. In this standalone profile,
`HTMLElementFactory::Create(...)` does not construct `HTMLAudioElement`,
`HTMLVideoElement`, or `HTMLSourceElement`; those tags are ordinary
`HTMLElement` instances and do not run the Blink media resource selection
algorithm. The active frame/client stubs also return `nullptr` from
`CreateWebMediaPlayer(...)`, so playback and decoding are unavailable even if
real media elements are imported later. As a result, `<audio src>`,
`<video src>`, and media `<source src>` URLs do not currently issue
`BLINK_STANDALONE_RESOURCE_TYPE_MEDIA` provider callbacks. Provider-required
mode remains fail-closed because no filesystem or network media fetch is
attempted; adding media provider routing requires importing/wiring the real
Blink media element load path separately from media decoding/playback.

## Live Mutations

Mutation calls queue work for the next `advance_frame`. They use live Blink
DOM, CSS, and form-control APIs and do not reload or recreate the document.
State is preserved when Blink preserves it; replacing or removing a subtree
also removes the state owned by that subtree.

Supported mutation groups are:

- Element text content.
- Element attributes and attribute removal.
- Full inline style attribute replacement.
- Stylesheet text replacement by `<style>` element id.
- Element inner HTML replacement.
- Body inner HTML replacement.
- HTML fragment insertion around or inside an element.
- Element removal.
- Form control value, checked state, focus/blur, and text selection.
- Multi-select selected-value mutation.

Fragment-style mutations reuse the no-script validation rules. Missing element
ids, invalid insert positions, unsafe fragments, and unsupported form controls
return recoverable non-OK status values and set renderer diagnostics.

Supported insert positions are:

- `BLINK_STANDALONE_INSERT_BEFORE_BEGIN`
- `BLINK_STANDALONE_INSERT_AFTER_BEGIN`
- `BLINK_STANDALONE_INSERT_BEFORE_END`
- `BLINK_STANDALONE_INSERT_AFTER_END`

## Metadata And Form State

Hit metadata is collected from the latest frame and includes element id, tag
name, `data-godot-action`, logical bounds, and disabled/editable/checked/focused
state where available.

Form state is collected from real Blink controls and includes element id, tag
name, value, checked/focused state, selection offsets where available, and
range metadata fields `type`, `min`, `max`, and `step`.

Range/slider controls expose their current value through
`blink_standalone_renderer_get_form_control_state_by_id`. Single-select controls
use `state.value` for the current selected value. Multi-select controls expose
the first/current Blink value through `state.value`; use
`blink_standalone_renderer_form_control_selected_value_count`,
`blink_standalone_renderer_get_form_control_selected_value`, and
`blink_standalone_renderer_set_form_control_selected_values` for the complete
selected-value list. Selected values are reported in Blink document option
order.

String pointers returned from output, metadata, form-state, selected-value, and
diagnostic APIs are renderer-owned and valid until the next renderer operation
that replaces the relevant snapshot, or until destroy.

## Diagnostics

Most APIs return a `blink_standalone_status_code_t`. Renderer-local failure
details are available through:

- `blink_standalone_renderer_get_last_error_code`
- `blink_standalone_renderer_get_last_error_message`
- `blink_standalone_renderer_clear_last_error`
- legacy `blink_standalone_renderer_last_error`

Successful renderer operations clear stale diagnostics. Null-renderer calls
cannot store renderer-local diagnostics, so the return code is the only
available signal for those cases. Messages are stable enough for debugging and
smoke tests, but embedders should branch on status codes rather than parse
message text for product behavior.

## Runtime Package

On Windows, embedders should use the generated C API runtime package rather than
copying sidecars by hand. Build it with:

```powershell
cmake --build --preset x64-Release-GeneratedV8-ChromiumLLVM-c-api-package
```

The package is generated under:

```text
build/cmake-generated-v8-chromium-llvm/package/c_api_runtime/
```

It contains the DLL, import library, ANGLE sidecars, ICU data, and link manifest
needed by external hosts. See `docs/SELF_BUILD_DEPENDENCIES.md` for the full
self-build and package details.

## Validation Smokes

The benchmark executable exposes focused C API smokes for embedder regressions:

- `--c-api-smoke`
- `--c-api-transparent-background-smoke`
- `--c-api-css-filter-blur-smoke`
- `--c-api-backdrop-filter-region-smoke`
- `--c-api-backdrop-filter-rounded-smoke`
- `--c-api-backdrop-filter-chain-smoke`
- `--c-api-backdrop-filter-unsupported-smoke`
- `--c-api-dom-mutation-smoke`
- `--c-api-body-mutation-smoke`
- `--c-api-form-control-mutation-smoke`
- `--c-api-absolute-form-mutation-smoke`
- `--c-api-separated-click-smoke`
- `--c-api-slider-form-state-smoke`
- `--c-api-select-form-state-smoke`
- `--c-api-multiselect-form-state-smoke`
- `--c-api-structural-dom-mutation-smoke`
- `--c-api-mutation-diagnostics-smoke`
- `--c-api-mutation-stress-smoke`

The multiselect smoke and stress fixture validate C API state and mutation
semantics. Visible listbox rendering is deliberately out of scope for those
fixtures today.
