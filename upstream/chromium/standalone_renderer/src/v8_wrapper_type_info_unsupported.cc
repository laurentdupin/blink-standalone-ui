// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// The standalone renderer does not enable Blink's generated V8 bindings in
// Phase 1. Some active DOM classes still carry WrapperTypeInfo references for
// tracing/type metadata, so provide inert metadata records without installing
// JavaScript interface templates.

#include "third_party/blink/renderer/bindings/core/v8/v8_event_target.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_file.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_html_canvas_element.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_html_meta_element.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_node.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_test_report_body.h"
#include "third_party/blink/renderer/core/dom/events/event_target.h"
#include "third_party/blink/renderer/core/dom/node.h"
#include "third_party/blink/renderer/core/fileapi/file.h"
#include "third_party/blink/renderer/core/frame/test_report_body.h"
#include "third_party/blink/renderer/core/html/canvas/html_canvas_element.h"
#include "third_party/blink/renderer/core/html/html_meta_element.h"
#include "third_party/blink/renderer/platform/bindings/wrapper_type_info.h"

namespace blink {

const WrapperTypeInfo V8EventTarget::wrapper_type_info_{
    {gin::kEmbedderBlink},
    nullptr,
    nullptr,
    "EventTarget",
    nullptr,
    V8EventTarget::kThisTag,
    V8EventTarget::kMaxSubclassTag,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kObjectClassId,
    WrapperTypeInfo::kIdlInterface,
    false,
};

const WrapperTypeInfo& EventTarget::wrapper_type_info_ =
    V8EventTarget::wrapper_type_info_;

const WrapperTypeInfo V8Node::wrapper_type_info_{
    {gin::kEmbedderBlink},
    nullptr,
    nullptr,
    "Node",
    V8EventTarget::GetWrapperTypeInfo(),
    V8Node::kThisTag,
    V8Node::kMaxSubclassTag,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kNodeClassId,
    WrapperTypeInfo::kIdlInterface,
    false,
};

const WrapperTypeInfo& Node::wrapper_type_info_ = V8Node::wrapper_type_info_;

const WrapperTypeInfo V8File::wrapper_type_info_{
    {gin::kEmbedderBlink},
    nullptr,
    nullptr,
    "File",
    nullptr,
    V8File::kThisTag,
    V8File::kMaxSubclassTag,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kObjectClassId,
    WrapperTypeInfo::kIdlInterface,
    false,
};

const WrapperTypeInfo& File::wrapper_type_info_ = V8File::wrapper_type_info_;

const WrapperTypeInfo V8TestReportBody::wrapper_type_info_{
    {gin::kEmbedderBlink},
    nullptr,
    nullptr,
    "TestReportBody",
    nullptr,
    V8TestReportBody::kThisTag,
    V8TestReportBody::kMaxSubclassTag,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kObjectClassId,
    WrapperTypeInfo::kIdlInterface,
    false,
};

const WrapperTypeInfo& TestReportBody::wrapper_type_info_ =
    V8TestReportBody::wrapper_type_info_;

const WrapperTypeInfo V8HTMLCanvasElement::wrapper_type_info_{
    {gin::kEmbedderBlink},
    nullptr,
    nullptr,
    "HTMLCanvasElement",
    V8Node::GetWrapperTypeInfo(),
    V8HTMLCanvasElement::kThisTag,
    V8HTMLCanvasElement::kMaxSubclassTag,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kNodeClassId,
    WrapperTypeInfo::kIdlInterface,
    false,
};

const WrapperTypeInfo& HTMLCanvasElement::wrapper_type_info_ =
    V8HTMLCanvasElement::wrapper_type_info_;

const WrapperTypeInfo V8HTMLMetaElement::wrapper_type_info_{
    {gin::kEmbedderBlink},
    nullptr,
    nullptr,
    "HTMLMetaElement",
    V8Node::GetWrapperTypeInfo(),
    V8HTMLMetaElement::kThisTag,
    V8HTMLMetaElement::kMaxSubclassTag,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kNodeClassId,
    WrapperTypeInfo::kIdlInterface,
    false,
};

const WrapperTypeInfo& HTMLMetaElement::wrapper_type_info_ =
    V8HTMLMetaElement::wrapper_type_info_;

}  // namespace blink
