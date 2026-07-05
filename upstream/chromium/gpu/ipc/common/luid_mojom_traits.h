// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_IPC_COMMON_LUID_MOJOM_TRAITS_H_
#define GPU_IPC_COMMON_LUID_MOJOM_TRAITS_H_

#include "build/build_config.h"
#include "gpu/ipc/common/gpu_ipc_common_export.h"
#include "gpu/ipc/common/luid.mojom-shared.h"

#if BUILDFLAG(IS_WIN)
#include "base/win/windows_types.h"
#elif defined(HTML_CSS_RENDERER_STANDALONE)
struct CHROME_LUID {
  int32_t HighPart = 0;
  uint32_t LowPart = 0;
};
#endif

namespace mojo {

template <>
struct GPU_IPC_COMMON_EXPORT StructTraits<gpu::mojom::LuidDataView,
                                          ::CHROME_LUID> {
  static bool Read(gpu::mojom::LuidDataView data, ::CHROME_LUID* out);

  static int32_t high(const ::CHROME_LUID& input) { return input.HighPart; }

  static uint32_t low(const ::CHROME_LUID& input) { return input.LowPart; }
};

}  // namespace mojo

#endif  // GPU_IPC_COMMON_LUID_MOJOM_TRAITS_H_
