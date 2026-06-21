// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/content_settings/core/common/content_settings.mojom.h"
#include "components/content_settings/core/common/content_settings.mojom-blink.h"
#include "components/content_settings/core/common/content_settings.mojom-shared-internal.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include <utility>

namespace content_settings::mojom {

PatternParts::PatternParts()
    : is_scheme_wildcard(false),
      has_domain_wildcard(false),
      is_port_wildcard(false),
      is_path_wildcard(false) {}

PatternParts::PatternParts(const std::string& scheme_in,
                           bool is_scheme_wildcard_in,
                           const std::string& host_in,
                           bool has_domain_wildcard_in,
                           const std::string& port_in,
                           bool is_port_wildcard_in,
                           const std::string& path_in,
                           bool is_path_wildcard_in)
    : scheme(scheme_in),
      is_scheme_wildcard(is_scheme_wildcard_in),
      host(host_in),
      has_domain_wildcard(has_domain_wildcard_in),
      port(port_in),
      is_port_wildcard(is_port_wildcard_in),
      path(path_in),
      is_path_wildcard(is_path_wildcard_in) {}

PatternParts::~PatternParts() = default;

size_t PatternParts::Hash(size_t seed) const {
  return seed;
}

void PatternParts::WriteIntoTrace(perfetto::TracedValue) const {}

bool PatternParts::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}

ContentSettingsPattern::ContentSettingsPattern() : is_valid(false) {}

ContentSettingsPattern::ContentSettingsPattern(PatternPartsPtr parts_in,
                                               bool is_valid_in)
    : parts(std::move(parts_in)), is_valid(is_valid_in) {}

ContentSettingsPattern::~ContentSettingsPattern() = default;

size_t ContentSettingsPattern::Hash(size_t seed) const {
  return seed;
}

void ContentSettingsPattern::WriteIntoTrace(perfetto::TracedValue) const {}

bool ContentSettingsPattern::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}

}  // namespace content_settings::mojom

namespace content_settings::mojom::blink {

PatternParts::PatternParts()
    : is_scheme_wildcard(false),
      has_domain_wildcard(false),
      is_port_wildcard(false),
      is_path_wildcard(false) {}

PatternParts::PatternParts(const ::blink::String& scheme_in,
                           bool is_scheme_wildcard_in,
                           const ::blink::String& host_in,
                           bool has_domain_wildcard_in,
                           const ::blink::String& port_in,
                           bool is_port_wildcard_in,
                           const ::blink::String& path_in,
                           bool is_path_wildcard_in)
    : scheme(scheme_in),
      is_scheme_wildcard(is_scheme_wildcard_in),
      host(host_in),
      has_domain_wildcard(has_domain_wildcard_in),
      port(port_in),
      is_port_wildcard(is_port_wildcard_in),
      path(path_in),
      is_path_wildcard(is_path_wildcard_in) {}

PatternParts::~PatternParts() = default;

size_t PatternParts::Hash(size_t seed) const {
  return seed;
}

void PatternParts::WriteIntoTrace(perfetto::TracedValue) const {}

bool PatternParts::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}

ContentSettingsPattern::ContentSettingsPattern() : is_valid(false) {}

ContentSettingsPattern::ContentSettingsPattern(PatternPartsPtr parts_in,
                                               bool is_valid_in)
    : parts(std::move(parts_in)), is_valid(is_valid_in) {}

ContentSettingsPattern::~ContentSettingsPattern() = default;

size_t ContentSettingsPattern::Hash(size_t seed) const {
  return seed;
}

void ContentSettingsPattern::WriteIntoTrace(perfetto::TracedValue) const {}

bool ContentSettingsPattern::Validate(
    const void* data,
    mojo::internal::ValidationContext* validation_context) {
  return Data_::Validate(data, validation_context);
}

}  // namespace content_settings::mojom::blink

namespace content_settings::mojom::internal {

bool PatternParts_Data::Validate(const void*,
                                 mojo::internal::ValidationContext*) {
  return true;
}

PatternParts_Data::PatternParts_Data()
    : header_({sizeof(*this), 0}),
      is_scheme_wildcard(false),
      has_domain_wildcard(false),
      is_port_wildcard(false),
      is_path_wildcard(false),
      pad4_{} {}

bool ContentSettingsPattern_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

ContentSettingsPattern_Data::ContentSettingsPattern_Data()
    : header_({sizeof(*this), 0}), is_valid(false), padfinal_{} {}

}  // namespace content_settings::mojom::internal

namespace mojo {

bool StructTraits<content_settings::mojom::PatternParts::DataView,
                  content_settings::mojom::PatternPartsPtr>::
    Read(content_settings::mojom::PatternParts::DataView,
         content_settings::mojom::PatternPartsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<content_settings::mojom::ContentSettingsPattern::DataView,
                  content_settings::mojom::ContentSettingsPatternPtr>::
    Read(content_settings::mojom::ContentSettingsPattern::DataView,
         content_settings::mojom::ContentSettingsPatternPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<content_settings::mojom::blink::PatternParts::DataView,
                  content_settings::mojom::blink::PatternPartsPtr>::
    Read(content_settings::mojom::blink::PatternParts::DataView,
         content_settings::mojom::blink::PatternPartsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<content_settings::mojom::blink::ContentSettingsPattern::DataView,
                  content_settings::mojom::blink::ContentSettingsPatternPtr>::
    Read(content_settings::mojom::blink::ContentSettingsPattern::DataView,
         content_settings::mojom::blink::ContentSettingsPatternPtr* output) {
  output->reset();
  return false;
}

}  // namespace mojo
