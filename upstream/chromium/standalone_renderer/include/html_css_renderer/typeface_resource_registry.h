#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_TYPEFACE_RESOURCE_REGISTRY_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_TYPEFACE_RESOURCE_REGISTRY_H_

#include <cstdint>
#include <string>
#include <vector>

#include "third_party/skia/include/core/SkFontStyle.h"
#include "third_party/skia/include/core/SkRefCnt.h"
#include "third_party/skia/include/core/SkTypeface.h"

namespace html_css_renderer {

struct TypefaceResource {
  uint64_t id = 0;
  sk_sp<SkTypeface> typeface;
  std::string family_name;
  int weight = 0;
  int width = 0;
  SkFontStyle::Slant slant = SkFontStyle::kUpright_Slant;
  bool same_process_only = true;
  bool portable_font_data_available = false;
};

struct TextBlobReplayDiagnostics {
  bool enabled = false;
  uint64_t deserialize_attempt_count = 0;
  uint64_t deserialize_success_count = 0;
  uint64_t deserialize_failure_count = 0;
  uint64_t typeface_lookup_attempt_count = 0;
  uint64_t typeface_lookup_success_count = 0;
  uint64_t typeface_lookup_failure_count = 0;
};

void ResetTypefaceResourceRegistryForFrame();
uint64_t RegisterSameProcessTypefaceResource(SkTypeface* typeface);
sk_sp<SkTypeface> LookupSameProcessTypefaceResource(uint64_t id);
std::vector<TypefaceResource> SnapshotTypefaceResources();
void SetTextBlobReplayDiagnosticsEnabled(bool enabled);
TextBlobReplayDiagnostics SnapshotTextBlobReplayDiagnostics();
void RecordTextBlobDeserializeAttempt();
void RecordTextBlobDeserializeSuccess();
void RecordTextBlobDeserializeFailure();

}  // namespace html_css_renderer

extern "C" uint64_t StandaloneRendererRegisterSameProcessTypefaceForSkTextBlob(
    SkTypeface* typeface);
extern "C" SkTypeface*
StandaloneRendererLookupSameProcessTypefaceForSkTextBlob(uint64_t id);
extern "C" void StandaloneRendererResetSameProcessTypefaceResourcesForFrame();
extern "C" void StandaloneRendererSetTextBlobReplayDiagnosticsEnabled(
    int enabled);
extern "C" int StandaloneRendererTextBlobReplayDiagnosticsEnabled();
extern "C" int StandaloneRendererSameProcessTypefaceResourceCount();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupAttemptCount();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupSuccessCount();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupFailureCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeAttemptCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeSuccessCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeFailureCount();
extern "C" int StandaloneRendererSameProcessTypefaceFamilyAt(int index,
                                                              char* buffer,
                                                              int buffer_size);

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_TYPEFACE_RESOURCE_REGISTRY_H_
