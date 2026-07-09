// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_TOOLS_FRAME_SINK_PROBE_CHROMIUM_FRAME_SINK_PROBE_H_
#define STANDALONE_RENDERER_TOOLS_FRAME_SINK_PROBE_CHROMIUM_FRAME_SINK_PROBE_H_

#include <string>

namespace html_css_renderer {

std::string RunChromiumRootFrameSinkProof(int width, int height);
std::string RunChromiumAsyncFrameSinkProof(int width, int height);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_TOOLS_FRAME_SINK_PROBE_CHROMIUM_FRAME_SINK_PROBE_H_
