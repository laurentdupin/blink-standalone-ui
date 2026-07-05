// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Phase 1 uses Mojo public value/handle vocabulary inside Blink-generated
// structs, but does not import Mojo Core or browser IPC runtime. This installs
// a minimal in-process thunk table so local scoped handles can be constructed
// and destroyed without enabling external services.

#include "mojo/public/c/system/thunks.h"

#include <algorithm>
#include <atomic>
#include <deque>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <unordered_map>
#include <vector>

#include "base/no_destructor.h"
#include "base/synchronization/lock.h"
#include "base/task/single_thread_task_runner.h"
#include "base/time/time.h"
#if defined(BLINK_STANDALONE_HAVE_MOJO_CORE_PROOF)
#include "mojo/core/entrypoints.h"
#endif

namespace {

class StandalonePhase1SingleThreadTaskRunner final
    : public base::SingleThreadTaskRunner {
 public:
  bool PostDelayedTask(const base::Location&,
                       base::OnceClosure task,
                       base::TimeDelta) override {
    std::move(task).Run();
    return true;
  }

  bool PostNonNestableDelayedTask(const base::Location&,
                                  base::OnceClosure task,
                                  base::TimeDelta) override {
    std::move(task).Run();
    return true;
  }

  bool RunsTasksInCurrentSequence() const override { return true; }
};

scoped_refptr<base::SingleThreadTaskRunner> StandalonePhase1TaskRunner() {
  static scoped_refptr<base::SingleThreadTaskRunner>* runner =
      new scoped_refptr<base::SingleThreadTaskRunner>(
          base::MakeRefCounted<StandalonePhase1SingleThreadTaskRunner>());
  return *runner;
}

void EnsureStandaloneCurrentDefaultTaskRunner() {
  static std::unique_ptr<base::SingleThreadTaskRunner::CurrentDefaultHandle>*
      handle = new std::unique_ptr<
          base::SingleThreadTaskRunner::CurrentDefaultHandle>();
  if (!base::SingleThreadTaskRunner::HasCurrentDefault()) {
    *handle = std::make_unique<base::SingleThreadTaskRunner::CurrentDefaultHandle>(
        StandalonePhase1TaskRunner());
  }
}

struct StandaloneMessage {
  std::vector<uint8_t> data;
  std::vector<MojoHandle> handles;
  uintptr_t context = 0;
  MojoMessageContextDestructor context_destructor = nullptr;
};

struct StandaloneBuffer {
  explicit StandaloneBuffer(uint64_t size) : bytes(static_cast<size_t>(size)) {}
  std::vector<uint8_t> bytes;
};

struct StandaloneMessagePipeEndpoint {
  MojoHandle peer = MOJO_HANDLE_INVALID;
  bool peer_closed = false;
  std::deque<MojoMessageHandle> queue;
};

struct StandaloneTrapTrigger {
  MojoHandle handle = MOJO_HANDLE_INVALID;
  MojoHandleSignals signals = 0;
  MojoTriggerCondition condition = MOJO_TRIGGER_CONDITION_SIGNALS_SATISFIED;
  uintptr_t context = 0;
};

struct StandaloneTrap {
  MojoTrapEventHandler handler = nullptr;
  bool armed = false;
  std::vector<StandaloneTrapTrigger> triggers;
};

enum class HandleKind {
  kMessagePipe,
  kSharedBuffer,
  kTrap,
  kPlatform,
  kInvitation,
};

struct HandleRecord {
  HandleKind kind;
  StandaloneBuffer* buffer = nullptr;
  StandaloneMessagePipeEndpoint* endpoint = nullptr;
  StandaloneTrap* trap = nullptr;
};

base::Lock& HandleLock() {
  static base::NoDestructor<base::Lock> lock;
  return *lock;
}

std::unordered_map<MojoHandle, HandleRecord>& Handles() {
  static auto* handles = new std::unordered_map<MojoHandle, HandleRecord>();
  return *handles;
}

MojoHandle NextHandle() {
  static std::atomic<uintptr_t> next{1};
  return next.fetch_add(1, std::memory_order_relaxed);
}

MojoResult Unsupported() {
  return MOJO_RESULT_UNIMPLEMENTED;
}

MojoResult StandaloneClose(MojoHandle handle);

void DestroyStandaloneMessage(MojoMessageHandle message) {
  if (message == MOJO_MESSAGE_HANDLE_INVALID)
    return;
  auto* standalone_message =
      reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
  if (standalone_message->context_destructor && standalone_message->context)
    standalone_message->context_destructor(standalone_message->context);
  std::vector<MojoHandle> handles = std::move(standalone_message->handles);
  delete standalone_message;
  for (MojoHandle handle : handles) {
    if (handle != MOJO_HANDLE_INVALID)
      StandaloneClose(handle);
  }
}

MojoHandleSignalsState SignalsStateForHandleLocked(MojoHandle handle) {
  MojoHandleSignalsState state = {};
  auto it = Handles().find(handle);
  if (it == Handles().end())
    return state;
  const HandleRecord& record = it->second;
  switch (record.kind) {
    case HandleKind::kMessagePipe: {
      const StandaloneMessagePipeEndpoint* endpoint = record.endpoint;
      if (!endpoint)
        break;
      if (!endpoint->queue.empty())
        state.satisfied_signals |= MOJO_HANDLE_SIGNAL_READABLE;
      if (!endpoint->peer_closed)
        state.satisfied_signals |= MOJO_HANDLE_SIGNAL_WRITABLE;
      if (endpoint->peer_closed)
        state.satisfied_signals |= MOJO_HANDLE_SIGNAL_PEER_CLOSED;

      if (!endpoint->peer_closed || !endpoint->queue.empty())
        state.satisfiable_signals |= MOJO_HANDLE_SIGNAL_READABLE;
      if (!endpoint->peer_closed)
        state.satisfiable_signals |= MOJO_HANDLE_SIGNAL_WRITABLE;
      state.satisfiable_signals |= MOJO_HANDLE_SIGNAL_PEER_CLOSED;
      break;
    }
    case HandleKind::kSharedBuffer:
    case HandleKind::kPlatform:
    case HandleKind::kInvitation:
    case HandleKind::kTrap:
      state.satisfied_signals = MOJO_HANDLE_SIGNAL_WRITABLE;
      state.satisfiable_signals = MOJO_HANDLE_SIGNAL_WRITABLE;
      break;
  }
  return state;
}

bool TriggerIsReadyLocked(const StandaloneTrapTrigger& trigger,
                          MojoResult* result,
                          MojoHandleSignalsState* state) {
  *state = SignalsStateForHandleLocked(trigger.handle);
  if (trigger.condition == MOJO_TRIGGER_CONDITION_SIGNALS_SATISFIED) {
    if (state->satisfied_signals & trigger.signals) {
      *result = MOJO_RESULT_OK;
      return true;
    }
    if ((state->satisfiable_signals & trigger.signals) != trigger.signals) {
      *result = MOJO_RESULT_FAILED_PRECONDITION;
      return true;
    }
    return false;
  }

  if ((state->satisfied_signals & trigger.signals) != trigger.signals) {
    *result = MOJO_RESULT_OK;
    return true;
  }
  return false;
}

struct PendingTrapEvent {
  MojoTrapEventHandler handler = nullptr;
  MojoTrapEvent event = {};
};

MojoTrapEvent BuildTrapEvent(uintptr_t context,
                             MojoResult result,
                             MojoHandleSignalsState state,
                             MojoTrapEventFlags flags) {
  MojoTrapEvent event = {};
  event.struct_size = sizeof(event);
  event.flags = flags;
  event.trigger_context = context;
  event.result = result;
  event.signals_state = state;
  return event;
}

void CollectReadyTrapEventsLocked(MojoHandle changed_handle,
                                  MojoTrapEventFlags flags,
                                  std::vector<PendingTrapEvent>* events) {
  for (auto& [trap_handle, record] : Handles()) {
    if (record.kind != HandleKind::kTrap || !record.trap ||
        !record.trap->armed || !record.trap->handler) {
      continue;
    }
    for (const StandaloneTrapTrigger& trigger : record.trap->triggers) {
      if (trigger.handle != changed_handle)
        continue;
      MojoResult result = MOJO_RESULT_OK;
      MojoHandleSignalsState state = {};
      if (!TriggerIsReadyLocked(trigger, &result, &state))
        continue;
      record.trap->armed = false;
      events->push_back({record.trap->handler,
                         BuildTrapEvent(trigger.context, result, state,
                                        flags)});
    }
  }
}

void CollectCancelledTrapEventsForHandleLocked(
    MojoHandle closed_handle,
    std::vector<PendingTrapEvent>* events) {
  for (auto& [trap_handle, record] : Handles()) {
    if (record.kind != HandleKind::kTrap || !record.trap ||
        !record.trap->handler) {
      continue;
    }
    auto& triggers = record.trap->triggers;
    for (auto it = triggers.begin(); it != triggers.end();) {
      if (it->handle != closed_handle) {
        ++it;
        continue;
      }
      events->push_back(
          {record.trap->handler,
           BuildTrapEvent(it->context, MOJO_RESULT_CANCELLED, {},
                          MOJO_TRAP_EVENT_FLAG_WITHIN_API_CALL)});
      it = triggers.erase(it);
    }
  }
}

void DispatchTrapEvents(const std::vector<PendingTrapEvent>& events) {
  for (const PendingTrapEvent& event : events) {
    if (event.handler)
      event.handler(&event.event);
  }
}

MojoResult StandaloneInitialize(const MojoInitializeOptions*) {
  return MOJO_RESULT_OK;
}

MojoTimeTicks StandaloneGetTimeTicksNow() {
  return 0;
}

MojoResult StandaloneClose(MojoHandle handle) {
  if (handle == MOJO_HANDLE_INVALID)
    return MOJO_RESULT_INVALID_ARGUMENT;
  std::vector<PendingTrapEvent> events;
  std::deque<MojoMessageHandle> messages_to_destroy;
  {
    base::AutoLock auto_lock(HandleLock());
    auto it = Handles().find(handle);
    if (it == Handles().end())
      return MOJO_RESULT_INVALID_ARGUMENT;
    CollectCancelledTrapEventsForHandleLocked(handle, &events);
    if (it->second.endpoint) {
      while (!it->second.endpoint->queue.empty()) {
        messages_to_destroy.push_back(it->second.endpoint->queue.front());
        it->second.endpoint->queue.pop_front();
      }
      const MojoHandle peer = it->second.endpoint->peer;
      if (peer != MOJO_HANDLE_INVALID) {
        auto peer_it = Handles().find(peer);
        if (peer_it != Handles().end() && peer_it->second.endpoint) {
          peer_it->second.endpoint->peer = MOJO_HANDLE_INVALID;
          peer_it->second.endpoint->peer_closed = true;
          CollectReadyTrapEventsLocked(
              peer, MOJO_TRAP_EVENT_FLAG_WITHIN_API_CALL, &events);
        }
      }
    }
    if (it->second.trap && it->second.trap->handler) {
      for (const StandaloneTrapTrigger& trigger : it->second.trap->triggers) {
        events.push_back(
            {it->second.trap->handler,
             BuildTrapEvent(trigger.context, MOJO_RESULT_CANCELLED, {},
                            MOJO_TRAP_EVENT_FLAG_WITHIN_API_CALL)});
      }
    }
    delete it->second.buffer;
    delete it->second.endpoint;
    delete it->second.trap;
    Handles().erase(it);
  }
  for (MojoMessageHandle message : messages_to_destroy)
    DestroyStandaloneMessage(message);
  DispatchTrapEvents(events);
  return MOJO_RESULT_OK;
}

MojoResult StandaloneQueryHandleSignalsState(
    MojoHandle handle,
    MojoHandleSignalsState* signals_state) {
  if (!signals_state)
    return MOJO_RESULT_INVALID_ARGUMENT;
  base::AutoLock auto_lock(HandleLock());
  if (Handles().find(handle) == Handles().end())
    return MOJO_RESULT_INVALID_ARGUMENT;
  *signals_state = SignalsStateForHandleLocked(handle);
  return MOJO_RESULT_OK;
}

MojoResult StandaloneCreateMessagePipe(const MojoCreateMessagePipeOptions*,
                                       MojoHandle* handle0,
                                       MojoHandle* handle1) {
  if (!handle0 || !handle1)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle first = NextHandle();
  MojoHandle second = NextHandle();
  {
    base::AutoLock auto_lock(HandleLock());
    auto* first_endpoint = new StandaloneMessagePipeEndpoint();
    auto* second_endpoint = new StandaloneMessagePipeEndpoint();
    first_endpoint->peer = second;
    second_endpoint->peer = first;
    Handles()[first] = {HandleKind::kMessagePipe, nullptr, first_endpoint,
                        nullptr};
    Handles()[second] = {HandleKind::kMessagePipe, nullptr, second_endpoint,
                         nullptr};
  }
  *handle0 = first;
  *handle1 = second;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneWriteMessage(MojoHandle handle,
                                  MojoMessageHandle message,
                                  const MojoWriteMessageOptions*) {
  std::vector<PendingTrapEvent> events;
  {
    base::AutoLock auto_lock(HandleLock());
    auto it = Handles().find(handle);
    if (it == Handles().end() || it->second.kind != HandleKind::kMessagePipe ||
        !it->second.endpoint) {
      return MOJO_RESULT_INVALID_ARGUMENT;
    }
    const MojoHandle peer = it->second.endpoint->peer;
    if (peer == MOJO_HANDLE_INVALID || it->second.endpoint->peer_closed)
      return MOJO_RESULT_FAILED_PRECONDITION;
    auto peer_it = Handles().find(peer);
    if (peer_it == Handles().end() || !peer_it->second.endpoint)
      return MOJO_RESULT_FAILED_PRECONDITION;
    peer_it->second.endpoint->queue.push_back(message);
    CollectReadyTrapEventsLocked(peer, MOJO_TRAP_EVENT_FLAG_WITHIN_API_CALL,
                                 &events);
  }
  DispatchTrapEvents(events);
  return MOJO_RESULT_OK;
}

MojoResult StandaloneReadMessage(MojoHandle handle,
                                 const MojoReadMessageOptions*,
                                 MojoMessageHandle* message) {
  if (!message)
    return MOJO_RESULT_INVALID_ARGUMENT;
  base::AutoLock auto_lock(HandleLock());
  auto it = Handles().find(handle);
  if (it == Handles().end() || it->second.kind != HandleKind::kMessagePipe ||
      !it->second.endpoint) {
    return MOJO_RESULT_INVALID_ARGUMENT;
  }
  if (!it->second.endpoint->queue.empty()) {
    *message = it->second.endpoint->queue.front();
    it->second.endpoint->queue.pop_front();
    return MOJO_RESULT_OK;
  }
  if (it->second.endpoint->peer_closed)
    return MOJO_RESULT_FAILED_PRECONDITION;
  return MOJO_RESULT_SHOULD_WAIT;
}

MojoResult StandaloneFuseMessagePipes(MojoHandle,
                                      MojoHandle,
                                      const MojoFuseMessagePipesOptions*) {
  return MOJO_RESULT_UNIMPLEMENTED;
}

MojoResult StandaloneCreateMessage(const MojoCreateMessageOptions*,
                                   MojoMessageHandle* message) {
  if (!message)
    return MOJO_RESULT_INVALID_ARGUMENT;
  *message = reinterpret_cast<MojoMessageHandle>(new StandaloneMessage());
  return MOJO_RESULT_OK;
}

MojoResult StandaloneDestroyMessage(MojoMessageHandle message) {
  if (message == MOJO_MESSAGE_HANDLE_INVALID)
    return MOJO_RESULT_INVALID_ARGUMENT;
  DestroyStandaloneMessage(message);
  return MOJO_RESULT_OK;
}

MojoResult StandaloneSerializeMessage(MojoMessageHandle,
                                      const MojoSerializeMessageOptions*) {
  return MOJO_RESULT_NOT_FOUND;
}

MojoResult StandaloneAppendMessageData(MojoMessageHandle message,
                                       uint32_t payload_size,
                                       const MojoHandle* handles,
                                       uint32_t num_handles,
                                       const MojoAppendMessageDataOptions*,
                                       void** buffer,
                                       uint32_t* buffer_size) {
  if (message == MOJO_MESSAGE_HANDLE_INVALID)
    return MOJO_RESULT_INVALID_ARGUMENT;
  if (num_handles && !handles)
    return MOJO_RESULT_INVALID_ARGUMENT;
  auto* standalone_message =
      reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
  const size_t old_size = standalone_message->data.size();
  standalone_message->data.resize(old_size + payload_size);
  if (num_handles) {
    standalone_message->handles.insert(standalone_message->handles.end(),
                                       handles, handles + num_handles);
  }
  if (buffer)
    *buffer = standalone_message->data.empty() ? nullptr
                                               : standalone_message->data.data();
  if (buffer_size)
    *buffer_size = static_cast<uint32_t>(standalone_message->data.size());
  return MOJO_RESULT_OK;
}

MojoResult StandaloneGetMessageData(MojoMessageHandle message,
                                    const MojoGetMessageDataOptions*,
                                    void** buffer,
                                    uint32_t* num_bytes,
                                    MojoHandle* handles,
                                    uint32_t* num_handles) {
  if (message == MOJO_MESSAGE_HANDLE_INVALID)
    return MOJO_RESULT_INVALID_ARGUMENT;
  auto* standalone_message =
      reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
  if (buffer)
    *buffer = standalone_message->data.data();
  if (num_bytes)
    *num_bytes = static_cast<uint32_t>(standalone_message->data.size());
  if (num_handles) {
    uint32_t available = *num_handles;
    *num_handles = static_cast<uint32_t>(standalone_message->handles.size());
    if (handles && available >= *num_handles) {
      std::memcpy(handles, standalone_message->handles.data(),
                  *num_handles * sizeof(MojoHandle));
      standalone_message->handles.clear();
    } else if (*num_handles) {
      return MOJO_RESULT_RESOURCE_EXHAUSTED;
    }
  }
  return MOJO_RESULT_OK;
}

MojoResult StandaloneSetMessageContext(MojoMessageHandle message,
                                       uintptr_t context,
                                       MojoMessageContextSerializer,
                                       MojoMessageContextDestructor destructor,
                                       const MojoSetMessageContextOptions*) {
  if (message == MOJO_MESSAGE_HANDLE_INVALID)
    return MOJO_RESULT_INVALID_ARGUMENT;
  auto* standalone_message =
      reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
  standalone_message->context = context;
  standalone_message->context_destructor = destructor;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneGetMessageContext(MojoMessageHandle message,
                                       const MojoGetMessageContextOptions*,
                                       uintptr_t* context) {
  if (message == MOJO_MESSAGE_HANDLE_INVALID || !context)
    return MOJO_RESULT_INVALID_ARGUMENT;
  auto* standalone_message =
      reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
  if (!standalone_message->context)
    return MOJO_RESULT_NOT_FOUND;
  *context = standalone_message->context;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneNotifyBadMessage(MojoMessageHandle,
                                      const char*,
                                      uint32_t,
                                      const MojoNotifyBadMessageOptions*) {
  return MOJO_RESULT_OK;
}

MojoResult StandaloneCreateDataPipe(const MojoCreateDataPipeOptions*,
                                    MojoHandle* producer,
                                    MojoHandle* consumer) {
  if (!producer || !consumer)
    return MOJO_RESULT_INVALID_ARGUMENT;
  *producer = MOJO_HANDLE_INVALID;
  *consumer = MOJO_HANDLE_INVALID;
  return MOJO_RESULT_UNIMPLEMENTED;
}

MojoResult StandaloneWriteData(MojoHandle,
                               const void*,
                               uint32_t*,
                               const MojoWriteDataOptions*) {
  return Unsupported();
}

MojoResult StandaloneBeginWriteData(MojoHandle,
                                    const MojoBeginWriteDataOptions*,
                                    void**,
                                    uint32_t*) {
  return Unsupported();
}

MojoResult StandaloneEndWriteData(MojoHandle,
                                  uint32_t,
                                  const MojoEndWriteDataOptions*) {
  return Unsupported();
}

MojoResult StandaloneReadData(MojoHandle,
                              const MojoReadDataOptions*,
                              void*,
                              uint32_t*) {
  return Unsupported();
}

MojoResult StandaloneBeginReadData(MojoHandle,
                                   const MojoBeginReadDataOptions*,
                                   const void**,
                                   uint32_t*) {
  return Unsupported();
}

MojoResult StandaloneEndReadData(MojoHandle,
                                 uint32_t,
                                 const MojoEndReadDataOptions*) {
  return Unsupported();
}

MojoResult StandaloneCreateSharedBuffer(uint64_t size,
                                        const MojoCreateSharedBufferOptions*,
                                        MojoHandle* handle) {
  if (!handle)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle new_handle = NextHandle();
  {
    base::AutoLock auto_lock(HandleLock());
    Handles()[new_handle] = {HandleKind::kSharedBuffer,
                             new StandaloneBuffer(size), nullptr, nullptr};
  }
  *handle = new_handle;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneDuplicateBufferHandle(
    MojoHandle handle,
    const MojoDuplicateBufferHandleOptions*,
    MojoHandle* new_handle) {
  if (!new_handle)
    return MOJO_RESULT_INVALID_ARGUMENT;
  base::AutoLock auto_lock(HandleLock());
  auto it = Handles().find(handle);
  if (it == Handles().end() || !it->second.buffer)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle duplicate = NextHandle();
  Handles()[duplicate] = {HandleKind::kSharedBuffer,
                          new StandaloneBuffer(*it->second.buffer), nullptr,
                          nullptr};
  *new_handle = duplicate;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneMapBuffer(MojoHandle handle,
                               uint64_t offset,
                               uint64_t size,
                               const MojoMapBufferOptions*,
                               void** buffer) {
  if (!buffer)
    return MOJO_RESULT_INVALID_ARGUMENT;
  base::AutoLock auto_lock(HandleLock());
  auto it = Handles().find(handle);
  if (it == Handles().end() || !it->second.buffer)
    return MOJO_RESULT_INVALID_ARGUMENT;
  if (offset + size > it->second.buffer->bytes.size())
    return MOJO_RESULT_OUT_OF_RANGE;
  *buffer = it->second.buffer->bytes.data() + offset;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneUnmapBuffer(void*) {
  return MOJO_RESULT_OK;
}

MojoResult StandaloneGetBufferInfo(MojoHandle handle,
                                   const MojoGetBufferInfoOptions*,
                                   MojoSharedBufferInfo* info) {
  if (!info)
    return MOJO_RESULT_INVALID_ARGUMENT;
  base::AutoLock auto_lock(HandleLock());
  auto it = Handles().find(handle);
  if (it == Handles().end() || !it->second.buffer)
    return MOJO_RESULT_INVALID_ARGUMENT;
  info->struct_size = sizeof(*info);
  info->size = it->second.buffer->bytes.size();
  return MOJO_RESULT_OK;
}

MojoResult StandaloneCreateTrap(MojoTrapEventHandler handler,
                                const MojoCreateTrapOptions*,
                                MojoHandle* trap) {
  if (!trap)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle handle = NextHandle();
  {
    base::AutoLock auto_lock(HandleLock());
    Handles()[handle] = {HandleKind::kTrap, nullptr, nullptr,
                         new StandaloneTrap{handler}};
  }
  *trap = handle;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneAddTrigger(MojoHandle trap_handle,
                                MojoHandle handle,
                                MojoHandleSignals signals,
                                MojoTriggerCondition condition,
                                uintptr_t context,
                                const MojoAddTriggerOptions*) {
  base::AutoLock auto_lock(HandleLock());
  auto trap_it = Handles().find(trap_handle);
  auto handle_it = Handles().find(handle);
  if (trap_it == Handles().end() || trap_it->second.kind != HandleKind::kTrap ||
      !trap_it->second.trap || handle_it == Handles().end() ||
      handle_it->second.kind != HandleKind::kMessagePipe) {
    return MOJO_RESULT_INVALID_ARGUMENT;
  }
  auto& triggers = trap_it->second.trap->triggers;
  if (std::any_of(triggers.begin(), triggers.end(),
                  [context, handle](const StandaloneTrapTrigger& trigger) {
                    return trigger.context == context ||
                           trigger.handle == handle;
                  })) {
    return MOJO_RESULT_ALREADY_EXISTS;
  }
  triggers.push_back({handle, signals, condition, context});
  return MOJO_RESULT_OK;
}

MojoResult StandaloneRemoveTrigger(MojoHandle trap_handle,
                                   uintptr_t context,
                                   const MojoRemoveTriggerOptions*) {
  PendingTrapEvent event;
  bool have_event = false;
  {
    base::AutoLock auto_lock(HandleLock());
    auto trap_it = Handles().find(trap_handle);
    if (trap_it == Handles().end() ||
        trap_it->second.kind != HandleKind::kTrap || !trap_it->second.trap) {
      return MOJO_RESULT_INVALID_ARGUMENT;
    }
    auto& triggers = trap_it->second.trap->triggers;
    auto it = std::find_if(
        triggers.begin(), triggers.end(),
        [context](const StandaloneTrapTrigger& trigger) {
          return trigger.context == context;
        });
    if (it == triggers.end())
      return MOJO_RESULT_NOT_FOUND;
    if (trap_it->second.trap->handler) {
      event = {trap_it->second.trap->handler,
               BuildTrapEvent(context, MOJO_RESULT_CANCELLED, {},
                              MOJO_TRAP_EVENT_FLAG_WITHIN_API_CALL)};
      have_event = true;
    }
    triggers.erase(it);
  }
  if (have_event)
    event.handler(&event.event);
  return MOJO_RESULT_OK;
}

MojoResult StandaloneArmTrap(MojoHandle trap_handle,
                             const MojoArmTrapOptions*,
                             uint32_t* num_blocking_events,
                             MojoTrapEvent* blocking_events) {
  base::AutoLock auto_lock(HandleLock());
  auto trap_it = Handles().find(trap_handle);
  if (trap_it == Handles().end() || trap_it->second.kind != HandleKind::kTrap ||
      !trap_it->second.trap) {
    return MOJO_RESULT_INVALID_ARGUMENT;
  }
  StandaloneTrap* trap = trap_it->second.trap;
  if (trap->triggers.empty())
    return MOJO_RESULT_NOT_FOUND;
  uint32_t capacity = num_blocking_events ? *num_blocking_events : 0;
  uint32_t ready_count = 0;
  for (const StandaloneTrapTrigger& trigger : trap->triggers) {
    MojoResult result = MOJO_RESULT_OK;
    MojoHandleSignalsState state = {};
    if (!TriggerIsReadyLocked(trigger, &result, &state))
      continue;
    if (blocking_events && ready_count < capacity) {
      blocking_events[ready_count] = BuildTrapEvent(
          trigger.context, result, state, MOJO_TRAP_EVENT_FLAG_NONE);
    }
    ++ready_count;
  }
  if (ready_count > 0) {
    if (num_blocking_events)
      *num_blocking_events = std::min(ready_count, capacity);
    trap->armed = false;
    return MOJO_RESULT_FAILED_PRECONDITION;
  }
  if (num_blocking_events)
    *num_blocking_events = 0;
  trap->armed = true;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneWrapPlatformHandle(const MojoPlatformHandle*,
                                        const MojoWrapPlatformHandleOptions*,
                                        MojoHandle* handle) {
  if (!handle)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle new_handle = NextHandle();
  {
    base::AutoLock auto_lock(HandleLock());
    Handles()[new_handle] = {HandleKind::kPlatform, nullptr, nullptr, nullptr};
  }
  *handle = new_handle;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneUnwrapPlatformHandle(
    MojoHandle handle,
    const MojoUnwrapPlatformHandleOptions*,
    MojoPlatformHandle* platform_handle) {
  if (platform_handle)
    std::memset(platform_handle, 0, sizeof(*platform_handle));
  return StandaloneClose(handle);
}

MojoResult StandaloneWrapPlatformSharedMemoryRegion(
    const MojoPlatformHandle*,
    uint32_t,
    uint64_t size,
    const MojoSharedBufferGuid*,
    MojoPlatformSharedMemoryRegionAccessMode,
    const MojoWrapPlatformSharedMemoryRegionOptions*,
    MojoHandle* handle) {
  return StandaloneCreateSharedBuffer(size, nullptr, handle);
}

MojoResult StandaloneUnwrapPlatformSharedMemoryRegion(
    MojoHandle handle,
    const MojoUnwrapPlatformSharedMemoryRegionOptions*,
    MojoPlatformHandle*,
    uint32_t* num_platform_handles,
    uint64_t* size,
    MojoSharedBufferGuid*,
    MojoPlatformSharedMemoryRegionAccessMode*) {
  if (num_platform_handles)
    *num_platform_handles = 0;
  if (size)
    *size = 0;
  return StandaloneClose(handle);
}

MojoResult StandaloneCreateInvitation(const MojoCreateInvitationOptions*,
                                      MojoHandle* invitation) {
  if (!invitation)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle handle = NextHandle();
  {
    base::AutoLock auto_lock(HandleLock());
    Handles()[handle] = {HandleKind::kInvitation, nullptr, nullptr, nullptr};
  }
  *invitation = handle;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneAttachMessagePipeToInvitation(
    MojoHandle,
    const void*,
    uint32_t,
    const MojoAttachMessagePipeToInvitationOptions*,
    MojoHandle* message_pipe_handle) {
  if (!message_pipe_handle)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle peer = MOJO_HANDLE_INVALID;
  return StandaloneCreateMessagePipe(nullptr, message_pipe_handle, &peer);
}

MojoResult StandaloneExtractMessagePipeFromInvitation(
    MojoHandle,
    const void*,
    uint32_t,
    const MojoExtractMessagePipeFromInvitationOptions*,
    MojoHandle* message_pipe_handle) {
  if (!message_pipe_handle)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle peer = MOJO_HANDLE_INVALID;
  return StandaloneCreateMessagePipe(nullptr, message_pipe_handle, &peer);
}

MojoResult StandaloneSendInvitation(MojoHandle,
                                    const MojoPlatformProcessHandle*,
                                    const MojoInvitationTransportEndpoint*,
                                    MojoProcessErrorHandler,
                                    uintptr_t,
                                    const MojoSendInvitationOptions*) {
  return MOJO_RESULT_UNIMPLEMENTED;
}

MojoResult StandaloneAcceptInvitation(
    const MojoInvitationTransportEndpoint*,
    const MojoAcceptInvitationOptions*,
    MojoHandle* invitation) {
  return StandaloneCreateInvitation(nullptr, invitation);
}

MojoResult StandaloneSetQuota(MojoHandle,
                              MojoQuotaType,
                              uint64_t,
                              const MojoSetQuotaOptions*) {
  return MOJO_RESULT_OK;
}

MojoResult StandaloneQueryQuota(MojoHandle handle,
                                MojoQuotaType,
                                const MojoQueryQuotaOptions*,
                                uint64_t* limit,
                                uint64_t* usage) {
  base::AutoLock auto_lock(HandleLock());
  auto it = Handles().find(handle);
  if (it == Handles().end())
    return MOJO_RESULT_INVALID_ARGUMENT;
  if (limit)
    *limit = 0;
  if (usage) {
    *usage = (it->second.endpoint)
                 ? static_cast<uint64_t>(it->second.endpoint->queue.size())
                 : 0;
  }
  return MOJO_RESULT_OK;
}

MojoResult StandaloneShutdown(const MojoShutdownOptions*) {
  return MOJO_RESULT_OK;
}

MojoResult StandaloneSetDefaultProcessErrorHandler(
    MojoDefaultProcessErrorHandler,
    const MojoSetDefaultProcessErrorHandlerOptions*) {
  return MOJO_RESULT_OK;
}

MojoResult StandaloneReserveMessageCapacity(MojoMessageHandle message,
                                            uint32_t payload_buffer_size,
                                            uint32_t* buffer_size) {
  if (message == MOJO_MESSAGE_HANDLE_INVALID)
    return MOJO_RESULT_INVALID_ARGUMENT;
  auto* standalone_message =
      reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
  standalone_message->data.reserve(payload_buffer_size);
  if (buffer_size)
    *buffer_size = static_cast<uint32_t>(standalone_message->data.capacity());
  return MOJO_RESULT_OK;
}

}  // namespace

namespace blink::standalone_renderer_probe {

void InstallStandaloneMojoThunksForStandaloneRenderer() {
  EnsureStandaloneCurrentDefaultTaskRunner();
  static bool installed = false;
  if (installed)
    return;
  MojoSystemThunks2 thunks = {};
  thunks.size = sizeof(thunks);
  thunks.Initialize = StandaloneInitialize;
  thunks.GetTimeTicksNow = StandaloneGetTimeTicksNow;
  thunks.Close = StandaloneClose;
  thunks.QueryHandleSignalsState = StandaloneQueryHandleSignalsState;
  thunks.CreateMessagePipe = StandaloneCreateMessagePipe;
  thunks.WriteMessage = StandaloneWriteMessage;
  thunks.ReadMessage = StandaloneReadMessage;
  thunks.FuseMessagePipes = StandaloneFuseMessagePipes;
  thunks.CreateMessage = StandaloneCreateMessage;
  thunks.DestroyMessage = StandaloneDestroyMessage;
  thunks.SerializeMessage = StandaloneSerializeMessage;
  thunks.AppendMessageData = StandaloneAppendMessageData;
  thunks.GetMessageData = StandaloneGetMessageData;
  thunks.SetMessageContext = StandaloneSetMessageContext;
  thunks.GetMessageContext = StandaloneGetMessageContext;
  thunks.NotifyBadMessage = StandaloneNotifyBadMessage;
  thunks.CreateDataPipe = StandaloneCreateDataPipe;
  thunks.WriteData = StandaloneWriteData;
  thunks.BeginWriteData = StandaloneBeginWriteData;
  thunks.EndWriteData = StandaloneEndWriteData;
  thunks.ReadData = StandaloneReadData;
  thunks.BeginReadData = StandaloneBeginReadData;
  thunks.EndReadData = StandaloneEndReadData;
  thunks.CreateSharedBuffer = StandaloneCreateSharedBuffer;
  thunks.DuplicateBufferHandle = StandaloneDuplicateBufferHandle;
  thunks.MapBuffer = StandaloneMapBuffer;
  thunks.UnmapBuffer = StandaloneUnmapBuffer;
  thunks.GetBufferInfo = StandaloneGetBufferInfo;
  thunks.CreateTrap = StandaloneCreateTrap;
  thunks.AddTrigger = StandaloneAddTrigger;
  thunks.RemoveTrigger = StandaloneRemoveTrigger;
  thunks.ArmTrap = StandaloneArmTrap;
  thunks.WrapPlatformHandle = StandaloneWrapPlatformHandle;
  thunks.UnwrapPlatformHandle = StandaloneUnwrapPlatformHandle;
  thunks.WrapPlatformSharedMemoryRegion =
      StandaloneWrapPlatformSharedMemoryRegion;
  thunks.UnwrapPlatformSharedMemoryRegion =
      StandaloneUnwrapPlatformSharedMemoryRegion;
  thunks.CreateInvitation = StandaloneCreateInvitation;
  thunks.AttachMessagePipeToInvitation =
      StandaloneAttachMessagePipeToInvitation;
  thunks.ExtractMessagePipeFromInvitation =
      StandaloneExtractMessagePipeFromInvitation;
  thunks.SendInvitation = StandaloneSendInvitation;
  thunks.AcceptInvitation = StandaloneAcceptInvitation;
  thunks.SetQuota = StandaloneSetQuota;
  thunks.QueryQuota = StandaloneQueryQuota;
  thunks.Shutdown = StandaloneShutdown;
  thunks.SetDefaultProcessErrorHandler = StandaloneSetDefaultProcessErrorHandler;
  thunks.ReserveMessageCapacity = StandaloneReserveMessageCapacity;
  MojoEmbedderSetSystemThunks(&thunks);
  installed = true;
}

#if defined(BLINK_STANDALONE_HAVE_MOJO_CORE_PROOF)
void InstallStandaloneMojoCoreForStandaloneRenderer() {
  EnsureStandaloneCurrentDefaultTaskRunner();
  static bool installed = false;
  if (installed)
    return;
  mojo::core::InitializeCore();
  MojoEmbedderSetSystemThunks(&mojo::core::GetSystemThunks());
  installed = true;
}
#else
void InstallStandaloneMojoCoreForStandaloneRenderer() {
  InstallStandaloneMojoThunksForStandaloneRenderer();
}
#endif

}  // namespace blink::standalone_renderer_probe
