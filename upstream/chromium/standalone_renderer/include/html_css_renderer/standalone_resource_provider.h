#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_STANDALONE_RESOURCE_PROVIDER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_STANDALONE_RESOURCE_PROVIDER_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "third_party/skia/include/core/SkImage.h"

namespace html_css_renderer {

enum class StandaloneResourceTypeHint {
  kUnknown,
  kImage,
  kStylesheet,
  kFont,
};

enum class StandaloneResourceInitiator {
  kOther,
  kImgElement,
  kCssBackgroundImage,
  kStylesheetLink,
  kFontFace,
};

enum class StandaloneResourceStatus {
  kSuccess,
  kNotFound,
  kUnsupportedScheme,
  kUnsupportedMime,
  kDecodeFailed,
  kBlockedByPolicy,
  kError,
};

enum class StandaloneResourceSourceKind {
  kUnsupported,
  kDataUrl,
  kFileUrl,
  kMemory,
};

struct StandaloneResourceRequest {
  std::string url;
  StandaloneResourceTypeHint type_hint = StandaloneResourceTypeHint::kUnknown;
  StandaloneResourceInitiator initiator = StandaloneResourceInitiator::kOther;
  std::string document_url;
  std::string base_url;
  std::string security_origin_summary;
  std::vector<std::string> accepted_mime_types;
};

struct StandaloneResourceResult {
  StandaloneResourceStatus status = StandaloneResourceStatus::kError;
  StandaloneResourceSourceKind source_kind =
      StandaloneResourceSourceKind::kUnsupported;
  std::string mime_type;
  std::vector<uint8_t> encoded_bytes;
  sk_sp<SkImage> decoded_image;
  int intrinsic_width = 0;
  int intrinsic_height = 0;
  std::string error;
  std::string cache_key;
  bool same_process_only = true;
};

struct StandaloneResourceProviderDiagnostics {
  int request_count = 0;
  int image_request_count = 0;
  int data_png_request_count = 0;
  int success_count = 0;
  int failure_count = 0;

  struct RequestDiagnostic {
    std::string url_prefix;
    std::string initiator;
    std::string mime_type;
    size_t encoded_bytes = 0;
    int decoded_width = 0;
    int decoded_height = 0;
    std::string status;
    std::string error;
  };

  std::vector<RequestDiagnostic> requests;
};

class StandaloneResourceProvider {
 public:
  virtual ~StandaloneResourceProvider() = default;
  virtual StandaloneResourceResult LoadResource(
      const StandaloneResourceRequest& request) = 0;
};

StandaloneResourceProvider& DefaultStandaloneResourceProvider();
void ResetStandaloneResourceProviderDiagnostics();
StandaloneResourceProviderDiagnostics GetStandaloneResourceProviderDiagnostics();

const char* ToString(StandaloneResourceStatus status);
const char* ToString(StandaloneResourceInitiator initiator);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_STANDALONE_RESOURCE_PROVIDER_H_
