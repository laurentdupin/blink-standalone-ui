// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_DATE_TIME_CHOOSER_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_DATE_TIME_CHOOSER_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/struct_ptr.h"

namespace blink::mojom::blink {

class DateTimeSuggestion;
class DateTimeDialogValue;
class DateTimeChooser;
using DateTimeSuggestionPtr = mojo::StructPtr<DateTimeSuggestion>;
using DateTimeDialogValuePtr = mojo::StructPtr<DateTimeDialogValue>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_DATE_TIME_CHOOSER_MOJOM_BLINK_FORWARD_H_
