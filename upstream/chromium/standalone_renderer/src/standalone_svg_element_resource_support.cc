#include "third_party/blink/renderer/core/svg/animation/smil_animation_sandwich.h"
#include "third_party/blink/renderer/core/svg/animation/smil_time_container.h"

#include "third_party/blink/public/mojom/webpreferences/web_preferences.mojom-blink.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/svg/svg_svg_element.h"

namespace blink {

SMILAnimationSandwich::SMILAnimationSandwich() = default;

void SMILAnimationSandwich::Add(SVGAnimationElement* animation) {
}

void SMILAnimationSandwich::Remove(SVGAnimationElement* animation) {
}

void SMILAnimationSandwich::UpdateActiveAnimationStack(SMILTime) {
  active_.Shrink(0);
}

bool SMILAnimationSandwich::ApplyAnimationValues() {
  return false;
}

void SMILAnimationSandwich::Trace(Visitor* visitor) const {
}

SMILTimeContainer::SMILTimeContainer(SVGSVGElement& owner)
    : frame_scheduling_state_(kIdle),
      started_(false),
      paused_(false),
      should_dispatch_events_(false),
      document_order_indexes_dirty_(false),
      is_updating_intervals_(false),
      wakeup_timer_(owner.GetDocument().GetTaskRunner(TaskType::kInternalDefault),
                    this,
                    &SMILTimeContainer::WakeupTimerFired),
      owner_svg_element_(&owner) {}

SMILTimeContainer::~SMILTimeContainer() = default;

void SMILTimeContainer::Schedule(SVGSMILElement*) {}
void SMILTimeContainer::Reschedule(SVGSMILElement*, SMILTime) {}
void SMILTimeContainer::Unschedule(SVGSMILElement*) {}

SMILTime SMILTimeContainer::Elapsed() const {
  return presentation_time_;
}

SMILTime SMILTimeContainer::LatestUpdatePresentationTime() const {
  return latest_update_time_;
}

bool SMILTimeContainer::IsPaused() const {
  return paused_;
}

bool SMILTimeContainer::IsStarted() const {
  return started_;
}

void SMILTimeContainer::Start() {
  started_ = true;
}

void SMILTimeContainer::Pause() {
  paused_ = true;
}

void SMILTimeContainer::Unpause() {
  paused_ = false;
}

void SMILTimeContainer::SetElapsed(SMILTime elapsed) {
  presentation_time_ = elapsed;
  latest_update_time_ = elapsed;
}

bool SMILTimeContainer::ServiceAnimations() {
  return false;
}

bool SMILTimeContainer::HasAnimations() const {
  return false;
}

void SMILTimeContainer::ResetDocumentTime() {
  presentation_time_ = SMILTime();
  latest_update_time_ = SMILTime();
}

void SMILTimeContainer::AdvanceFrameForTesting() {}

void SMILTimeContainer::Trace(Visitor* visitor) const {
  visitor->Trace(owner_svg_element_);
}

void SMILTimeContainer::DidAttachLayoutObject() {}

bool SMILTimeContainer::IsTimelineRunning() const {
  return started_ && !paused_;
}

void SMILTimeContainer::SynchronizeToDocumentTimeline() {}
void SMILTimeContainer::ScheduleAnimationFrame(base::TimeDelta, bool) {}
void SMILTimeContainer::CancelAnimationFrame() {}
void SMILTimeContainer::WakeupTimerFired(TimerBase*) {}

mojom::blink::ImageAnimationPolicy SMILTimeContainer::AnimationPolicy() const {
  return mojom::blink::ImageAnimationPolicy::kImageAnimationPolicyNoAnimation;
}

bool SMILTimeContainer::AnimationsDisabled() const {
  return true;
}

bool SMILTimeContainer::UpdateAnimationsAndScheduleFrameIfNeeded(
    TimingUpdate&) {
  return false;
}

void SMILTimeContainer::PrepareSeek(TimingUpdate&) {}
void SMILTimeContainer::ResetIntervals() {}
void SMILTimeContainer::UpdateIntervals(TimingUpdate&) {}
void SMILTimeContainer::UpdateTimedElements(TimingUpdate&) {}

bool SMILTimeContainer::ApplyTimedEffects(SMILTime) {
  return false;
}

SMILTime SMILTimeContainer::NextProgressTime(SMILTime presentation_time,
                                             bool) const {
  return presentation_time;
}

void SMILTimeContainer::ServiceOnNextFrame() {}
void SMILTimeContainer::ScheduleWakeUp(base::TimeDelta, FrameSchedulingState) {}

bool SMILTimeContainer::HasPendingSynchronization() const {
  return false;
}

void SMILTimeContainer::SetPresentationTime(SMILTime new_presentation_time) {
  presentation_time_ = new_presentation_time;
  latest_update_time_ = new_presentation_time;
}

SMILTime SMILTimeContainer::ClampPresentationTime(
    SMILTime presentation_time) const {
  return presentation_time;
}

void SMILTimeContainer::UpdateDocumentOrderIndexes() {
  document_order_indexes_dirty_ = false;
}

SVGSVGElement& SMILTimeContainer::OwnerSVGElement() const {
  return *owner_svg_element_;
}

Document& SMILTimeContainer::GetDocument() const {
  return owner_svg_element_->GetDocument();
}

}  // namespace blink
