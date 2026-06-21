// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cc/metrics/scroll_jank_v4_frame_stage_calculator.h"
#include "cc/metrics/scroll_jank_v4_tracing_recorder.h"

#include <memory>
#include <vector>

#include "cc/metrics/event_metrics.h"

namespace cc {
namespace {

class UnsupportedScrollJankV4FrameStageCalculator final
    : public ScrollJankV4FrameStageCalculator {
 public:
  ScrollJankV4Frame::StageList CalculateStages(
      EventMetrics::List& events_metrics,
      uint64_t result_id) override {
    return {};
  }

  ScrollJankV4Frame::StageList CalculateStages(
      std::vector<ScrollEventMetrics*>& events_metrics,
      uint64_t result_id) override {
    return {};
  }
};

}  // namespace

std::unique_ptr<ScrollJankV4FrameStageCalculator>
ScrollJankV4FrameStageCalculator::Create() {
  return std::make_unique<UnsupportedScrollJankV4FrameStageCalculator>();
}

void ScrollJankV4TracingRecorder::RecordTraceEvents(
    const ScrollJankV4Frame::Stage::ScrollUpdates& updates,
    const ScrollJankV4Frame::ScrollDamage& damage,
    const ScrollJankV4Frame::BeginFrameArgsForScrollJank& args,
    const ScrollJankV4Result& result) {}

}  // namespace cc
