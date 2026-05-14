// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

namespace blink {

class LocalFrame;

namespace inspector_commit_load_event {

void Data(perfetto::TracedValue, LocalFrame*) {}

}  // namespace inspector_commit_load_event

}  // namespace blink
