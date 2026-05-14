#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_LCP_CRITICAL_PATH_PREDICTOR_ELEMENT_LOCATOR_PB_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_LCP_CRITICAL_PATH_PREDICTOR_ELEMENT_LOCATOR_PB_H_

#include <string>

namespace blink {

class ElementLocator {
 public:
  bool ParseFromString(const std::string&) { return false; }
  std::string SerializeAsString() const { return {}; }
};

}  // namespace blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_LCP_CRITICAL_PATH_PREDICTOR_ELEMENT_LOCATOR_PB_H_
