#include "html_css_renderer/standalone_resource_provider.h"

#include <algorithm>
#include <span>
#include <filesystem>
#include <limits>
#include <cstring>
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

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/no_destructor.h"
#include "base/numerics/byte_conversions.h"
#include "base/strings/string_util.h"
#include "base/synchronization/lock.h"
#include "net/base/data_url.h"
#include "net/base/mime_util.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPixmap.h"
#include "url/gurl.h"
#include "url/third_party/mozilla/url_parse.h"
#include "url/url_constants.h"
#include "url/url_util.h"

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

base::Lock& DiagnosticsLock() {
  static base::NoDestructor<base::Lock> lock;
  return *lock;
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
  base::AutoLock auto_lock(DiagnosticsLock());
  ResourceProviderContextState& state = CurrentContextStateLocked();
  return {state.embedder_provider, state.embedder_provider_flags};
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
  return base::U32FromLittleEndian(std::span<const uint8_t, 4>(data, 4));
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
  base::AutoLock auto_lock(DiagnosticsLock());
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

bool IsSvgImageMime(std::string_view mime_type);
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

bool MimeEquals(std::string_view mime_type, std::string_view expected_mime_type) {
  return base::EqualsCaseInsensitiveASCII(mime_type, expected_mime_type);
}

std::string SupportedDataImageMime(std::string_view media_type) {
  std::optional<std::string> mime_type =
      net::ExtractMimeTypeFromMediaType(media_type,
                                        /*accept_comma_separated=*/false);
  if (!mime_type) {
    return std::string();
  }
  if (MimeEquals(*mime_type, "image/png"))
    return "image/png";
  if (MimeEquals(*mime_type, "image/jpeg") ||
      MimeEquals(*mime_type, "image/jpg"))
    return "image/jpeg";
  if (MimeEquals(*mime_type, "image/bmp") ||
      MimeEquals(*mime_type, "image/x-ms-bmp"))
    return "image/bmp";
  if (MimeEquals(*mime_type, "image/webp"))
    return "image/webp";
  if (MimeEquals(*mime_type, "image/svg+xml"))
    return "image/svg+xml";
  return std::string();
}

bool IsSvgImageMime(std::string_view mime_type) {
  return net::MatchesMimeType("image/svg+xml", mime_type);
}

bool IsDataUrl(const std::string& url) {
  return url::FindAndCompareScheme(url, url::kDataScheme, nullptr);
}

StandaloneResourceResult DecodeDataImageUrl(const std::string& url) {
  if (!IsDataUrl(url)) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedScheme,
                       "not a data URL");
  }

  std::string parsed_mime_type;
  std::string parsed_charset;
  std::string data;
  if (!net::DataURL::Parse(GURL(url), &parsed_mime_type, &parsed_charset,
                           &data)) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "malformed data URL");
  }

  std::string mime_type = SupportedDataImageMime(parsed_mime_type);
  if (mime_type.empty()) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedMime,
                       "only PNG/JPEG/BMP/WebP/SVG data URLs are enabled", "");
  }
  if (data.empty()) {
    return ErrorResult(StandaloneResourceStatus::kDecodeFailed,
                       "data URL image payload is empty", mime_type);
  }

  StandaloneResourceResult result;
  result.source_kind = StandaloneResourceSourceKind::kDataUrl;
  result.mime_type = std::move(mime_type);
  result.cache_key = url;
  result.encoded_bytes.assign(data.begin(), data.end());
  if (IsSvgImageMime(result.mime_type)) {
    result.status = StandaloneResourceStatus::kUnsupportedMime;
    result.error = "SVG image rendering is unsupported in this standalone build";
    return result;
  }
  return DecodeOrClassifyImageBytes(std::move(result));
}

std::string StripFileUrlPrefix(const std::string& url) {
  std::string path = url;
  if (base::StartsWith(path, "file:///")) {
    path = path.substr(8);
  } else if (base::StartsWith(path, "file://")) {
    path = path.substr(7);
  }
#if defined(_WIN32)
  std::replace(path.begin(), path.end(), '/', '\\');
#endif
  return path;
}

bool HasScheme(const std::string& url) {
  url::Component scheme;
  return url::ExtractScheme(url, &scheme);
}

bool SchemeIs(const std::string& url, const char* lower_ascii_scheme) {
  return url::FindAndCompareScheme(url, lower_ascii_scheme, nullptr);
}

bool IsWithinRoot(const std::filesystem::path& path,
                  const std::filesystem::path& root) {
  const base::FilePath path_file(path.native());
  const base::FilePath root_file(root.native());
  return path_file == root_file || root_file.IsParent(path_file);
}

std::string SupportedImageMimeFromFile(const base::FilePath& path) {
  std::string mime_type;
  if (!net::GetWellKnownMimeTypeFromFile(path, &mime_type)) {
    return std::string();
  }
  return SupportedDataImageMime(mime_type);
}

StandaloneResourceResult DecodeLocalImage(const std::string& url) {
  if (SchemeIs(url, url::kHttpScheme) || SchemeIs(url, url::kHttpsScheme)) {
    return ErrorResult(StandaloneResourceStatus::kUnsupportedScheme,
                       "HTTP/HTTPS loading is disabled");
  }
  if (HasScheme(url) && !SchemeIs(url, url::kFileScheme)) {
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
  const bool is_file_url = SchemeIs(url, url::kFileScheme);
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
  const base::FilePath candidate_file_path(candidate.native());

  StandaloneResourceResult result;
  result.source_kind = is_file_url ? StandaloneResourceSourceKind::kFileUrl
                                   : StandaloneResourceSourceKind::kRelativeFile;
  result.mime_type = SupportedImageMimeFromFile(candidate_file_path);
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
  base::File::Info file_info;
  if (!base::GetFileInfo(candidate_file_path, &file_info) ||
      file_info.is_directory) {
    result.status = StandaloneResourceStatus::kNotFound;
    result.error = "local image file was not found";
    return result;
  }

  std::optional<std::vector<uint8_t>> file_bytes =
      base::ReadFileToBytes(candidate_file_path);
  if (!file_bytes) {
    result.status = StandaloneResourceStatus::kError;
    result.error = "failed to open local image file";
    return result;
  }
  result.encoded_bytes = std::move(*file_bytes);
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
  base::AutoLock auto_lock(DiagnosticsLock());
  const uint64_t context_id = NextContextId()++;
  MutableContexts().emplace(context_id, ResourceProviderContextState());
  return context_id;
}

void DestroyStandaloneResourceProviderContext(uint64_t context_id) {
  base::AutoLock auto_lock(DiagnosticsLock());
  MutableContexts().erase(context_id);
  if (g_current_context_id == context_id)
    g_current_context_id = 0;
}

void SetCurrentStandaloneResourceProviderContext(uint64_t context_id) {
  base::AutoLock auto_lock(DiagnosticsLock());
  if (context_id != 0 &&
      MutableContexts().find(context_id) == MutableContexts().end()) {
    context_id = 0;
  }
  g_current_context_id = context_id;
}

void SetStandaloneResourceProviderResourceRoot(std::string root_path) {
  base::AutoLock auto_lock(DiagnosticsLock());
  MutableResourceRoot() = std::move(root_path);
}

std::string GetStandaloneResourceProviderResourceRoot() {
  base::AutoLock auto_lock(DiagnosticsLock());
  return MutableResourceRoot();
}

void SetStandaloneResourceProviderDocumentBasePath(std::string base_path) {
  base::AutoLock auto_lock(DiagnosticsLock());
  MutableDocumentBasePath() = std::move(base_path);
}

std::string GetStandaloneResourceProviderDocumentBasePath() {
  base::AutoLock auto_lock(DiagnosticsLock());
  return MutableDocumentBasePath();
}

void SetStandaloneResourceProviderEmbedderProvider(
    std::shared_ptr<StandaloneResourceProvider> provider,
    uint32_t flags) {
  base::AutoLock auto_lock(DiagnosticsLock());
  ResourceProviderContextState& state = CurrentContextStateLocked();
  state.embedder_provider = std::move(provider);
  state.embedder_provider_flags = flags;
}

void ResetStandaloneResourceProviderDiagnostics() {
  base::AutoLock auto_lock(DiagnosticsLock());
  MutableDiagnostics() = StandaloneResourceProviderDiagnostics();
}

StandaloneResourceProviderDiagnostics GetStandaloneResourceProviderDiagnostics() {
  base::AutoLock auto_lock(DiagnosticsLock());
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
