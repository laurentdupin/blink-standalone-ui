#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_WIDGET_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_WIDGET_MOJOM_SHARED_H_

namespace blink::mojom {

namespace blink {
class FrameWidget;
class FrameWidgetHost;
class Widget;
class WidgetHost;
}  // namespace blink

using FrameWidgetInterfaceBase = ::blink::mojom::blink::FrameWidget;
using FrameWidgetHostInterfaceBase = ::blink::mojom::blink::FrameWidgetHost;
using WidgetInterfaceBase = ::blink::mojom::blink::Widget;
using WidgetHostInterfaceBase = ::blink::mojom::blink::WidgetHost;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_WIDGET_MOJOM_SHARED_H_
