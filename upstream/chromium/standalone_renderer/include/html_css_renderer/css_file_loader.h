#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_CSS_FILE_LOADER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_CSS_FILE_LOADER_H_

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include "html_css_renderer/compositor_types.h"

namespace html_css_renderer {

bool CssContainsImportRule(const std::string& css);
void AppendUnsupportedCssImportDiagnostic(
    const std::string& css,
    const std::string& stylesheet_label,
    std::vector<std::string>* diagnostics);
std::string RebaseCssUrlsToDocumentBase(
    const std::string& css,
    const std::filesystem::path& stylesheet_path,
    const std::filesystem::path& document_base_dir);
std::optional<Stylesheet> LoadStylesheetFileForDocument(
    const std::filesystem::path& stylesheet_path,
    const std::filesystem::path& document_base_dir,
    std::vector<std::string>* diagnostics);
void AddLocalLinkedStylesheetsForDocument(
    const std::filesystem::path& html_path,
    const std::string& html,
    RendererCreateInfo* create_info,
    std::vector<std::string>* diagnostics);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_CSS_FILE_LOADER_H_
