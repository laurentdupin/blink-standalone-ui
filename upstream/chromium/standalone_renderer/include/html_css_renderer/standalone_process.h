// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef HTML_CSS_RENDERER_STANDALONE_PROCESS_H_
#define HTML_CSS_RENDERER_STANDALONE_PROCESS_H_

namespace html_css_renderer {

void ConfigureStandaloneToolProcess();
void InitializeStandaloneIcu();
void SetStandaloneCrashBreadcrumb(const char* stage);

}  // namespace html_css_renderer

extern "C" void HtmlCssRendererStandaloneSetCrashBreadcrumb(const char* stage);

#endif  // HTML_CSS_RENDERER_STANDALONE_PROCESS_H_
