#include "html_css_renderer/compositor_runtime.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdint>
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
uint64_t StandaloneBlinkLiveFrameBridgeCreateInstanceForStandaloneRenderer();
void StandaloneBlinkLiveFrameBridgeSetCurrentInstanceForStandaloneRenderer(
    uint64_t instance_id);
void StandaloneBlinkLiveFrameBridgeDestroyInstanceForStandaloneRenderer(
    uint64_t instance_id);
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
void StandaloneBlinkLiveFrameBridgeClearMouseInputEventsForStandaloneRenderer();
void StandaloneBlinkLiveFrameBridgeAppendMouseInputEventForStandaloneRenderer(
    int type,
    float x,
    float y,
    int button,
    int modifiers,
    int click_count);
void StandaloneBlinkLiveFrameBridgeClearKeyboardInputEventsForStandaloneRenderer();
void StandaloneBlinkLiveFrameBridgeAppendKeyboardInputEventForStandaloneRenderer(
    int type,
    int key,
    const char* text,
    int modifiers);
void StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
    float x,
    float y,
    float delta_x,
    float delta_y,
    int requested);
void StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetFrameDiagnosticsForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
    const char* lifecycle_stop);
void StandaloneBlinkLiveFrameBridgeSetTransparentBackgroundForStandaloneRenderer(
    int enabled);
void StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer();
void StandaloneBlinkLiveFrameBridgeSetNativeWindowForStandaloneRenderer(
    void* native_window_handle,
    int width,
    int height);
void StandaloneBlinkLiveFrameBridgeRequestPngSnapshotForStandaloneRenderer();
void StandaloneBlinkLiveFrameBridgeRequestRawFrameForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer();
int StandaloneBlinkLiveFrameBridgePrewarmCcFrameSinkForStandaloneRenderer(
    int width,
    int height);
int StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeNeedsBeginFrameForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingTotalMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingInputSetupMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingHtmlDocumentSetupMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingStyleUpdateMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingLayoutLifecycleMsForStandaloneRenderer(
    const char* body_html);
double
StandaloneBlinkLiveFrameBridgeTimingPrepaintAndPaintLifecycleMsForStandaloneRenderer(
    const char* body_html);
double
StandaloneBlinkLiveFrameBridgeTimingPaintArtifactGenerationMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingPaintArtifactAuditMsForStandaloneRenderer(
    const char* body_html);
double
StandaloneBlinkLiveFrameBridgeTimingPaintArtifactExtractionMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingCcCompositeMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingCcFrameSinkWarmupMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingCcRootPreattachMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingCcPendingUpdateMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingCcSchedulerRunLoopMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingCcSubmitWaitMsForStandaloneRenderer(
    const char* body_html);
double StandaloneBlinkLiveFrameBridgeTimingCcStartupPrewarmMsForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeTimingCacheHitForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeTimingReusedLiveDocumentForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeTimingRebuiltForAttributesForStandaloneRenderer(
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
int StandaloneBlinkLiveFrameBridgeCcSubmittedOutputSizeForStandaloneRenderer(
    const char* body_html,
    int* width,
    int* height);
int StandaloneBlinkLiveFrameBridgeCcVizDisplayOutputSizeForStandaloneRenderer(
    const char* body_html,
    int* width,
    int* height);
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
    char* tag_name,
    int tag_name_capacity,
    char* data_godot_action,
    int data_godot_action_capacity,
    float* x,
    float* y,
    float* width,
    float* height,
    int* disabled,
    int* editable,
    int* checked,
    int* focused);
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
int StandaloneBlinkLiveFrameBridgeRawFrameInfoForStandaloneRenderer(
    const char* body_html,
    int* width,
    int* height,
    int* stride,
    int* pixel_format,
    int* premultiplied_alpha);
int StandaloneBlinkLiveFrameBridgeRawFrameByteSizeForStandaloneRenderer(
    const char* body_html);
int StandaloneBlinkLiveFrameBridgeRawFrameBytesForStandaloneRenderer(
    const char* body_html,
    uint8_t* destination,
    int destination_size);
}  // namespace blink::standalone_renderer_probe

namespace html_css_renderer {
namespace {

namespace fs = std::filesystem;

using RuntimeClock = std::chrono::steady_clock;

double RuntimeElapsedMs(RuntimeClock::time_point start,
                        RuntimeClock::time_point end) {
  return std::chrono::duration<double, std::milli>(end - start).count();
}

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

std::string RemoveStandaloneStylesheetLinkTags(const std::string& html) {
  std::string output;
  const std::string lower = LowerAscii(html);
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
    const std::string tag = lower.substr(open, open_end - open + 1);
    const bool rel_stylesheet =
        tag.find("rel=\"stylesheet\"") != std::string::npos ||
        tag.find("rel='stylesheet'") != std::string::npos ||
        tag.find("rel=stylesheet") != std::string::npos;
    if (rel_stylesheet) {
      output += html.substr(search_offset, open - search_offset);
    } else {
      output += html.substr(search_offset, open_end + 1 - search_offset);
    }
    search_offset = open_end + 1;
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
    std::string output = RemoveStandaloneStylesheetLinkTags(
        RewriteStandaloneHtmlStyleBlocksToFileUrls(html));
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
           RemoveStandaloneStylesheetLinkTags(
               RewriteStandaloneHtmlStyleBlocksToFileUrls(html));
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

bool SameFloat(float lhs, float rhs) {
  return std::abs(lhs - rhs) <= 0.001f;
}

bool SamePoint(const Point& lhs, const Point& rhs) {
  return SameFloat(lhs.x, rhs.x) && SameFloat(lhs.y, rhs.y);
}

bool SameSize(const Size& lhs, const Size& rhs) {
  return SameFloat(lhs.width, rhs.width) && SameFloat(lhs.height, rhs.height);
}

bool SameStylesheets(const std::vector<Stylesheet>& lhs,
                     const std::vector<Stylesheet>& rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (size_t i = 0; i < lhs.size(); ++i) {
    if (lhs[i].id != rhs[i].id || lhs[i].css != rhs[i].css)
      return false;
  }
  return true;
}

bool SamePointMap(const std::unordered_map<std::string, Point>& lhs,
                  const std::unordered_map<std::string, Point>& rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (const auto& [key, value] : lhs) {
    const auto it = rhs.find(key);
    if (it == rhs.end() || !SamePoint(value, it->second))
      return false;
  }
  return true;
}

bool SameStringMap(
    const std::unordered_map<std::string, std::string>& lhs,
    const std::unordered_map<std::string, std::string>& rhs) {
  return lhs == rhs;
}

bool SamePointerState(const PointerState& lhs, const PointerState& rhs) {
  return lhs.id == rhs.id && SamePoint(lhs.position, rhs.position) &&
         lhs.pressed == rhs.pressed;
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

class ScopedStandaloneBridgeInstance {
 public:
  explicit ScopedStandaloneBridgeInstance(uint64_t instance_id)
      : instance_id_(instance_id) {
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetCurrentInstanceForStandaloneRenderer(
            instance_id_);
  }

  ScopedStandaloneBridgeInstance(const ScopedStandaloneBridgeInstance&) =
      delete;
  ScopedStandaloneBridgeInstance& operator=(
      const ScopedStandaloneBridgeInstance&) = delete;

  ~ScopedStandaloneBridgeInstance() {
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeSetCurrentInstanceForStandaloneRenderer(0);
  }

 private:
  uint64_t instance_id_ = 0;
};

class ScopedStandaloneResourceProviderContext {
 public:
  explicit ScopedStandaloneResourceProviderContext(uint64_t context_id)
      : context_id_(context_id) {
    SetCurrentStandaloneResourceProviderContext(context_id_);
  }

  ScopedStandaloneResourceProviderContext(
      const ScopedStandaloneResourceProviderContext&) = delete;
  ScopedStandaloneResourceProviderContext& operator=(
      const ScopedStandaloneResourceProviderContext&) = delete;

  ~ScopedStandaloneResourceProviderContext() {
    SetCurrentStandaloneResourceProviderContext(0);
  }

 private:
  uint64_t context_id_ = 0;
};

class ScopedTypefaceResourceRegistryContext {
 public:
  explicit ScopedTypefaceResourceRegistryContext(uint64_t context_id)
      : context_id_(context_id) {
    SetCurrentTypefaceResourceRegistryContext(context_id_);
  }

  ScopedTypefaceResourceRegistryContext(
      const ScopedTypefaceResourceRegistryContext&) = delete;
  ScopedTypefaceResourceRegistryContext& operator=(
      const ScopedTypefaceResourceRegistryContext&) = delete;

  ~ScopedTypefaceResourceRegistryContext() {
    SetCurrentTypefaceResourceRegistryContext(0);
  }

 private:
  uint64_t context_id_ = 0;
};

class StandaloneCompositorRuntimeImpl final : public StandaloneCompositorRuntime {
 public:
  explicit StandaloneCompositorRuntimeImpl(CompositorRuntimeCreateInfo create_info)
      : audit_enabled_(create_info.enable_paint_artifact_audit),
        trace_stages_(create_info.trace_stages),
        no_script_profile_(create_info.no_script_profile ||
                           create_info.renderer.no_script_profile),
        transparent_background_(create_info.transparent_background ||
                                create_info.renderer.transparent_background),
        lifecycle_stop_(std::move(create_info.lifecycle_stop)),
        resource_provider_context_id_(CreateStandaloneResourceProviderContext()),
        resource_root_(GetStandaloneResourceProviderResourceRoot()),
        resource_base_path_(GetStandaloneResourceProviderDocumentBasePath()),
        typeface_registry_context_id_(CreateTypefaceResourceRegistryContext()),
        bridge_instance_id_(
            ::blink::standalone_renderer_probe::
                StandaloneBlinkLiveFrameBridgeCreateInstanceForStandaloneRenderer()) {
    snapshot_.html = create_info.renderer.html;
    snapshot_.stylesheets = create_info.renderer.stylesheets;
    snapshot_.viewport = create_info.renderer.viewport;
    snapshot_.device_scale_factor = create_info.renderer.device_scale_factor;
    snapshot_.asset_namespace = create_info.renderer.asset_namespace;
  }

  ~StandaloneCompositorRuntimeImpl() override {
    ScopedStandaloneResourceProviderContext scoped_resources(
        resource_provider_context_id_);
    ScopedTypefaceResourceRegistryContext scoped_typefaces(
        typeface_registry_context_id_);
    ScopedStandaloneBridgeInstance scoped_bridge(bridge_instance_id_);
    ::blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeDestroyInstanceForStandaloneRenderer(
            bridge_instance_id_);
    DestroyTypefaceResourceRegistryContext(typeface_registry_context_id_);
    DestroyStandaloneResourceProviderContext(resource_provider_context_id_);
  }

  bool Initialize(std::vector<std::string>* diagnostics) override {
    namespace probe = ::blink::standalone_renderer_probe;
    ScopedStandaloneResourceProviderContext scoped_resources(
        resource_provider_context_id_);
    ScopedTypefaceResourceRegistryContext scoped_typefaces(
        typeface_registry_context_id_);
    ScopedStandaloneBridgeInstance scoped_bridge(bridge_instance_id_);
    ApplyResourceProviderContext();
    EnsureStandaloneDiscardableMemoryAllocator();
    probe::StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
        audit_enabled_ ? 1 : 0);
    probe::StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
        trace_stages_ ? 1 : 0);
    probe::StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
        lifecycle_stop_.empty() ? nullptr : lifecycle_stop_.c_str());
    probe::StandaloneBlinkLiveFrameBridgeSetTransparentBackgroundForStandaloneRenderer(
        transparent_background_ ? 1 : 0);
    const int prewarm_width =
        std::max(1, static_cast<int>(std::round(snapshot_.viewport.width)));
    const int prewarm_height =
        std::max(1, static_cast<int>(std::round(snapshot_.viewport.height)));
    const int prewarm_ok =
        probe::StandaloneBlinkLiveFrameBridgePrewarmCcFrameSinkForStandaloneRenderer(
            prewarm_width, prewarm_height);
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
      if (no_script_profile_) {
        diagnostics->push_back(
            "no-script profile requested by embedder configuration");
      }
      diagnostics->push_back(std::string("cc/viz frame sink prewarm: ") +
                             (prewarm_ok ? "ok" : "failed"));
    }
    return probe::StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer() &&
           probe::StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer();
  }

  NativePresentationResult InitializeNativeWindow(
      const NativeWindowConfig& config) override {
    ScopedStandaloneResourceProviderContext scoped_resources(
        resource_provider_context_id_);
    ScopedTypefaceResourceRegistryContext scoped_typefaces(
        typeface_registry_context_id_);
    ScopedStandaloneBridgeInstance scoped_bridge(bridge_instance_id_);
    ApplyResourceProviderContext();
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
    ScopedStandaloneResourceProviderContext scoped_resources(
        resource_provider_context_id_);
    ScopedTypefaceResourceRegistryContext scoped_typefaces(
        typeface_registry_context_id_);
    ScopedStandaloneBridgeInstance scoped_bridge(bridge_instance_id_);
    if (!NeedsFrameForInput(input))
      return MakeSkippedFrameResult(input);

    const auto runtime_start = RuntimeClock::now();
    const auto apply_state_start = RuntimeClock::now();
    ApplyInput(input);
    ApplyResourceProviderContext();
    if (native_window_config_) {
      native_window_config_->viewport = snapshot_.viewport;
      probe::StandaloneBlinkLiveFrameBridgeSetNativeWindowForStandaloneRenderer(
          native_window_config_->win32_hwnd,
          static_cast<int>(native_window_config_->viewport.width),
          static_cast<int>(native_window_config_->viewport.height));
    }
    CompositorFrameResult result;
    result.png_snapshot_requested = input.request_png_snapshot;
    result.raw_frame_requested = input.request_raw_frame;
    result.successor_snapshot = snapshot_;
    const bool collect_full_result =
        input.request_png_snapshot || input.request_raw_frame ||
        input.result_collection == FrameResultCollection::kFull;
    probe::StandaloneBlinkLiveFrameBridgeSetFrameDiagnosticsForStandaloneRenderer(
        collect_full_result ? 1 : 0);
    probe::StandaloneBlinkLiveFrameBridgeSetTransparentBackgroundForStandaloneRenderer(
        transparent_background_ ? 1 : 0);
    const std::string probe_html =
        BuildLiveBlinkProbeHtml(snapshot_.html, snapshot_.stylesheets);
    if (input.force_document_reload || last_probe_html_ != probe_html) {
      ResetTypefaceResourceRegistryForFrame();
      probe::StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer();
      last_probe_html_ = probe_html;
    }
    if (input.request_png_snapshot) {
      probe::StandaloneBlinkLiveFrameBridgeRequestPngSnapshotForStandaloneRenderer();
    }
    if (input.request_raw_frame) {
      probe::StandaloneBlinkLiveFrameBridgeRequestRawFrameForStandaloneRenderer();
    }
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
    probe::StandaloneBlinkLiveFrameBridgeClearMouseInputEventsForStandaloneRenderer();
    if (!input.mouse_events.empty()) {
      for (const MouseInputEvent& event : input.mouse_events) {
        probe::StandaloneBlinkLiveFrameBridgeAppendMouseInputEventForStandaloneRenderer(
            static_cast<int>(event.type), event.position.x, event.position.y,
            static_cast<int>(event.button), event.modifiers,
            event.click_count);
      }
      last_pointer_pressed_ = false;
      previous_pointer_.reset();
    } else if (!input.pointers.empty()) {
      const PointerState& pointer = input.pointers.front();
      MouseInputEventType event_type = MouseInputEventType::kMove;
      if (!last_pointer_pressed_ && pointer.pressed) {
        event_type = MouseInputEventType::kDown;
      } else if (last_pointer_pressed_ && !pointer.pressed) {
        event_type = MouseInputEventType::kUp;
      }
      int modifiers = 0;
      if (pointer.pressed)
        modifiers |= 1 << 6;  // blink::WebInputEvent::kLeftButtonDown.
      probe::StandaloneBlinkLiveFrameBridgeAppendMouseInputEventForStandaloneRenderer(
          static_cast<int>(event_type), pointer.position.x, pointer.position.y,
          static_cast<int>(MouseInputButton::kLeft), modifiers,
          event_type == MouseInputEventType::kMove ? 0 : 1);
      last_pointer_pressed_ = pointer.pressed;
      previous_pointer_ = pointer;
    } else {
      last_pointer_pressed_ = false;
      previous_pointer_.reset();
    }
    if (input.wheel) {
      probe::StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
          input.wheel->position.x, input.wheel->position.y,
          input.wheel->delta.x, input.wheel->delta.y, 1);
    } else {
      probe::StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
          0.0f, 0.0f, 0.0f, 0.0f, 0);
    }
    probe::StandaloneBlinkLiveFrameBridgeClearKeyboardInputEventsForStandaloneRenderer();
    for (const KeyboardInputEvent& event : input.keyboard_events) {
      probe::StandaloneBlinkLiveFrameBridgeAppendKeyboardInputEventForStandaloneRenderer(
          static_cast<int>(event.type), static_cast<int>(event.key),
          event.text.c_str(), event.modifiers);
    }
    result.timing.runtime_apply_state_ms =
        RuntimeElapsedMs(apply_state_start, RuntimeClock::now());

    const auto bridge_query_start = RuntimeClock::now();
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
    int submitted_output_width = 0;
    int submitted_output_height = 0;
    if (probe::StandaloneBlinkLiveFrameBridgeCcSubmittedOutputSizeForStandaloneRenderer(
            probe_html.c_str(), &submitted_output_width,
            &submitted_output_height)) {
      result.compositor_output_size =
          Size{static_cast<float>(submitted_output_width),
               static_cast<float>(submitted_output_height)};
    }
    int viz_output_width = 0;
    int viz_output_height = 0;
    if (probe::StandaloneBlinkLiveFrameBridgeCcVizDisplayOutputSizeForStandaloneRenderer(
            probe_html.c_str(), &viz_output_width, &viz_output_height)) {
      result.viz_display_output_size =
          Size{static_cast<float>(viz_output_width),
               static_cast<float>(viz_output_height)};
    }
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

    if (collect_full_result) {
      ImportHitTestEntries(probe_html, result);
      ImportScrollableElementEntries(probe_html, result);
      CopyRawAudit(probe_html, result);
    }
    CopyPngSnapshot(probe_html, result);
    CopyRawFrame(probe_html, result);
    if (collect_full_result) {
      AppendFrameDiagnostics(probe_html, result);
    } else if (!result.cc_root_layer_attached ||
               !result.cc_frame_sink_bound ||
               !result.compositor_frame_submitted) {
      AppendFrameFailures(probe_html, result);
    }
    result.timing.bridge_total_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingTotalMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_input_setup_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingInputSetupMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_html_document_setup_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingHtmlDocumentSetupMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_style_update_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingStyleUpdateMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_layout_lifecycle_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingLayoutLifecycleMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_prepaint_and_paint_lifecycle_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingPrepaintAndPaintLifecycleMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_paint_artifact_generation_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingPaintArtifactGenerationMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_paint_artifact_audit_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingPaintArtifactAuditMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_paint_artifact_extraction_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingPaintArtifactExtractionMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cc_composite_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingCcCompositeMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cc_frame_sink_warmup_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingCcFrameSinkWarmupMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cc_root_preattach_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingCcRootPreattachMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cc_pending_update_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingCcPendingUpdateMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cc_scheduler_run_loop_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingCcSchedulerRunLoopMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cc_submit_wait_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingCcSubmitWaitMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cc_startup_prewarm_ms =
        probe::StandaloneBlinkLiveFrameBridgeTimingCcStartupPrewarmMsForStandaloneRenderer(
            probe_html.c_str());
    result.timing.bridge_cache_hit =
        probe::StandaloneBlinkLiveFrameBridgeTimingCacheHitForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.timing.bridge_reused_live_document =
        probe::StandaloneBlinkLiveFrameBridgeTimingReusedLiveDocumentForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.timing.bridge_rebuilt_for_attributes =
        probe::StandaloneBlinkLiveFrameBridgeTimingRebuiltForAttributesForStandaloneRenderer(
            probe_html.c_str()) != 0;
    result.timing.runtime_bridge_query_ms =
        RuntimeElapsedMs(bridge_query_start, RuntimeClock::now());
    result.timing.runtime_total_ms =
        RuntimeElapsedMs(runtime_start, RuntimeClock::now());
    last_frame_result_ = result;
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
  bool NeedsFrameForInput(const FrameInput& input) const {
    if (!last_frame_result_)
      return true;
    if (input.request_png_snapshot || input.request_raw_frame)
      return true;
    if (input.force_document_reload)
      return true;
    if (last_frame_result_->needs_begin_frame)
      return true;
    if (input.viewport && !SameSize(*input.viewport, snapshot_.viewport))
      return true;
    if (input.html_override && *input.html_override != snapshot_.html)
      return true;
    if (input.stylesheets_override &&
        !SameStylesheets(*input.stylesheets_override, snapshot_.stylesheets)) {
      return true;
    }
    if (input.resource_root && *input.resource_root != resource_root_)
      return true;
    if (input.resource_base_path &&
        *input.resource_base_path != resource_base_path_) {
      return true;
    }
    if (!SameStringMap(input.element_attributes_by_id_and_name,
                       snapshot_.element_attributes_by_id_and_name)) {
      return true;
    }
    if (!SamePointMap(input.scroll_offsets_by_element_id,
                      snapshot_.scroll_offsets_by_element_id)) {
      return true;
    }
    if (!SameStringMap(input.form_values_by_element_id,
                       snapshot_.form_values_by_element_id)) {
      return true;
    }
    if (!input.mouse_events.empty())
      return true;
    if (input.wheel)
      return true;
    if (!input.keyboard.pressed_key_codes.empty())
      return true;
    if (!input.keyboard_events.empty())
      return true;
    if (input.pointers.empty()) {
      if (previous_pointer_)
        return true;
    } else {
      if (!previous_pointer_)
        return true;
      if (input.pointers.size() != 1 ||
          !SamePointerState(input.pointers.front(), *previous_pointer_)) {
        return true;
      }
    }
    return false;
  }

  CompositorFrameResult MakeSkippedFrameResult(const FrameInput& input) const {
    CompositorFrameResult result = *last_frame_result_;
    result.timing = CompositorFrameTiming();
    result.frame_advanced = false;
    result.frame_skipped_due_to_no_demand = true;
    result.png_snapshot_requested = input.request_png_snapshot;
    result.raw_frame_requested = input.request_raw_frame;
    result.png_snapshot_available = false;
    result.png_snapshot_failure.clear();
    result.png_snapshot_bytes.clear();
    result.raw_frame_failure.clear();
    result.raw_frame = RawFrameOutput();
    if (input.result_collection == FrameResultCollection::kMinimal) {
      result.raw_paint_artifact_audit_json.clear();
      result.hit_test_entries.clear();
      result.scrollable_element_entries.clear();
      result.diagnostics.clear();
    }
    return result;
  }

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
    if (input.resource_root)
      resource_root_ = *input.resource_root;
    if (input.resource_base_path)
      resource_base_path_ = *input.resource_base_path;
    snapshot_.element_attributes_by_id_and_name =
        input.element_attributes_by_id_and_name;
    snapshot_.scroll_offsets_by_element_id = input.scroll_offsets_by_element_id;
    snapshot_.form_values_by_element_id = input.form_values_by_element_id;
  }

  void ApplyResourceProviderContext() {
    SetStandaloneResourceProviderResourceRoot(resource_root_);
    SetStandaloneResourceProviderDocumentBasePath(resource_base_path_);
  }

  static void ImportHitTestEntries(const std::string& probe_html,
                                   CompositorFrameResult& result) {
    namespace probe = ::blink::standalone_renderer_probe;
    const int entry_count =
        probe::StandaloneBlinkLiveFrameBridgeHitTestEntryCountForStandaloneRenderer(
            probe_html.c_str());
    for (int i = 0; i < entry_count && i < 4096; ++i) {
      std::array<char, 256> element_id{};
      std::array<char, 64> tag_name{};
      std::array<char, 256> data_godot_action{};
      float x = 0.0f;
      float y = 0.0f;
      float width = 0.0f;
      float height = 0.0f;
      int disabled = 0;
      int editable = 0;
      int checked = 0;
      int focused = 0;
      if (!probe::StandaloneBlinkLiveFrameBridgeHitTestEntryAtForStandaloneRenderer(
              probe_html.c_str(), i, element_id.data(),
              static_cast<int>(element_id.size()), tag_name.data(),
              static_cast<int>(tag_name.size()), data_godot_action.data(),
              static_cast<int>(data_godot_action.size()), &x, &y, &width,
              &height, &disabled, &editable, &checked, &focused)) {
        continue;
      }
      const size_t id_length = std::strlen(element_id.data());
      if (id_length == 0 || width <= 0.0f || height <= 0.0f)
        continue;
      HitTestEntry entry;
      entry.element_id = std::string(element_id.data(), id_length);
      entry.tag_name = tag_name.data();
      entry.data_godot_action = data_godot_action.data();
      entry.bounds = Rect{x, y, width, height};
      entry.disabled = disabled != 0;
      entry.editable = editable != 0;
      entry.checked = checked != 0;
      entry.focused = focused != 0;
      result.hit_test_entries.push_back(std::move(entry));
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

  static void CopyRawFrame(const std::string& probe_html,
                           CompositorFrameResult& result) {
    if (!result.raw_frame_requested)
      return;
    namespace probe = ::blink::standalone_renderer_probe;
    int width = 0;
    int height = 0;
    int stride = 0;
    int pixel_format = 0;
    int premultiplied_alpha = 0;
    if (!probe::StandaloneBlinkLiveFrameBridgeRawFrameInfoForStandaloneRenderer(
            probe_html.c_str(), &width, &height, &stride, &pixel_format,
            &premultiplied_alpha)) {
      result.raw_frame_failure = "Viz CopyOutput raw frame info was not produced";
      return;
    }
    const int byte_size =
        probe::StandaloneBlinkLiveFrameBridgeRawFrameByteSizeForStandaloneRenderer(
            probe_html.c_str());
    if (byte_size <= 0) {
      std::array<char, 256> failure{};
      const int copied =
          probe::StandaloneBlinkLiveFrameBridgePngSnapshotFailureForStandaloneRenderer(
              probe_html.c_str(), failure.data(),
              static_cast<int>(failure.size()));
      result.raw_frame_failure =
          copied > 0 ? failure.data()
                     : "Viz CopyOutput raw frame bytes were not produced";
      return;
    }
    RawFrameOutput raw_frame;
    raw_frame.width = width;
    raw_frame.height = height;
    raw_frame.stride = stride;
    raw_frame.premultiplied_alpha = premultiplied_alpha != 0;
    raw_frame.pixel_format =
        pixel_format == 1
            ? RawFramePixelFormat::kRGBA8
            : (pixel_format == 2 ? RawFramePixelFormat::kBGRA8
                                 : RawFramePixelFormat::kNone);
    raw_frame.pixels.resize(static_cast<size_t>(byte_size));
    const int copied =
        probe::StandaloneBlinkLiveFrameBridgeRawFrameBytesForStandaloneRenderer(
            probe_html.c_str(), raw_frame.pixels.data(), byte_size);
    if (copied != byte_size ||
        raw_frame.pixel_format == RawFramePixelFormat::kNone) {
      result.raw_frame_failure =
          "Viz CopyOutput raw frame bytes could not be copied";
      return;
    }
    raw_frame.dirty_rects.push_back(
        Rect{0.0f, 0.0f, static_cast<float>(width),
             static_cast<float>(height)});
    result.raw_frame = std::move(raw_frame);
  }

  static void AppendFrameFailures(const std::string& probe_html,
                                  CompositorFrameResult& result) {
    namespace probe = ::blink::standalone_renderer_probe;
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
  }

  static void AppendFrameDiagnostics(const std::string& probe_html,
                                     CompositorFrameResult& result) {
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
    AppendFrameFailures(probe_html, result);
  }

  RendererSnapshot snapshot_;
  bool audit_enabled_ = false;
  bool trace_stages_ = false;
  bool no_script_profile_ = false;
  bool transparent_background_ = false;
  std::string lifecycle_stop_;
  bool last_pointer_pressed_ = false;
  std::optional<PointerState> previous_pointer_;
  std::optional<NativeWindowConfig> native_window_config_;
  std::unique_ptr<VulkanWindowHost> vulkan_window_host_;
  std::string last_probe_html_;
  std::optional<CompositorFrameResult> last_frame_result_;
  uint64_t resource_provider_context_id_ = 0;
  std::string resource_root_;
  std::string resource_base_path_;
  uint64_t typeface_registry_context_id_ = 0;
  uint64_t bridge_instance_id_ = 0;
};

}  // namespace

std::unique_ptr<StandaloneCompositorRuntime> CreateStandaloneCompositorRuntime(
    CompositorRuntimeCreateInfo create_info) {
  return std::make_unique<StandaloneCompositorRuntimeImpl>(
      std::move(create_info));
}

}  // namespace html_css_renderer
