// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_PERFETTO_TRACING_TRACED_VALUE_BLINK_TRAITS_H_
#define STANDALONE_RENDERER_STUBS_PERFETTO_TRACING_TRACED_VALUE_BLINK_TRAITS_H_

#include <utility>

#include "third_party/blink/renderer/core/css/invalidation/invalidation_set.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace perfetto {

inline void WriteIntoTracedValue(TracedValue context, const blink::String&) {
  std::move(context).WriteString("");
}

inline void WriteIntoTracedValue(TracedValue context,
                                 const blink::AtomicString&) {
  std::move(context).WriteString("");
}

inline void WriteIntoTracedValue(
    TracedValue context,
    const blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kIds>::Range&) {
  std::move(context).WriteString("");
}

inline void WriteIntoTracedValue(
    TracedValue context,
    const blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kClasses>::Range&) {
  std::move(context).WriteString("");
}

inline void WriteIntoTracedValue(
    TracedValue context,
    const blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kTagNames>::Range&) {
  std::move(context).WriteString("");
}

inline void WriteIntoTracedValue(
    TracedValue context,
    const blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kCustomPseudoNames>::Range&) {
  std::move(context).WriteString("");
}

inline void WriteIntoTracedValue(
    TracedValue context,
    const blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kAttributes>::Range&) {
  std::move(context).WriteString("");
}

template <>
struct TraceFormatTraits<blink::String> {
  static void WriteIntoTrace(TracedValue context, const blink::String&) {
    std::move(context).WriteString("");
  }
};

template <>
struct TraceFormatTraits<blink::AtomicString> {
  static void WriteIntoTrace(TracedValue context, const blink::AtomicString&) {
    std::move(context).WriteString("");
  }
};

template <>
struct TraceFormatTraits<
    blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kIds>::Range> {
  static void WriteIntoTrace(TracedValue context, const auto&) {
    std::move(context).WriteString("");
  }
};

template <>
struct TraceFormatTraits<
    blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kClasses>::Range> {
  static void WriteIntoTrace(TracedValue context, const auto&) {
    std::move(context).WriteString("");
  }
};

template <>
struct TraceFormatTraits<
    blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kTagNames>::Range> {
  static void WriteIntoTrace(TracedValue context, const auto&) {
    std::move(context).WriteString("");
  }
};

template <>
struct TraceFormatTraits<
    blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kCustomPseudoNames>::Range> {
  static void WriteIntoTrace(TracedValue context, const auto&) {
    std::move(context).WriteString("");
  }
};

template <>
struct TraceFormatTraits<
    blink::InvalidationSet::Backing<
        blink::InvalidationSet::BackingType::kAttributes>::Range> {
  static void WriteIntoTrace(TracedValue context, const auto&) {
    std::move(context).WriteString("");
  }
};

}  // namespace perfetto

#endif  // STANDALONE_RENDERER_STUBS_PERFETTO_TRACING_TRACED_VALUE_BLINK_TRAITS_H_
