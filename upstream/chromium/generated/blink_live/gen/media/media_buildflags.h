// Standalone Blink export shim for //media:media_buildflags.
//
// The standalone renderer only attempts static PNG image decode in this build
// mode. Keep optional media/image formats disabled unless their real generated
// headers and decoder dependencies are exported.

#ifndef MEDIA_MEDIA_BUILDFLAGS_H_
#define MEDIA_MEDIA_BUILDFLAGS_H_

#include "build/buildflag.h"  // IWYU pragma: export

#define BUILDFLAG_INTERNAL_ENABLE_AV1_DECODER() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_AC3_EAC3_AUDIO() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_AC4_AUDIO() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_DOLBY_VISION() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_DTS_AUDIO() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_ENCRYPTED_DOLBY_VISION() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_HEVC() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_IAMF_AUDIO() (0)
#define BUILDFLAG_INTERNAL_ENABLE_PLATFORM_MPEG_H_AUDIO() (0)

#endif  // MEDIA_MEDIA_BUILDFLAGS_H_
