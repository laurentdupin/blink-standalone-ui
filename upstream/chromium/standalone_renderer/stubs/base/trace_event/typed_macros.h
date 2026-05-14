#ifndef STANDALONE_RENDERER_STUBS_BASE_TRACE_EVENT_TYPED_MACROS_H_
#define STANDALONE_RENDERER_STUBS_BASE_TRACE_EVENT_TYPED_MACROS_H_

#ifndef TRACE_EVENT
#define TRACE_EVENT(...)
#endif
#ifndef TRACE_EVENT_BEGIN
#define TRACE_EVENT_BEGIN(...)
#endif
#ifndef TRACE_EVENT_END
#define TRACE_EVENT_END(...)
#endif
#ifndef TRACE_EVENT_INSTANT
#define TRACE_EVENT_INSTANT(...)
#endif
#ifndef TRACE_EVENT_CATEGORY_ENABLED
#define TRACE_EVENT_CATEGORY_ENABLED(category) false
#endif

#include "perfetto/tracing/data_source.h"

namespace trace_event {

class TraceSessionObserver {
 public:
  virtual ~TraceSessionObserver() = default;
  virtual void OnStart(const perfetto::DataSourceBase::StartArgs&) {}
};

}  // namespace trace_event

#endif  // STANDALONE_RENDERER_STUBS_BASE_TRACE_EVENT_TYPED_MACROS_H_
