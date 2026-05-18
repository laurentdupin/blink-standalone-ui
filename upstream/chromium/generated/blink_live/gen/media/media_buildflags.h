// Standalone Blink export shim for //media:media_buildflags.
//
// The standalone renderer only attempts static PNG image decode in this build
// mode. Keep optional media/image formats disabled unless their real generated
// headers and decoder dependencies are exported.

#ifndef MEDIA_MEDIA_BUILDFLAGS_H_
#define MEDIA_MEDIA_BUILDFLAGS_H_

#include "build/buildflag.h"  // IWYU pragma: export

#define BUILDFLAG_INTERNAL_ENABLE_AV1_DECODER() (0)

#endif  // MEDIA_MEDIA_BUILDFLAGS_H_
