// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/native_theme/native_theme.h"

#include <algorithm>
#include <cmath>
#include <optional>
#include <utility>

#include "base/no_destructor.h"
#include "cc/paint/paint_canvas.h"
#include "cc/paint/paint_flags.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkRect.h"
#include "ui/color/color_id.h"
#include "ui/color/color_provider.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/geometry/insets.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/skia_conversions.h"
#include "ui/gfx/scoped_canvas.h"
#include "ui/native_theme/native_theme_aura.h"
#include "ui/native_theme/native_theme_observer.h"

namespace gfx {

Canvas::Canvas(cc::PaintCanvas* sk_canvas, float image_scale)
    : image_scale_(image_scale), canvas_(sk_canvas) {}

Canvas::~Canvas() = default;

void Canvas::Save() {
  if (canvas_) {
    canvas_->save();
  }
}

void Canvas::Restore() {
  if (canvas_) {
    canvas_->restore();
  }
}

ScopedCanvas::ScopedCanvas(gfx::Canvas* canvas) : canvas_(canvas) {
  if (canvas_) {
    canvas_->Save();
  }
}

ScopedCanvas::~ScopedCanvas() {
  if (canvas_) {
    canvas_->Restore();
  }
}

void ScopedCanvas::FlipIfRTL(int) {}

}  // namespace gfx

namespace ui {

NativeTheme::MenuListExtraParams::MenuListExtraParams() = default;
NativeTheme::MenuListExtraParams::MenuListExtraParams(
    const NativeTheme::MenuListExtraParams&) = default;
NativeTheme::MenuListExtraParams& NativeTheme::MenuListExtraParams::operator=(
    const NativeTheme::MenuListExtraParams&) = default;

NativeTheme::TextFieldExtraParams::TextFieldExtraParams() = default;
NativeTheme::TextFieldExtraParams::TextFieldExtraParams(
    const NativeTheme::TextFieldExtraParams&) = default;
NativeTheme::TextFieldExtraParams& NativeTheme::TextFieldExtraParams::operator=(
    const NativeTheme::TextFieldExtraParams&) = default;

NativeTheme* NativeTheme::GetInstanceForNativeUi() {
  return GetInstanceForWeb();
}

NativeTheme* NativeTheme::GetInstanceForWeb() {
  static base::NoDestructor<NativeThemeAura> theme(false);
  return theme.get();
}

float NativeTheme::AdjustBorderWidthByZoom(float border_width,
                                           float zoom_level) {
  return std::max(std::floor(border_width * zoom_level), 1.0f);
}

float NativeTheme::AdjustBorderRadiusByZoom(Part part,
                                            float border_radius,
                                            float zoom) {
  return (part == kCheckbox || part == kTextField || part == kPushButton)
             ? AdjustBorderWidthByZoom(border_radius, zoom)
             : border_radius;
}

gfx::Size NativeTheme::GetPartSize(Part, State, const ExtraParams&) const {
  return {};
}

int NativeTheme::GetPaintedScrollbarTrackInset() const {
  return 0;
}

gfx::Insets NativeTheme::GetScrollbarSolidColorThumbInsets(Part) const {
  return {};
}

float NativeTheme::GetBorderRadiusForPart(Part, float, float) const {
  return 0;
}

bool NativeTheme::SupportsNinePatch(Part) const {
  return false;
}

gfx::Size NativeTheme::GetNinePatchCanvasSize(Part) const {
  return {};
}

gfx::Rect NativeTheme::GetNinePatchAperture(Part) const {
  return {};
}

SkColor NativeTheme::GetScrollbarThumbColor(
    const ColorProvider*,
    State,
    const ScrollbarThumbExtraParams&) const {
  return SK_ColorTRANSPARENT;
}

SkColor NativeTheme::GetSystemButtonPressedColor(SkColor base_color) const {
  return base_color;
}

void NativeTheme::BeginObservingOsSettingChanges() {}

void NativeTheme::AddObserver(NativeThemeObserver* observer) {
  native_theme_observers_.AddObserver(observer);
}

void NativeTheme::RemoveObserver(NativeThemeObserver* observer) {
  native_theme_observers_.RemoveObserver(observer);
}

void NativeTheme::NotifyOnNativeThemeUpdated() {
  native_theme_observers_.Notify(&NativeThemeObserver::OnNativeThemeUpdated,
                                 this);
}

void NativeTheme::NotifyOnCaptionStyleUpdated() {
  native_theme_observers_.Notify(&NativeThemeObserver::OnCaptionStyleUpdated);
}

void NativeTheme::Paint(cc::PaintCanvas* canvas,
                        const ColorProvider* color_provider,
                        Part part,
                        State state,
                        const gfx::Rect& rect,
                        const ExtraParams& extra_params,
                        bool forced_colors,
                        PreferredColorScheme color_scheme,
                        PreferredContrast contrast,
                        std::optional<SkColor> accent_color) const {
  if (rect.IsEmpty()) {
    return;
  }

  const bool dark_mode =
      color_scheme == PreferredColorScheme::kDark ||
      (color_scheme == PreferredColorScheme::kNoPreference &&
       preferred_color_scheme() == PreferredColorScheme::kDark);
  const std::optional<SkColor> accent_color_opaque = accent_color.transform(
      [](SkColor c) { return SkColorSetA(c, SK_AlphaOPAQUE); });

  canvas->save();
  canvas->clipRect(gfx::RectToSkRect(rect));
  PaintImpl(canvas, color_provider, part, state, rect, extra_params,
            forced_colors, dark_mode, contrast, accent_color_opaque);
  canvas->restore();
}

NativeTheme::NativeTheme(SystemTheme system_theme)
    : system_theme_(system_theme) {}

NativeTheme::~NativeTheme() = default;

bool NativeTheme::IsForcedDarkMode() {
  return false;
}

bool NativeTheme::IsForcedHighContrast() {
  return false;
}

void NativeTheme::PaintMenuItemBackground(
    cc::PaintCanvas* canvas,
    const ColorProvider* color_provider,
    State state,
    const gfx::Rect& rect,
    const MenuItemExtraParams& extra_params) const {
  if (!color_provider) {
    return;
  }
  const SkScalar radius = SkIntToScalar(extra_params.corner_radius);
  cc::PaintFlags flags;
  flags.setColor(color_provider->GetColor(
      state == kHovered ? kColorMenuItemBackgroundSelected
                        : kColorMenuBackground));
  canvas->drawRoundRect(gfx::RectToSkRect(rect), radius, radius, flags);
}

void NativeTheme::OnToolkitSettingsChanged(bool force_notify) {
  if (force_notify) {
    NotifyOnNativeThemeUpdated();
  }
}

void NativeTheme::SetAssociatedWebInstance(NativeTheme*) {}

bool NativeTheme::UpdateWebInstance() const {
  return false;
}

}  // namespace ui
