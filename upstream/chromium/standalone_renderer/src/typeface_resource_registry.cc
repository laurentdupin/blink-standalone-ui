#include "html_css_renderer/typeface_resource_registry.h"

#include <algorithm>
#include <cstring>
#include <mutex>
#include <unordered_map>

#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/core/SkTypeface.h"

namespace html_css_renderer {
namespace {

struct RegistryState {
  std::unordered_map<uint64_t, TypefaceResource> resources;
  std::unordered_map<const SkTypeface*, uint64_t> ids;
  uint64_t next_id = 1;
  TextBlobReplayDiagnostics diagnostics;
};

std::mutex& RegistryMutex() {
  static auto* mutex = new std::mutex();
  return *mutex;
}

RegistryState& Registry() {
  static auto* registry = new RegistryState();
  return *registry;
}

}  // namespace

void ResetTypefaceResourceRegistryForFrame() {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  Registry().resources.clear();
  Registry().ids.clear();
  Registry().next_id = 1;
  Registry().diagnostics = TextBlobReplayDiagnostics{
      .enabled = Registry().diagnostics.enabled,
  };
}

uint64_t RegisterSameProcessTypefaceResource(SkTypeface* typeface) {
  if (!typeface) {
    return 0;
  }
  std::lock_guard<std::mutex> lock(RegistryMutex());
  auto& registry = Registry();
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

sk_sp<SkTypeface> LookupSameProcessTypefaceResource(uint64_t id) {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  auto& registry = Registry();
  ++registry.diagnostics.typeface_lookup_attempt_count;
  const auto found = registry.resources.find(id);
  if (found == registry.resources.end() || !found->second.typeface) {
    ++registry.diagnostics.typeface_lookup_failure_count;
    return nullptr;
  }
  ++registry.diagnostics.typeface_lookup_success_count;
  return found->second.typeface;
}

std::vector<TypefaceResource> SnapshotTypefaceResources() {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  std::vector<TypefaceResource> resources;
  resources.reserve(Registry().resources.size());
  for (const auto& [id, resource] : Registry().resources) {
    resources.push_back(resource);
  }
  std::sort(resources.begin(), resources.end(),
            [](const TypefaceResource& lhs, const TypefaceResource& rhs) {
              return lhs.id < rhs.id;
            });
  return resources;
}

void SetTextBlobReplayDiagnosticsEnabled(bool enabled) {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  Registry().diagnostics.enabled = enabled;
}

TextBlobReplayDiagnostics SnapshotTextBlobReplayDiagnostics() {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  return Registry().diagnostics;
}

void RecordTextBlobDeserializeAttempt() {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  ++Registry().diagnostics.deserialize_attempt_count;
}

void RecordTextBlobDeserializeSuccess() {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  ++Registry().diagnostics.deserialize_success_count;
}

void RecordTextBlobDeserializeFailure() {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  ++Registry().diagnostics.deserialize_failure_count;
}

void RecordDiagnosticTypefaceFallback() {
  std::lock_guard<std::mutex> lock(RegistryMutex());
  ++Registry().diagnostics.diagnostic_typeface_fallback_count;
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
