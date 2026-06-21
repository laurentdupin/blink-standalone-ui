#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_MEDIA_TYPE_NAMES_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_MEDIA_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::media_type_names {
extern const AtomicString& kAll;
extern const AtomicString& kScreen;
extern const AtomicString& kPrint;
extern const AtomicString& kTv;

constexpr unsigned kNamesCount = 4;

void Init();


}  // namespace blink::media_type_names

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_MEDIA_TYPE_NAMES_H_
