#include "html_css_renderer/css_file_loader.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>

namespace html_css_renderer {
namespace {

namespace fs = std::filesystem;

std::optional<std::string> ReadTextFile(const fs::path& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return std::nullopt;
  }
  return std::string(std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>());
}

std::string ToLowerAscii(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return value;
}

std::string TrimAscii(std::string value) {
  auto is_space = [](unsigned char c) { return std::isspace(c) != 0; };
  value.erase(value.begin(),
              std::find_if(value.begin(), value.end(), [&](char c) {
                return !is_space(static_cast<unsigned char>(c));
              }));
  value.erase(std::find_if(value.rbegin(), value.rend(), [&](char c) {
                return !is_space(static_cast<unsigned char>(c));
              }).base(),
              value.end());
  return value;
}

bool HasUrlScheme(const std::string& value) {
  const size_t colon = value.find(':');
  if (colon == std::string::npos || colon == 0) {
    return false;
  }
  for (size_t i = 0; i < colon; ++i) {
    const unsigned char c = static_cast<unsigned char>(value[i]);
    if (!std::isalnum(c) && value[i] != '+' && value[i] != '-' &&
        value[i] != '.') {
      return false;
    }
  }
  return true;
}

std::string RebaseCssUrlValue(const std::string& raw_value,
                              const fs::path& stylesheet_dir,
                              const fs::path& document_base_dir) {
  std::string value = TrimAscii(raw_value);
  if (value.empty()) {
    return raw_value;
  }
  char quote = '\0';
  if (value.size() >= 2 &&
      ((value.front() == '"' && value.back() == '"') ||
       (value.front() == '\'' && value.back() == '\''))) {
    quote = value.front();
    value = value.substr(1, value.size() - 2);
  }
  const std::string lower = ToLowerAscii(value);
  if (value.empty() || value.front() == '#' ||
      lower.rfind("//", 0) == 0 || lower.rfind("/", 0) == 0 ||
      lower.rfind("\\", 0) == 0 || HasUrlScheme(value)) {
    return raw_value;
  }
  const fs::path absolute_url =
      (stylesheet_dir / fs::path(value)).lexically_normal();
  fs::path rebased = absolute_url.lexically_relative(document_base_dir);
  if (rebased.empty()) {
    rebased = absolute_url;
  }
  std::string rewritten = rebased.generic_string();
  if (quote != '\0') {
    rewritten = std::string(1, quote) + rewritten + std::string(1, quote);
  }
  return rewritten;
}

std::optional<std::string> ExtractAttribute(const std::string& tag,
                                            const std::string& name) {
  const std::string lower = ToLowerAscii(tag);
  const std::string needle = ToLowerAscii(name) + "=";
  const size_t attr = lower.find(needle);
  if (attr == std::string::npos) {
    return std::nullopt;
  }
  size_t value_start = attr + needle.size();
  if (value_start >= tag.size()) {
    return std::nullopt;
  }
  const char quote = tag[value_start];
  if (quote == '"' || quote == '\'') {
    ++value_start;
    const size_t value_end = tag.find(quote, value_start);
    if (value_end == std::string::npos) {
      return std::nullopt;
    }
    return tag.substr(value_start, value_end - value_start);
  }
  size_t value_end = value_start;
  while (value_end < tag.size() &&
         !std::isspace(static_cast<unsigned char>(tag[value_end])) &&
         tag[value_end] != '>') {
    ++value_end;
  }
  return tag.substr(value_start, value_end - value_start);
}

std::vector<std::string> ExtractLinkedStylesheetHrefs(const std::string& html) {
  std::vector<std::string> hrefs;
  const std::string lower = ToLowerAscii(html);
  size_t search_offset = 0;
  while (true) {
    const size_t link_start = lower.find("<link", search_offset);
    if (link_start == std::string::npos) {
      break;
    }
    const size_t link_end = lower.find('>', link_start);
    if (link_end == std::string::npos) {
      break;
    }
    const std::string tag = html.substr(link_start, link_end - link_start + 1);
    const std::string lower_tag = lower.substr(link_start,
                                               link_end - link_start + 1);
    const std::optional<std::string> rel = ExtractAttribute(tag, "rel");
    const std::optional<std::string> href = ExtractAttribute(tag, "href");
    if (href && rel &&
        ToLowerAscii(*rel).find("stylesheet") != std::string::npos) {
      hrefs.push_back(*href);
    } else if (href && lower_tag.find("stylesheet") != std::string::npos) {
      hrefs.push_back(*href);
    }
    search_offset = link_end + 1;
  }
  return hrefs;
}

}  // namespace

bool CssContainsImportRule(const std::string& css) {
  const std::string lower = ToLowerAscii(css);
  bool in_single_quote = false;
  bool in_double_quote = false;
  bool in_comment = false;
  for (size_t i = 0; i < lower.size(); ++i) {
    if (in_comment) {
      if (i + 1 < lower.size() && lower[i] == '*' && lower[i + 1] == '/') {
        in_comment = false;
        ++i;
      }
      continue;
    }
    if (in_single_quote) {
      if (lower[i] == '\\') {
        ++i;
      } else if (lower[i] == '\'') {
        in_single_quote = false;
      }
      continue;
    }
    if (in_double_quote) {
      if (lower[i] == '\\') {
        ++i;
      } else if (lower[i] == '"') {
        in_double_quote = false;
      }
      continue;
    }
    if (i + 1 < lower.size() && lower[i] == '/' && lower[i + 1] == '*') {
      in_comment = true;
      ++i;
      continue;
    }
    if (lower[i] == '\'') {
      in_single_quote = true;
      continue;
    }
    if (lower[i] == '"') {
      in_double_quote = true;
      continue;
    }
    if (lower.compare(i, 7, "@import") == 0) {
      const size_t after = i + 7;
      if (after >= lower.size() ||
          !std::isalnum(static_cast<unsigned char>(lower[after]))) {
        return true;
      }
    }
  }
  return false;
}

void AppendUnsupportedCssImportDiagnostic(
    const std::string& css,
    const std::string& stylesheet_label,
    std::vector<std::string>* diagnostics) {
  if (diagnostics && CssContainsImportRule(css)) {
    diagnostics->push_back("unsupported CSS @import rule in stylesheet: " +
                           stylesheet_label);
  }
}

std::string RebaseCssUrlsToDocumentBase(
    const std::string& css,
    const fs::path& stylesheet_path,
    const fs::path& document_base_dir) {
  const fs::path stylesheet_dir = stylesheet_path.parent_path();
  std::string output;
  output.reserve(css.size());
  const std::string lower = ToLowerAscii(css);
  size_t search_offset = 0;
  while (true) {
    const size_t url_start = lower.find("url(", search_offset);
    if (url_start == std::string::npos) {
      output += css.substr(search_offset);
      break;
    }
    const size_t value_start = url_start + 4;
    const size_t value_end = css.find(')', value_start);
    if (value_end == std::string::npos) {
      output += css.substr(search_offset);
      break;
    }
    output += css.substr(search_offset, value_start - search_offset);
    output += RebaseCssUrlValue(css.substr(value_start,
                                           value_end - value_start),
                                stylesheet_dir, document_base_dir);
    output.push_back(')');
    search_offset = value_end + 1;
  }
  return output;
}

std::optional<Stylesheet> LoadStylesheetFileForDocument(
    const fs::path& stylesheet_path,
    const fs::path& document_base_dir,
    std::vector<std::string>* diagnostics) {
  const std::optional<std::string> css = ReadTextFile(stylesheet_path);
  if (!css) {
    return std::nullopt;
  }
  AppendUnsupportedCssImportDiagnostic(*css, stylesheet_path.string(),
                                       diagnostics);
  const fs::path absolute_stylesheet_path = fs::absolute(stylesheet_path);
  return Stylesheet{stylesheet_path.string(),
                    RebaseCssUrlsToDocumentBase(*css, absolute_stylesheet_path,
                                                document_base_dir)};
}

void AddLocalLinkedStylesheetsForDocument(
    const fs::path& html_path,
    const std::string& html,
    RendererCreateInfo* create_info,
    std::vector<std::string>* diagnostics) {
  const fs::path base_dir = fs::absolute(html_path).parent_path();
  for (const std::string& href : ExtractLinkedStylesheetHrefs(html)) {
    if (href.find("://") != std::string::npos || href.rfind("//", 0) == 0 ||
        href.rfind("data:", 0) == 0 || href.empty()) {
      continue;
    }
    fs::path css_path = fs::path(href);
    if (css_path.is_relative()) {
      css_path = base_dir / css_path;
    }
    std::optional<Stylesheet> stylesheet =
        LoadStylesheetFileForDocument(css_path, base_dir, diagnostics);
    if (stylesheet) {
      create_info->stylesheets.push_back(std::move(*stylesheet));
    }
  }
}

}  // namespace html_css_renderer
