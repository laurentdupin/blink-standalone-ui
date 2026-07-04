#include "html_css_renderer/typeface_resource_registry.h"

#include <algorithm>
#include <cstring>
#include <unordered_map>

#include "base/no_destructor.h"
#include "base/synchronization/lock.h"
#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/core/SkTypeface.h"

namespace html_css_renderer {
namespace {

struct RegistryState {
  std::unordered_map<uint64_t, TypefaceResource> resources;
  std::unordered_map<uint64_t, TypefaceResource> replay_resources;
  std::unordered_map<const SkTypeface*, uint64_t> ids;
  uint64_t next_id = 1;
  TextBlobReplayDiagnostics diagnostics;
};

base::Lock& RegistryLock() {
  static base::NoDestructor<base::Lock> lock;
  return *lock;
}

RegistryState& Registry() {
  static auto* registry = new RegistryState();
  return *registry;
}

std::unordered_map<uint64_t, RegistryState>& Registries() {
  static auto* registries = new std::unordered_map<uint64_t, RegistryState>();
  return *registries;
}

uint64_t& NextRegistryContextId() {
  static uint64_t* next_id = new uint64_t(1);
  return *next_id;
}

thread_local uint64_t g_current_registry_context_id = 0;

RegistryState& CurrentRegistryLocked() {
  if (g_current_registry_context_id != 0) {
    auto it = Registries().find(g_current_registry_context_id);
    if (it != Registries().end())
      return it->second;
  }
  return Registry();
}

}  // namespace

void ResetTypefaceResourceRegistryForFrame() {
  base::AutoLock auto_lock(RegistryLock());
  auto& registry = CurrentRegistryLocked();
  registry.resources.clear();
  registry.ids.clear();
  registry.next_id = 1;
  registry.diagnostics = TextBlobReplayDiagnostics{
      .enabled = registry.diagnostics.enabled,
  };
}

uint64_t CreateTypefaceResourceRegistryContext() {
  base::AutoLock auto_lock(RegistryLock());
  const uint64_t context_id = NextRegistryContextId()++;
  Registries().emplace(context_id, RegistryState());
  return context_id;
}

void DestroyTypefaceResourceRegistryContext(uint64_t context_id) {
  base::AutoLock auto_lock(RegistryLock());
  Registries().erase(context_id);
  if (g_current_registry_context_id == context_id)
    g_current_registry_context_id = 0;
}

void SetCurrentTypefaceResourceRegistryContext(uint64_t context_id) {
  base::AutoLock auto_lock(RegistryLock());
  if (context_id != 0 && Registries().find(context_id) == Registries().end())
    context_id = 0;
  g_current_registry_context_id = context_id;
}

uint64_t RegisterSameProcessTypefaceResource(SkTypeface* typeface) {
  if (!typeface) {
    return 0;
  }
  base::AutoLock auto_lock(RegistryLock());
  auto& registry = CurrentRegistryLocked();
  if (const auto found = registry.ids.find(typeface);
      found != registry.ids.end()) {
    return found->second;
  }
  const uint64_t id = registry.next_id++;
  SkString family;
  typeface->getFamilyName(&family);
  TypefaceResource resource;
  resource.id = id;
  resource.typeface = sk_ref_sp(typeface);
  resource.family_name = family.c_str();
  resource.weight = typeface->fontStyle().weight();
  resource.width = typeface->fontStyle().width();
  resource.slant = typeface->fontStyle().slant();
  registry.resources[id] = std::move(resource);
  registry.ids[typeface] = id;
  return id;
}

bool RegisterTypefaceResourceWithId(uint64_t id, SkTypeface* typeface) {
  if (!id || !typeface) {
    return false;
  }
  base::AutoLock auto_lock(RegistryLock());
  auto& registry = CurrentRegistryLocked();
  SkString family;
  typeface->getFamilyName(&family);
  TypefaceResource resource;
  resource.id = id;
  resource.typeface = sk_ref_sp(typeface);
  resource.family_name = family.c_str();
  resource.weight = typeface->fontStyle().weight();
  resource.width = typeface->fontStyle().width();
  resource.slant = typeface->fontStyle().slant();
  resource.same_process_only = true;
  resource.portable_font_data_available = false;
  registry.resources[id] = std::move(resource);
  registry.ids[typeface] = id;
  registry.next_id = std::max(registry.next_id, id + 1);
  return true;
}

void FreezeTypefaceResourcesForReplay() {
  base::AutoLock auto_lock(RegistryLock());
  auto& registry = CurrentRegistryLocked();
  registry.replay_resources = registry.resources;
}

sk_sp<SkTypeface> LookupSameProcessTypefaceResource(uint64_t id) {
  base::AutoLock auto_lock(RegistryLock());
  auto& registry = CurrentRegistryLocked();
  ++registry.diagnostics.typeface_lookup_attempt_count;
  const auto found = registry.resources.find(id);
  if (found != registry.resources.end() && found->second.typeface) {
    ++registry.diagnostics.typeface_lookup_success_count;
    return found->second.typeface;
  }
  const auto replay_found = registry.replay_resources.find(id);
  if (replay_found != registry.replay_resources.end() &&
      replay_found->second.typeface) {
    ++registry.diagnostics.typeface_lookup_success_count;
    return replay_found->second.typeface;
  }
  ++registry.diagnostics.typeface_lookup_failure_count;
  return nullptr;
}

std::vector<TypefaceResource> SnapshotTypefaceResources() {
  base::AutoLock auto_lock(RegistryLock());
  std::vector<TypefaceResource> resources;
  auto& registry = CurrentRegistryLocked();
  resources.reserve(registry.resources.size());
  for (const auto& [id, resource] : registry.resources) {
    resources.push_back(resource);
  }
  std::sort(resources.begin(), resources.end(),
            [](const TypefaceResource& lhs, const TypefaceResource& rhs) {
              return lhs.id < rhs.id;
            });
  return resources;
}

void SetTextBlobReplayDiagnosticsEnabled(bool enabled) {
  base::AutoLock auto_lock(RegistryLock());
  CurrentRegistryLocked().diagnostics.enabled = enabled;
}

TextBlobReplayDiagnostics SnapshotTextBlobReplayDiagnostics() {
  base::AutoLock auto_lock(RegistryLock());
  return CurrentRegistryLocked().diagnostics;
}

void RecordTextBlobDeserializeAttempt() {
  base::AutoLock auto_lock(RegistryLock());
  ++CurrentRegistryLocked().diagnostics.deserialize_attempt_count;
}

void RecordTextBlobDeserializeSuccess() {
  base::AutoLock auto_lock(RegistryLock());
  ++CurrentRegistryLocked().diagnostics.deserialize_success_count;
}

void RecordTextBlobDeserializeFailure() {
  base::AutoLock auto_lock(RegistryLock());
  ++CurrentRegistryLocked().diagnostics.deserialize_failure_count;
}

void RecordDiagnosticTypefaceFallback() {
  base::AutoLock auto_lock(RegistryLock());
  ++CurrentRegistryLocked().diagnostics.diagnostic_typeface_fallback_count;
}

}  // namespace html_css_renderer

extern "C" uint64_t StandaloneRendererRegisterSameProcessTypefaceForSkTextBlob(
    SkTypeface* typeface) {
  return html_css_renderer::RegisterSameProcessTypefaceResource(typeface);
}

extern "C" SkTypeface*
StandaloneRendererLookupSameProcessTypefaceForSkTextBlob(uint64_t id) {
  sk_sp<SkTypeface> typeface =
      html_css_renderer::LookupSameProcessTypefaceResource(id);
  return typeface.get();
}

extern "C" void StandaloneRendererResetSameProcessTypefaceResourcesForFrame() {
  html_css_renderer::ResetTypefaceResourceRegistryForFrame();
}

extern "C" void StandaloneRendererSetTextBlobReplayDiagnosticsEnabled(
    int enabled) {
  html_css_renderer::SetTextBlobReplayDiagnosticsEnabled(enabled != 0);
}

extern "C" int StandaloneRendererTextBlobReplayDiagnosticsEnabled() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics().enabled ? 1 : 0;
}

extern "C" int StandaloneRendererSameProcessTypefaceResourceCount() {
  return static_cast<int>(
      html_css_renderer::SnapshotTypefaceResources().size());
}

extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupAttemptCount() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics()
      .typeface_lookup_attempt_count;
}

extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupSuccessCount() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics()
      .typeface_lookup_success_count;
}

extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupFailureCount() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics()
      .typeface_lookup_failure_count;
}

extern "C" uint64_t StandaloneRendererTextBlobDeserializeAttemptCount() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics()
      .deserialize_attempt_count;
}

extern "C" uint64_t StandaloneRendererTextBlobDeserializeSuccessCount() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics()
      .deserialize_success_count;
}

extern "C" uint64_t StandaloneRendererTextBlobDeserializeFailureCount() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics()
      .deserialize_failure_count;
}

extern "C" uint64_t StandaloneRendererDiagnosticTypefaceFallbackCount() {
  return html_css_renderer::SnapshotTextBlobReplayDiagnostics()
      .diagnostic_typeface_fallback_count;
}

extern "C" int StandaloneRendererSameProcessTypefaceFamilyAt(int index,
                                                              char* buffer,
                                                              int buffer_size) {
  if (!buffer || buffer_size <= 0 || index < 0) {
    return 0;
  }
  const std::vector<html_css_renderer::TypefaceResource> resources =
      html_css_renderer::SnapshotTypefaceResources();
  if (index >= static_cast<int>(resources.size())) {
    return 0;
  }
  const std::string& family = resources[static_cast<size_t>(index)].family_name;
  const int copy_size =
      std::min(static_cast<int>(family.size()), buffer_size - 1);
  std::memcpy(buffer, family.data(), copy_size);
  buffer[copy_size] = '\0';
  return copy_size;
}
