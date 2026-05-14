// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_CORE_PROBE_SINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_CORE_PROBE_SINK_H_

#include "third_party/blink/renderer/platform/heap/garbage_collected.h"

namespace blink {

class InspectorIssueReporter;
class InspectorTraceEvents;
class Document;
class DocumentParser;
class ExecutionContext;
class WebString;

class CoreProbeSink : public GarbageCollected<CoreProbeSink> {
 public:
  enum AgentType {
    kInspectorLayerTreeAgent,
    kDevToolsSession,
  };

  bool HasAgentsGlobal(AgentType) const { return false; }
  bool HasDevToolsSessions() const { return false; }
  bool HasInspectorNetworkAgents() const { return false; }

  void AddInspectorIssueReporter(InspectorIssueReporter*) {}
  void RemoveInspectorIssueReporter(InspectorIssueReporter*) {}
  void AddInspectorTraceEvents(InspectorTraceEvents*) {}
  void RemoveInspectorTraceEvents(InspectorTraceEvents*) {}
  void Trace(Visitor*) const {}
};

namespace probe {

class ParseHTML {
 public:
  ParseHTML(Document*, DocumentParser*) {}
  ~ParseHTML() = default;
};

inline CoreProbeSink* ToCoreProbeSink(void*) {
  return nullptr;
}

template <typename T>
inline void GetDisabledImageTypes(ExecutionContext*, T*) {}

}  // namespace probe

}  // namespace blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_CORE_PROBE_SINK_H_
