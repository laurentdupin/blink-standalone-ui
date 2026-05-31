#ifndef STANDALONE_RENDERER_STUBS_SERVICES_METRICS_PUBLIC_CPP_UKM_BUILDERS_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_METRICS_PUBLIC_CPP_UKM_BUILDERS_H_

#include "services/metrics/public/cpp/ukm_recorder.h"

namespace ukm::builders {

class Blink_FindInPage {
 public:
  explicit Blink_FindInPage(SourceId) {}
  Blink_FindInPage& SetDidSearch(bool) { return *this; }
  Blink_FindInPage& SetDidHaveRenderSubtree(bool) { return *this; }
  Blink_FindInPage& SetDidHaveRenderSubtreeMatch(bool) { return *this; }
  Blink_FindInPage& SetDidSearchRenderSubtree(bool) { return *this; }
  Blink_FindInPage& SetDidSearchRenderSubtreeMatch(bool) { return *this; }
  Blink_FindInPage& SetDidSearchMainFrame(bool) { return *this; }
  Blink_FindInPage& SetDidSearchMainFrameMatch(bool) { return *this; }
  Blink_FindInPage& SetBeforematchExpandedHiddenMatchable(bool) {
    return *this;
  }
  void Record(UkmRecorder*) {}
};

class Blink_SVGImage {
 public:
  explicit Blink_SVGImage(SourceId) {}
  Blink_SVGImage& SetCount(int64_t) { return *this; }
  Blink_SVGImage& SetTotalTime(int64_t) { return *this; }
  void Record(UkmRecorder*) {}
};

class Network_DataUrls {
 public:
  explicit Network_DataUrls(SourceId) {}
  Network_DataUrls& SetUrlLength(int64_t) { return *this; }
  Network_DataUrls& SetParseTime(int64_t) { return *this; }
  Network_DataUrls& SetIsImage(bool) { return *this; }
  void Record(UkmRecorder*) {}
};

class MainFrameNavigation_ZstdContentEncoding {
 public:
  explicit MainFrameNavigation_ZstdContentEncoding(SourceId) {}
  MainFrameNavigation_ZstdContentEncoding& SetUsedZstd(bool) { return *this; }
  void Record(UkmRecorder*) {}
};

}  // namespace ukm::builders

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_METRICS_PUBLIC_CPP_UKM_BUILDERS_H_
