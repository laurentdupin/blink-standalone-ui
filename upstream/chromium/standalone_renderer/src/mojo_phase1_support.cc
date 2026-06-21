// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Phase 1 uses Mojo public value/handle vocabulary inside Blink-generated
// structs, but does not import Mojo Core or browser IPC runtime. This installs
// a minimal in-process thunk table so local scoped handles can be constructed
// and destroyed without enabling external services.

#include "mojo/public/c/system/thunks.h"

#include <atomic>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "base/task/single_thread_task_runner.h"
#include "base/time/time.h"

namespace {

class StandalonePhase1SingleThreadTaskRunner final
    : public base::SingleThreadTaskRunner {
 public:
  bool PostDelayedTask(const base::Location&,
                       base::OnceClosure,
                       base::TimeDelta) override {
    return true;
  }

  bool PostNonNestableDelayedTask(const base::Location&,
                                  base::OnceClosure,
                                  base::TimeDelta) override {
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
};

std::mutex& HandleMutex() {
  static std::mutex* mutex = new std::mutex();
  return *mutex;
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

MojoResult StandaloneInitialize(const MojoInitializeOptions*) {
  return MOJO_RESULT_OK;
}

MojoTimeTicks StandaloneGetTimeTicksNow() {
  return 0;
}

MojoResult StandaloneClose(MojoHandle handle) {
  if (handle == MOJO_HANDLE_INVALID)
    return MOJO_RESULT_INVALID_ARGUMENT;
  std::lock_guard<std::mutex> lock(HandleMutex());
  auto it = Handles().find(handle);
  if (it == Handles().end())
    return MOJO_RESULT_INVALID_ARGUMENT;
  delete it->second.buffer;
  Handles().erase(it);
  return MOJO_RESULT_OK;
}

MojoResult StandaloneQueryHandleSignalsState(
    MojoHandle handle,
    MojoHandleSignalsState* signals_state) {
  if (!signals_state)
    return MOJO_RESULT_INVALID_ARGUMENT;
  std::lock_guard<std::mutex> lock(HandleMutex());
  if (Handles().find(handle) == Handles().end())
    return MOJO_RESULT_INVALID_ARGUMENT;
  signals_state->satisfied_signals = MOJO_HANDLE_SIGNAL_WRITABLE;
  signals_state->satisfiable_signals =
      MOJO_HANDLE_SIGNAL_WRITABLE | MOJO_HANDLE_SIGNAL_PEER_CLOSED;
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
    std::lock_guard<std::mutex> lock(HandleMutex());
    Handles()[first] = {HandleKind::kMessagePipe, nullptr};
    Handles()[second] = {HandleKind::kMessagePipe, nullptr};
  }
  *handle0 = first;
  *handle1 = second;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneWriteMessage(MojoHandle handle,
                                  MojoMessageHandle message,
                                  const MojoWriteMessageOptions*) {
  {
    std::lock_guard<std::mutex> lock(HandleMutex());
    if (Handles().find(handle) == Handles().end())
      return MOJO_RESULT_INVALID_ARGUMENT;
  }
  if (message != MOJO_MESSAGE_HANDLE_INVALID) {
    auto* standalone_message =
        reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
    if (standalone_message->context_destructor && standalone_message->context)
      standalone_message->context_destructor(standalone_message->context);
    delete standalone_message;
  }
  return MOJO_RESULT_OK;
}

MojoResult StandaloneReadMessage(MojoHandle handle,
                                 const MojoReadMessageOptions*,
                                 MojoMessageHandle*) {
  std::lock_guard<std::mutex> lock(HandleMutex());
  if (Handles().find(handle) == Handles().end())
    return MOJO_RESULT_INVALID_ARGUMENT;
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
  auto* standalone_message =
      reinterpret_cast<StandaloneMessage*>(static_cast<uintptr_t>(message));
  if (standalone_message->context_destructor && standalone_message->context)
    standalone_message->context_destructor(standalone_message->context);
  delete standalone_message;
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
  size_t old_size = standalone_message->data.size();
  standalone_message->data.resize(old_size + payload_size);
  if (num_handles) {
    standalone_message->handles.insert(standalone_message->handles.end(),
                                       handles, handles + num_handles);
  }
  if (buffer)
    *buffer = standalone_message->data.data() + old_size;
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
    std::lock_guard<std::mutex> lock(HandleMutex());
    Handles()[new_handle] = {HandleKind::kSharedBuffer,
                             new StandaloneBuffer(size)};
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
  std::lock_guard<std::mutex> lock(HandleMutex());
  auto it = Handles().find(handle);
  if (it == Handles().end() || !it->second.buffer)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle duplicate = NextHandle();
  Handles()[duplicate] = {HandleKind::kSharedBuffer,
                          new StandaloneBuffer(*it->second.buffer)};
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
  std::lock_guard<std::mutex> lock(HandleMutex());
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
  std::lock_guard<std::mutex> lock(HandleMutex());
  auto it = Handles().find(handle);
  if (it == Handles().end() || !it->second.buffer)
    return MOJO_RESULT_INVALID_ARGUMENT;
  info->struct_size = sizeof(*info);
  info->size = it->second.buffer->bytes.size();
  return MOJO_RESULT_OK;
}

MojoResult StandaloneCreateTrap(MojoTrapEventHandler,
                                const MojoCreateTrapOptions*,
                                MojoHandle* trap) {
  if (!trap)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle handle = NextHandle();
  {
    std::lock_guard<std::mutex> lock(HandleMutex());
    Handles()[handle] = {HandleKind::kTrap, nullptr};
  }
  *trap = handle;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneAddTrigger(MojoHandle,
                                MojoHandle,
                                MojoHandleSignals,
                                MojoTriggerCondition,
                                uintptr_t,
                                const MojoAddTriggerOptions*) {
  return MOJO_RESULT_OK;
}

MojoResult StandaloneRemoveTrigger(MojoHandle,
                                   uintptr_t,
                                   const MojoRemoveTriggerOptions*) {
  return MOJO_RESULT_OK;
}

MojoResult StandaloneArmTrap(MojoHandle,
                             const MojoArmTrapOptions*,
                             uint32_t* num_blocking_events,
                             MojoTrapEvent*) {
  if (num_blocking_events)
    *num_blocking_events = 0;
  return MOJO_RESULT_OK;
}

MojoResult StandaloneWrapPlatformHandle(const MojoPlatformHandle*,
                                        const MojoWrapPlatformHandleOptions*,
                                        MojoHandle* handle) {
  if (!handle)
    return MOJO_RESULT_INVALID_ARGUMENT;
  MojoHandle new_handle = NextHandle();
  {
    std::lock_guard<std::mutex> lock(HandleMutex());
    Handles()[new_handle] = {HandleKind::kPlatform, nullptr};
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
    std::lock_guard<std::mutex> lock(HandleMutex());
    Handles()[handle] = {HandleKind::kInvitation, nullptr};
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

MojoResult StandaloneQueryQuota(MojoHandle,
                                MojoQuotaType,
                                const MojoQueryQuotaOptions*,
                                uint64_t* limit,
                                uint64_t* usage) {
  if (limit)
    *limit = 0;
  if (usage)
    *usage = 0;
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

}  // namespace blink::standalone_renderer_probe
