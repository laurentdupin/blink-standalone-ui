#include "html_css_renderer/standalone_resource_provider.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <limits>
#include <cstring>
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <objbase.h>
#include <wincodec.h>
#include <wrl/client.h>
#endif

#include "third_party/blink/renderer/platform/wtf/text/base64.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPixmap.h"

namespace html_css_renderer {
namespace {

struct ResourceProviderContextState {
  StandaloneResourceProviderDiagnostics diagnostics;
  std::string resource_root;
  std::string document_base_path;
  std::shared_ptr<StandaloneResourceProvider> embedder_provider;
  uint32_t embedder_provider_flags = 0;
};

ResourceProviderContextState& GlobalContextState() {
  static ResourceProviderContextState* state = new ResourceProviderContextState();
  return *state;
}

std::unordered_map<uint64_t, ResourceProviderContextState>& MutableContexts() {
  static auto* contexts =
      new std::unordered_map<uint64_t, ResourceProviderContextState>();
  return *contexts;
}

std::mutex& DiagnosticsMutex() {
  static std::mutex* mutex = new std::mutex();
  return *mutex;
}

uint64_t& NextContextId() {
  static uint64_t* next_id = new uint64_t(1);
  return *next_id;
}

thread_local uint64_t g_current_context_id = 0;

ResourceProviderContextState& CurrentContextStateLocked() {
  if (g_current_context_id != 0) {
    auto it = MutableContexts().find(g_current_context_id);
    if (it != MutableContexts().end())
      return it->second;
  }
  return GlobalContextState();
}

StandaloneResourceProviderDiagnostics& MutableDiagnostics() {
  return CurrentContextStateLocked().diagnostics;
}

std::string& MutableResourceRoot() {
  return CurrentContextStateLocked().resource_root;
}

std::string& MutableDocumentBasePath() {
  return CurrentContextStateLocked().document_base_path;
}

std::pair<std::shared_ptr<StandaloneResourceProvider>, uint32_t>
CurrentEmbedderProviderAndFlags() {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  ResourceProviderContextState& state = CurrentContextStateLocked();
  return {state.embedder_provider, state.embedder_provider_flags};
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

uint32_t ReadLittleEndian24(const uint8_t* data) {
  return static_cast<uint32_t>(data[0]) |
         (static_cast<uint32_t>(data[1]) << 8) |
         (static_cast<uint32_t>(data[2]) << 16);
}

uint32_t ReadLittleEndian32(const uint8_t* data) {
  return static_cast<uint32_t>(data[0]) |
         (static_cast<uint32_t>(data[1]) << 8) |
         (static_cast<uint32_t>(data[2]) << 16) |
         (static_cast<uint32_t>(data[3]) << 24);
}

bool BytesEqual(const std::vector<uint8_t>& bytes,
                size_t offset,
                const char* literal,
                size_t length) {
  return offset + length <= bytes.size() &&
         std::equal(literal, literal + length, bytes.begin() + offset);
}

std::optional<std::pair<int, int>> ParseWebPDimensions(
    const std::vector<uint8_t>& bytes) {
  if (bytes.size() < 20 || !BytesEqual(bytes, 0, "RIFF", 4) ||
      !BytesEqual(bytes, 8, "WEBP", 4)) {
    return std::nullopt;
  }

  size_t offset = 12;
  while (offset + 8 <= bytes.size()) {
    const char* fourcc = reinterpret_cast<const char*>(bytes.data() + offset);
    const uint32_t chunk_size = ReadLittleEndian32(bytes.data() + offset + 4);
    const size_t payload = offset + 8;
    if (payload + chunk_size > bytes.size()) {
      return std::nullopt;
    }

    if (std::memcmp(fourcc, "VP8 ", 4) == 0) {
      if (chunk_size < 10 || payload + 10 > bytes.size() ||
          bytes[payload + 3] != 0x9d || bytes[payload + 4] != 0x01 ||
          bytes[payload + 5] != 0x2a) {
        return std::nullopt;
      }
      const int width =
          (bytes[payload + 6] | (bytes[payload + 7] << 8)) & 0x3fff;
      const int height =
          (bytes[payload + 8] | (bytes[payload + 9] << 8)) & 0x3fff;
      if (width > 0 && height > 0)
        return std::make_pair(width, height);
      return std::nullopt;
    }

    if (std::memcmp(fourcc, "VP8L", 4) == 0) {
      if (chunk_size < 5 || payload + 5 > bytes.size() ||
          bytes[payload] != 0x2f) {
        return std::nullopt;
      }
      const int width =
          1 + bytes[payload + 1] + ((bytes[payload + 2] & 0x3f) << 8);
      const int height =
          1 + ((bytes[payload + 2] & 0xc0) >> 6) +
          (bytes[payload + 3] << 2) + ((bytes[payload + 4] & 0x0f) << 10);
      if (width > 0 && height > 0)
        return std::make_pair(width, height);
      return std::nullopt;
    }

    if (std::memcmp(fourcc, "VP8X", 4) == 0) {
      if (chunk_size < 10 || payload + 10 > bytes.size()) {
        return std::nullopt;
      }
      const int width =
          1 + static_cast<int>(ReadLittleEndian24(bytes.data() + payload + 4));
      const int height =
          1 + static_cast<int>(ReadLittleEndian24(bytes.data() + payload + 7));
      if (width > 0 && height > 0)
        return std::make_pair(width, height);
      return std::nullopt;
    }

    offset = payload + chunk_size + (chunk_size & 1);
  }
  return std::nullopt;
}

StandaloneResourceResult CreateTransparentDecodedImage(
    StandaloneResourceResult result,
    int width,
    int height,
    std::string note) {
  if (width <= 0 || height <= 0) {
    result.status = StandaloneResourceStatus::kDecodeFailed;
    result.error = "decoded image dimensions are invalid";
    return result;
  }
  const size_t pixel_count = static_cast<size_t>(width) * height;
  std::vector<uint8_t> pixels(pixel_count * 4, 0);
  SkImageInfo image_info =
      SkImageInfo::Make(width, height, kBGRA_8888_SkColorType,
                        kPremul_SkAlphaType);
  SkPixmap pixmap(image_info, pixels.data(), static_cast<size_t>(width) * 4);
  result.decoded_image = SkImages::RasterFromPixmapCopy(pixmap);
  if (!result.decoded_image) {
    result.status = StandaloneResourceStatus::kDecodeFailed;
    result.error = "SkImage creation failed for transparent image";
    return result;
  }
  result.intrinsic_width = width;
  result.intrinsic_height = height;
  result.status = StandaloneResourceStatus::kSuccess;
  result.error = std::move(note);
  return result;
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

StandaloneResourceResult DecodeImageBytes(StandaloneResourceResult result) {
#if defined(_WIN32)
  if (result.encoded_bytes.size() > std::numeric_limits<DWORD>::max()) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "encoded image is too large", result.mime_type);
  }

  HRESULT initialize_result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
  if (FAILED(initialize_result) && initialize_result != RPC_E_CHANGED_MODE) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "CoInitializeEx failed", result.mime_type);
  }

  Microsoft::WRL::ComPtr<IWICImagingFactory> factory;
  HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
                                CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC factory creation failed", result.mime_type);
  }

  Microsoft::WRL::ComPtr<IWICStream> stream;
  hr = factory->CreateStream(&stream);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC stream creation failed", result.mime_type);
  }
  hr = stream->InitializeFromMemory(
      result.encoded_bytes.data(),
      static_cast<DWORD>(result.encoded_bytes.size()));
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC stream initialization failed", result.mime_type);
  }

  Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
  hr = factory->CreateDecoderFromStream(
      stream.Get(), nullptr, WICDecodeMetadataCacheOnLoad, &decoder);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC image decoder failed", result.mime_type);
  }

  Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
  hr = decoder->GetFrame(0, &frame);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC image frame extraction failed", result.mime_type);
  }

  UINT width = 0;
  UINT height = 0;
  hr = frame->GetSize(&width, &height);
  if (FAILED(hr) || width == 0 || height == 0) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC image size query failed", result.mime_type);
  }

  Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
  hr = factory->CreateFormatConverter(&converter);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kError,
                       "WIC format converter creation failed", result.mime_type);
  }
  hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppPBGRA,
                             WICBitmapDitherTypeNone, nullptr, 0.0,
                             WICBitmapPaletteTypeCustom);
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC image conversion to BGRA failed", result.mime_type);
  }

  constexpr UINT kBytesPerPixel = 4;
  uint64_t stride64 = static_cast<uint64_t>(width) * kBytesPerPixel;
  uint64_t byte_count64 = stride64 * height;
  if (stride64 > std::numeric_limits<UINT>::max() ||
      byte_count64 > std::numeric_limits<size_t>::max()) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "decoded image is too large", result.mime_type);
  }

  std::vector<uint8_t> pixels(static_cast<size_t>(byte_count64));
  hr = converter->CopyPixels(nullptr, static_cast<UINT>(stride64),
                             static_cast<UINT>(byte_count64), pixels.data());
  if (FAILED(hr)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "WIC image pixel copy failed", result.mime_type);
  }

  SkImageInfo image_info =
      SkImageInfo::Make(static_cast<int>(width), static_cast<int>(height),
                        kBGRA_8888_SkColorType, kPremul_SkAlphaType);
  SkPixmap pixmap(image_info, pixels.data(), static_cast<size_t>(stride64));
  result.decoded_image = SkImages::RasterFromPixmapCopy(pixmap);
  if (!result.decoded_image) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "SkImage creation failed after WIC decode",
                       result.mime_type);
  }
  result.intrinsic_width = static_cast<int>(width);
  result.intrinsic_height = static_cast<int>(height);
  result.status = StandaloneResourceStatus::kSuccess;
  return result;
#else
  return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                     "image decode provider is implemented only on Windows",
                     result.mime_type);
#endif
}

StandaloneResourceResult DecodeOrClassifyImageBytes(
    StandaloneResourceResult result) {
  std::optional<std::pair<int, int>> webp_dimensions;
  std::vector<uint8_t> webp_encoded_bytes;
  StandaloneResourceSourceKind webp_source_kind =
      StandaloneResourceSourceKind::kUnsupported;
  std::string webp_cache_key;
  std::string webp_resolved_path;
  if (result.mime_type == "image/webp") {
    webp_dimensions = ParseWebPDimensions(result.encoded_bytes);
    if (webp_dimensions) {
      webp_encoded_bytes = result.encoded_bytes;
      webp_source_kind = result.source_kind;
      webp_cache_key = result.cache_key;
      webp_resolved_path = result.resolved_path;
    }
  }

  StandaloneResourceResult decoded = DecodeImageBytes(std::move(result));
  if (decoded.status == StandaloneResourceStatus::kSuccess ||
      decoded.mime_type != "image/webp") {
    return decoded;
  }

  if (!webp_dimensions) {
    return decoded;
  }
  decoded.encoded_bytes = std::move(webp_encoded_bytes);
  decoded.source_kind = webp_source_kind;
  decoded.cache_key = std::move(webp_cache_key);
  decoded.resolved_path = std::move(webp_resolved_path);

  return CreateTransparentDecodedImage(
      std::move(decoded), webp_dimensions->first, webp_dimensions->second,
      "valid WebP resource classified without platform WebP decoder");
}

bool IsSvgImageMime(const std::string& mime_type);
bool IsDataUrl(const std::string& url);

StandaloneResourceResult FinalizeProviderMemoryResult(
    StandaloneResourceResult result,
    StandaloneResourceTypeHint type_hint) {
  result.source_kind = StandaloneResourceSourceKind::kMemory;
  if (result.cache_key.empty()) {
    result.cache_key = result.resolved_path;
  }
  if (result.status != StandaloneResourceStatus::kSuccess) {
    return result;
  }
  if (type_hint != StandaloneResourceTypeHint::kImage) {
    return result;
  }
  if (result.mime_type.empty()) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedMime,
                       "resource provider returned image bytes without MIME");
  }
  if (IsSvgImageMime(result.mime_type)) {
    result.status = StandaloneResourceStatus::kUnsupportedMime;
    result.error = "SVG image rendering is unsupported in this standalone build";
    return result;
  }
  if (result.encoded_bytes.empty()) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "resource provider returned empty image bytes",
                       result.mime_type);
  }
  return DecodeOrClassifyImageBytes(std::move(result));
}

bool ShouldBlockFallbackForRequest(const StandaloneResourceRequest& request,
                                   uint32_t flags,
                                   bool provider_was_available) {
  if (IsDataUrl(request.url) &&
      !(flags & kStandaloneResourceProviderCallbackForDataUrls)) {
    return false;
  }
  if (IsDataUrl(request.url) && provider_was_available &&
      (flags & kStandaloneResourceProviderCallbackForDataUrls)) {
    return true;
  }
  if (!provider_was_available &&
      (flags & kStandaloneResourceProviderRequireProviderForExternal) &&
      !IsDataUrl(request.url)) {
    return true;
  }
  if ((flags & kStandaloneResourceProviderDisableFileFallback) &&
      !IsDataUrl(request.url)) {
    return true;
  }
  if ((flags & kStandaloneResourceProviderRequireProviderForExternal) &&
      !IsDataUrl(request.url)) {
    return true;
  }
  return false;
}

std::string SupportedImageMimeFromMetadata(const std::string& metadata) {
  if (metadata.find("image/png") != std::string::npos)
    return "image/png";
  if (metadata.find("image/jpeg") != std::string::npos ||
      metadata.find("image/jpg") != std::string::npos)
    return "image/jpeg";
  if (metadata.find("image/bmp") != std::string::npos ||
      metadata.find("image/x-ms-bmp") != std::string::npos)
    return "image/bmp";
  if (metadata.find("image/webp") != std::string::npos)
    return "image/webp";
  if (metadata.find("image/svg+xml") != std::string::npos)
    return "image/svg+xml";
  return std::string();
}

bool IsSvgImageMime(const std::string& mime_type) {
  return mime_type == "image/svg+xml";
}

bool IsDataUrl(const std::string& url) {
  return LowerAscii(url).rfind("data:", 0) == 0;
}

std::vector<uint8_t> PercentDecodeBytes(const std::string& input) {
  auto hex_value = [](char c) -> int {
    if (c >= '0' && c <= '9')
      return c - '0';
    if (c >= 'a' && c <= 'f')
      return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
      return c - 'A' + 10;
    return -1;
  };

  std::vector<uint8_t> output;
  output.reserve(input.size());
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] == '%' && i + 2 < input.size()) {
      int high = hex_value(input[i + 1]);
      int low = hex_value(input[i + 2]);
      if (high >= 0 && low >= 0) {
        output.push_back(static_cast<uint8_t>((high << 4) | low));
        i += 2;
        continue;
      }
    }
    output.push_back(static_cast<uint8_t>(input[i]));
  }
  return output;
}

StandaloneResourceResult DecodeDataImageUrl(const std::string& url) {
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
  std::string mime_type = SupportedImageMimeFromMetadata(metadata);
  if (mime_type.empty()) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedMime,
                       "only PNG/JPEG/BMP/WebP/SVG data URLs are enabled", "");
  }

  const bool is_base64 = metadata.find(";base64") != std::string::npos;
  if (!is_base64 && !IsSvgImageMime(mime_type)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "image data URL is not base64 encoded", mime_type);
  }

  std::string payload = url.substr(comma + 1);

  StandaloneResourceResult result;
  result.source_kind = StandaloneResourceSourceKind::kDataUrl;
  result.mime_type = std::move(mime_type);
  result.cache_key = url;
  if (is_base64) {
    blink::Vector<uint8_t> blink_encoded;
    if (!blink::Base64Decode(blink::String(payload.c_str()), blink_encoded,
                             blink::Base64DecodePolicy::kForgiving) ||
        blink_encoded.empty()) {
      return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                         "base64 decode failed", result.mime_type);
    }
    result.encoded_bytes.assign(blink_encoded.begin(), blink_encoded.end());
  } else {
    result.encoded_bytes = PercentDecodeBytes(payload);
    if (result.encoded_bytes.empty()) {
      return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                         "SVG data URL is empty", result.mime_type);
    }
  }
  if (IsSvgImageMime(result.mime_type)) {
    result.status = StandaloneResourceStatus::kUnsupportedMime;
    result.error = "SVG image rendering is unsupported in this standalone build";
    return result;
  }
  return DecodeOrClassifyImageBytes(std::move(result));
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

std::string SupportedImageMimeFromExtension(std::string extension) {
  extension = LowerAscii(std::move(extension));
  if (extension == ".png")
    return "image/png";
  if (extension == ".jpg" || extension == ".jpeg")
    return "image/jpeg";
  if (extension == ".bmp")
    return "image/bmp";
  if (extension == ".webp")
    return "image/webp";
  if (extension == ".svg")
    return "image/svg+xml";
  return std::string();
}

StandaloneResourceResult DecodeLocalImage(const std::string& url) {
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
  const bool is_file_url = lower_url.rfind("file:", 0) == 0;
  std::filesystem::path candidate =
      is_file_url ? std::filesystem::path(StripFileUrlPrefix(url))
                  : std::filesystem::path(url);
  if (candidate.is_relative())
    candidate = base_path / candidate;
  std::error_code candidate_error;
  candidate = std::filesystem::weakly_canonical(candidate, candidate_error);
  if (candidate_error) {
    candidate = std::filesystem::absolute(candidate);
  }

  StandaloneResourceResult result;
  result.source_kind = is_file_url ? StandaloneResourceSourceKind::kFileUrl
                                   : StandaloneResourceSourceKind::kRelativeFile;
  result.mime_type = SupportedImageMimeFromExtension(candidate.extension().string());
  result.resolved_path = candidate.string();
  result.cache_key = result.resolved_path;

  if (!IsWithinRoot(candidate, root)) {
    result.status = StandaloneResourceStatus::kBlockedByPolicy;
    result.error = "resolved local image path escapes resource root";
    return result;
  }
  if (result.mime_type.empty()) {
    result.status = StandaloneResourceStatus::kUnsupportedMime;
    result.error = "only local PNG/JPEG/BMP/WebP/SVG images are enabled";
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
  if (IsSvgImageMime(result.mime_type)) {
    result.status = StandaloneResourceStatus::kUnsupportedMime;
    result.error = "SVG image rendering is unsupported in this standalone build";
    return result;
  }
  return DecodeOrClassifyImageBytes(std::move(result));
}

class DefaultProvider final : public StandaloneResourceProvider {
 public:
  StandaloneResourceResult LoadResource(
      const StandaloneResourceRequest& request) override {
    StandaloneResourceResult result;
    auto [embedder_provider, flags] = CurrentEmbedderProviderAndFlags();
    const bool should_call_embedder =
        embedder_provider &&
        (!IsDataUrl(request.url) ||
         (flags & kStandaloneResourceProviderCallbackForDataUrls));
    if (should_call_embedder) {
      result = FinalizeProviderMemoryResult(
          embedder_provider->LoadResource(request), request.type_hint);
      if (result.status == StandaloneResourceStatus::kSuccess ||
          ShouldBlockFallbackForRequest(request, flags,
                                        /*provider_was_available=*/true)) {
        RecordRequest(request, result);
        return result;
      }
    } else if (ShouldBlockFallbackForRequest(request, flags,
                                             embedder_provider != nullptr)) {
      result = ErrorResult(
          StandaloneResourceStatus::kBlockedByPolicy,
          embedder_provider
              ? "resource provider is required for external resources"
              : "resource provider is required but not configured");
      RecordRequest(request, result);
      return result;
    }

    if (request.type_hint != StandaloneResourceTypeHint::kImage) {
      result = ErrorResult(StandaloneResourceStatus::kUnsupportedMime,
                           "provider currently supports image requests only");
    } else {
      result = DecodeDataImageUrl(request.url);
      if (result.status == StandaloneResourceStatus::kUnsupportedScheme)
        result = DecodeLocalImage(request.url);
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

uint64_t CreateStandaloneResourceProviderContext() {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  const uint64_t context_id = NextContextId()++;
  MutableContexts().emplace(context_id, ResourceProviderContextState());
  return context_id;
}

void DestroyStandaloneResourceProviderContext(uint64_t context_id) {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  MutableContexts().erase(context_id);
  if (g_current_context_id == context_id)
    g_current_context_id = 0;
}

void SetCurrentStandaloneResourceProviderContext(uint64_t context_id) {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  if (context_id != 0 &&
      MutableContexts().find(context_id) == MutableContexts().end()) {
    context_id = 0;
  }
  g_current_context_id = context_id;
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

void SetStandaloneResourceProviderEmbedderProvider(
    std::shared_ptr<StandaloneResourceProvider> provider,
    uint32_t flags) {
  std::lock_guard<std::mutex> lock(DiagnosticsMutex());
  ResourceProviderContextState& state = CurrentContextStateLocked();
  state.embedder_provider = std::move(provider);
  state.embedder_provider_flags = flags;
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
    case StandaloneResourceInitiator::kCssImport:
      return "css_import";
    case StandaloneResourceInitiator::kFontFace:
      return "font_face";
    case StandaloneResourceInitiator::kMedia:
      return "media";
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
    case StandaloneResourceSourceKind::kRelativeFile:
      return "relative_file";
    case StandaloneResourceSourceKind::kLocalFile:
      return "local_file";
    case StandaloneResourceSourceKind::kMemory:
      return "memory";
  }
  return "unsupported";
}

}  // namespace html_css_renderer
