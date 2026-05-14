#include "html_css_renderer/render_policy.h"

#include <algorithm>
#include <cctype>

namespace html_css_renderer {
namespace {

bool StartsWithInsensitive(const std::string& value,
                           size_t offset,
                           const std::string& token) {
  if (offset + token.size() > value.size()) {
    return false;
  }
  for (size_t i = 0; i < token.size(); ++i) {
    if (std::tolower(static_cast<unsigned char>(value[offset + i])) !=
        std::tolower(static_cast<unsigned char>(token[i]))) {
      return false;
    }
  }
  return true;
}

std::string DecodeBasicEntities(std::string value) {
  struct Entity {
    const char* escaped;
    const char* decoded;
  };
  constexpr Entity entities[] = {
      {"&amp;", "&"},
      {"&lt;", "<"},
      {"&gt;", ">"},
      {"&quot;", "\""},
      {"&#39;", "'"},
      {"&nbsp;", " "},
  };

  for (const auto& entity : entities) {
    size_t pos = 0;
    while ((pos = value.find(entity.escaped, pos)) != std::string::npos) {
      value.replace(pos, std::char_traits<char>::length(entity.escaped),
                    entity.decoded);
      pos += std::char_traits<char>::length(entity.decoded);
    }
  }
  return value;
}

bool StartsWithInsensitive(const std::string& value,
                           size_t offset,
                           const char* token) {
  const std::string token_string(token);
  return StartsWithInsensitive(value, offset, token_string);
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

std::string StripCssImports(const std::string& css,
                            std::vector<std::string>& diagnostics) {
  std::string output;
  output.reserve(css.size());
  const std::string lower = ToLowerAscii(css);

  for (size_t i = 0; i < css.size();) {
    if (StartsWithInsensitive(lower, i, "@import")) {
      const size_t semicolon = css.find(';', i);
      i = semicolon == std::string::npos ? css.size() : semicolon + 1;
      diagnostics.push_back("ignored CSS @import rule");
      continue;
    }
    output.push_back(css[i]);
    ++i;
  }

  return output;
}

std::vector<ResourceReference> ExtractCssUrlReferences(
    const Stylesheet& stylesheet) {
  std::vector<ResourceReference> references;
  const std::string lower = ToLowerAscii(stylesheet.css);

  size_t pos = 0;
  while ((pos = lower.find("url(", pos)) != std::string::npos) {
    size_t value_begin = pos + 4;
    size_t value_end = stylesheet.css.find(')', value_begin);
    if (value_end == std::string::npos) {
      break;
    }

    std::string value =
        TrimAscii(stylesheet.css.substr(value_begin, value_end - value_begin));
    if (value.size() >= 2 &&
        ((value.front() == '"' && value.back() == '"') ||
         (value.front() == '\'' && value.back() == '\''))) {
      value = value.substr(1, value.size() - 2);
    }
    value = TrimAscii(value);

    if (!value.empty()) {
      const std::string prefix =
          lower.rfind("@font-face", pos) != std::string::npos
              ? "font"
              : "stylesheet-url";
      references.push_back({value, prefix});
    }
    pos = value_end + 1;
  }

  return references;
}

}  // namespace

std::string ToLowerAscii(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return value;
}

SanitizedDocument SanitizeHtmlForRendering(const std::string& html) {
  SanitizedDocument document;
  document.html.reserve(html.size());

  const std::string lowered_html = ToLowerAscii(html);
  for (size_t i = 0; i < html.size();) {
    if (StartsWithInsensitive(html, i, "<script")) {
      const size_t script_end = lowered_html.find("</script", i);
      const size_t close = script_end == std::string::npos
                               ? std::string::npos
                               : html.find('>', script_end);
      i = close == std::string::npos ? html.size() : close + 1;
      document.diagnostics.push_back("ignored script block");
      continue;
    }

    if (StartsWithInsensitive(html, i, "javascript:")) {
      i += std::string("javascript:").size();
      document.diagnostics.push_back("ignored javascript: URL");
      continue;
    }

    if (html[i] == '<') {
      const size_t tag_end = html.find('>', i);
      if (tag_end == std::string::npos) {
        document.html.append(html.substr(i));
        break;
      }

      std::string tag = html.substr(i, tag_end - i + 1);
      std::string lowered = ToLowerAscii(tag);
      size_t event_attr = lowered.find(" on");
      while (event_attr != std::string::npos) {
        size_t attr_end = lowered.find_first_of(" \t\r\n>", event_attr + 1);
        size_t equals = lowered.find('=', event_attr + 1);
        if (equals != std::string::npos &&
            equals < (attr_end == std::string::npos ? lowered.size()
                                                    : attr_end)) {
          char quote = equals + 1 < tag.size() ? tag[equals + 1] : '\0';
          if (quote == '"' || quote == '\'') {
            size_t quoted_end = tag.find(quote, equals + 2);
            attr_end = quoted_end == std::string::npos ? tag.size()
                                                       : quoted_end + 1;
          }
        }
        tag.erase(event_attr, attr_end - event_attr);
        lowered = ToLowerAscii(tag);
        event_attr = lowered.find(" on");
        document.diagnostics.push_back(
            "ignored inline event handler attribute");
      }

      size_t script_url = lowered.find("javascript:");
      while (script_url != std::string::npos) {
        tag.erase(script_url, std::string("javascript:").size());
        lowered = ToLowerAscii(tag);
        script_url = lowered.find("javascript:");
        document.diagnostics.push_back("ignored javascript: URL");
      }

      document.html.append(tag);
      i = tag_end + 1;
      continue;
    }

    document.html.push_back(html[i]);
    ++i;
  }

  return document;
}

SanitizedStylesheet SanitizeStylesheetForRendering(
    const Stylesheet& stylesheet) {
  SanitizedStylesheet sanitized;
  sanitized.stylesheet = stylesheet;
  sanitized.stylesheet.css =
      StripCssImports(stylesheet.css, sanitized.diagnostics);
  return sanitized;
}

std::vector<SanitizedStylesheet> SanitizeStylesheetsForRendering(
    const std::vector<Stylesheet>& stylesheets) {
  std::vector<SanitizedStylesheet> sanitized;
  sanitized.reserve(stylesheets.size());
  for (const auto& stylesheet : stylesheets) {
    sanitized.push_back(SanitizeStylesheetForRendering(stylesheet));
  }
  return sanitized;
}

std::string ExtractDocumentText(const std::string& html) {
  std::string text;
  text.reserve(html.size());
  bool in_tag = false;
  bool last_was_space = true;

  for (char c : html) {
    if (c == '<') {
      in_tag = true;
      if (!last_was_space) {
        text.push_back(' ');
        last_was_space = true;
      }
      continue;
    }
    if (c == '>') {
      in_tag = false;
      continue;
    }
    if (in_tag) {
      continue;
    }

    if (std::isspace(static_cast<unsigned char>(c))) {
      if (!last_was_space) {
        text.push_back(' ');
        last_was_space = true;
      }
      continue;
    }

    text.push_back(c);
    last_was_space = false;
  }

  return DecodeBasicEntities(text);
}

std::vector<ResourceReference> ExtractResourceReferences(
    const std::string& html,
    const std::vector<Stylesheet>& stylesheets) {
  std::vector<ResourceReference> references;
  std::string lowered = ToLowerAscii(html);

  size_t pos = 0;
  while ((pos = lowered.find("<img", pos)) != std::string::npos) {
    const size_t tag_end = lowered.find('>', pos);
    if (tag_end == std::string::npos) {
      break;
    }

    const size_t src = lowered.find("src", pos);
    if (src != std::string::npos && src < tag_end) {
      const size_t equals = lowered.find('=', src);
      if (equals != std::string::npos && equals < tag_end) {
        size_t value_begin = equals + 1;
        while (value_begin < tag_end &&
               std::isspace(static_cast<unsigned char>(html[value_begin]))) {
          ++value_begin;
        }

        char quote = html[value_begin];
        size_t value_end = std::string::npos;
        if (quote == '"' || quote == '\'') {
          ++value_begin;
          value_end = html.find(quote, value_begin);
        } else {
          value_end = lowered.find_first_of(" \t\r\n>", value_begin);
        }

        if (value_end != std::string::npos && value_end <= tag_end) {
          references.push_back(
              {html.substr(value_begin, value_end - value_begin), "image"});
        }
      }
    }
    pos = tag_end + 1;
  }

  for (const auto& stylesheet : stylesheets) {
    std::vector<ResourceReference> css_references =
        ExtractCssUrlReferences(stylesheet);
    references.insert(references.end(), css_references.begin(),
                      css_references.end());
  }

  return references;
}

bool IsPermittedResourceReference(const std::string& resource_id) {
  const std::string trimmed = TrimAscii(resource_id);
  const std::string lower = ToLowerAscii(trimmed);
  if (trimmed.empty()) {
    return false;
  }
  if (lower.rfind("//", 0) == 0 || lower.rfind("/", 0) == 0 ||
      lower.rfind("\\", 0) == 0) {
    return false;
  }

  constexpr const char* kBlockedSchemes[] = {
      "http:", "https:", "file:", "ftp:", "ws:", "wss:", "data:", "blob:"};
  for (const char* scheme : kBlockedSchemes) {
    if (lower.rfind(scheme, 0) == 0) {
      return false;
    }
  }

  return true;
}

std::vector<ResourceResolution> ResolveResourceReferences(
    const std::vector<ResourceReference>& references,
    AssetProvider* asset_provider) {
  std::vector<ResourceResolution> resolutions;
  resolutions.reserve(references.size());

  for (const auto& reference : references) {
    ResourceResolution resolution;
    resolution.reference = reference;
    if (!IsPermittedResourceReference(reference.id)) {
      resolution.diagnostic =
          "blocked external " + reference.element_kind + " resource: " +
          reference.id;
    } else if (!asset_provider) {
      resolution.diagnostic =
          "missing asset provider for " + reference.element_kind + ": " +
          reference.id;
    } else {
      resolution.asset = asset_provider->Load(reference.id);
      if (!resolution.asset) {
        resolution.diagnostic =
            "missing " + reference.element_kind + " asset: " + reference.id;
      }
    }
    resolutions.push_back(std::move(resolution));
  }

  return resolutions;
}

FrameStateUpdate BuildFrameStateUpdate(const RendererSnapshot& current,
                                       const FrameInput& input) {
  FrameStateUpdate update;
  update.timeline_time_seconds = current.timeline_time_seconds;
  update.viewport = current.viewport;
  update.scroll_offsets_by_element_id = current.scroll_offsets_by_element_id;
  update.focused_element_id = current.focused_element_id;
  update.hovered_element_id = current.hovered_element_id;
  update.active_element_id = current.active_element_id;
  update.form_values_by_element_id = current.form_values_by_element_id;
  update.keyboard = input.keyboard;
  update.pointers = input.pointers;

  if (input.timeline_time_seconds > 0.0) {
    update.timeline_time_seconds = input.timeline_time_seconds;
  } else if (input.delta_time_seconds >= 0.0) {
    update.timeline_time_seconds += input.delta_time_seconds;
  } else {
    update.diagnostics.push_back("ignored negative frame delta time");
  }

  if (input.viewport) {
    if (input.viewport->width > 0.0f && input.viewport->height > 0.0f) {
      update.viewport = *input.viewport;
    } else {
      update.diagnostics.push_back("ignored invalid viewport size");
    }
  }

  if (!input.scroll_offsets_by_element_id.empty()) {
    update.scroll_offsets_by_element_id = input.scroll_offsets_by_element_id;
  }
  if (!input.focused_element_id.empty()) {
    update.focused_element_id = input.focused_element_id;
  }
  if (!input.hovered_element_id.empty()) {
    update.hovered_element_id = input.hovered_element_id;
  }
  if (!input.active_element_id.empty()) {
    update.active_element_id = input.active_element_id;
  }
  if (!input.form_values_by_element_id.empty()) {
    update.form_values_by_element_id = input.form_values_by_element_id;
  }

  if (!update.pointers.empty()) {
    update.diagnostics.push_back("applied pointer state");
  }
  if (!update.keyboard.pressed_key_codes.empty()) {
    update.diagnostics.push_back("applied keyboard state");
  }
  if (!input.scroll_offsets_by_element_id.empty()) {
    update.diagnostics.push_back("applied scroll state");
  }
  if (!input.form_values_by_element_id.empty()) {
    update.diagnostics.push_back("applied form state");
  }

  return update;
}

bool HasScriptCapableHtmlSurface(const std::string& html) {
  const std::string lower = ToLowerAscii(html);
  return lower.find("<script") != std::string::npos ||
         lower.find("javascript:") != std::string::npos ||
         lower.find(" on") != std::string::npos;
}

}  // namespace html_css_renderer
