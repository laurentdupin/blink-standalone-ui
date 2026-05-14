#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_STATE_PAGE_STATE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_STATE_PAGE_STATE_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {

enum class ScrollRestorationType;
struct DEPRECATED_FileSystemFile;
using DEPRECATED_FileSystemFilePtr = std::unique_ptr<DEPRECATED_FileSystemFile>;
struct File;
using FilePtr = std::unique_ptr<File>;
struct FrameState;
using FrameStatePtr = std::unique_ptr<FrameState>;
struct HttpBody;
using HttpBodyPtr = std::unique_ptr<HttpBody>;
struct PageState;
using PageStatePtr = std::unique_ptr<PageState>;
struct RequestBody;
using RequestBodyPtr = std::unique_ptr<RequestBody>;
struct ViewState;
using ViewStatePtr = std::unique_ptr<ViewState>;
class Element;

}  // namespace blink::mojom::blink

namespace blink::mojom {

using ScrollRestorationType = ::blink::mojom::blink::ScrollRestorationType;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_STATE_PAGE_STATE_MOJOM_BLINK_FORWARD_H_
