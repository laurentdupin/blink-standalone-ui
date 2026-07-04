#ifndef HTML_CSS_RENDERER_STANDALONE_STYLESHEET_LINK_PARSER_H_
#define HTML_CSS_RENDERER_STANDALONE_STYLESHEET_LINK_PARSER_H_

#include <optional>
#include <string>
#include <vector>

#include "base/strings/string_util.h"

namespace html_css_renderer {

inline std::optional<std::string> StandaloneHtmlTagAttributeValue(
    const std::string& tag,
    const std::string& name) {
  const std::string lower = base::ToLowerASCII(tag);
  const std::string needle = base::ToLowerASCII(name);
  size_t pos = 0;
  while ((pos = lower.find(needle, pos)) != std::string::npos) {
    if (pos > 0) {
      const char prev = lower[pos - 1];
      if (base::IsAsciiAlphaNumeric(prev) || prev == '-' || prev == '_') {
        pos += needle.size();
        continue;
      }
    }
    size_t cursor = pos + needle.size();
    while (cursor < lower.size() && base::IsAsciiWhitespace(lower[cursor])) {
      ++cursor;
    }
    if (cursor >= lower.size() || lower[cursor] != '=') {
      pos += needle.size();
      continue;
    }
    ++cursor;
    while (cursor < lower.size() && base::IsAsciiWhitespace(lower[cursor])) {
      ++cursor;
    }
    if (cursor >= tag.size())
      return std::string();
    const char quote = tag[cursor];
    if (quote == '\'' || quote == '"') {
      const size_t end = tag.find(quote, cursor + 1);
      if (end == std::string::npos)
        return std::nullopt;
      return tag.substr(cursor + 1, end - cursor - 1);
    }
    size_t end = cursor;
    while (end < tag.size() && !base::IsAsciiWhitespace(tag[end]) &&
           tag[end] != '>') {
      ++end;
    }
    return tag.substr(cursor, end - cursor);
  }
  return std::nullopt;
}

inline bool StandaloneHtmlLinkTagReferencesStylesheet(
    const std::string& tag) {
  const std::optional<std::string> rel =
      StandaloneHtmlTagAttributeValue(tag, "rel");
  if (rel && base::ToLowerASCII(*rel).find("stylesheet") != std::string::npos)
    return true;

  // Preserve the local CSS loader's permissive fallback for malformed link
  // tags that still contain "stylesheet" and a usable href.
  return base::ToLowerASCII(tag).find("stylesheet") != std::string::npos;
}

inline std::vector<std::string> ExtractStandaloneStylesheetLinkHrefs(
    const std::string& html) {
  std::vector<std::string> hrefs;
  const std::string lower = base::ToLowerASCII(html);
  size_t search_offset = 0;
  while (true) {
    const size_t open = lower.find("<link", search_offset);
    if (open == std::string::npos)
      break;
    const size_t open_end = lower.find('>', open);
    if (open_end == std::string::npos)
      break;
    const std::string tag = html.substr(open, open_end - open + 1);
    const std::optional<std::string> href =
        StandaloneHtmlTagAttributeValue(tag, "href");
    if (href && StandaloneHtmlLinkTagReferencesStylesheet(tag))
      hrefs.push_back(*href);
    search_offset = open_end + 1;
  }
  return hrefs;
}

inline std::string RemoveStandaloneStylesheetLinkTagsFromHtml(
    const std::string& html) {
  std::string output;
  const std::string lower = base::ToLowerASCII(html);
  size_t search_offset = 0;
  while (true) {
    const size_t open = lower.find("<link", search_offset);
    if (open == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    const size_t open_end = lower.find('>', open);
    if (open_end == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    const std::string tag = html.substr(open, open_end - open + 1);
    if (StandaloneHtmlLinkTagReferencesStylesheet(tag)) {
      output += html.substr(search_offset, open - search_offset);
    } else {
      output += html.substr(search_offset, open_end + 1 - search_offset);
    }
    search_offset = open_end + 1;
  }
  return output;
}

}  // namespace html_css_renderer

#endif  // HTML_CSS_RENDERER_STANDALONE_STYLESHEET_LINK_PARSER_H_
