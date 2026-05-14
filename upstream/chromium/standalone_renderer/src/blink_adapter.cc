#include "html_css_renderer/blink_adapter.h"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace html_css_renderer {
namespace {

namespace fs = std::filesystem;

struct SourceSpec {
  const char* role;
  const char* path;
  bool required;
};

constexpr SourceSpec kSourceSpecs[] = {
    {"blink core", "third_party/blink/renderer/core", true},
    {"blink platform", "third_party/blink/renderer/platform", true},
    {"blink bindings", "third_party/blink/renderer/bindings", true},
    {"dom", "third_party/blink/renderer/core/dom", true},
    {"html", "third_party/blink/renderer/core/html", true},
    {"css", "third_party/blink/renderer/core/css", true},
    {"style", "third_party/blink/renderer/core/style", true},
    {"layout", "third_party/blink/renderer/core/layout", true},
    {"paint", "third_party/blink/renderer/core/paint", true},
    {"page", "third_party/blink/renderer/core/page", true},
    {"frame", "third_party/blink/renderer/core/frame", true},
    {"events", "third_party/blink/renderer/core/events", true},
    {"input", "third_party/blink/renderer/core/input", true},
    {"scroll", "third_party/blink/renderer/core/scroll", true},
    {"animation", "third_party/blink/renderer/core/animation", true},
    {"geometry", "third_party/blink/renderer/core/geometry", true},
    {"svg", "third_party/blink/renderer/core/svg", true},
    {"mathml", "third_party/blink/renderer/core/mathml", true},
    {"dummy page holder header",
     "third_party/blink/renderer/core/testing/dummy_page_holder.h", true},
    {"dummy page holder source",
     "third_party/blink/renderer/core/testing/dummy_page_holder.cc", true},
    {"paint records", "cc/paint", true},
    {"compositor base", "cc/base", true},
    {"skia", "third_party/skia", true},
    {"gfx geometry", "ui/gfx/geometry", true},
    {"ui color", "ui/color", true},
    {"icu", "third_party/icu", true},
    {"harfbuzz", "third_party/harfbuzz", true},
    {"opentype sanitizer", "third_party/ots", true},
    {"png decoder", "third_party/libpng", true},
    {"jpeg decoder", "third_party/libjpeg_turbo", true},
    {"webp decoder", "third_party/libwebp", true},
    {"zlib", "third_party/zlib", true},
};

constexpr const char* kBuildFiles[] = {
    "third_party/blink/renderer/core/BUILD.gn",
    "third_party/blink/renderer/platform/BUILD.gn",
};

constexpr const char* kBlockedTokens[] = {
    "services/network",
    "services/service_manager",
    "services/viz",
    "gpu/",
    "gpu:",
    "mojo/",
    "media/",
    "renderer/core/xmlhttprequest",
    "renderer/core/workers",
    "renderer/core/fetch",
    "bindings/core/v8/script_controller",
};

struct CandidateRoot {
  const char* category;
  const char* path;
};

constexpr CandidateRoot kCandidateRoots[] = {
    {"dom", "third_party/blink/renderer/core/dom"},
    {"html", "third_party/blink/renderer/core/html"},
    {"css", "third_party/blink/renderer/core/css"},
    {"style", "third_party/blink/renderer/core/style"},
    {"layout", "third_party/blink/renderer/core/layout"},
    {"paint", "third_party/blink/renderer/core/paint"},
    {"page", "third_party/blink/renderer/core/page"},
    {"frame", "third_party/blink/renderer/core/frame"},
    {"events", "third_party/blink/renderer/core/events"},
    {"input", "third_party/blink/renderer/core/input"},
    {"scroll", "third_party/blink/renderer/core/scroll"},
    {"animation", "third_party/blink/renderer/core/animation"},
    {"geometry", "third_party/blink/renderer/core/geometry"},
    {"svg", "third_party/blink/renderer/core/svg"},
    {"mathml", "third_party/blink/renderer/core/mathml"},
    {"platform-fonts", "third_party/blink/renderer/platform/fonts"},
    {"platform-graphics", "third_party/blink/renderer/platform/graphics"},
    {"platform-geometry", "third_party/blink/renderer/platform/geometry"},
    {"platform-text", "third_party/blink/renderer/platform/text"},
    {"platform-transforms", "third_party/blink/renderer/platform/transforms"},
    {"platform-wtf", "third_party/blink/renderer/platform/wtf"},
    {"cc-paint", "cc/paint"},
    {"cc-base", "cc/base"},
    {"gfx-geometry", "ui/gfx/geometry"},
    {"ui-color", "ui/color"},
};

constexpr const char* kRejectedPathTokens[] = {
    "/ad_tracker/",
    "/accessibility/",
    "/bluetooth/",
    "/canvas/",
    "/clipboard/",
    "/content_capture/",
    "/credentialmanagement/",
    "/encryptedmedia/",
    "/fetch/",
    "/fileapi/",
    "/geolocation/",
    "/indexeddb/",
    "/inspector/",
    "/loader/",
    "/media/",
    "/messaging/",
    "/mojo/",
    "/navigation_api/",
    "/notifications/",
    "/offscreencanvas/",
    "/payments/",
    "/permissions/",
    "/presentation/",
    "/push_messaging/",
    "/serial/",
    "/service_worker/",
    "/speech/",
    "/storage/",
    "/streams/",
    "/webdatabase/",
    "/webgpu/",
    "/webrtc/",
    "/workers/",
    "/bindings/core/v8/script_controller",
    "/xmlhttprequest/",
};

int CountFiles(const fs::path& path) {
  if (fs::is_regular_file(path)) {
    return 1;
  }
  if (!fs::is_directory(path)) {
    return 0;
  }

  int count = 0;
  std::error_code error;
  fs::recursive_directory_iterator iterator(path, error);
  fs::recursive_directory_iterator end;
  while (!error && iterator != end) {
    if (iterator->is_regular_file(error)) {
      ++count;
    }
    iterator.increment(error);
  }
  return count;
}

std::string NormalizeForMatch(std::string value) {
  std::replace(value.begin(), value.end(), '\\', '/');
  return value;
}

bool IsSourceOrHeader(const fs::path& path) {
  const std::string extension = path.extension().string();
  return extension == ".cc" || extension == ".h" || extension == ".cpp" ||
         extension == ".hpp";
}

std::string RejectionReason(const std::string& normalized_relative_path) {
  const std::string wrapped = "/" + normalized_relative_path;
  for (const char* token : kRejectedPathTokens) {
    if (wrapped.find(token) != std::string::npos) {
      return std::string("blocked path token ") + token;
    }
  }
  if (normalized_relative_path.find("_test.") != std::string::npos ||
      normalized_relative_path.find("_fuzzer.") != std::string::npos ||
      normalized_relative_path.find("mock_") != std::string::npos) {
    return "test or fuzz-only source";
  }
  return {};
}

std::string ReadFile(const fs::path& path) {
  std::ifstream stream(path, std::ios::in | std::ios::binary);
  if (!stream) {
    return {};
  }
  std::ostringstream buffer;
  buffer << stream.rdbuf();
  return buffer.str();
}

std::vector<std::string> SplitLines(const std::string& text) {
  std::vector<std::string> lines;
  std::istringstream stream(text);
  std::string line;
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
  return lines;
}

}  // namespace

bool BlinkAdapterInventory::HasRequiredSources() const {
  return std::all_of(source_paths.begin(), source_paths.end(),
                     [](const ChromiumSourcePath& path) {
                       return !path.required || path.present;
                     });
}

bool BlinkAdapterInventory::HasBlockedBroadTargets() const {
  return !blocked_edges.empty();
}

std::vector<std::string> BlinkAdapterInventory::MissingRequiredPaths() const {
  std::vector<std::string> missing;
  for (const auto& path : source_paths) {
    if (path.required && !path.present) {
      missing.push_back(path.relative_path);
    }
  }
  return missing;
}

int BlinkSourceManifest::AcceptedCount() const {
  return static_cast<int>(
      std::count_if(files.begin(), files.end(), [](const BlinkSourceFile& file) {
        return file.accepted;
      }));
}

int BlinkSourceManifest::RejectedCount() const {
  return static_cast<int>(files.size()) - AcceptedCount();
}

std::vector<BlinkSourceFile> BlinkSourceManifest::AcceptedFiles() const {
  std::vector<BlinkSourceFile> accepted;
  for (const auto& file : files) {
    if (file.accepted) {
      accepted.push_back(file);
    }
  }
  return accepted;
}

std::vector<BlinkSourceFile> BlinkSourceManifest::RejectedFiles() const {
  std::vector<BlinkSourceFile> rejected;
  for (const auto& file : files) {
    if (!file.accepted) {
      rejected.push_back(file);
    }
  }
  return rejected;
}

BlinkAdapterInventory InspectChromiumCheckoutForBlinkAdapter(
    const std::string& chromium_root) {
  BlinkAdapterInventory inventory;
  inventory.chromium_root = chromium_root;

  const fs::path root = fs::path(chromium_root);
  for (const auto& spec : kSourceSpecs) {
    const fs::path path = root / fs::path(spec.path);
    ChromiumSourcePath source_path;
    source_path.role = spec.role;
    source_path.relative_path = spec.path;
    source_path.required = spec.required;
    source_path.present = fs::exists(path);
    source_path.file_count = CountFiles(path);
    inventory.source_paths.push_back(source_path);
  }

  for (const char* build_file : kBuildFiles) {
    const fs::path path = root / fs::path(build_file);
    const std::vector<std::string> lines = SplitLines(ReadFile(path));
    for (size_t i = 0; i < lines.size(); ++i) {
      for (const char* token : kBlockedTokens) {
        if (lines[i].find(token) == std::string::npos) {
          continue;
        }
        ChromiumBuildEdge edge;
        edge.file = build_file;
        edge.line = static_cast<int>(i + 1);
        edge.token = token;
        edge.text = lines[i];
        inventory.blocked_edges.push_back(edge);
      }
    }
  }

  return inventory;
}

BlinkSourceManifest BuildBlinkSourceManifest(const std::string& chromium_root) {
  BlinkSourceManifest manifest;
  manifest.chromium_root = chromium_root;

  const fs::path root = fs::path(chromium_root);
  for (const auto& candidate_root : kCandidateRoots) {
    const fs::path absolute_root = root / fs::path(candidate_root.path);
    if (!fs::is_directory(absolute_root)) {
      continue;
    }

    std::error_code error;
    fs::recursive_directory_iterator iterator(absolute_root, error);
    fs::recursive_directory_iterator end;
    while (!error && iterator != end) {
      const fs::path path = iterator->path();
      if (iterator->is_regular_file(error) && IsSourceOrHeader(path)) {
        BlinkSourceFile source_file;
        source_file.relative_path =
            NormalizeForMatch(fs::relative(path, root, error).string());
        source_file.category = candidate_root.category;
        source_file.reason = RejectionReason(source_file.relative_path);
        source_file.accepted = source_file.reason.empty();
        manifest.files.push_back(source_file);
      }
      iterator.increment(error);
    }
  }

  std::sort(manifest.files.begin(), manifest.files.end(),
            [](const BlinkSourceFile& lhs, const BlinkSourceFile& rhs) {
              return lhs.relative_path < rhs.relative_path;
            });
  return manifest;
}

}  // namespace html_css_renderer
