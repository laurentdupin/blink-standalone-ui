#include "html_css_renderer/css_file_loader.h"

#include <algorithm>
#include <string_view>

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/strings/strcat.h"
#include "base/strings/string_util.h"
#include "net/base/filename_util.h"
#include "url/gurl.h"
#include "url/url_constants.h"

namespace html_css_renderer {
namespace {

namespace fs = std::filesystem;

base::FilePath FilePathFromFsPath(const fs::path& path) {
  return base::FilePath(path.native());
}

fs::path FsPathFromFilePath(const base::FilePath& path) {
  return fs::path(path.value());
}

base::FilePath AbsoluteFilePathForCssPolicy(base::FilePath path) {
  if (path.empty())
    return path;
  base::FilePath resolved = base::MakeAbsoluteFilePath(path);
  if (!resolved.empty())
    return resolved;
  if (path.IsAbsolute())
    return path.NormalizePathSeparators();
  base::FilePath current_directory;
  if (base::GetCurrentDirectory(&current_directory))
    return current_directory.Append(path).NormalizePathSeparators();
  return path.NormalizePathSeparators();
}

std::optional<std::string> ReadTextFile(const fs::path& path) {
  std::string contents;
  if (!base::ReadFileToString(FilePathFromFsPath(path), &contents)) {
    return std::nullopt;
  }
  return contents;
}

std::optional<fs::path> ResolveLocalPathReference(
    const std::string& reference,
    const fs::path& base_dir) {
  if (base::StartsWith(reference, "//")) {
    return std::nullopt;
  }
  const GURL url(reference);
  if (url.has_scheme()) {
    if (!url.SchemeIs(url::kFileScheme)) {
      return std::nullopt;
    }
    base::FilePath file_path;
    if (!net::FileURLToFilePath(url, &file_path)) {
      return std::nullopt;
    }
    return FsPathFromFilePath(file_path);
  }
  fs::path path(reference);
  if (path.is_relative()) {
    path = base_dir / path;
  }
  return path;
}

bool IsPathWithinRoot(const fs::path& path, const fs::path& root) {
  const base::FilePath path_file = FilePathFromFsPath(path);
  const base::FilePath root_file = FilePathFromFsPath(root);
  return path_file == root_file || root_file.IsParent(path_file);
}

fs::path NormalizePathForPolicy(const fs::path& path) {
  return FsPathFromFilePath(
      AbsoluteFilePathForCssPolicy(FilePathFromFsPath(path)));
}

bool IsImportBoundary(char c) {
  return !base::IsAsciiAlphaNumeric(c) && c != '_' && c != '-';
}

void AppendUnsupportedCssImportRuleDiagnostic(
    const std::string& stylesheet_label,
    const std::string& reason,
    std::vector<std::string>* diagnostics) {
  if (!diagnostics) {
    return;
  }
  std::string message = base::StrCat(
      {"unsupported CSS @import rule in stylesheet: ", stylesheet_label});
  if (!reason.empty()) {
    base::StrAppend(&message, {" (", reason, ")"});
  }
  diagnostics->push_back(message);
}

struct ParsedImportRule {
  bool supported = false;
  std::string href;
  std::string reason;
};

size_t FindCssRuleEnd(const std::string& css, size_t rule_start) {
  bool in_single_quote = false;
  bool in_double_quote = false;
  bool in_comment = false;
  int paren_depth = 0;
  for (size_t i = rule_start; i < css.size(); ++i) {
    if (in_comment) {
      if (i + 1 < css.size() && css[i] == '*' && css[i + 1] == '/') {
        in_comment = false;
        ++i;
      }
      continue;
    }
    if (in_single_quote) {
      if (css[i] == '\\') {
        ++i;
      } else if (css[i] == '\'') {
        in_single_quote = false;
      }
      continue;
    }
    if (in_double_quote) {
      if (css[i] == '\\') {
        ++i;
      } else if (css[i] == '"') {
        in_double_quote = false;
      }
      continue;
    }
    if (i + 1 < css.size() && css[i] == '/' && css[i + 1] == '*') {
      in_comment = true;
      ++i;
      continue;
    }
    if (css[i] == '\'') {
      in_single_quote = true;
      continue;
    }
    if (css[i] == '"') {
      in_double_quote = true;
      continue;
    }
    if (css[i] == '(') {
      ++paren_depth;
      continue;
    }
    if (css[i] == ')' && paren_depth > 0) {
      --paren_depth;
      continue;
    }
    if (css[i] == ';' && paren_depth == 0) {
      return i + 1;
    }
  }
  return css.size();
}

ParsedImportRule ParseImportRule(const std::string& rule) {
  ParsedImportRule parsed;
  const std::string lower = base::ToLowerASCII(rule);
  size_t cursor = 7;
  auto skip_space = [&]() {
    while (cursor < rule.size() && base::IsAsciiWhitespace(rule[cursor])) {
      ++cursor;
    }
  };
  skip_space();
  size_t value_end = cursor;
  if (base::StartsWith(std::string_view(lower).substr(cursor), "url")) {
    cursor += 3;
    skip_space();
    if (cursor >= rule.size() || rule[cursor] != '(') {
      parsed.reason = "invalid url() import";
      return parsed;
    }
    ++cursor;
    skip_space();
    if (cursor < rule.size() && (rule[cursor] == '"' || rule[cursor] == '\'')) {
      const char quote = rule[cursor++];
      const size_t href_start = cursor;
      while (cursor < rule.size() && rule[cursor] != quote) {
        if (rule[cursor] == '\\' && cursor + 1 < rule.size()) {
          cursor += 2;
        } else {
          ++cursor;
        }
      }
      if (cursor >= rule.size()) {
        parsed.reason = "unterminated quoted import";
        return parsed;
      }
      parsed.href = rule.substr(href_start, cursor - href_start);
      ++cursor;
      skip_space();
      if (cursor >= rule.size() || rule[cursor] != ')') {
        parsed.reason = "invalid url() import";
        return parsed;
      }
      value_end = ++cursor;
    } else {
      const size_t href_start = cursor;
      while (cursor < rule.size() && rule[cursor] != ')') {
        ++cursor;
      }
      if (cursor >= rule.size()) {
        parsed.reason = "unterminated url() import";
        return parsed;
      }
      parsed.href = std::string(base::TrimWhitespaceASCII(
          rule.substr(href_start, cursor - href_start), base::TRIM_ALL));
      value_end = ++cursor;
    }
  } else if (cursor < rule.size() &&
             (rule[cursor] == '"' || rule[cursor] == '\'')) {
    const char quote = rule[cursor++];
    const size_t href_start = cursor;
    while (cursor < rule.size() && rule[cursor] != quote) {
      if (rule[cursor] == '\\' && cursor + 1 < rule.size()) {
        cursor += 2;
      } else {
        ++cursor;
      }
    }
    if (cursor >= rule.size()) {
      parsed.reason = "unterminated quoted import";
      return parsed;
    }
    parsed.href = rule.substr(href_start, cursor - href_start);
    value_end = ++cursor;
  } else {
    parsed.reason = "missing import URL";
    return parsed;
  }

  std::string tail = std::string(
      base::TrimWhitespaceASCII(rule.substr(value_end), base::TRIM_ALL));
  if (!tail.empty() && tail.back() == ';') {
    tail.pop_back();
    tail = std::string(base::TrimWhitespaceASCII(tail, base::TRIM_ALL));
  }
  if (!tail.empty()) {
    parsed.reason = "media-qualified imports are not expanded";
    parsed.href.clear();
    return parsed;
  }
  parsed.href =
      std::string(base::TrimWhitespaceASCII(parsed.href, base::TRIM_ALL));
  if (parsed.href.empty()) {
    parsed.reason = "empty import URL";
    return parsed;
  }
  parsed.supported = true;
  return parsed;
}

std::optional<std::string> ExpandAndRebaseStylesheetFile(
    const fs::path& stylesheet_path,
    const fs::path& document_base_dir,
    std::vector<std::string>* diagnostics,
    std::vector<fs::path>* import_stack,
    size_t depth);

std::string ExpandImportsAndRebaseCssSegments(
    const std::string& css,
    const fs::path& stylesheet_path,
    const fs::path& document_base_dir,
    std::vector<std::string>* diagnostics,
    std::vector<fs::path>* import_stack,
    size_t depth) {
  std::string output;
  output.reserve(css.size());
  const std::string lower = base::ToLowerASCII(css);
  bool in_single_quote = false;
  bool in_double_quote = false;
  bool in_comment = false;
  size_t segment_start = 0;
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
    if (!base::StartsWith(std::string_view(lower).substr(i), "@import")) {
      continue;
    }
    const size_t after_import = i + 7;
    if (after_import < lower.size() &&
        !IsImportBoundary(lower[after_import])) {
      continue;
    }
    output += RebaseCssUrlsToDocumentBase(
        css.substr(segment_start, i - segment_start), stylesheet_path,
        document_base_dir);
    const size_t rule_end = FindCssRuleEnd(css, i);
    const ParsedImportRule parsed =
        ParseImportRule(css.substr(i, rule_end - i));
    if (!parsed.supported) {
      AppendUnsupportedCssImportRuleDiagnostic(stylesheet_path.string(),
                                              parsed.reason, diagnostics);
    } else {
      std::optional<fs::path> resolved_import =
          ResolveLocalPathReference(parsed.href, stylesheet_path.parent_path());
      if (!resolved_import) {
        AppendUnsupportedCssImportRuleDiagnostic(
            stylesheet_path.string(), "non-local import URL", diagnostics);
      } else {
        const fs::path import_path = NormalizePathForPolicy(*resolved_import);
        const fs::path root = NormalizePathForPolicy(document_base_dir);
        if (!IsPathWithinRoot(import_path, root)) {
          AppendUnsupportedCssImportRuleDiagnostic(
              stylesheet_path.string(), "import path escapes document base",
              diagnostics);
        } else if (std::find(import_stack->begin(), import_stack->end(),
                             import_path) != import_stack->end()) {
          AppendUnsupportedCssImportRuleDiagnostic(stylesheet_path.string(),
                                                  "cyclic import", diagnostics);
        } else {
          std::optional<std::string> imported =
              ExpandAndRebaseStylesheetFile(import_path, document_base_dir,
                                            diagnostics, import_stack,
                                            depth + 1);
          if (imported) {
            if (!output.empty() && output.back() != '\n') {
              output.push_back('\n');
            }
            output += *imported;
            if (!output.empty() && output.back() != '\n') {
              output.push_back('\n');
            }
          } else {
            AppendUnsupportedCssImportRuleDiagnostic(
                stylesheet_path.string(), "import file not found",
                diagnostics);
          }
        }
      }
    }
    i = rule_end == 0 ? 0 : rule_end - 1;
    segment_start = rule_end;
  }
  output += RebaseCssUrlsToDocumentBase(css.substr(segment_start),
                                        stylesheet_path, document_base_dir);
  return output;
}

std::optional<std::string> ExpandAndRebaseStylesheetFile(
    const fs::path& stylesheet_path,
    const fs::path& document_base_dir,
    std::vector<std::string>* diagnostics,
    std::vector<fs::path>* import_stack,
    size_t depth) {
  constexpr size_t kMaxImportDepth = 16;
  if (depth > kMaxImportDepth) {
    AppendUnsupportedCssImportRuleDiagnostic(stylesheet_path.string(),
                                            "import depth limit exceeded",
                                            diagnostics);
    return std::string();
  }
  const fs::path normalized_stylesheet =
      NormalizePathForPolicy(stylesheet_path);
  const std::optional<std::string> css = ReadTextFile(normalized_stylesheet);
  if (!css) {
    return std::nullopt;
  }
  import_stack->push_back(normalized_stylesheet);
  std::string expanded = ExpandImportsAndRebaseCssSegments(
      *css, normalized_stylesheet, NormalizePathForPolicy(document_base_dir),
      diagnostics, import_stack, depth);
  import_stack->pop_back();
  return expanded;
}

std::string RebaseCssUrlValue(const std::string& raw_value,
                              const fs::path& stylesheet_dir,
                              const fs::path& document_base_dir) {
  std::string value =
      std::string(base::TrimWhitespaceASCII(raw_value, base::TRIM_ALL));
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
  const std::string lower = base::ToLowerASCII(value);
  if (value.empty() || value.front() == '#' ||
      base::StartsWith(lower, "//") || base::StartsWith(lower, "/") ||
      base::StartsWith(lower, "\\") || GURL(value).has_scheme()) {
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
    const std::string quote_string(1, quote);
    rewritten = base::StrCat({quote_string, rewritten, quote_string});
  }
  return rewritten;
}

std::optional<std::string> ExtractAttribute(const std::string& tag,
                                            const std::string& name) {
  const std::string lower = base::ToLowerASCII(tag);
  const std::string needle = base::StrCat({base::ToLowerASCII(name), "="});
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
         !base::IsAsciiWhitespace(tag[value_end]) &&
         tag[value_end] != '>') {
    ++value_end;
  }
  return tag.substr(value_start, value_end - value_start);
}

std::vector<std::string> ExtractLinkedStylesheetHrefs(const std::string& html) {
  std::vector<std::string> hrefs;
  const std::string lower = base::ToLowerASCII(html);
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
        base::ToLowerASCII(*rel).find("stylesheet") != std::string::npos) {
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
  const std::string lower = base::ToLowerASCII(css);
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
    if (base::StartsWith(std::string_view(lower).substr(i), "@import")) {
      const size_t after = i + 7;
      if (after >= lower.size() ||
          !base::IsAsciiAlphaNumeric(lower[after])) {
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
    diagnostics->push_back(base::StrCat(
        {"unsupported CSS @import rule in stylesheet: ", stylesheet_label}));
  }
}

std::string RebaseCssUrlsToDocumentBase(
    const std::string& css,
    const fs::path& stylesheet_path,
    const fs::path& document_base_dir) {
  const fs::path stylesheet_dir = stylesheet_path.parent_path();
  std::string output;
  output.reserve(css.size());
  const std::string lower = base::ToLowerASCII(css);
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
  std::vector<fs::path> import_stack;
  const std::optional<std::string> css = ExpandAndRebaseStylesheetFile(
      stylesheet_path, document_base_dir, diagnostics, &import_stack, 0);
  if (!css) {
    return std::nullopt;
  }
  return Stylesheet{stylesheet_path.string(), *css};
}

void AddLocalLinkedStylesheetsForDocument(
    const fs::path& html_path,
    const std::string& html,
    RendererCreateInfo* create_info,
    std::vector<std::string>* diagnostics) {
  const fs::path base_dir = NormalizePathForPolicy(html_path).parent_path();
  for (const std::string& href : ExtractLinkedStylesheetHrefs(html)) {
    if (href.empty()) {
      continue;
    }
    std::optional<fs::path> css_path = ResolveLocalPathReference(href, base_dir);
    if (!css_path) {
      continue;
    }
    std::optional<Stylesheet> stylesheet =
        LoadStylesheetFileForDocument(*css_path, base_dir, diagnostics);
    if (stylesheet) {
      create_info->stylesheets.push_back(std::move(*stylesheet));
    }
  }
}

}  // namespace html_css_renderer
