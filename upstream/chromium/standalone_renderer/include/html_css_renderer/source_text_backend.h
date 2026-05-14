#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SOURCE_TEXT_BACKEND_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SOURCE_TEXT_BACKEND_H_

#include <memory>

#include "html_css_renderer/text_engine.h"

namespace html_css_renderer {

class SourceTextBackend : public FontProvider,
                          public TextShaper,
                          public GlyphRasterizer {
 public:
  ~SourceTextBackend() override = default;
};

bool IsSourceTextBackendAvailable();
std::unique_ptr<SourceTextBackend> CreateSourceTextBackend();

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SOURCE_TEXT_BACKEND_H_
