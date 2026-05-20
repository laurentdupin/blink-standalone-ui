#include "html_css_renderer/standalone_resource_provider.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <limits>
#include <mutex>
#include <string>

#if defined(_WIN32)
#include <objbase.h>
#include <wincodec.h>
#include <wrl/client.h>
#endif

#include "third_party/blink/renderer/platform/wtf/text/base64.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPixmap.h"

namespace html_css_renderer {
namespace {

StandaloneResourceProviderDiagnostics& MutableDiagnostics() {
  static StandaloneResourceProviderDiagnostics* diagnostics =
      new StandaloneResourceProviderDiagnostics();
  return *diagnostics;
}

std::mutex& DiagnosticsMutex() {
  static std::mutex* mutex = new std::mutex();
  return *mutex;
}

std::string& MutableResourceRoot() {
  static std::string* root = new std::string();
  return *root;
}

std::string& MutableDocumentBasePath() {
  static std::string* base_path = new std::string();
  return *base_path;
}

std::string LowerAscii(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(), [](char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  });
  return value;
}

std::string UrlPrefix(const std::string& url) {
  constexpr size_t kMaxPrefix = 96;
  if (url.size() <= kMaxPrefix) {
    return url;
  }
  return url.substr(0, kMaxPrefix) + "...";
}

void RecordRequest(const StandaloneResourceRequest& request,
                   const StandaloneResourceResult& result) {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  StandaloneResourceProviderDiagnostics& diagnostics = MutableDiagnostics();
  ++diagnostics.request_count;
  if (request.type_hint == StandaloneResourceTypeHint::kImage) {
    ++diagnostics.image_request_count;
  }
  if (result.source_kind == StandaloneResourceSourceKind::kDataUrl &&
      result.mime_type == "image/png") {
    ++diagnostics.data_png_request_count;
  }
  if (result.status == StandaloneResourceStatus::kSuccess) {
    ++diagnostics.success_count;
  } else {
    ++diagnostics.failure_count;
  }

  StandaloneResourceProviderDiagnostics::RequestDiagnostic item;
  item.url_prefix = UrlPrefix(request.url);
  item.initiator = ToString(request.initiator);
  item.source_kind = ToString(result.source_kind);
  item.mime_type = result.mime_type;
  item.resolved_path = result.resolved_path;
  item.cache_key = result.cache_key;
  item.encoded_bytes = result.encoded_bytes.size();
  item.decoded_width = result.intrinsic_width;
  item.decoded_height = result.intrinsic_height;
  item.status = ToString(result.status);
  item.error = result.error;
  diagnostics.requests.push_back(std::move(item));
}

StandaloneResourceResult ErrorResult(StandaloneResourceStatus status,
                                     std::string error,
                                     std::string mime_type = std::string()) {
  StandaloneResourceResult result;
  result.status = status;
  result.mime_type = std::move(mime_type);
  result.error = std::move(error);
  return result;
}

StandaloneResourceResult DecodePngBytes(StandaloneResourceResult result) {
#if defined(_WIN32)
  if (result.encoded_bytes.size() > std::numeric_limits<DWORD>::max()) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "encoded PNG is too large", "image/png");
  }

  HRESULT initialize_result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  if (FAILED(initialize_result) && initialize_result != RPC_E_CHANGED_MODE) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "CoInitializeEx failed", "image/png");
  }

  Microsoft::WRL::ComPtr<IWICImagingFactory> factory;
  HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
                                CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC factory creation failed", "image/png");
  }

  Microsoft::WRL::ComPtr<IWICStream> stream;
  hr = factory->CreateStream(&stream);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC stream creation failed", "image/png");
  }
  hr = stream->InitializeFromMemory(
      result.encoded_bytes.data(),
      static_cast<DWORD>(result.encoded_bytes.size()));
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC stream initialization failed", "image/png");
  }

  Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
  hr = factory->CreateDecoderFromStream(
      stream.Get(), nullptr, WICDecodeMetadataCacheOnLoad, &decoder);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC PNG decoder failed", "image/png");
  }

  Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
  hr = decoder->GetFrame(0, &frame);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC PNG frame extraction failed", "image/png");
  }

  UINT width = 0;
  UINT height = 0;
  hr = frame->GetSize(&width, &height);
  if (FAILED(hr) || width == 0 || height == 0) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC PNG size query failed", "image/png");
  }

  Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
  hr = factory->CreateFormatConverter(&converter);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC format converter creation failed", "image/png");
  }
  hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA,
                             WICBitmapDitherTypeNone, nullptr, 0.0,
                             WICBitmapPaletteTypeCustom);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC PNG conversion to BGRA failed", "image/png");
  }

  constexpr UINT kBytesPerPixel = 4;
  uint64_t stride64 = static_cast<uint64_t>(width) * kBytesPerPixel;
  uint64_t byte_count64 = stride64 * height;
  if (stride64 > std::numeric_limits<UINT>::max() ||
      byte_count64 > std::numeric_limits<size_t>::max()) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "decoded PNG is too large", "image/png");
  }

  std::vector<uint8_t> pixels(static_cast<size_t>(byte_count64));
  hr = converter->CopyPixels(nullptr, static_cast<UINT>(stride64),
                             static_cast<UINT>(byte_count64), pixels.data());
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC PNG pixel copy failed", "image/png");
  }

  SkImageInfo image_info =
      SkImageInfo::Make(static_cast<int>(width), static_cast<int>(height),
                        kBGRA_8888_SkColorType, kPremul_SkAlphaType);
  SkPixmap pixmap(image_info, pixels.data(), static_cast<size_t>(stride64));
  result.decoded_image = SkImages::RasterFromPixmapCopy(pixmap);
  if (!result.decoded_image) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "SkImage creation failed after WIC decode",
                       "image/png");
  }
  result.intrinsic_width = static_cast<int>(width);
  result.intrinsic_height = static_cast<int>(height);
  result.status = StandaloneResourceStatus::kSuccess;
  return result;
#else
  return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                     "PNG decode provider is implemented only on Windows",
                     "image/png");
#endif
}

StandaloneResourceResult DecodeDataPngUrl(const std::string& url) {
  std::string lower_url = LowerAscii(url);
  constexpr char kPrefix[] = "data:";
  if (lower_url.rfind(kPrefix, 0) != 0) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedScheme,
                       "not a data URL");
  }

  size_t comma = url.find(',');
  if (comma == std::string::npos || comma == 0) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "malformed data URL");
  }

  std::string metadata =
      lower_url.substr(sizeof(kPrefix) - 1, comma - (sizeof(kPrefix) - 1));
  if (metadata.find("image/png") == std::string::npos) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedMime,
                       "only image/png data URLs are enabled", "");
  }
  if (metadata.find(";base64") == std::string::npos) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "image/png data URL is not base64 encoded",
                       "image/png");
  }

  blink::Vector<uint8_t> blink_encoded;
  std::string payload = url.substr(comma + 1);
  if (!blink::Base64Decode(blink::String(payload.c_str()), blink_encoded,
                           blink::Base64DecodePolicy::kForgiving) ||
      blink_encoded.empty()) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "base64 decode failed", "image/png");
  }

  StandaloneResourceResult result;
  result.source_kind = StandaloneResourceSourceKind::kDataUrl;
  result.mime_type = "image/png";
  result.encoded_bytes.assign(blink_encoded.begin(), blink_encoded.end());
  result.cache_key = url;
  return DecodePngBytes(std::move(result));
}

std::string StripFileUrlPrefix(const std::string& url) {
  std::string path = url;
  if (path.rfind("file:///", 0) == 0) {
    path = path.substr(8);
  } else if (path.rfind("file://", 0) == 0) {
    path = path.substr(7);
  }
#if defined(_WIN32)
  std::replace(path.begin(), path.end(), '/', '\\');
#endif
  return path;
}

bool HasScheme(const std::string& url) {
  size_t colon = url.find(':');
  if (colon == std::string::npos || colon == 0)
    return false;
  for (size_t i = 0; i < colon; ++i) {
    unsigned char c = static_cast<unsigned char>(url[i]);
    if (!std::isalnum(c) && url[i] != '+' && url[i] != '-' && url[i] != '.')
      return false;
  }
  return true;
}

bool IsWithinRoot(const std::filesystem::path& path,
                  const std::filesystem::path& root) {
  auto path_it = path.begin();
  auto root_it = root.begin();
  for (; root_it != root.end(); ++root_it, ++path_it) {
    if (path_it == path.end() || *path_it != *root_it)
      return false;
  }
  return true;
}

StandaloneResourceResult DecodeLocalPng(const std::string& url) {
  std::string lower_url = LowerAscii(url);
  if (lower_url.rfind("http:", 0) == 0 || lower_url.rfind("https:", 0) == 0) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedScheme,
                       "HTTP/HTTPS loading is disabled");
  }
  if (HasScheme(lower_url) && lower_url.rfind("file:", 0) != 0) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedScheme,
                       "only data:, file:, and document-relative resources are enabled");
  }

  const std::string root_string = GetStandaloneResourceProviderResourceRoot();
  if (root_string.empty()) {
    return ErrorResult(StandaloneResourceStatus::kBlockedByPolicy,
                       "local resource root is not configured");
  }

  std::error_code root_error;
  std::filesystem::path root =
      std::filesystem::weakly_canonical(root_string, root_error);
  if (root_error) {
    return ErrorResult(StandaloneResourceStatus::kBlockedByPolicy,
                       "local resource root cannot be resolved");
  }
  const std::string base_string = GetStandaloneResourceProviderDocumentBasePath();
  std::filesystem::path base_path = root;
  if (!base_string.empty()) {
    std::error_code base_error;
    base_path = std::filesystem::weakly_canonical(base_string, base_error);
    if (base_error) {
      return ErrorResult(StandaloneResourceStatus::kBlockedByPolicy,
                         "document base path cannot be resolved");
    }
  }
  std::filesystem::path candidate =
      lower_url.rfind("file:", 0) == 0 ? std::filesystem::path(StripFileUrlPrefix(url))
                                       : std::filesystem::path(url);
  if (candidate.is_relative())
    candidate = base_path / candidate;
  std::error_code candidate_error;
  candidate = std::filesystem::weakly_canonical(candidate, candidate_error);
  if (candidate_error) {
    candidate = std::filesystem::absolute(candidate);
  }

  StandaloneResourceResult result;
  result.source_kind = StandaloneResourceSourceKind::kLocalFile;
  result.mime_type = "image/png";
  result.resolved_path = candidate.string();
  result.cache_key = result.resolved_path;

  if (!IsWithinRoot(candidate, root)) {
    result.status = StandaloneResourceStatus::kBlockedByPolicy;
    result.error = "resolved local image path escapes resource root";
    return result;
  }
  if (LowerAscii(candidate.extension().string()) != ".png") {
    result.status = StandaloneResourceStatus::kUnsupportedMime;
    result.error = "only local PNG images are enabled";
    return result;
  }
  if (!std::filesystem::exists(candidate) ||
      !std::filesystem::is_regular_file(candidate)) {
    result.status = StandaloneResourceStatus::kNotFound;
    result.error = "local image file was not found";
    return result;
  }

  std::ifstream file(candidate, std::ios::binary);
  if (!file) {
    result.status = StandaloneResourceStatus::kError;
    result.error = "failed to open local image file";
    return result;
  }
  result.encoded_bytes.assign(std::istreambuf_iterator<char>(file),
                              std::istreambuf_iterator<char>());
  if (result.encoded_bytes.empty()) {
    result.status = StandaloneResourceStatus::kDecodeFailed;
    result.error = "local image file is empty";
    return result;
  }
  return DecodePngBytes(std::move(result));
}

class DefaultProvider final : public StandaloneResourceProvider {
 public:
  StandaloneResourceResult LoadResource(
      const StandaloneResourceRequest& request) override {
    StandaloneResourceResult result;
    if (request.type_hint != StandaloneResourceTypeHint::kImage) {
      result = ErrorResult(StandaloneResourceStatus::kUnsupportedMime,
                           "provider currently supports image requests only");
    } else {
      result = DecodeDataPngUrl(request.url);
      if (result.status == StandaloneResourceStatus::kUnsupportedScheme)
        result = DecodeLocalPng(request.url);
    }
    RecordRequest(request, result);
    return result;
  }
};

}  // namespace

StandaloneResourceProvider& DefaultStandaloneResourceProvider() {
  static DefaultProvider* provider = new DefaultProvider();
  return *provider;
}

void SetStandaloneResourceProviderResourceRoot(std::string root_path) {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  MutableResourceRoot() = std::move(root_path);
}

std::string GetStandaloneResourceProviderResourceRoot() {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  return MutableResourceRoot();
}

void SetStandaloneResourceProviderDocumentBasePath(std::string base_path) {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  MutableDocumentBasePath() = std::move(base_path);
}

std::string GetStandaloneResourceProviderDocumentBasePath() {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  return MutableDocumentBasePath();
}

void ResetStandaloneResourceProviderDiagnostics() {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  MutableDiagnostics() = StandaloneResourceProviderDiagnostics();
}

StandaloneResourceProviderDiagnostics GetStandaloneResourceProviderDiagnostics() {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  return MutableDiagnostics();
}

const char* ToString(StandaloneResourceStatus status) {
  switch (status) {
    case StandaloneResourceStatus::kSuccess:
      return "success";
    case StandaloneResourceStatus::kNotFound:
      return "not_found";
    case StandaloneResourceStatus::kUnsupportedScheme:
      return "unsupported_scheme";
    case StandaloneResourceStatus::kUnsupportedMime:
      return "unsupported_mime";
    case StandaloneResourceStatus::kDecodeFailed:
      return "decode_failed";
    case StandaloneResourceStatus::kBlockedByPolicy:
      return "blocked_by_policy";
    case StandaloneResourceStatus::kError:
      return "error";
  }
  return "error";
}

const char* ToString(StandaloneResourceInitiator initiator) {
  switch (initiator) {
    case StandaloneResourceInitiator::kOther:
      return "other";
    case StandaloneResourceInitiator::kImgElement:
      return "img";
    case StandaloneResourceInitiator::kCssBackgroundImage:
      return "css_background_image";
    case StandaloneResourceInitiator::kStylesheetLink:
      return "stylesheet_link";
    case StandaloneResourceInitiator::kFontFace:
      return "font_face";
  }
  return "other";
}

const char* ToString(StandaloneResourceSourceKind source_kind) {
  switch (source_kind) {
    case StandaloneResourceSourceKind::kUnsupported:
      return "unsupported";
    case StandaloneResourceSourceKind::kDataUrl:
      return "data_url";
    case StandaloneResourceSourceKind::kFileUrl:
      return "file_url";
    case StandaloneResourceSourceKind::kLocalFile:
      return "local_file";
    case StandaloneResourceSourceKind::kMemory:
      return "memory";
  }
  return "unsupported";
}

}  // namespace html_css_renderer
