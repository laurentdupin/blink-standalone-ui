#ifndef STANDALONE_RENDERER_STUBS_UI_ACCESSIBILITY_AX_ENUMS_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_UI_ACCESSIBILITY_AX_ENUMS_MOJOM_FORWARD_H_

namespace ax::mojom {

enum class AXTreeIDType {
  kUnknown,
  kToken,
};
class AXTreeIDDataView;
enum class Action { kNone };
enum class ActionFlags { kNone };
enum class AriaCurrentState { kNone };
enum class AriaNotificationInterrupt { kNone };
enum class AriaNotificationPriority { kNone };
enum class BoolAttribute { kNone };
enum class CheckedState { kNone };
enum class Command { kNone };
enum class DefaultActionVerb { kNone };
enum class DescriptionFrom { kNone };
enum class DetailsFrom { kNone };
enum class Event { kNone };
enum class EventFrom { kNone };
enum class FloatAttribute { kNone };
enum class Gesture { kNone };
enum class HasPopup { kNone };
enum class HighlightType { kNone };
enum class ImageAnnotationStatus { kNone };
enum class InputEventType { kNone };
enum class IntAttribute { kNone };
enum class IntListAttribute { kNone };
enum class InvalidState { kNone };
enum class IsPopup { kNone };
enum class ListStyle { kNone };
enum class MarkerType { kNone };
enum class Mutation { kNone };
enum class MoveDirection { kNone };
enum class NameFrom { kNone };
enum class Restriction { kNone };
enum class Role { kNone };
enum class ScrollAlignment { kNone };
enum class ScrollBehavior { kNone };
enum class SortDirection { kNone };
enum class State { kNone };
enum class StringAttribute { kNone };
enum class StringListAttribute { kNone };
enum class TextAffinity { kNone };
enum class TextAlign { kNone };
enum class TextBoundary { kNone };
enum class TextDecorationStyle { kNone };
enum class TextPosition { kNone };
enum class TextStyle { kNone };
enum class TreeOrder { kNone };
enum class WritingDirection { kNone };

}  // namespace ax::mojom

namespace ax::mojom::blink {

using Action = ::ax::mojom::Action;
using ActionFlags = ::ax::mojom::ActionFlags;
using AriaCurrentState = ::ax::mojom::AriaCurrentState;
using AriaNotificationInterrupt = ::ax::mojom::AriaNotificationInterrupt;
using AriaNotificationPriority = ::ax::mojom::AriaNotificationPriority;
using BoolAttribute = ::ax::mojom::BoolAttribute;
using CheckedState = ::ax::mojom::CheckedState;
using DefaultActionVerb = ::ax::mojom::DefaultActionVerb;
using DescriptionFrom = ::ax::mojom::DescriptionFrom;
using DetailsFrom = ::ax::mojom::DetailsFrom;
using Event = ::ax::mojom::Event;
using EventFrom = ::ax::mojom::EventFrom;
using FloatAttribute = ::ax::mojom::FloatAttribute;
using Gesture = ::ax::mojom::Gesture;
using HasPopup = ::ax::mojom::HasPopup;
using HighlightType = ::ax::mojom::HighlightType;
using ImageAnnotationStatus = ::ax::mojom::ImageAnnotationStatus;
using InputEventType = ::ax::mojom::InputEventType;
using IntAttribute = ::ax::mojom::IntAttribute;
using IntListAttribute = ::ax::mojom::IntListAttribute;
using InvalidState = ::ax::mojom::InvalidState;
using IsPopup = ::ax::mojom::IsPopup;
using ListStyle = ::ax::mojom::ListStyle;
using MarkerType = ::ax::mojom::MarkerType;
using Mutation = ::ax::mojom::Mutation;
using MoveDirection = ::ax::mojom::MoveDirection;
using Restriction = ::ax::mojom::Restriction;
using ScrollAlignment = ::ax::mojom::ScrollAlignment;
using ScrollBehavior = ::ax::mojom::ScrollBehavior;
using SortDirection = ::ax::mojom::SortDirection;
using State = ::ax::mojom::State;
using StringAttribute = ::ax::mojom::StringAttribute;
using StringListAttribute = ::ax::mojom::StringListAttribute;
using TextAffinity = ::ax::mojom::TextAffinity;
using TextAlign = ::ax::mojom::TextAlign;
using TextBoundary = ::ax::mojom::TextBoundary;
using TextDecorationStyle = ::ax::mojom::TextDecorationStyle;
using TextPosition = ::ax::mojom::TextPosition;
using TextStyle = ::ax::mojom::TextStyle;
using TreeOrder = ::ax::mojom::TreeOrder;
using WritingDirection = ::ax::mojom::WritingDirection;

}  // namespace ax::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_UI_ACCESSIBILITY_AX_ENUMS_MOJOM_FORWARD_H_
