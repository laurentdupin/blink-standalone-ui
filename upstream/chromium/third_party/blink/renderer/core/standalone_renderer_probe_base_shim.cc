// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/check.h"
#include "base/check_op.h"
#include "base/functional/callback_internal.h"
#include "base/feature_list.h"
#include "base/debug/stack_trace.h"
#include "base/i18n/string_search.h"
#include "base/location.h"
#include "base/logging.h"
#include "base/metrics/field_trial_params.h"
#include "base/sequence_checker_impl.h"
#include "base/strings/cstring_view.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/lock_impl.h"
#include "base/time/time.h"
#include "base/threading/platform_thread.h"
#include "base/threading/thread_collision_warner.h"
#include "base/threading/thread_local_storage.h"
#include "partition_alloc/partition_address_space.h"
#include "partition_alloc/partition_alloc_base/check.h"
#include "partition_alloc/partition_alloc_base/scoped_clear_last_error.h"
#include "partition_alloc/partition_alloc_base/strings/cstring_builder.h"
#include "partition_alloc/pointers/raw_ptr_backup_ref_impl.h"
#include "third_party/blink/renderer/core/css/css_primitive_value.h"
#include "third_party/blink/renderer/core/css/css_property_names.h"
#include "third_party/blink/renderer/core/css/css_markup.h"
#include "third_party/blink/renderer/core/css_value_keywords.h"
#include "third_party/blink/renderer/core/css/parser/at_rule_descriptors.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_mode.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/qualified_name.h"
#include "third_party/blink/renderer/core/execution_context/agent.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/allocator/partition_allocator.h"
#include "third_party/blink/renderer/platform/wtf/allocator/partitions.h"
#include "third_party/blink/renderer/platform/wtf/text/case_map.h"
#include "third_party/blink/renderer/platform/wtf/text/string_impl.h"
#include "third_party/blink/renderer/platform/wtf/stack_util.h"
#include "third_party/blink/renderer/platform/wtf/text/text_codec_cjk.h"
#include "third_party/blink/renderer/platform/wtf/text/text_codec_icu.h"

#include <algorithm>
#include <atomic>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "unicode/uchar.h"
#include "unicode/ustring.h"

namespace {

char* DuplicateString(std::string_view value) {
  char* result = static_cast<char*>(std::malloc(value.size() + 1));
  if (!result) {
    std::abort();
  }
  std::memcpy(result, value.data(), value.size());
  result[value.size()] = '\0';
  return result;
}

class NullBuffer : public std::streambuf {
 public:
  int overflow(int c) override { return c; }
};

}  // namespace

namespace base {

namespace subtle {

bool RefCountedThreadSafeBase::HasOneRef() const {
  return true;
}

RefCountedThreadSafeBase::~RefCountedThreadSafeBase() = default;

}  // namespace subtle

Location::Location() = default;
Location::Location(const Location& other) = default;
Location::Location(Location&& other) noexcept = default;
Location& Location::operator=(const Location& other) = default;

Location::Location(const char* file_name, const void* program_counter)
    : file_name_(file_name), program_counter_(program_counter) {}

Location::Location(const char* function_name,
                   const char* file_name,
                   int line_number,
                   const void* program_counter)
    : function_name_(function_name),
      file_name_(file_name),
      line_number_(line_number),
      program_counter_(program_counter) {}

Location Location::Current(const char* function_name,
                           const char* file_name,
                           int line_number) {
  return Location(function_name, file_name, line_number, GetProgramCounter());
}

Location Location::CurrentWithoutFunctionName(const char* file_name,
                                              int line_number) {
  return Location(nullptr, file_name, line_number, GetProgramCounter());
}

std::string Location::ToString() const {
  std::ostringstream stream;
  stream << (file_name_ ? file_name_ : "<unknown>") << ":" << line_number_;
  return stream.str();
}

const void* GetProgramCounter() {
  return __builtin_return_address(0);
}

}  // namespace base

namespace logging {

namespace {
NullBuffer null_buffer;
std::ostream null_stream(&null_buffer);
}  // namespace

std::ostream* g_swallow_stream = &null_stream;

#if BUILDFLAG(DCHECK_IS_CONFIGURABLE)
LogSeverity LOGGING_DCHECK = LOGGING_FATAL;
#endif

int GetVlogLevelHelper(const char*, size_t) {
  return 0;
}

bool ShouldCreateLogMessage(int) {
  return false;
}

LogMessage::LogMessage(const char* file, int line, LogSeverity severity)
    : severity_(severity), message_start_(0), file_(file), line_(line) {}

LogMessage::~LogMessage() = default;

std::string LogMessage::BuildCrashString() const {
  return str();
}

void LogMessage::Flush() {}

void LogMessage::Init(const char*, int) {}

void LogMessage::HandleFatal(size_t, const std::string&) const {}

LogMessageFatal::~LogMessageFatal() {
  std::abort();
}

SystemErrorCode GetLastSystemErrorCode() {
  return 0;
}

std::string SystemErrorCodeToString(SystemErrorCode error_code) {
  return std::to_string(error_code);
}

CheckError::CheckError(LogMessage* log_message) : log_message_(log_message) {}

CheckError CheckError::Check(const char*,
                             base::NotFatalUntil,
                             const base::Location&) {
  return CheckError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

LogMessage* CheckError::CheckOp(char* log_message_str,
                                base::NotFatalUntil,
                                const base::Location&) {
  std::free(log_message_str);
  return new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR);
}

CheckError CheckError::DCheck(const char*, const base::Location&) {
  return CheckError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

LogMessage* CheckError::DCheckOp(char* log_message_str,
                                 const base::Location&) {
  std::free(log_message_str);
  return new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR);
}

CheckError CheckError::DumpWillBeCheck(const char*, const base::Location&) {
  return CheckError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

LogMessage* CheckError::DumpWillBeCheckOp(char* log_message_str,
                                          const base::Location&) {
  std::free(log_message_str);
  return new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR);
}

CheckError CheckError::DPCheck(const char*, const base::Location&) {
  return CheckError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

CheckError CheckError::NotImplemented(const char*, const base::Location&) {
  return CheckError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

std::ostream& CheckError::stream() {
  return log_message_ ? log_message_->stream() : null_stream;
}

CheckError::~CheckError() = default;

CheckNoreturnError::~CheckNoreturnError() {
  std::abort();
}

CheckNoreturnError CheckNoreturnError::Check(const char*,
                                             const base::Location&) {
  return CheckNoreturnError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

LogMessage* CheckNoreturnError::CheckOp(char* log_message_str,
                                        const base::Location&) {
  std::free(log_message_str);
  return new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR);
}

CheckNoreturnError CheckNoreturnError::PCheck(const char*,
                                              const base::Location&) {
  return CheckNoreturnError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

CheckNoreturnError CheckNoreturnError::PCheck(const base::Location&) {
  return CheckNoreturnError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

NotReachedError NotReachedError::NotReached(base::NotFatalUntil,
                                            const base::Location&) {
  return NotReachedError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

NotReachedError NotReachedError::DumpWillBeNotReached(const base::Location&) {
  return NotReachedError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR));
}

NotReachedError::~NotReachedError() = default;

NotReachedNoreturnError::NotReachedNoreturnError(const base::Location&)
    : CheckError(new LogMessage("standalone_renderer_probe", 0, LOGGING_ERROR)) {}

NotReachedNoreturnError::~NotReachedNoreturnError() {
  std::abort();
}

char* CheckOpValueStr(int v) {
  return DuplicateString(std::to_string(v));
}

char* CheckOpValueStr(unsigned v) {
  return DuplicateString(std::to_string(v));
}

char* CheckOpValueStr(long v) {
  return DuplicateString(std::to_string(v));
}

char* CheckOpValueStr(unsigned long v) {
  return DuplicateString(std::to_string(v));
}

char* CheckOpValueStr(long long v) {
  return DuplicateString(std::to_string(v));
}

char* CheckOpValueStr(unsigned long long v) {
  return DuplicateString(std::to_string(v));
}

char* CheckOpValueStr(const void* v) {
  char buffer[32];
  std::snprintf(buffer, sizeof(buffer), "%p", v);
  return DuplicateString(buffer);
}

char* CheckOpValueStr(std::nullptr_t) {
  return DuplicateString("nullptr");
}

char* CheckOpValueStr(double v) {
  return DuplicateString(std::to_string(v));
}

char* CheckOpValueStr(const std::string& v) {
  return DuplicateString(v);
}

char* CheckOpValueStr(std::string_view v) {
  return DuplicateString(v);
}

char* CheckOpValueStr(base::cstring_view v) {
  return DuplicateString(v.c_str());
}

char* StreamValToStr(const void* value,
                     void (*stream_func)(std::ostream&, const void*)) {
  std::ostringstream stream;
  stream_func(stream, value);
  return DuplicateString(stream.str());
}

char* CreateCheckOpLogMessageString(const char* expr_str,
                                    char* v1_str,
                                    char* v2_str) {
  std::string message = std::string(expr_str) + " (" + v1_str + " vs. " +
                        v2_str + ")";
  std::free(v1_str);
  std::free(v2_str);
  return DuplicateString(message);
}

void RawCheckFailure(const char*) {
  std::abort();
}

}  // namespace logging

namespace blink {

ExecutionContext* Document::GetExecutionContext() const {
  return nullptr;
}

Agent& Document::GetAgent() const {
  static char storage[sizeof(Agent)] = {};
  return *reinterpret_cast<Agent*>(storage);
}

LocalFrame* Document::GetFrame() const {
  return nullptr;
}

Element* Document::CreateElement(const QualifiedName&,
                                 CreateElementFlags,
                                 const AtomicString&,
                                 CustomElementRegistry*) {
  return nullptr;
}

void Document::SetCompatibilityMode(CompatibilityMode) {}

void Document::FinishedParsing() {}

void Document::WillInsertBody() {}

void Document::AddConsoleMessage(ConsoleMessage*, bool) const {}

namespace features {
extern constinit const base::Feature kCapStringBuilderLengthTo1GiB(
    "CapStringBuilderLengthTo1GiB",
    base::FEATURE_DISABLED_BY_DEFAULT,
    base::internal::FeatureMacroHandshake::kSecret);
}  // namespace features

namespace {
QualifiedName* MakeNullQualifiedName() {
  static QualifiedName* name =
      new QualifiedName(scoped_refptr<QualifiedName::QualifiedNameImpl>());
  return name;
}
}  // namespace

const QualifiedName& g_any_name = *MakeNullQualifiedName();
const QualifiedName& g_null_name = *MakeNullQualifiedName();

QualifiedName::QualifiedName(const AtomicString& prefix,
                             const AtomicString& local_name,
                             const AtomicString& namespace_uri) {
  impl_ = QualifiedNameImpl::Create(prefix.Impl(), local_name.Impl(),
                                    namespace_uri.Impl(), false);
}

QualifiedName::QualifiedName(const AtomicString& local_name)
    : QualifiedName(g_null_atom, local_name, g_null_atom) {}

QualifiedName::QualifiedName(const AtomicString& prefix,
                             const AtomicString& local_name,
                             const AtomicString& namespace_uri,
                             bool is_static) {
  impl_ = QualifiedNameImpl::Create(prefix.Impl(), local_name.Impl(),
                                    namespace_uri.Impl(), is_static);
}

QualifiedName::~QualifiedName() = default;

QualifiedName::QualifiedNameImpl::~QualifiedNameImpl() = default;

unsigned QualifiedName::QualifiedNameImpl::ComputeHash() const {
  QualifiedNameComponents components = {prefix_.Impl(), local_name_.Impl(),
                                        namespace_.Impl()};
  return HashComponents(components);
}

String QualifiedName::ToString() const {
  return impl_ ? impl_->local_name_.GetString() : String();
}

void QualifiedName::InitAndReserveCapacityForSize(wtf_size_t) {}

CSSPropertyID UnresolvedCSSPropertyID(const ExecutionContext*,
                                      StringView,
                                      CSSParserMode) {
  return CSSPropertyID::kInvalid;
}

AtRuleDescriptorID AsAtRuleDescriptorID(StringView) {
  return AtRuleDescriptorID::Invalid;
}

CSSValueID CssValueKeywordID(StringView) {
  return CSSValueID::kInvalid;
}

const AtomicString& QualifiedName::LocalNameUpperSlow() const {
  impl_->local_name_upper_ = impl_->local_name_.ToAsciiUpper();
  return impl_->local_name_upper_;
}

void QualifiedName::CreateStatic(void* target_address, StringImpl* name) {
  new (target_address)
      QualifiedName(g_null_atom, AtomicString(name), g_null_atom, true);
}

void QualifiedName::CreateStatic(void* target_address,
                                 StringImpl* name,
                                 const AtomicString& name_namespace) {
  new (target_address)
      QualifiedName(g_null_atom, AtomicString(name), name_namespace, true);
}

QualifiedNameWithHash::QualifiedNameWithHash(const AtomicString& prefix,
                                             const AtomicString& local_name,
                                             const AtomicString& namespace_uri,
                                             bool is_static)
    : QualifiedName(prefix, local_name, namespace_uri, is_static),
      bloom_filter(0) {}

void QualifiedNameWithHash::CreateStatic(void* target_address,
                                         StringImpl* name) {
  new (target_address)
      QualifiedNameWithHash(g_null_atom, AtomicString(name), g_null_atom, true);
}

void QualifiedNameWithHash::CreateStatic(void* target_address,
                                         StringImpl* name,
                                         const AtomicString& name_namespace) {
  new (target_address) QualifiedNameWithHash(g_null_atom, AtomicString(name),
                                             name_namespace, true);
}

std::ostream& operator<<(std::ostream& stream, const QualifiedName& name) {
  return stream << name.ToString();
}

void TextCodecCjk::RegisterEncodingNames(EncodingNameRegistrar) {}

void TextCodecCjk::RegisterCodecs(TextCodecRegistrar) {}

bool TextCodecCjk::IsSupported(StringView) {
  return false;
}

void TextCodecIcu::RegisterEncodingNames(EncodingNameRegistrar) {}

void TextCodecIcu::RegisterCodecs(TextCodecRegistrar) {}

IcuConverterWrapper::~IcuConverterWrapper() = default;

namespace internal {
uintptr_t g_main_thread_stack_start = 0;
uintptr_t g_main_thread_underestimated_stack_size = 0;

void InitializeMainThreadStackEstimate() {
  int dummy = 0;
  g_main_thread_stack_start = reinterpret_cast<uintptr_t>(&dummy);
  g_main_thread_underestimated_stack_size = 8 * 1024 * 1024;
}

size_t ThreadStackSize() {
  return 8 * 1024 * 1024;
}
}  // namespace internal

void* Partitions::BufferMalloc(size_t n, const char*) {
  if (n == 0) {
    n = 1;
  }
  void* result = std::malloc(n);
  if (!result) {
    std::abort();
  }
  return result;
}

void* Partitions::FastMalloc(size_t n, const char* type_name) {
  return BufferMalloc(n, type_name);
}

void* Partitions::FastZeroedMalloc(size_t n, const char* type_name) {
  void* result = BufferMalloc(n, type_name);
  std::memset(result, 0, n);
  return result;
}

void Partitions::FastFree(void* p) {
  std::free(p);
}

void Partitions::BufferFree(void* p) {
  std::free(p);
}

void Partitions::BufferFreeWithSize(void* p, size_t) {
  std::free(p);
}

size_t Partitions::BufferPotentialCapacity(size_t n) {
  return n;
}

void* PartitionAllocator::AllocateBacking(size_t size, const char* type_name) {
  return Partitions::BufferMalloc(size, type_name);
}

void PartitionAllocator::FreeBacking(void* address) {
  Partitions::BufferFree(address);
}

template <>
char* PartitionAllocator::AllocateVectorBacking<char>(size_t size) {
  return reinterpret_cast<char*>(
      AllocateBacking(size, WTF_HEAP_PROFILER_TYPE_NAME(char)));
}

bool RuntimeEnabledFeaturesBase::is_html_processing_instruction_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_html_command_element_removal_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_html_adoption_algorithm_new_steps_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_input_in_select_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_correct_template_form_parsing_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_custom_elements_disable_formatting_fixups_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_document_patching_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_fed_cm_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_fenced_frames_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_geolocation_element_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_install_element_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_login_element_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_menu_elements_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_new_html_setting_methods_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_sanitizer_api_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scoped_custom_element_registry_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_set_html_can_run_scripts_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_streaming_sanitizer_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_trusted_types_create_parser_options_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_user_media_element_enabled_ = false;

bool RuntimeEnabledFeaturesBase::InstallElementEnabled(
    const FeatureContext*) {
  return false;
}

bool RuntimeEnabledFeaturesBase::UserMediaElementEnabled(
    const FeatureContext*) {
  return false;
}

bool RuntimeEnabledFeaturesBase::ShadowRootReferenceTargetEnabled(
    const FeatureContext*) {
  return false;
}

scoped_refptr<StringImpl> CaseMap::FastToLowerInvariant(StringImpl* source) {
  if (!source) {
    return nullptr;
  }
  if (!source->Is8Bit()) {
    return source;
  }

  const base::span<const LChar> source8 = source->Span8();
  bool changed = false;
  for (LChar ch : source8) {
    if (ch >= 'A' && ch <= 'Z') {
      changed = true;
      break;
    }
  }
  if (!changed) {
    return source;
  }

  Vector<LChar> lowered;
  lowered.reserve(source8.size());
  for (LChar ch : source8) {
    lowered.push_back(ch >= 'A' && ch <= 'Z' ? ch + ('a' - 'A') : ch);
  }
  return StringImpl::Create(base::span<const LChar>(lowered));
}

}  // namespace blink

namespace base::internal {

namespace {
bool StandaloneQueryCancellationTraits(
    const BindStateBase*,
    BindStateBase::CancellationQueryMode mode) {
  return std::to_underlying(mode);
}
}  // namespace

BindStateHolder::BindStateHolder(const BindStateHolder&) = default;
BindStateHolder& BindStateHolder::operator=(const BindStateHolder&) = default;
BindStateHolder& BindStateHolder::operator=(BindStateHolder&&) noexcept =
    default;
BindStateHolder::~BindStateHolder() = default;

void BindStateHolder::Reset() {
  bind_state_ = nullptr;
}

bool BindStateHolder::IsCancelled() const {
  return bind_state_ && bind_state_->IsCancelled();
}

bool BindStateHolder::MaybeValid() const {
  return bind_state_ && bind_state_->MaybeValid();
}

void BindStateBaseRefCountTraits::Destruct(const BindStateBase* bind_state) {
  bind_state->destructor_(bind_state);
}

BindStateBase::BindStateBase(InvokeFuncStorage polymorphic_invoke,
                             DestructorPtr destructor)
    : BindStateBase(polymorphic_invoke,
                    destructor,
                    &StandaloneQueryCancellationTraits) {}

BindStateBase::BindStateBase(
    InvokeFuncStorage polymorphic_invoke,
    DestructorPtr destructor,
    QueryCancellationTraitsPtr query_cancellation_traits)
    : polymorphic_invoke_(polymorphic_invoke),
      destructor_(destructor),
      query_cancellation_traits_(query_cancellation_traits) {}

void CheckThatAddressIsntWithinFirstPartitionPage(uintptr_t) {}

template <bool AllowDangling>
void RawPtrBackupRefImpl<AllowDangling>::AcquireInternal(uintptr_t) {}

template <bool AllowDangling>
void RawPtrBackupRefImpl<AllowDangling>::ReleaseInternal(uintptr_t) {}

template <bool AllowDangling>
bool RawPtrBackupRefImpl<AllowDangling>::IsPointeeAlive(uintptr_t) {
  return true;
}

template <bool AllowDangling>
void RawPtrBackupRefImpl<AllowDangling>::ReportIfDanglingInternal(uintptr_t) {}

template <bool AllowDangling>
bool RawPtrBackupRefImpl<AllowDangling>::CheckPointerWithinSameAlloc(uintptr_t,
                                                                     uintptr_t,
                                                                     size_t) {
  return false;
}

template struct RawPtrBackupRefImpl<false>;
template struct RawPtrBackupRefImpl<true>;

}  // namespace base::internal

namespace base {

SequenceCheckerImpl::SequenceCheckerImpl() = default;
SequenceCheckerImpl::SequenceCheckerImpl(SequenceCheckerImpl&&) {}
SequenceCheckerImpl& SequenceCheckerImpl::operator=(SequenceCheckerImpl&&) {
  return *this;
}
SequenceCheckerImpl::~SequenceCheckerImpl() = default;

void SequenceCheckerImpl::EnableStackLogging() {}

bool SequenceCheckerImpl::CalledOnValidSequence(
    std::unique_ptr<debug::StackTrace>*) const {
  return true;
}

void SequenceCheckerImpl::DetachFromSequence() {}

void SequenceCheckerImpl::EnsureAssigned() const {}

#if DCHECK_IS_ON()
ScopedValidateSequenceChecker::ScopedValidateSequenceChecker(
    const SequenceChecker&) {}

ScopedValidateSequenceChecker::~ScopedValidateSequenceChecker() = default;
#endif

namespace subtle {

void RefCountedBase::AddRefImpl() const {
  ++ref_count_;
}

void RefCountedBase::ReleaseImpl() const {
  --ref_count_;
}

bool RefCountedBase::CalledOnValidSequence() const {
  return true;
}

}  // namespace subtle

void DCheckAsserter::warn() {}

PlatformThreadId PlatformThreadBase::CurrentId() {
  return PlatformThreadId::ForTest(1);
}

namespace internal {

LockImpl::LockImpl() {
  std::memset(&native_handle_, 0, sizeof(native_handle_));
}

LockImpl::~LockImpl() = default;

void LockImpl::LockInternal() {}

}  // namespace internal

void Lock::Acquire(subtle::LockTracking) {}

Lock::~Lock() = default;

void Lock::Release() {}

bool Lock::Try(subtle::LockTracking) {
  return true;
}

void Lock::AssertAcquired() const {}

void Lock::AssertNotHeld() const {}

bool FeatureList::IsEnabled(const Feature& feature) {
  return feature.default_state == FEATURE_ENABLED_BY_DEFAULT;
}

TimeTicks TimeTicks::Now() {
  return TimeTicks();
}

namespace internal {

bool IsFeatureParamWithCacheEnabled() {
  return false;
}

}  // namespace internal

namespace {
thread_local std::unordered_map<size_t, void*> tls_values;
std::atomic_size_t next_tls_slot{1};
}  // namespace

ThreadLocalStorage::Slot::Slot(TLSDestructorFunc destructor) {
  Initialize(destructor);
}

ThreadLocalStorage::Slot::~Slot() {
  Free();
}

void ThreadLocalStorage::Slot::Initialize(TLSDestructorFunc) {
  slot_ = next_tls_slot.fetch_add(1, std::memory_order_relaxed);
}

void ThreadLocalStorage::Slot::Free() {
  tls_values.erase(slot_);
  slot_ = kInvalidSlotValue;
}

void* ThreadLocalStorage::Slot::Get() const {
  auto it = tls_values.find(slot_);
  return it == tls_values.end() ? nullptr : it->second;
}

void ThreadLocalStorage::Slot::Set(void* value) {
  tls_values[slot_] = value;
}

bool ThreadLocalStorage::HasBeenDestroyed() {
  return false;
}

template <>
bool FeatureParam<bool>::GetWithoutCache() const {
  return default_value;
}

template <>
int FeatureParam<int>::GetWithoutCache() const {
  return default_value;
}

template <>
size_t FeatureParam<size_t>::GetWithoutCache() const {
  return default_value;
}

template <>
double FeatureParam<double>::GetWithoutCache() const {
  return default_value;
}

template <>
std::string FeatureParam<std::string>::GetWithoutCache() const {
  return default_value;
}

template <>
TimeDelta FeatureParam<TimeDelta>::GetWithoutCache() const {
  return default_value;
}

namespace i18n {

bool StringSearchIgnoringCaseAndAccents(std::u16string find_this,
                                        std::u16string_view in_this,
                                        size_t* match_index,
                                        size_t* match_length) {
  auto lower = [](char16_t c) {
    return c >= u'A' && c <= u'Z' ? static_cast<char16_t>(c + (u'a' - u'A'))
                                  : c;
  };
  if (find_this.empty()) {
    if (match_index) {
      *match_index = 0;
    }
    if (match_length) {
      *match_length = 0;
    }
    return true;
  }
  for (size_t i = 0; i + find_this.size() <= in_this.size(); ++i) {
    bool matched = true;
    for (size_t j = 0; j < find_this.size(); ++j) {
      if (lower(find_this[j]) != lower(in_this[i + j])) {
        matched = false;
        break;
      }
    }
    if (matched) {
      if (match_index) {
        *match_index = i;
      }
      if (match_length) {
        *match_length = find_this.size();
      }
      return true;
    }
  }
  return false;
}

}  // namespace i18n

}  // namespace base

extern "C" {

UChar32 u_foldCase(UChar32 c, uint32_t) {
  return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
}

UCharDirection u_charDirection(UChar32) {
  return U_LEFT_TO_RIGHT;
}

UChar32 u_tolower(UChar32 c) {
  return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
}

int32_t u_memcasecmp(const UChar* s1,
                     const UChar* s2,
                     int32_t length,
                     uint32_t options) {
  for (int32_t i = 0; i < length; ++i) {
    UChar32 c1 = u_foldCase(s1[i], options);
    UChar32 c2 = u_foldCase(s2[i], options);
    if (c1 != c2) {
      return c1 < c2 ? -1 : 1;
    }
  }
  return 0;
}

int32_t u_strFoldCase(UChar* dest,
                      int32_t dest_capacity,
                      const UChar* src,
                      int32_t src_length,
                      uint32_t options,
                      UErrorCode* status) {
  if (src_length < 0) {
    src_length = 0;
    while (src[src_length]) {
      ++src_length;
    }
  }
  const int32_t count = dest_capacity < src_length ? dest_capacity : src_length;
  for (int32_t i = 0; i < count; ++i) {
    dest[i] = static_cast<UChar>(u_foldCase(src[i], options));
  }
  if (status) {
    *status = U_ZERO_ERROR;
  }
  return src_length;
}

void WTFAnnotateBenignRaceSized(const char*, int, const volatile void*, size_t,
                                const char*) {}

}  // extern "C"

namespace std {

int uncaught_exceptions() noexcept {
  return 0;
}

}  // namespace std

namespace partition_alloc::internal {

PartitionAddressSpace::PoolSetup PartitionAddressSpace::setup_;

namespace base {

#if PA_BUILDFLAG(IS_WIN)
ScopedClearLastError::ScopedClearLastError() : last_system_error_(0) {}
ScopedClearLastError::~ScopedClearLastError() = default;
#endif

namespace strings {

CStringBuilder& CStringBuilder::operator<<(char ch) {
  PutText(&ch, 1);
  return *this;
}

CStringBuilder& CStringBuilder::operator<<(const char* text) {
  PutText(text ? text : "(null)");
  return *this;
}

CStringBuilder& CStringBuilder::operator<<(float value) {
  return *this << static_cast<double>(value);
}

CStringBuilder& CStringBuilder::operator<<(double value) {
  char buffer[64];
  std::snprintf(buffer, sizeof(buffer), "%g", value);
  PutText(buffer);
  return *this;
}

CStringBuilder& CStringBuilder::operator<<(int value) {
  return *this << static_cast<long long>(value);
}

CStringBuilder& CStringBuilder::operator<<(unsigned int value) {
  return *this << static_cast<unsigned long long>(value);
}

CStringBuilder& CStringBuilder::operator<<(long value) {
  return *this << static_cast<long long>(value);
}

CStringBuilder& CStringBuilder::operator<<(unsigned long value) {
  return *this << static_cast<unsigned long long>(value);
}

CStringBuilder& CStringBuilder::operator<<(long long value) {
  char buffer[64];
  std::snprintf(buffer, sizeof(buffer), "%lld", value);
  PutText(buffer);
  return *this;
}

CStringBuilder& CStringBuilder::operator<<(unsigned long long value) {
  char buffer[64];
  std::snprintf(buffer, sizeof(buffer), "%llu", value);
  PutText(buffer);
  return *this;
}

CStringBuilder& CStringBuilder::operator<<(const void* value) {
  char buffer[32];
  std::snprintf(buffer, sizeof(buffer), "%p", value);
  PutText(buffer);
  return *this;
}

CStringBuilder& CStringBuilder::operator<<(std::nullptr_t) {
  PutText("nullptr");
  return *this;
}

const char* CStringBuilder::c_str() {
  *ptr_ = '\0';
  return buffer_;
}

template <typename T>
void CStringBuilder::PutInteger(T value) {
  *this << static_cast<long long>(value);
}

void CStringBuilder::PutFloatingPoint(double value, unsigned) {
  *this << value;
}

void CStringBuilder::PutNormalFloatingPoint(double value, unsigned) {
  *this << value;
}

void CStringBuilder::PutText(const char* text) {
  PutText(text, std::strlen(text));
}

void CStringBuilder::PutText(const char* text, size_t length) {
  const size_t remaining = static_cast<size_t>(buffer_ + kBufferSize - 1 - ptr_);
  const size_t copied = std::min(remaining, length);
  std::memcpy(ptr_, text, copied);
  ptr_ += copied;
  *ptr_ = '\0';
}

}  // namespace strings
}  // namespace base

namespace logging {

base::strings::CStringBuilder* g_swallow_stream = nullptr;

LogMessage::LogMessage(const char* file, int line, LogSeverity severity)
    : severity_(severity), message_start_(0), file_(file), line_(line) {}

LogMessage::LogMessage(const char* file, int line, const char* condition)
    : severity_(LOGGING_FATAL), message_start_(0), file_(file), line_(line) {
  stream_ << "Check failed: " << condition;
}

LogMessage::~LogMessage() = default;

SystemErrorCode GetLastSystemErrorCode() {
  return 0;
}

#if PA_BUILDFLAG(IS_WIN)
Win32ErrorLogMessage::Win32ErrorLogMessage(const char* file,
                                           int line,
                                           LogSeverity severity,
                                           SystemErrorCode err)
    : LogMessage(file, line, severity), err_(err) {}

Win32ErrorLogMessage::~Win32ErrorLogMessage() = default;
#endif

CheckError::CheckError(const char* file,
                       int line,
                       LogSeverity severity,
                       const char* condition)
    : log_message_(file, line, condition), has_errno(false) {}

CheckError::CheckError(const char* file, int line, LogSeverity severity)
    : log_message_(file, line, severity), has_errno(false) {}

CheckError::CheckError(const char* file,
                       int line,
                       LogSeverity severity,
                       const char* condition,
                       SystemErrorCode)
    : log_message_(file, line, condition), has_errno(false) {}

CheckError::~CheckError() {
  log_message_.~LogMessage();
}

base::strings::CStringBuilder& CheckError::stream() {
  static base::strings::CStringBuilder builder;
  return builder;
}

namespace check_error {

Check::Check(const char* file, int line, const char* condition)
    : CheckError(file, line, LOGGING_FATAL, condition) {}

DCheck::DCheck(const char* file, int line, const char* condition)
    : CheckError(file, line, LOGGING_DFATAL, condition) {}

PCheck::PCheck(const char* file, int line, const char* condition)
    : CheckError(file, line, LOGGING_FATAL, condition) {}

PCheck::PCheck(const char* file, int line)
    : CheckError(file, line, LOGGING_FATAL) {}

DPCheck::DPCheck(const char* file, int line, const char* condition)
    : CheckError(file, line, LOGGING_DFATAL, condition) {}

NotImplemented::NotImplemented(const char* file,
                               int line,
                               const char* function)
    : CheckError(file, line, LOGGING_ERROR, function) {}

}  // namespace check_error

void RawCheckFailure(const char*) {
  std::abort();
}

}  // namespace logging
}  // namespace partition_alloc::internal
