// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/skresources/include/SkResources.h"

#include "include/core/SkImage.h"

namespace skresources {

ImageAsset::FrameData ImageAsset::getFrameData(float t) {
  return {getFrame(t), SkSamplingOptions(SkFilterMode::kLinear,
                                         SkMipmapMode::kNearest),
          SkMatrix::I(), SizeFit::kCenter};
}

}  // namespace skresources
