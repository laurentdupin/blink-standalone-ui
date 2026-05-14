#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CLIPBOARD_CLIPBOARD_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CLIPBOARD_CLIPBOARD_MOJOM_BLINK_FORWARD_H_

#include <functional>
#include <memory>
#include <utility>

#include "mojo/public/cpp/base/big_buffer.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "url/gurl.h"

namespace blink::mojom::blink {

enum class ClipboardFormat {
  kPlaintext,
  kHtml,
  kSmartPaste,
  kBookmark,
};

enum class ClipboardBuffer {
  kStandard,
  kSelection,
};

struct ClipboardFiles {
  Vector<String> files;
};
using ClipboardFilesPtr = std::unique_ptr<ClipboardFiles>;

class ClipboardListener {
 public:
  virtual ~ClipboardListener() = default;
  virtual void OnClipboardDataChanged(const Vector<String>&, const absl::uint128&) {}
};

class ClipboardHost {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t kMaxFormatSize = 1024;
  static constexpr uint32_t kMaxDataSize = 1073741824;

  using ReadTextCallback = std::function<void(const String&)>;
  using ReadHtmlCallback =
      std::function<void(const String&, const GURL&, uint32_t, uint32_t)>;
  using ReadSvgCallback = std::function<void(const String&)>;
  using ReadAvailableCustomAndStandardFormatsCallback =
      std::function<void(Vector<String>)>;
  using ReadUnsanitizedCustomFormatCallback =
      std::function<void(mojo_base::BigBuffer)>;
#if BUILDFLAG(IS_MAC)
  using GetPlatformPermissionStateCallback = std::function<void(int)>;
#endif

  class Proxy_ {};
  template <typename ImplRefTraits>
  class Stub_ {};
};

}  // namespace blink::mojom::blink

namespace blink::mojom {

using ClipboardFormat = ::blink::mojom::blink::ClipboardFormat;
using ClipboardBuffer = ::blink::mojom::blink::ClipboardBuffer;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CLIPBOARD_CLIPBOARD_MOJOM_BLINK_FORWARD_H_
