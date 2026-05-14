// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_INSTRUMENTATION_TRACING_TRACE_EVENT_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_INSTRUMENTATION_TRACING_TRACE_EVENT_H_

// Keep Blink/base call sites compiling without pulling Perfetto's generated
// category registry into the standalone renderer. The internal header owns the
// legacy constants used by base/trace_event, while the event macros below are
// forced to no-ops.
#ifndef PERFETTO_ENABLE_LEGACY_TRACE_EVENTS
#define PERFETTO_ENABLE_LEGACY_TRACE_EVENTS 1
#endif
#include "perfetto/tracing/internal/track_event_legacy.h"

#ifndef TRACE_EVENT_FLAG_MANGLE_ID
#define TRACE_EVENT_FLAG_MANGLE_ID 0
#endif

#ifndef TRACE_DISABLED_BY_DEFAULT
#define TRACE_DISABLED_BY_DEFAULT(category) category
#endif

#ifdef TRACE_EVENT0
#undef TRACE_EVENT0
#endif
#ifdef TRACE_EVENT
#undef TRACE_EVENT
#endif
#define TRACE_EVENT(...) \
  do {                  \
  } while (false)
#define TRACE_EVENT0(...) \
  do {                   \
  } while (false)
#ifdef TRACE_EVENT1
#undef TRACE_EVENT1
#endif
#define TRACE_EVENT1(...) \
  do {                   \
  } while (false)
#ifdef TRACE_EVENT2
#undef TRACE_EVENT2
#endif
#define TRACE_EVENT2(...) \
  do {                   \
  } while (false)
#ifdef TRACE_EVENT_INSTANT
#undef TRACE_EVENT_INSTANT
#endif
#define TRACE_EVENT_INSTANT(...) \
  do {                          \
  } while (false)
#ifdef TRACE_EVENT_INSTANT0
#undef TRACE_EVENT_INSTANT0
#endif
#define TRACE_EVENT_INSTANT0(...) \
  do {                           \
  } while (false)
#ifdef TRACE_EVENT_INSTANT1
#undef TRACE_EVENT_INSTANT1
#endif
#define TRACE_EVENT_INSTANT1(...) \
  do {                           \
  } while (false)
#ifdef TRACE_EVENT_INSTANT2
#undef TRACE_EVENT_INSTANT2
#endif
#define TRACE_EVENT_INSTANT2(...) \
  do {                           \
  } while (false)
#ifdef TRACE_EVENT_BEGIN0
#undef TRACE_EVENT_BEGIN0
#endif
#define TRACE_EVENT_BEGIN0(...) \
  do {                         \
  } while (false)
#ifdef TRACE_EVENT_BEGIN1
#undef TRACE_EVENT_BEGIN1
#endif
#define TRACE_EVENT_BEGIN1(...) \
  do {                         \
  } while (false)
#ifdef TRACE_EVENT_BEGIN2
#undef TRACE_EVENT_BEGIN2
#endif
#define TRACE_EVENT_BEGIN2(...) \
  do {                         \
  } while (false)
#ifdef TRACE_EVENT_END0
#undef TRACE_EVENT_END0
#endif
#define TRACE_EVENT_END0(...) \
  do {                       \
  } while (false)
#ifdef TRACE_EVENT_END1
#undef TRACE_EVENT_END1
#endif
#define TRACE_EVENT_END1(...) \
  do {                       \
  } while (false)
#ifdef TRACE_EVENT_END2
#undef TRACE_EVENT_END2
#endif
#define TRACE_EVENT_END2(...) \
  do {                       \
  } while (false)

#ifdef TRACE_EVENT_BEGIN
#undef TRACE_EVENT_BEGIN
#endif
#define TRACE_EVENT_BEGIN(...) \
  do {                        \
  } while (false)
#ifdef TRACE_EVENT_END
#undef TRACE_EVENT_END
#endif
#define TRACE_EVENT_END(...) \
  do {                      \
  } while (false)

#ifdef TRACE_EVENT_WITH_CATEGORIES
#undef TRACE_EVENT_WITH_CATEGORIES
#endif
#define TRACE_EVENT_WITH_CATEGORIES(...) \
  do {                                  \
  } while (false)
#ifdef TRACE_EVENT_INSTANT_WITH_CATEGORIES
#undef TRACE_EVENT_INSTANT_WITH_CATEGORIES
#endif
#define TRACE_EVENT_INSTANT_WITH_CATEGORIES(...) \
  do {                                          \
  } while (false)
#ifdef TRACE_EVENT_INSTANT_WITH_TIMESTAMP0
#undef TRACE_EVENT_INSTANT_WITH_TIMESTAMP0
#endif
#define TRACE_EVENT_INSTANT_WITH_TIMESTAMP0(...) \
  do {                                          \
  } while (false)
#ifdef TRACE_EVENT_MARK_WITH_TIMESTAMP1
#undef TRACE_EVENT_MARK_WITH_TIMESTAMP1
#endif
#define TRACE_EVENT_MARK_WITH_TIMESTAMP1(...) \
  do {                                       \
  } while (false)
#ifdef TRACE_EVENT_MARK_WITH_TIMESTAMP2
#undef TRACE_EVENT_MARK_WITH_TIMESTAMP2
#endif
#define TRACE_EVENT_MARK_WITH_TIMESTAMP2(...) \
  do {                                       \
  } while (false)
#ifdef TRACE_EVENT_COPY_NESTABLE_ASYNC_BEGIN2
#undef TRACE_EVENT_COPY_NESTABLE_ASYNC_BEGIN2
#endif
#define TRACE_EVENT_COPY_NESTABLE_ASYNC_BEGIN2(...) \
  do {                                             \
  } while (false)
#ifdef TRACE_EVENT_COPY_NESTABLE_ASYNC_END0
#undef TRACE_EVENT_COPY_NESTABLE_ASYNC_END0
#endif
#define TRACE_EVENT_COPY_NESTABLE_ASYNC_END0(...) \
  do {                                           \
  } while (false)
#ifdef TRACE_EVENT_OBJECT_CREATED_WITH_ID
#undef TRACE_EVENT_OBJECT_CREATED_WITH_ID
#endif
#define TRACE_EVENT_OBJECT_CREATED_WITH_ID(...) \
  do {                                         \
  } while (false)
#ifdef TRACE_EVENT_OBJECT_DELETED_WITH_ID
#undef TRACE_EVENT_OBJECT_DELETED_WITH_ID
#endif
#define TRACE_EVENT_OBJECT_DELETED_WITH_ID(...) \
  do {                                         \
  } while (false)
#ifdef TRACE_EVENT_OBJECT_SNAPSHOT_WITH_ID
#undef TRACE_EVENT_OBJECT_SNAPSHOT_WITH_ID
#endif
#define TRACE_EVENT_OBJECT_SNAPSHOT_WITH_ID(...) \
  do {                                          \
  } while (false)

#ifdef TRACE_EVENT_IS_NEW_TRACE
#undef TRACE_EVENT_IS_NEW_TRACE
#endif
#define TRACE_EVENT_IS_NEW_TRACE() false
#ifdef TRACE_EVENT_CATEGORY_GROUP_ENABLED
#undef TRACE_EVENT_CATEGORY_GROUP_ENABLED
#endif
#define STANDALONE_TRACE_EVENT_CATEGORY_GROUP_ENABLED1(category_group) false
#define STANDALONE_TRACE_EVENT_CATEGORY_GROUP_ENABLED2(category_group, ret) \
  (*(ret) = false)
#define STANDALONE_TRACE_EVENT_CATEGORY_GROUP_ENABLED_SELECT(_1, _2, NAME, ...) \
  NAME
#define TRACE_EVENT_CATEGORY_GROUP_ENABLED(...)                                \
  STANDALONE_TRACE_EVENT_CATEGORY_GROUP_ENABLED_SELECT(                        \
      __VA_ARGS__, STANDALONE_TRACE_EVENT_CATEGORY_GROUP_ENABLED2,             \
      STANDALONE_TRACE_EVENT_CATEGORY_GROUP_ENABLED1)                          \
  (__VA_ARGS__)
#ifdef TRACE_EVENT_API_GET_CATEGORY_GROUP_ENABLED
#undef TRACE_EVENT_API_GET_CATEGORY_GROUP_ENABLED
#endif
#define TRACE_EVENT_API_GET_CATEGORY_GROUP_ENABLED(category_group) nullptr

#ifdef TRACE_EVENT_CATEGORY_ENABLED
#undef TRACE_EVENT_CATEGORY_ENABLED
#endif
#define STANDALONE_TRACE_EVENT_CATEGORY_ENABLED1(category_group) false
#define STANDALONE_TRACE_EVENT_CATEGORY_ENABLED2(category_group, ret) \
  (*(ret) = false)
#define STANDALONE_TRACE_EVENT_CATEGORY_ENABLED_SELECT(_1, _2, NAME, ...) NAME
#define TRACE_EVENT_CATEGORY_ENABLED(...)                                \
  STANDALONE_TRACE_EVENT_CATEGORY_ENABLED_SELECT(                        \
      __VA_ARGS__, STANDALONE_TRACE_EVENT_CATEGORY_ENABLED2,             \
      STANDALONE_TRACE_EVENT_CATEGORY_ENABLED1)                          \
  (__VA_ARGS__)

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_INSTRUMENTATION_TRACING_TRACE_EVENT_H_
