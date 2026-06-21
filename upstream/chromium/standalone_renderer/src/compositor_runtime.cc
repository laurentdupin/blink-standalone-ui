#include "html_css_renderer/compositor_runtime.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <memory>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "base/check.h"
#include "base/memory/discardable_memory.h"
#include "base/memory/discardable_memory_allocator.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "html_css_renderer/typeface_resource_registry.h"
#include "html_css_renderer/vulkan_window_host.h"

namespace blink::standalone_renderer_probe {
void StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(int width,
                                                                    int height);
void StandaloneBlinkLiveFrameBridgeSetDocumentScrollOffsetForStandaloneRenderer(
    float x,
    float y);
void StandaloneBlinkLiveFrameBridgeSetElementScrollOffsetsForStandaloneRenderer(
    const char* serialized_offsets);
void StandaloneBlinkLiveFrameBridgeSetAnimationTimeForStandaloneRenderer(
    double time_ms);
void StandaloneBlinkLiveFrameBridgeSetElementAttributesForStandaloneRenderer(
    const char* serialized_attributes);
void StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
    const char* hovered_element_id,
    const char* active_element_id);
void StandaloneBlinkLiveFrameBridgeSetPointerStateForStandaloneRenderer(
    float x,
    float y,
    int pressed,
    int event_type,
    int requested);
void StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
    float x,
    float y,
    float delta_x,
    float delta_y,
    int requested);
void StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
    const char* lifecycle_stop);
void StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer();
void StandaloneBlinkLiveFrameBridgeSetNativeWindowForStandaloneRenderer(
    void* native_window_handle,
    int width,
    int height);
void StandaloneBlinkLiveFrameBridgeRequestPngSnapshotForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeNeedsBeginFrameForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCompositorRootLayerForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcHostForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcRootLayerAttachedForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcCommitRequestedForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcFrameSinkRequestedForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcFrameSinkBoundForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcCompositorFrameSubmittedForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcGpuContextForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcRasterContextForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcSharedImageInterfaceForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcVizDisplayForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcSkiaGpuForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeCcFrameSinkFailureForStandaloneRenderer(
    const char* body_html,
    char* out,
    int capacity);
int StandaloneBlinkLiveFrameBridgeCcAttachFailureForStandaloneRenderer(
    const char* body_html,
    char* out,
    int capacity);
int StandaloneBlinkLiveFrameBridgeCompositorLayerCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeDocumentScrollOffsetForStandaloneRenderer(
    const char* body_html,
    float* x,
    float* y,
    float* max_x,
    float* max_y);
int StandaloneBlinkLiveFrameBridgePointerObservedStateForStandaloneRenderer(
    const char* body_html,
    char* hovered_element_id,
    int hovered_element_id_capacity,
    char* active_element_id,
    int active_element_id_capacity);
int StandaloneBlinkLiveFrameBridgeHitTestEntryCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeHitTestEntryAtForStandaloneRenderer(
    const char* body_html,
    int index,
    char* element_id,
    int element_id_capacity,
    float* x,
    float* y,
    float* width,
    float* height);
int StandaloneBlinkLiveFrameBridgeScrollableElementEntryCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeScrollableElementEntryAtForStandaloneRenderer(
    const char* body_html,
    int index,
    char* element_id,
    int element_id_capacity,
    float* x,
    float* y,
    float* width,
    float* height,
    float* scroll_x,
    float* scroll_y,
    float* max_scroll_x,
    float* max_scroll_y,
    int* can_scroll_x,
    int* can_scroll_y);
int StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonSizeForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonForStandaloneRenderer(
    const char* body_html,
    char* buffer,
    int buffer_size);
int StandaloneBlinkLiveFrameBridgePngSnapshotStatusForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgePngSnapshotByteSizeForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgePngSnapshotBytesForStandaloneRenderer(
    const char* body_html,
    uint8_t* destination,
    int destination_size);
int StandaloneBlinkLiveFrameBridgePngSnapshotFailureForStandaloneRenderer(
    const char* body_html,
    char* buffer,
    int buffer_size);
}  // namespace blink::standalone_renderer_probe

namespace html_css_renderer {
namespace {

namespace fs = std::filesystem;

class StandaloneLocalDiscardableMemory final : public base::DiscardableMemory {
 public:
  explicit StandaloneLocalDiscardableMemory(size_t size) : data_(size) {}

  bool Lock() override {
    if (discarded_)
      return false;
    DCHECK(!is_locked_);
    is_locked_ = true;
    return true;
  }

  void Unlock() override {
    DCHECK(is_locked_);
    is_locked_ = false;
  }

  void* data() const override {
    DCHECK(is_locked_);
    return const_cast<uint8_t*>(data_.data());
  }

  void DiscardForTesting() override {
    DCHECK(!is_locked_);
    discarded_ = true;
    data_.clear();
  }

  base::trace_event::MemoryAllocatorDump* CreateMemoryAllocatorDump(
      const char*,
      base::trace_event::ProcessMemoryDump*) const override {
    return nullptr;
  }

 private:
  bool is_locked_ = true;
  bool discarded_ = false;
  std::vector<uint8_t> data_;
};

class StandaloneLocalDiscardableMemoryAllocator final
    : public base::DiscardableMemoryAllocator {
 public:
  std::unique_ptr<base::DiscardableMemory> AllocateLockedDiscardableMemory(
      size_t size) override {
    bytes_allocated_ += size;
    return std::make_unique<StandaloneLocalDiscardableMemory>(size);
  }

  size_t GetBytesAllocated() const override { return bytes_allocated_; }

  void ReleaseFreeMemory() override {}

 private:
  size_t bytes_allocated_ = 0;
};

void EnsureStandaloneDiscardableMemoryAllocator() {
  static StandaloneLocalDiscardableMemoryAllocator allocator;
  if (!base::DiscardableMemoryAllocator::HasInstance())
    base::DiscardableMemoryAllocator::SetInstance(&allocator);
}

std::string LowerAscii(std::string value) {
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
  if (colon == std::string::npos || colon == 0)
    return false;
  for (size_t i = 0; i < colon; ++i) {
    const unsigned char c = static_cast<unsigned char>(value[i]);
    if (!std::isalnum(c) && value[i] != '+' && value[i] != '-' &&
        value[i] != '.') {
      return false;
    }
  }
  return true;
}

bool HasHtmlBaseElement(const std::string& html) {
  const std::string lower = LowerAscii(html);
  return lower.find("<base") != std::string::npos;
}

std::string PercentEncodeFileUrlPath(std::string path) {
  std::string output;
  output.reserve(path.size() + 16);
  constexpr char kHex[] = "0123456789ABCDEF";
  for (const unsigned char c : path) {
    const bool safe =
        std::isalnum(c) || c == '/' || c == ':' || c == '-' || c == '_' ||
        c == '.' || c == '~';
    if (safe) {
      output.push_back(static_cast<char>(c));
      continue;
    }
    output.push_back('%');
    output.push_back(kHex[c >> 4]);
    output.push_back(kHex[c & 0x0F]);
  }
  return output;
}

std::string FileUrlForBaseDirectory(const std::string& base_path_string) {
  if (base_path_string.empty())
    return std::string();

  std::error_code error;
  fs::path base_path = fs::absolute(fs::path(base_path_string), error);
  if (error)
    base_path = fs::path(base_path_string);
  if (fs::is_regular_file(base_path, error))
    base_path = base_path.parent_path();
  fs::path normalized = fs::weakly_canonical(base_path, error);
  if (!error)
    base_path = std::move(normalized);

  std::string path = base_path.generic_string();
  if (path.empty())
    return std::string();
  if (path.back() != '/')
    path.push_back('/');
  return "file:///" + PercentEncodeFileUrlPath(path);
}

fs::path StandaloneDocumentBaseDirectoryPath() {
  const std::string base_path_string =
      GetStandaloneResourceProviderDocumentBasePath();
  if (base_path_string.empty())
    return fs::path();

  std::error_code error;
  fs::path base_path = fs::absolute(fs::path(base_path_string), error);
  if (error)
    base_path = fs::path(base_path_string);
  if (fs::is_regular_file(base_path, error))
    base_path = base_path.parent_path();
  fs::path normalized = fs::weakly_canonical(base_path, error);
  if (!error)
    base_path = std::move(normalized);
  return base_path;
}

std::string FileUrlForLocalPath(const fs::path& path) {
  if (path.empty())
    return std::string();
  std::error_code error;
  fs::path absolute = fs::absolute(path, error);
  if (error)
    absolute = path;
  fs::path normalized = fs::weakly_canonical(absolute, error);
  if (!error)
    absolute = std::move(normalized);
  return "file:///" + PercentEncodeFileUrlPath(absolute.generic_string());
}

std::string StandaloneDocumentBaseElementHtml(const std::string& html) {
  if (HasHtmlBaseElement(html))
    return std::string();
  const std::string base_url =
      FileUrlForBaseDirectory(GetStandaloneResourceProviderDocumentBasePath());
  if (base_url.empty())
    return std::string();
  return "<base href=\"" + base_url + "\">";
}

std::string RewriteStandaloneCssUrlValueToFileUrl(
    const std::string& raw_value,
    const fs::path& document_base_dir) {
  std::string value = TrimAscii(raw_value);
  if (value.empty() || document_base_dir.empty())
    return raw_value;

  char quote = '\0';
  if (value.size() >= 2 &&
      ((value.front() == '"' && value.back() == '"') ||
       (value.front() == '\'' && value.back() == '\''))) {
    quote = value.front();
    value = value.substr(1, value.size() - 2);
  }

  const std::string lower = LowerAscii(value);
  if (value.empty() || value.front() == '#' || lower.rfind("//", 0) == 0 ||
      lower.rfind("/", 0) == 0 || lower.rfind("\\", 0) == 0 ||
      HasUrlScheme(value)) {
    return raw_value;
  }

  const std::string file_url =
      FileUrlForLocalPath((document_base_dir / fs::path(value)).lexically_normal());
  if (file_url.empty())
    return raw_value;
  return std::string(1, quote == '\0' ? '"' : quote) + file_url +
         std::string(1, quote == '\0' ? '"' : quote);
}

std::string RewriteStandaloneCssUrlsToFileUrls(const std::string& css) {
  const fs::path document_base_dir = StandaloneDocumentBaseDirectoryPath();
  if (document_base_dir.empty())
    return css;

  std::string output;
  output.reserve(css.size());
  const std::string lower = LowerAscii(css);
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
    output += RewriteStandaloneCssUrlValueToFileUrl(
        css.substr(value_start, value_end - value_start), document_base_dir);
    output.push_back(')');
    search_offset = value_end + 1;
  }
  return output;
}

std::string RewriteStandaloneHtmlStyleBlocksToFileUrls(
    const std::string& html) {
  std::string output;
  const std::string lower = LowerAscii(html);
  size_t search_offset = 0;
  while (true) {
    const size_t open = lower.find("<style", search_offset);
    if (open == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    const size_t open_end = lower.find('>', open);
    if (open_end == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    const size_t close = lower.find("</style>", open_end + 1);
    if (close == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    output += html.substr(search_offset, open_end + 1 - search_offset);
    output += RewriteStandaloneCssUrlsToFileUrls(
        html.substr(open_end + 1, close - open_end - 1));
    output += html.substr(close, 8);
    search_offset = close + 8;
  }
  return output;
}

std::string BuildLiveBlinkProbeHtml(const std::string& html,
                                    const std::vector<Stylesheet>& stylesheets) {
  const auto extract_style_blocks = [&](const std::string& input) {
    std::string styles;
    const std::string lower = LowerAscii(input);
    size_t search_offset = 0;
    while (true) {
      const size_t open = lower.find("<style", search_offset);
      if (open == std::string::npos)
        break;
      const size_t open_end = lower.find('>', open);
      if (open_end == std::string::npos)
        break;
      const size_t close = lower.find("</style>", open_end + 1);
      if (close == std::string::npos)
        break;
      styles += "<style>";
      styles += RewriteStandaloneCssUrlsToFileUrls(
          input.substr(open_end + 1, close - open_end - 1));
      styles += "</style>";
      search_offset = close + 8;
    }
    return styles;
  };
  const auto remove_style_blocks = [&](const std::string& input) {
    std::string output;
    const std::string lower = LowerAscii(input);
    size_t search_offset = 0;
    while (true) {
      const size_t open = lower.find("<style", search_offset);
      if (open == std::string::npos) {
        output += input.substr(search_offset);
        break;
      }
      const size_t open_end = lower.find('>', open);
      if (open_end == std::string::npos) {
        output += input.substr(search_offset);
        break;
      }
      const size_t close = lower.find("</style>", open_end + 1);
      if (close == std::string::npos) {
        output += input.substr(search_offset);
        break;
      }
      output += input.substr(search_offset, open - search_offset);
      search_offset = close + 8;
    }
    return output;
  };

  std::string stylesheet_html;
  const std::string base_html = StandaloneDocumentBaseElementHtml(html);
  for (const Stylesheet& stylesheet : stylesheets) {
    stylesheet_html += "<style>";
    stylesheet_html += RewriteStandaloneCssUrlsToFileUrls(stylesheet.css);
    stylesheet_html += "</style>";
  }

  const bool has_head = html.find("<head") != std::string::npos ||
                        html.find("<HEAD") != std::string::npos;
  const bool has_body = html.find("<body") != std::string::npos ||
                        html.find("<BODY") != std::string::npos;
  const bool has_html = html.find("<html") != std::string::npos ||
                        html.find("<HTML") != std::string::npos;
  if (has_head) {
    std::string output = RewriteStandaloneHtmlStyleBlocksToFileUrls(html);
    const size_t head_close = output.find("</head>");
    const size_t head_close_upper = output.find("</HEAD>");
    const size_t insert_at =
        head_close != std::string::npos ? head_close : head_close_upper;
    if (insert_at != std::string::npos) {
      output.insert(insert_at, base_html + stylesheet_html);
      return output;
    }
    return base_html + stylesheet_html + output;
  }
  if (has_body || has_html)
    return "<head>" + base_html + stylesheet_html + "</head>" +
           RewriteStandaloneHtmlStyleBlocksToFileUrls(html);
  return "<head>" + base_html + stylesheet_html + extract_style_blocks(html) +
         "</head><body>" + remove_style_blocks(html) + "</body>";
}

Point SnapshotDocumentScrollOffset(const RendererSnapshot& snapshot) {
  const auto document_scroll =
      snapshot.scroll_offsets_by_element_id.find("document");
  if (document_scroll != snapshot.scroll_offsets_by_element_id.end())
    return document_scroll->second;
  const auto body_scroll = snapshot.scroll_offsets_by_element_id.find("body");
  if (body_scroll != snapshot.scroll_offsets_by_element_id.end())
    return body_scroll->second;
  return Point{};
}

std::string SerializeElementScrollOffsets(
    const std::unordered_map<std::string, Point>& scroll_offsets) {
  std::vector<std::pair<std::string, Point>> ordered;
  ordered.reserve(scroll_offsets.size());
  for (const auto& [key, value] : scroll_offsets) {
    if (key == "document" || key == "body")
      continue;
    ordered.push_back({key, value});
  }
  std::sort(ordered.begin(), ordered.end(),
            [](const auto& lhs, const auto& rhs) {
              return lhs.first < rhs.first;
            });
  std::ostringstream out;
  for (const auto& [key, value] : ordered)
    out << key << "=" << value.x << "," << value.y << "\n";
  return out.str();
}

std::string SerializeElementAttributes(
    const std::unordered_map<std::string, std::string>& attributes) {
  std::vector<std::pair<std::string, std::string>> ordered(attributes.begin(),
                                                            attributes.end());
  std::sort(ordered.begin(), ordered.end(),
            [](const auto& lhs, const auto& rhs) {
              return lhs.first < rhs.first;
            });
  std::ostringstream out;
  for (const auto& [key, value] : ordered)
    out << key << "=" << value << "\n";
  return out.str();
}

class StandaloneCompositorRuntimeImpl final : public StandaloneCompositorRuntime {
 public:
  explicit StandaloneCompositorRuntimeImpl(CompositorRuntimeCreateInfo create_info)
      : audit_enabled_(create_info.enable_paint_artifact_audit),
        trace_stages_(create_info.trace_stages),
        lifecycle_stop_(std::move(create_info.lifecycle_stop)) {
    snapshot_.html = create_info.renderer.html;
    snapshot_.stylesheets = create_info.renderer.stylesheets;
    snapshot_.viewport = create_info.renderer.viewport;
    snapshot_.device_scale_factor = create_info.renderer.device_scale_factor;
    snapshot_.asset_namespace = create_info.renderer.asset_namespace;
  }

  bool Initialize(std::vector<std::string>* diagnostics) override {
    namespace probe = ::blink::standalone_renderer_probe;
    EnsureStandaloneDiscardableMemoryAllocator();
    probe::StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
        audit_enabled_ ? 1 : 0);
    probe::StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
        trace_stages_ ? 1 : 0);
    probe::StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
        lifecycle_stop_.empty() ? nullptr : lifecycle_stop_.c_str());
    if (diagnostics) {
      diagnostics->push_back("standalone Chromium compositor runtime linked");
      diagnostics->push_back(
          "production path is Blink lifecycle -> PaintArtifactCompositor -> cc layers");
      diagnostics->push_back(
          "SDL supplies the native window; cc frames submit through Viz and create a Skia GPU Display when an HWND is available");
      diagnostics->push_back(
          "live Blink bridge recipe version: " +
          std::to_string(
              probe::StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer()));
    }
    return probe::StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer() &&
           probe::StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer();
  }

  NativePresentationResult InitializeNativeWindow(
      const NativeWindowConfig& config) override {
    native_window_config_ = config;
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetNativeWindowForStandaloneRenderer(
            config.win32_hwnd, static_cast<int>(config.viewport.width),
            static_cast<int>(config.viewport.height));
    if (!vulkan_window_host_)
      vulkan_window_host_ = std::make_unique<VulkanWindowHost>();
    return vulkan_window_host_->Initialize(config);
  }

  CompositorFrameResult AdvanceFrame(const FrameInput& input) override {
    namespace probe = ::blink::standalone_renderer_probe;
    ApplyInput(input);
    if (native_window_config_) {
      native_window_config_->viewport = snapshot_.viewport;
      probe::StandaloneBlinkLiveFrameBridgeSetNativeWindowForStandaloneRenderer(
          native_window_config_->win32_hwnd,
          static_cast<int>(native_window_config_->viewport.width),
          static_cast<int>(native_window_config_->viewport.height));
    }
    CompositorFrameResult result;
    result.png_snapshot_requested = input.request_png_snapshot;
    result.successor_snapshot = snapshot_;
    const std::string probe_html =
        BuildLiveBlinkProbeHtml(snapshot_.html, snapshot_.stylesheets);
    if (input.request_png_snapshot) {
      probe::StandaloneBlinkLiveFrameBridgeRequestPngSnapshotForStandaloneRenderer();
    }

    ResetTypefaceResourceRegistryForFrame();
    probe::StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer();
    probe::StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(
        static_cast<int>(snapshot_.viewport.width),
        static_cast<int>(snapshot_.viewport.height));
    const Point document_scroll = SnapshotDocumentScrollOffset(snapshot_);
    probe::StandaloneBlinkLiveFrameBridgeSetDocumentScrollOffsetForStandaloneRenderer(
        document_scroll.x, document_scroll.y);
    const std::string serialized_scroll_offsets =
        SerializeElementScrollOffsets(snapshot_.scroll_offsets_by_element_id);
    probe::StandaloneBlinkLiveFrameBridgeSetElementScrollOffsetsForStandaloneRenderer(
        serialized_scroll_offsets.c_str());
    probe::StandaloneBlinkLiveFrameBridgeSetAnimationTimeForStandaloneRenderer(
        snapshot_.timeline_time_seconds * 1000.0);
    const std::string serialized_attributes =
        SerializeElementAttributes(snapshot_.element_attributes_by_id_and_name);
    probe::StandaloneBlinkLiveFrameBridgeSetElementAttributesForStandaloneRenderer(
        serialized_attributes.c_str());
    if (input.pointers.empty()) {
      probe::StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
          snapshot_.hovered_element_id.c_str(), snapshot_.active_element_id.c_str());
    } else {
      probe::StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
          nullptr, nullptr);
    }
    if (input.wheel) {
      probe::StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
          input.wheel->position.x, input.wheel->position.y,
          input.wheel->delta.x, input.wheel->delta.y, 1);
    } else {
      probe::StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
          0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    if (!input.pointers.empty()) {
      const PointerState& pointer = input.pointers.front();
      int pointer_event_type = 0;
      if (!last_pointer_pressed_ && pointer.pressed) {
        pointer_event_type = 1;
      } else if (last_pointer_pressed_ && !pointer.pressed) {
        pointer_event_type = 2;
      }
      const bool pointer_changed =
          !previous_pointer_ || previous_pointer_->id != pointer.id ||
          previous_pointer_->position.x != pointer.position.x ||
          previous_pointer_->position.y != pointer.position.y ||
          previous_pointer_->pressed != pointer.pressed;
      probe::StandaloneBlinkLiveFrameBridgeSetPointerStateForStandaloneRenderer(
          pointer.position.x, pointer.position.y, pointer.pressed ? 1 : 0,
          pointer_event_type, pointer_changed ? 1 : 0);
      last_pointer_pressed_ = pointer.pressed;
      previous_pointer_ = pointer;
    } else {
      probe::StandaloneBlinkLiveFrameBridgeSetPointerStateForStandaloneRenderer(
          0.0f, 0.0f, 0, 0, 0);
      last_pointer_pressed_ = false;
      previous_pointer_.reset();
    }

    result.paint_clean =
        probe::StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.paint_chunk_count =
        probe::StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
            probe_html.c_str());
    result.display_item_count =
        probe::StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
            probe_html.c_str());
    result.needs_begin_frame =
        probe::StandaloneBlinkLiveFrameBridgeNeedsBeginFrameForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.root_layer_available =
        probe::StandaloneBlinkLiveFrameBridgeCompositorRootLayerForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.cc_host_created =
        probe::StandaloneBlinkLiveFrameBridgeCcHostForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.cc_root_layer_attached =
        probe::StandaloneBlinkLiveFrameBridgeCcRootLayerAttachedForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.cc_commit_requested =
        probe::StandaloneBlinkLiveFrameBridgeCcCommitRequestedForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.cc_frame_sink_requested =
        probe::StandaloneBlinkLiveFrameBridgeCcFrameSinkRequestedForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.cc_frame_sink_bound =
        probe::StandaloneBlinkLiveFrameBridgeCcFrameSinkBoundForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.gpu_context_created =
        probe::StandaloneBlinkLiveFrameBridgeCcGpuContextForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.raster_context_created =
        probe::StandaloneBlinkLiveFrameBridgeCcRasterContextForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.shared_image_interface_available =
        probe::StandaloneBlinkLiveFrameBridgeCcSharedImageInterfaceForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.compositor_frame_submitted =
        probe::StandaloneBlinkLiveFrameBridgeCcCompositorFrameSubmittedForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.viz_display_created =
        probe::StandaloneBlinkLiveFrameBridgeCcVizDisplayForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.skia_renderer_gpu_path_reached =
        probe::StandaloneBlinkLiveFrameBridgeCcSkiaGpuForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.compositor_layer_count =
        probe::StandaloneBlinkLiveFrameBridgeCompositorLayerCountForStandaloneRenderer(
            probe_html.c_str());

    float scroll_x = 0.0f;
    float scroll_y = 0.0f;
    float max_scroll_x = 0.0f;
    float max_scroll_y = 0.0f;
    if (probe::StandaloneBlinkLiveFrameBridgeDocumentScrollOffsetForStandaloneRenderer(
            probe_html.c_str(), &scroll_x, &scroll_y, &max_scroll_x,
            &max_scroll_y)) {
      result.successor_snapshot.scroll_offsets_by_element_id["document"] =
          Point{scroll_x, scroll_y};
      snapshot_.scroll_offsets_by_element_id =
          result.successor_snapshot.scroll_offsets_by_element_id;
      result.document_max_scroll_offset = Point{max_scroll_x, max_scroll_y};
    }

    std::array<char, 256> observed_hovered{};
    std::array<char, 256> observed_active{};
    if (probe::StandaloneBlinkLiveFrameBridgePointerObservedStateForStandaloneRenderer(
            probe_html.c_str(), observed_hovered.data(),
            static_cast<int>(observed_hovered.size()), observed_active.data(),
            static_cast<int>(observed_active.size()))) {
      result.successor_snapshot.hovered_element_id = observed_hovered.data();
      result.successor_snapshot.active_element_id = observed_active.data();
      snapshot_.hovered_element_id = result.successor_snapshot.hovered_element_id;
      snapshot_.active_element_id = result.successor_snapshot.active_element_id;
    }

    ImportHitTestEntries(probe_html, result);
    ImportScrollableElementEntries(probe_html, result);
    CopyRawAudit(probe_html, result);
    CopyPngSnapshot(probe_html, result);
    result.diagnostics.push_back(
        result.paint_clean ? "Blink lifecycle reached PaintClean"
                           : "Blink lifecycle did not reach PaintClean");
    result.diagnostics.push_back(
        result.root_layer_available
            ? "PaintArtifactCompositor produced a cc root layer"
            : "PaintArtifactCompositor did not produce a cc root layer");
    result.diagnostics.push_back(
        result.cc_host_created ? "Standalone cc::LayerTreeHost created"
                               : "Standalone cc::LayerTreeHost was not created");
    result.diagnostics.push_back(
        result.cc_root_layer_attached
            ? "PAC root cc::Layer attached to cc::LayerTreeHost"
            : "PAC root cc::Layer is not attached to cc::LayerTreeHost");
    result.diagnostics.push_back(
        result.cc_commit_requested
            ? "cc::LayerTreeHost commit requested after root attach"
            : "cc::LayerTreeHost commit was not requested");
    result.diagnostics.push_back(
        result.cc_frame_sink_requested
            ? "cc::LayerTreeHost requested a LayerTreeFrameSink"
            : "cc::LayerTreeHost has not requested a LayerTreeFrameSink");
    result.diagnostics.push_back(
        result.cc_frame_sink_bound
            ? "cc::LayerTreeHost initialized a real LayerTreeFrameSink"
            : "cc::LayerTreeHost has not initialized a LayerTreeFrameSink");
    result.diagnostics.push_back(
        result.gpu_context_created
            ? "Standalone GPU command-buffer context created"
            : "Standalone GPU command-buffer context not created");
    result.diagnostics.push_back(
        result.raster_context_created
            ? "Standalone raster command-buffer context created"
            : "Standalone raster command-buffer context not created");
    result.diagnostics.push_back(
        result.shared_image_interface_available
            ? "Standalone shared-image interface available"
            : "Standalone shared-image interface unavailable");
    result.diagnostics.push_back(
        result.compositor_frame_submitted
            ? "cc submitted a compositor frame through the Viz frame sink"
            : "cc has not submitted a compositor frame yet");
    result.diagnostics.push_back(
        result.viz_display_created
            ? "Viz Display created for the submitted root surface"
            : "Viz Display is not available for this frame");
    result.diagnostics.push_back(
        result.skia_renderer_gpu_path_reached
            ? "Viz SkiaRenderer GPU draw/swap path was reached"
            : "Viz SkiaRenderer GPU draw/swap path was not reached");
    std::array<char, 256> cc_attach_failure{};
    if (probe::StandaloneBlinkLiveFrameBridgeCcAttachFailureForStandaloneRenderer(
            probe_html.c_str(), cc_attach_failure.data(),
            static_cast<int>(cc_attach_failure.size())) > 0) {
      result.diagnostics.emplace_back(std::string("cc attach failure: ") +
                                      cc_attach_failure.data());
    }
    std::array<char, 256> cc_frame_sink_failure{};
    if (probe::StandaloneBlinkLiveFrameBridgeCcFrameSinkFailureForStandaloneRenderer(
            probe_html.c_str(), cc_frame_sink_failure.data(),
            static_cast<int>(cc_frame_sink_failure.size())) > 0) {
      result.diagnostics.emplace_back(std::string("cc frame sink failure: ") +
                                      cc_frame_sink_failure.data());
    }
    return result;
  }

  NativePresentationResult PresentToNativeWindow(
      const CompositorFrameResult& frame) override {
    if (!vulkan_window_host_) {
      NativePresentationResult result;
      result.failure_reason = "native window presentation was not initialized";
      result.diagnostics.push_back("presentation failure: " +
                                   result.failure_reason);
      return result;
    }
    return vulkan_window_host_->Present(frame);
  }

  RendererSnapshot Snapshot() const override { return snapshot_; }

 private:
  void ApplyInput(const FrameInput& input) {
    snapshot_.timeline_time_seconds =
        input.timeline_time_seconds > 0.0
            ? input.timeline_time_seconds
            : snapshot_.timeline_time_seconds + input.delta_time_seconds;
    if (input.viewport)
      snapshot_.viewport = *input.viewport;
    if (input.html_override)
      snapshot_.html = *input.html_override;
    if (input.stylesheets_override)
      snapshot_.stylesheets = *input.stylesheets_override;
    snapshot_.element_attributes_by_id_and_name =
        input.element_attributes_by_id_and_name;
    snapshot_.scroll_offsets_by_element_id = input.scroll_offsets_by_element_id;
    snapshot_.focused_element_id = input.focused_element_id;
    snapshot_.hovered_element_id = input.hovered_element_id;
    snapshot_.active_element_id = input.active_element_id;
    snapshot_.form_values_by_element_id = input.form_values_by_element_id;
  }

  static void ImportHitTestEntries(const std::string& probe_html,
                                   CompositorFrameResult& result) {
    namespace probe = ::blink::standalone_renderer_probe;
    const int entry_count =
        probe::StandaloneBlinkLiveFrameBridgeHitTestEntryCountForStandaloneRenderer(
            probe_html.c_str());
    for (int i = 0; i < entry_count && i < 4096; ++i) {
      std::array<char, 256> element_id{};
      float x = 0.0f;
      float y = 0.0f;
      float width = 0.0f;
      float height = 0.0f;
      if (!probe::StandaloneBlinkLiveFrameBridgeHitTestEntryAtForStandaloneRenderer(
              probe_html.c_str(), i, element_id.data(),
              static_cast<int>(element_id.size()), &x, &y, &width, &height)) {
        continue;
      }
      const size_t id_length = std::strlen(element_id.data());
      if (id_length == 0 || width <= 0.0f || height <= 0.0f)
        continue;
      result.hit_test_entries.push_back(
          {std::string(element_id.data(), id_length), Rect{x, y, width, height}});
    }
  }

  static void ImportScrollableElementEntries(const std::string& probe_html,
                                             CompositorFrameResult& result) {
    namespace probe = ::blink::standalone_renderer_probe;
    const int entry_count =
        probe::StandaloneBlinkLiveFrameBridgeScrollableElementEntryCountForStandaloneRenderer(
            probe_html.c_str());
    for (int i = 0; i < entry_count && i < 4096; ++i) {
      std::array<char, 256> element_id{};
      float x = 0.0f;
      float y = 0.0f;
      float width = 0.0f;
      float height = 0.0f;
      float scroll_x = 0.0f;
      float scroll_y = 0.0f;
      float max_scroll_x = 0.0f;
      float max_scroll_y = 0.0f;
      int can_scroll_x = 0;
      int can_scroll_y = 0;
      if (!probe::StandaloneBlinkLiveFrameBridgeScrollableElementEntryAtForStandaloneRenderer(
              probe_html.c_str(), i, element_id.data(),
              static_cast<int>(element_id.size()), &x, &y, &width, &height,
              &scroll_x, &scroll_y, &max_scroll_x, &max_scroll_y,
              &can_scroll_x, &can_scroll_y)) {
        continue;
      }
      const size_t id_length = std::strlen(element_id.data());
      if (id_length == 0 || width <= 0.0f || height <= 0.0f)
        continue;
      result.scrollable_element_entries.push_back(
          {std::string(element_id.data(), id_length),
           Rect{x, y, width, height},
           Point{scroll_x, scroll_y},
           Point{max_scroll_x, max_scroll_y},
           can_scroll_x != 0,
           can_scroll_y != 0});
    }
  }

  static void CopyRawAudit(const std::string& probe_html,
                           CompositorFrameResult& result) {
    namespace probe = ::blink::standalone_renderer_probe;
    const int raw_size =
        probe::StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonSizeForStandaloneRenderer(
            probe_html.c_str());
    if (raw_size <= 0)
      return;
    std::string raw(static_cast<size_t>(raw_size) + 1, '\0');
    const int copied =
        probe::StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonForStandaloneRenderer(
            probe_html.c_str(), raw.data(), static_cast<int>(raw.size()));
    if (copied > 0) {
      raw.resize(static_cast<size_t>(copied));
      result.raw_paint_artifact_audit_json = std::move(raw);
    }
  }

  static void CopyPngSnapshot(const std::string& probe_html,
                              CompositorFrameResult& result) {
    if (!result.png_snapshot_requested)
      return;
    namespace probe = ::blink::standalone_renderer_probe;
    const int status =
        probe::StandaloneBlinkLiveFrameBridgePngSnapshotStatusForStandaloneRenderer(
            probe_html.c_str());
    result.png_snapshot_available = status > 0;
    if (status > 0) {
      const int byte_size =
          probe::StandaloneBlinkLiveFrameBridgePngSnapshotByteSizeForStandaloneRenderer(
              probe_html.c_str());
      if (byte_size > 0) {
        result.png_snapshot_bytes.resize(static_cast<size_t>(byte_size));
        const int copied =
            probe::StandaloneBlinkLiveFrameBridgePngSnapshotBytesForStandaloneRenderer(
                probe_html.c_str(), result.png_snapshot_bytes.data(),
                byte_size);
        if (copied != byte_size) {
          result.png_snapshot_bytes.clear();
          result.png_snapshot_available = false;
          result.png_snapshot_failure =
              "Viz CopyOutput PNG bytes could not be copied";
        }
      }
    }
    if (!result.png_snapshot_available) {
      std::array<char, 256> failure{};
      const int copied =
          probe::StandaloneBlinkLiveFrameBridgePngSnapshotFailureForStandaloneRenderer(
              probe_html.c_str(), failure.data(),
              static_cast<int>(failure.size()));
      result.png_snapshot_failure =
          copied > 0 ? failure.data()
                     : "Viz CopyOutput PNG snapshot was not produced";
    }
  }

  RendererSnapshot snapshot_;
  bool audit_enabled_ = false;
  bool trace_stages_ = false;
  std::string lifecycle_stop_;
  bool last_pointer_pressed_ = false;
  std::optional<PointerState> previous_pointer_;
  std::optional<NativeWindowConfig> native_window_config_;
  std::unique_ptr<VulkanWindowHost> vulkan_window_host_;
};

}  // namespace

std::unique_ptr<StandaloneCompositorRuntime> CreateStandaloneCompositorRuntime(
    CompositorRuntimeCreateInfo create_info) {
  return std::make_unique<StandaloneCompositorRuntimeImpl>(
      std::move(create_info));
}

}  // namespace html_css_renderer
