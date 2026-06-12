#include "html_css_renderer/blink_adapter.h"

namespace html_css_renderer {

std::vector<BlinkBoundaryReplacement> RequiredBlinkBoundaryReplacements() {
  return {
      {"ChromeClient", "standalone live-frame test client", true},
      {"LocalFrameClient", "standalone live-frame test client", true},
      {"DocumentLoader", "live Blink in-memory document commit", true},
      {"URLLoader", "AssetProvider/resource-root-backed resource resolver",
       true},
      {"BrowserInterfaceBroker", "null broker with no Mojo surface", true},
      {"CodeCacheHost", "disabled code cache", true},
      {"ScriptController", "no script context creation or execution", true},
      {"V8/cppgc runtime",
       "transitional internal memory/runtime dependency only; no public script "
       "API or script execution",
       true},
      {"background execution startup", "blocked at feature policy boundary",
       true},
      {"Timer/microtask scheduling", "deterministic caller-provided timeline",
       true},
      {"GPU/compositor presentation",
       "pending PaintArtifactCompositor/cc integration", true},
      {"Navigation/form submission/preload",
       "diagnostic-only rejected side effect", true},
      {"Remote @import/fetch/XHR", "diagnostic-only missing resource", true},
  };
}

std::vector<BlinkRuntimeShim> RequiredBlinkRuntimeShims() {
  return {
      {"standalone page clients",
       {"ChromeClient", "LocalFrameClient", "Page::PageClients"},
       "own the minimal Page/Frame client surface with no browser process, UI "
       "chrome, accessibility tree, inspector, or navigation side effects",
       {"third_party/blink/renderer/core/testing/dummy_page_holder.cc",
        "third_party/blink/renderer/core/loader/empty_clients.h"},
       {"chrome/", "content/", "extensions/", "mojo/", "services/network/"},
       true,
       false},
      {"in-memory document commit",
       {"DocumentLoader", "WebNavigationParams", "PolicyContainer"},
       "commit caller-supplied HTML and stylesheets directly into a LocalFrame "
       "without navigation, history, preload, or form submission",
       {"third_party/blink/renderer/core/frame/local_frame.h",
        "third_party/blink/renderer/core/loader/document_loader.h"},
       {"content/", "net/", "services/network/", "mojo/"},
       true,
       false},
      {"asset-provider resource loading",
       {"URLLoaderFactory", "ResourceFetcher", "URLLoaderMockFactory"},
       "resolve url(...), images, SVG references, and font-face sources through "
       "the standalone resource bridge instead of browser network services",
       {"third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h"},
       {"services/network/", "content/", "mojo/"},
       true,
       false},
      {"script-disabled execution context",
       {"ScriptController", "V8PerContextData", "DOMWrapperWorld"},
       "allow Blink lifecycle setup without exposing script execution as a "
       "standalone product surface",
       {"third_party/blink/renderer/bindings/core/v8/script_controller.h"},
       {"v8/src/", "content/"},
       true,
       false},
      {"paint artifact extraction",
       {"PaintController", "PaintArtifact", "DisplayItemList"},
       "read Blink PaintArtifact output from LocalFrameView after lifecycle "
       "updates",
       {"third_party/blink/renderer/platform/graphics/paint/paint_artifact.h"},
       {"cc/", "gpu/"},
       true,
       true},
      {"PaintArtifactCompositor/cc presentation",
       {"PaintArtifactCompositor", "cc::LayerTreeHost"},
       "replace the transitional retained Skia CPU presenter with Chromium's "
       "compositor path",
       {"third_party/blink/renderer/platform/graphics/compositing/"
        "paint_artifact_compositor.h"},
       {"gpu/"},
       true,
       false},
  };
}

}  // namespace html_css_renderer
