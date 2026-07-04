#ifndef HTML_CSS_RENDERER_STANDALONE_CSS_IMPORT_PARSER_H_
#define HTML_CSS_RENDERER_STANDALONE_CSS_IMPORT_PARSER_H_

#include <optional>
#include <string>
#include <string_view>

#include "base/strings/string_util.h"

namespace html_css_renderer {

struct StandaloneCssImportRule {
  bool supported = false;
  size_t start = 0;
  size_t end = 0;
  std::string href;
  std::string reason;
};

inline bool StandaloneCssImportBoundary(char c) {
  return !base::IsAsciiAlphaNumeric(c) && c != '_' && c != '-';
}

inline size_t FindStandaloneCssRuleEnd(const std::string& css,
                                       size_t rule_start) {
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
    if (css[i] == ';' && paren_depth == 0)
      return i + 1;
  }
  return css.size();
}

inline StandaloneCssImportRule ParseStandaloneCssImportRule(
    const std::string& rule) {
  StandaloneCssImportRule parsed;
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

inline std::optional<StandaloneCssImportRule> FindNextStandaloneCssImportRule(
    const std::string& css,
    size_t offset) {
  const std::string lower = base::ToLowerASCII(css);
  bool in_single_quote = false;
  bool in_double_quote = false;
  bool in_comment = false;
  for (size_t i = offset; i < lower.size(); ++i) {
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
    if (!base::StartsWith(std::string_view(lower).substr(i), "@import"))
      continue;
    const size_t after_import = i + 7;
    if (after_import < lower.size() &&
        !StandaloneCssImportBoundary(lower[after_import])) {
      continue;
    }
    const size_t rule_end = FindStandaloneCssRuleEnd(css, i);
    StandaloneCssImportRule parsed =
        ParseStandaloneCssImportRule(css.substr(i, rule_end - i));
    parsed.start = i;
    parsed.end = rule_end;
    return parsed;
  }
  return std::nullopt;
}

}  // namespace html_css_renderer

#endif  // HTML_CSS_RENDERER_STANDALONE_CSS_IMPORT_PARSER_H_
