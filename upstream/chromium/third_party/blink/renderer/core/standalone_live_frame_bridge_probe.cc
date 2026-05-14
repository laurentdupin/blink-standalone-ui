// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/testing/dummy_page_holder.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <memory>
#include <optional>
#include <utility>
#include <string>
#include <vector>

#include "cc/paint/paint_op.h"
#include "cc/paint/paint_op_buffer_iterator.h"
#include "cc/paint/paint_record.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPath.h"
#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/node.h"
#include "third_party/blink/renderer/core/dom/text.h"
#include "third_party/blink/renderer/core/core_initializer.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/css/style_engine.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/html/html_body_element.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/html/html_style_element.h"
#include "third_party/blink/renderer/core/layout/layout_box.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_display_item.h"
#include "third_party/blink/renderer/platform/graphics/paint/geometry_mapper.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_artifact.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_chunk.h"
#include "third_party/blink/renderer/platform/geometry/length.h"
#include "third_party/blink/renderer/platform/wtf/wtf.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/skia/include/core/SkTextBlob.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/rect_conversions.h"

namespace blink::standalone_renderer_probe {

extern "C" bool g_standalone_blink_saw_font_draw_text;
extern "C" int g_standalone_blink_viewport_width;
extern "C" int g_standalone_blink_viewport_height;

namespace {

struct LiveFramePaintProbeResult {
  int lifecycle_reached_paint_clean = 0;
  int paint_chunk_count = 0;
  int display_item_count = 0;
};

struct LiveExportedGlyph {
  uint32_t glyph_id = 0;
  float x = 0.0f;
  float y = 0.0f;
};

struct LiveExportedDrawOp {
  int type = 0;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 1.0f;
  float font_size = 0.0f;
  float radius_x = 0.0f;
  float radius_y = 0.0f;
  std::vector<LiveExportedGlyph> glyphs;
  int mask_width = 0;
  int mask_height = 0;
  std::vector<uint8_t> alpha_mask;
  std::vector<uint8_t> rgba_pixels;
};

struct LiveFramePaintProbeCache {
  DummyPageHolder* holder = nullptr;
  LiveFramePaintProbeResult result;
  std::string body_html;
  std::vector<LiveExportedDrawOp> exported_draw_ops;
  int viewport_width = 320;
  int viewport_height = 200;
  bool initialized = false;
};

LiveFramePaintProbeCache& ProbeCache() {
  static LiveFramePaintProbeCache* cache = new LiveFramePaintProbeCache();
  return *cache;
}

void TraceLiveFrameProbeStage(const char* stage) {
}

void DumpNodeForStandaloneRenderer(const Node& node, int depth) {
  const String node_name = node.nodeName();
  const String text = node.textContent();
  if (const auto* text_node = DynamicTo<Text>(node)) {
  }
  if (const auto* element = DynamicTo<Element>(node)) {
    const String namespace_uri = element->namespaceURI();
    if (const ComputedStyle* style = element->GetComputedStyle()) {
      const LayoutObject* layout_object = element->GetLayoutObject();
      PhysicalOffset physical_location;
      PhysicalOffset paint_offset;
      PhysicalSize stitched_size;
      if (const auto* box = DynamicTo<LayoutBox>(layout_object)) {
        physical_location = box->PhysicalLocation();
        paint_offset = box->FirstFragment().PaintOffset();
        stitched_size = box->StitchedSize();
      }
    }
  }
  if (depth >= 4) {
    return;
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    DumpNodeForStandaloneRenderer(*child, depth + 1);
  }
}

void AppendSkColor(LiveExportedDrawOp& op, const SkColor4f& color) {
  op.r = color.fR;
  op.g = color.fG;
  op.b = color.fB;
  op.a = color.fA;
}

void AppendFillRectOp(float x,
                      float y,
                      float width,
                      float height,
                      const SkColor4f& color,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (width <= 0.0f || height <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 1;
  exported.x = x;
  exported.y = y;
  exported.width = width;
  exported.height = height;
  AppendSkColor(exported, color);
  exported_draw_ops.push_back(exported);
}

void AppendSkRectFillOp(const SkRect& rect,
                        float translate_x,
                        float translate_y,
                        const SkColor4f& color,
                        std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!rect.isFinite()) {
    return;
  }
  AppendFillRectOp(translate_x + rect.x(), translate_y + rect.y(),
                   rect.width(), rect.height(), color, exported_draw_ops);
}

void AppendSkIRectFillOp(const SkIRect& rect,
                         float translate_x,
                         float translate_y,
                         const SkColor4f& color,
                         std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  AppendFillRectOp(translate_x + static_cast<float>(rect.x()),
                   translate_y + static_cast<float>(rect.y()),
                   static_cast<float>(rect.width()),
                   static_cast<float>(rect.height()), color,
                   exported_draw_ops);
}

void AppendStrokeRectOp(float x,
                        float y,
                        float width,
                        float height,
                        SkScalar stroke_width,
                        const SkColor4f& color,
                        std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (width <= 0.0f || height <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 4;
  exported.x = x;
  exported.y = y;
  exported.width = width;
  exported.height = height;
  exported.font_size = stroke_width > 0.0f ? stroke_width : 1.0f;
  AppendSkColor(exported, color);
  exported_draw_ops.push_back(exported);
}

void AppendRRectOp(float x,
                   float y,
                   float width,
                   float height,
                   float radius_x,
                   float radius_y,
                   SkScalar stroke_width,
                   const SkColor4f& color,
                   bool stroke,
                   std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (width <= 0.0f || height <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = stroke ? 6 : 5;
  exported.x = x;
  exported.y = y;
  exported.width = width;
  exported.height = height;
  exported.radius_x = radius_x;
  exported.radius_y = radius_y;
  exported.font_size = stroke_width > 0.0f ? stroke_width : 1.0f;
  AppendSkColor(exported, color);
  exported_draw_ops.push_back(exported);
}

void AppendSkRectOpWithFlags(
    const SkRect& rect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!rect.isFinite()) {
    return;
  }
  if (flags.HasShader() && flags.getStyle() != cc::PaintFlags::kStroke_Style) {
    const int bitmap_width = SkScalarCeilToInt(rect.width());
    const int bitmap_height = SkScalarCeilToInt(rect.height());
    if (bitmap_width > 0 && bitmap_height > 0) {
      std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                       static_cast<size_t>(bitmap_height) * 4u);
      SkImageInfo info =
          SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                            kPremul_SkAlphaType);
      sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
          info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
      if (surface) {
        SkCanvas* canvas = surface->getCanvas();
        canvas->clear(SK_ColorTRANSPARENT);
        canvas->translate(-rect.x(), -rect.y());
        canvas->drawRect(rect, flags.ToSkPaint());
        LiveExportedDrawOp exported;
        exported.type = 7;
        exported.x = translate_x + rect.x();
        exported.y = translate_y + rect.y();
        exported.width = static_cast<float>(bitmap_width);
        exported.height = static_cast<float>(bitmap_height);
        exported.mask_width = bitmap_width;
        exported.mask_height = bitmap_height;
        exported.rgba_pixels = std::move(rgba_pixels);
        exported_draw_ops.push_back(std::move(exported));
        return;
      }
    }
  }
  if (flags.getStyle() == cc::PaintFlags::kStroke_Style) {
    AppendStrokeRectOp(translate_x + rect.x(), translate_y + rect.y(),
                       rect.width(), rect.height(), flags.getStrokeWidth(),
                       flags.getColor4f(), exported_draw_ops);
    return;
  }
  AppendSkRectFillOp(rect, translate_x, translate_y, flags.getColor4f(),
                     exported_draw_ops);
}

void AppendSkIRectOpWithFlags(
    const SkIRect& rect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (flags.getStyle() == cc::PaintFlags::kStroke_Style) {
    AppendStrokeRectOp(translate_x + static_cast<float>(rect.x()),
                       translate_y + static_cast<float>(rect.y()),
                       static_cast<float>(rect.width()),
                       static_cast<float>(rect.height()),
                       flags.getStrokeWidth(), flags.getColor4f(),
                       exported_draw_ops);
    return;
  }
  AppendSkIRectFillOp(rect, translate_x, translate_y, flags.getColor4f(),
                      exported_draw_ops);
}

void AppendSkRRectOpWithFlags(
    const SkRRect& rrect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  const SkRect rect = rrect.rect();
  if (!rect.isFinite()) {
    return;
  }
  const SkVector radii = rrect.getSimpleRadii();
  if (flags.HasShader() && flags.getStyle() != cc::PaintFlags::kStroke_Style) {
    const int bitmap_width = SkScalarCeilToInt(rect.width());
    const int bitmap_height = SkScalarCeilToInt(rect.height());
    if (bitmap_width > 0 && bitmap_height > 0) {
      std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                       static_cast<size_t>(bitmap_height) * 4u);
      SkImageInfo info =
          SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                            kPremul_SkAlphaType);
      sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
          info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
      if (surface) {
        SkCanvas* canvas = surface->getCanvas();
        canvas->clear(SK_ColorTRANSPARENT);
        canvas->translate(-rect.x(), -rect.y());
        canvas->drawRRect(rrect, flags.ToSkPaint());
        LiveExportedDrawOp exported;
        exported.type = 7;
        exported.x = translate_x + rect.x();
        exported.y = translate_y + rect.y();
        exported.width = static_cast<float>(bitmap_width);
        exported.height = static_cast<float>(bitmap_height);
        exported.mask_width = bitmap_width;
        exported.mask_height = bitmap_height;
        exported.rgba_pixels = std::move(rgba_pixels);
        exported_draw_ops.push_back(std::move(exported));
        return;
      }
    }
  }
  AppendRRectOp(translate_x + rect.x(), translate_y + rect.y(), rect.width(),
                rect.height(), radii.x(), radii.y(), flags.getStrokeWidth(),
                flags.getColor4f(),
                flags.getStyle() == cc::PaintFlags::kStroke_Style,
                exported_draw_ops);
}

void AppendSkPathOpWithFlags(
    const SkPath& path,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  const SkRect bounds = path.getBounds();
  if (!bounds.isFinite()) {
    return;
  }
  if (!flags.HasShader()) {
    SkRect decoration_bounds = bounds;
    if (flags.getStyle() == cc::PaintFlags::kStroke_Style) {
      const SkScalar outset = std::max<SkScalar>(1.0f, flags.getStrokeWidth()) *
                              0.5f + 1.0f;
      decoration_bounds.outset(outset, outset);
    }
    if (decoration_bounds.width() <= 4.0f ||
        decoration_bounds.height() <= 4.0f) {
      AppendFillRectOp(translate_x + decoration_bounds.x(),
                       translate_y + decoration_bounds.y(),
                       decoration_bounds.width(), decoration_bounds.height(),
                       flags.getColor4f(), exported_draw_ops);
    }
    if (flags.getStyle() != cc::PaintFlags::kStroke_Style) {
      const int bitmap_width = SkScalarCeilToInt(bounds.width());
      const int bitmap_height = SkScalarCeilToInt(bounds.height());
      constexpr int kMaxPathBitmapPixels = 1024 * 1024;
      if (bitmap_width > 0 && bitmap_height > 0 &&
          static_cast<int64_t>(bitmap_width) *
                  static_cast<int64_t>(bitmap_height) <=
              kMaxPathBitmapPixels) {
        std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                         static_cast<size_t>(bitmap_height) *
                                         4u);
        SkImageInfo info = SkImageInfo::Make(bitmap_width, bitmap_height,
                                             kRGBA_8888_SkColorType,
                                             kPremul_SkAlphaType);
        sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
            info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
        if (surface) {
          SkCanvas* canvas = surface->getCanvas();
          canvas->clear(SK_ColorTRANSPARENT);
          canvas->translate(-bounds.x(), -bounds.y());
          canvas->drawPath(path, flags.ToSkPaint());
          LiveExportedDrawOp exported;
          exported.type = 7;
          exported.x = translate_x + bounds.x();
          exported.y = translate_y + bounds.y();
          exported.width = static_cast<float>(bitmap_width);
          exported.height = static_cast<float>(bitmap_height);
          exported.mask_width = bitmap_width;
          exported.mask_height = bitmap_height;
          exported.rgba_pixels = std::move(rgba_pixels);
          exported_draw_ops.push_back(std::move(exported));
        }
      }
    }
    return;
  }
  SkRect draw_bounds = bounds;
  if (flags.getStyle() == cc::PaintFlags::kStroke_Style) {
    const SkScalar outset = std::max<SkScalar>(1.0f, flags.getStrokeWidth()) *
                            0.5f + 1.0f;
    draw_bounds.outset(outset, outset);
  }
  const int bitmap_width = SkScalarCeilToInt(draw_bounds.width());
  const int bitmap_height = SkScalarCeilToInt(draw_bounds.height());
  if (bitmap_width <= 0 || bitmap_height <= 0) {
    return;
  }
  std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                   static_cast<size_t>(bitmap_height) * 4u);
  SkImageInfo info =
      SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
  if (surface) {
    SkCanvas* canvas = surface->getCanvas();
    canvas->clear(SK_ColorTRANSPARENT);
    canvas->translate(-draw_bounds.x(), -draw_bounds.y());
    canvas->drawRect(draw_bounds, flags.ToSkPaint());
    LiveExportedDrawOp exported;
    exported.type = 7;
    exported.x = translate_x + draw_bounds.x();
    exported.y = translate_y + draw_bounds.y();
    exported.width = static_cast<float>(bitmap_width);
    exported.height = static_cast<float>(bitmap_height);
    exported.mask_width = bitmap_width;
    exported.mask_height = bitmap_height;
    exported.rgba_pixels = std::move(rgba_pixels);
    exported_draw_ops.push_back(std::move(exported));
  }
}

void AppendTextBlobOp(const cc::DrawTextBlobOp& text_op,
                      int fallback_x,
                      int fallback_y,
                      int fallback_width,
                      int fallback_height,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!text_op.blob) {
    return;
  }
  const float absolute_x = text_op.x;
  const float absolute_y = text_op.y;
  const SkRect bounds = text_op.blob->bounds().makeOffset(absolute_x,
                                                          absolute_y);
  SkIRect ibounds = bounds.roundOut();
  if (ibounds.width() <= 0 || ibounds.height() <= 0) {
    ibounds = SkIRect::MakeXYWH(fallback_x, fallback_y, fallback_width,
                                fallback_height);
  }
  float export_offset_x = 0.0f;
  float export_offset_y = 0.0f;
  if (fallback_width > 0 && fallback_height > 0) {
    const SkIRect fallback_bounds =
        SkIRect::MakeXYWH(fallback_x, fallback_y, fallback_width,
                          fallback_height);
    SkIRect intersection;
    if (!intersection.intersect(ibounds, fallback_bounds)) {
      export_offset_x = static_cast<float>(fallback_x);
      export_offset_y = static_cast<float>(fallback_y);
    }
  }
  const int mask_width = std::max(0, ibounds.width());
  const int mask_height = std::max(0, ibounds.height());
  if (mask_width <= 0 || mask_height <= 0) {
    return;
  }

  std::vector<uint8_t> rgba_pixels(static_cast<size_t>(mask_width) *
                                   static_cast<size_t>(mask_height) * 4u,
                                   0);
  SkImageInfo mask_info = SkImageInfo::MakeN32Premul(mask_width, mask_height);
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      mask_info, rgba_pixels.data(), static_cast<size_t>(mask_width) * 4u);
  if (!surface) {
    return;
  }
  SkCanvas* canvas = surface->getCanvas();
  canvas->clear(SK_ColorTRANSPARENT);
  canvas->translate(-static_cast<SkScalar>(ibounds.left()),
                    -static_cast<SkScalar>(ibounds.top()));
  text_op.Raster(canvas, cc::PlaybackParams());
  int outline_path_count = 0;
  int nonempty_outline_path_count = 0;

  std::vector<uint8_t> mask_pixels(static_cast<size_t>(mask_width) *
                                       static_cast<size_t>(mask_height),
                                   0);
  size_t nonzero_alpha_count = 0;
  for (int row = 0; row < mask_height; ++row) {
    for (int col = 0; col < mask_width; ++col) {
      const size_t pixel_index =
          static_cast<size_t>(row) * static_cast<size_t>(mask_width) +
          static_cast<size_t>(col);
      const size_t rgba_offset = pixel_index * 4u;
      const uint8_t alpha = rgba_pixels[rgba_offset + 3u];
      const uint8_t color_coverage =
          std::max(rgba_pixels[rgba_offset + 0u],
                   std::max(rgba_pixels[rgba_offset + 1u],
                            rgba_pixels[rgba_offset + 2u]));
      const uint8_t coverage = alpha != 0 ? alpha : color_coverage;
      mask_pixels[pixel_index] = coverage;
      if (coverage != 0) {
        ++nonzero_alpha_count;
      }
    }
  }

  LiveExportedDrawOp bitmap_export;
  bitmap_export.type = 3;
  AppendSkColor(bitmap_export, text_op.flags.getColor4f());
  bitmap_export.x = export_offset_x + static_cast<float>(ibounds.left());
  bitmap_export.y = export_offset_y + static_cast<float>(ibounds.top());
  bitmap_export.width = static_cast<float>(mask_width);
  bitmap_export.height = static_cast<float>(mask_height);
  bitmap_export.mask_width = mask_width;
  bitmap_export.mask_height = mask_height;
  bitmap_export.alpha_mask = std::move(mask_pixels);
  exported_draw_ops.push_back(std::move(bitmap_export));

  SkTextBlob::Iter iterator(*text_op.blob);
  SkTextBlob::Iter::ExperimentalRun run;
  while (iterator.experimentalNext(&run)) {
    if (run.count <= 0 || !run.glyphs) {
      continue;
    }
    for (int i = 0; i < std::min(run.count, 12); ++i) {
    }
    SkString typeface_family;
    if (run.font.getTypeface()) {
      run.font.getTypeface()->getFamilyName(&typeface_family);
    }
    LiveExportedDrawOp exported;
    exported.type = 2;
    AppendSkColor(exported, text_op.flags.getColor4f());
    exported.font_size = run.font.getSize();
    const SkRect bounds = text_op.blob->bounds().makeOffset(text_op.x, text_op.y);
    exported.x = export_offset_x + bounds.x();
    exported.y = export_offset_y + bounds.y();
    exported.width = bounds.width();
    exported.height = bounds.height();
    exported.glyphs.reserve(static_cast<size_t>(run.count));
    for (int i = 0; i < run.count; ++i) {
      LiveExportedGlyph glyph;
      glyph.glyph_id = run.glyphs[i];
      if (run.positions) {
        glyph.x = export_offset_x + text_op.x + run.positions[i].x();
        glyph.y = export_offset_y + text_op.y + run.positions[i].y();
      } else {
        glyph.x = export_offset_x + text_op.x;
        glyph.y = export_offset_y + text_op.y;
      }
      exported.glyphs.push_back(glyph);
    }
    exported_draw_ops.push_back(std::move(exported));
  }
}

bool AppendPaintRecordBitmapOp(
    const cc::PaintRecord& record,
    int fallback_x,
    int fallback_y,
    int fallback_width,
    int fallback_height,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (fallback_width <= 0 || fallback_height <= 0) {
    return false;
  }
  constexpr int kMaxBitmapExportDimension = 4096;
  constexpr int kMaxBitmapExportPixels = 8 * 1024 * 1024;
  const int bitmap_width =
      std::min(fallback_width, kMaxBitmapExportDimension);
  const int bitmap_height =
      std::min(fallback_height, kMaxBitmapExportDimension);
  if (bitmap_width <= 0 || bitmap_height <= 0 ||
      static_cast<int64_t>(bitmap_width) *
              static_cast<int64_t>(bitmap_height) >
          kMaxBitmapExportPixels) {
    return false;
  }

  std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                   static_cast<size_t>(bitmap_height) * 4u);
  SkImageInfo info =
      SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
  if (!surface) {
    return false;
  }

  SkCanvas* canvas = surface->getCanvas();
  canvas->clear(SK_ColorTRANSPARENT);
  canvas->translate(-static_cast<SkScalar>(fallback_x),
                    -static_cast<SkScalar>(fallback_y));
  record.Playback(canvas);

  LiveExportedDrawOp exported;
  exported.type = 7;
  exported.x = static_cast<float>(fallback_x);
  exported.y = static_cast<float>(fallback_y);
  exported.width = static_cast<float>(bitmap_width);
  exported.height = static_cast<float>(bitmap_height);
  exported.mask_width = bitmap_width;
  exported.mask_height = bitmap_height;
  exported.rgba_pixels = std::move(rgba_pixels);
  exported_draw_ops.push_back(std::move(exported));
  return true;
}

bool PaintRecordNeedsBitmapExport(const cc::PaintRecord& record) {
  for (const cc::PaintOp& op : record) {
    switch (op.GetType()) {
      case cc::PaintOpType::kDrawArc:
      case cc::PaintOpType::kDrawArcLite:
      case cc::PaintOpType::kDrawDRRect:
      case cc::PaintOpType::kDrawImage:
      case cc::PaintOpType::kDrawImageRect:
      case cc::PaintOpType::kDrawScrollingContents:
      case cc::PaintOpType::kDrawSkottie:
      case cc::PaintOpType::kDrawSlug:
      case cc::PaintOpType::kDrawVertices:
      case cc::PaintOpType::kRotate:
      case cc::PaintOpType::kSaveLayerFilters:
      case cc::PaintOpType::kScale:
      case cc::PaintOpType::kSetMatrix:
        return true;
      case cc::PaintOpType::kDrawIRect:
        if (static_cast<const cc::DrawIRectOp&>(op).flags.HasShader()) {
          return true;
        }
        break;
      case cc::PaintOpType::kDrawOval:
        if (static_cast<const cc::DrawOvalOp&>(op).flags.HasShader()) {
          return true;
        }
        break;
      case cc::PaintOpType::kDrawPath:
        break;
      case cc::PaintOpType::kDrawRect:
        if (static_cast<const cc::DrawRectOp&>(op).flags.HasShader()) {
          return true;
        }
        break;
      case cc::PaintOpType::kDrawRRect:
        if (static_cast<const cc::DrawRRectOp&>(op).flags.HasShader()) {
          return true;
        }
        break;
      case cc::PaintOpType::kDrawRecord:
        if (PaintRecordNeedsBitmapExport(
                static_cast<const cc::DrawRecordOp&>(op).record)) {
          return true;
        }
        break;
      default:
        break;
    }
  }
  return false;
}

bool PaintRecordHasTextExport(const cc::PaintRecord& record) {
  for (const cc::PaintOp& op : record) {
    switch (op.GetType()) {
      case cc::PaintOpType::kDrawTextBlob:
      case cc::PaintOpType::kDrawSlug:
        return true;
      case cc::PaintOpType::kDrawRecord:
        if (PaintRecordHasTextExport(
                static_cast<const cc::DrawRecordOp&>(op).record)) {
          return true;
        }
        break;
      default:
        break;
    }
  }
  return false;
}

std::pair<float, float> TranslateForPaintOpBounds(
    const SkRect& local_bounds,
    float current_translate_x,
    float current_translate_y,
    float fallback_x,
    float fallback_y,
    int fallback_width,
    int fallback_height) {
  if (!local_bounds.isFinite() || fallback_width <= 0 || fallback_height <= 0) {
    return {current_translate_x, current_translate_y};
  }
  const SkRect translated_bounds =
      local_bounds.makeOffset(current_translate_x, current_translate_y);
  const SkRect fallback_bounds =
      SkRect::MakeXYWH(fallback_x, fallback_y,
                       static_cast<float>(fallback_width),
                       static_cast<float>(fallback_height));
  SkRect intersection;
  if (intersection.intersect(translated_bounds, fallback_bounds)) {
    return {current_translate_x, current_translate_y};
  }
  return {current_translate_x + fallback_x, current_translate_y + fallback_y};
}

void AppendPaintRecordOps(const cc::PaintRecord& record,
                          float fallback_x,
                          float fallback_y,
                          int fallback_width,
                          int fallback_height,
                          std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  struct PaintRecordState {
    float translate_x = 0.0f;
    float translate_y = 0.0f;
    std::optional<SkRect> clip;
  };
  std::vector<PaintRecordState> state_stack;
  float current_translate_x = 0.0f;
  float current_translate_y = 0.0f;
  std::optional<SkRect> current_clip;
  for (const cc::PaintOp& op : record) {
    switch (op.GetType()) {
      case cc::PaintOpType::kSave:
      case cc::PaintOpType::kSaveLayer:
      case cc::PaintOpType::kSaveLayerAlpha:
      case cc::PaintOpType::kSaveLayerFilters:
        state_stack.push_back(
            {current_translate_x, current_translate_y, current_clip});
        break;
      case cc::PaintOpType::kRestore:
        if (!state_stack.empty()) {
          current_translate_x = state_stack.back().translate_x;
          current_translate_y = state_stack.back().translate_y;
          current_clip = state_stack.back().clip;
          state_stack.pop_back();
        }
        break;
      case cc::PaintOpType::kTranslate: {
        const auto& translate_op = static_cast<const cc::TranslateOp&>(op);
        current_translate_x += translate_op.dx;
        current_translate_y += translate_op.dy;
        break;
      }
      case cc::PaintOpType::kConcat: {
        const auto& concat_op = static_cast<const cc::ConcatOp&>(op);
        current_translate_x += concat_op.matrix.rc(0, 3);
        current_translate_y += concat_op.matrix.rc(1, 3);
        break;
      }
      case cc::PaintOpType::kSetMatrix: {
        const auto& matrix_op = static_cast<const cc::SetMatrixOp&>(op);
        current_translate_x = matrix_op.matrix.rc(0, 3);
        current_translate_y = matrix_op.matrix.rc(1, 3);
        break;
      }
      case cc::PaintOpType::kClipRect: {
        const auto& clip_op = static_cast<const cc::ClipRectOp&>(op);
        if (clip_op.op == SkClipOp::kIntersect && clip_op.rect.isFinite()) {
          SkRect clip = clip_op.rect.makeOffset(current_translate_x,
                                                current_translate_y);
          if (current_clip) {
            SkRect intersection;
            if (intersection.intersect(*current_clip, clip)) {
              current_clip = intersection;
            } else {
              current_clip = SkRect::MakeEmpty();
            }
          } else {
            current_clip = clip;
          }
        }
        break;
      }
      case cc::PaintOpType::kDrawColor: {
        const auto& color_op = static_cast<const cc::DrawColorOp&>(op);
        if (current_clip) {
          SkRect export_clip = *current_clip;
          if (fallback_width > 0 && fallback_height > 0) {
            const SkRect fallback_bounds = SkRect::MakeXYWH(
                fallback_x, fallback_y, static_cast<float>(fallback_width),
                static_cast<float>(fallback_height));
            SkRect intersection;
            if (!intersection.intersect(export_clip, fallback_bounds)) {
              export_clip = export_clip.makeOffset(fallback_x, fallback_y);
            }
          }
          AppendFillRectOp(export_clip.x(), export_clip.y(),
                           export_clip.width(), export_clip.height(),
                           color_op.color, exported_draw_ops);
        } else {
          AppendFillRectOp(fallback_x + current_translate_x,
                           fallback_y + current_translate_y,
                           static_cast<float>(fallback_width),
                           static_cast<float>(fallback_height), color_op.color,
                           exported_draw_ops);
        }
        break;
      }
      case cc::PaintOpType::kDrawIRect: {
        const auto& rect_op = static_cast<const cc::DrawIRectOp&>(op);
        const auto [translate_x, translate_y] = TranslateForPaintOpBounds(
            SkRect::Make(rect_op.rect), current_translate_x,
            current_translate_y, fallback_x, fallback_y, fallback_width,
            fallback_height);
        AppendSkIRectOpWithFlags(rect_op.rect, translate_x, translate_y,
                                 rect_op.flags, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawRect: {
        const auto& rect_op = static_cast<const cc::DrawRectOp&>(op);
        const auto [translate_x, translate_y] = TranslateForPaintOpBounds(
            rect_op.rect, current_translate_x, current_translate_y, fallback_x,
            fallback_y, fallback_width, fallback_height);
        AppendSkRectOpWithFlags(rect_op.rect, translate_x, translate_y,
                                rect_op.flags, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawRRect: {
        const auto& rect_op = static_cast<const cc::DrawRRectOp&>(op);
        const auto [translate_x, translate_y] = TranslateForPaintOpBounds(
            rect_op.rrect.rect(), current_translate_x, current_translate_y,
            fallback_x, fallback_y, fallback_width, fallback_height);
        AppendSkRRectOpWithFlags(rect_op.rrect, translate_x, translate_y,
                                 rect_op.flags,
                                 exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawOval: {
        const auto& oval_op = static_cast<const cc::DrawOvalOp&>(op);
        const auto [translate_x, translate_y] = TranslateForPaintOpBounds(
            oval_op.oval, current_translate_x, current_translate_y, fallback_x,
            fallback_y, fallback_width, fallback_height);
        AppendSkRectOpWithFlags(oval_op.oval, translate_x, translate_y,
                                oval_op.flags, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawLine: {
        const auto& line_op = static_cast<const cc::DrawLineOp&>(op);
        const SkScalar stroke_width =
            line_op.flags.getStrokeWidth() > 0.0f
                ? line_op.flags.getStrokeWidth()
                : 1.0f;
        const SkScalar left = std::min(line_op.x0, line_op.x1);
        const SkScalar top = std::min(line_op.y0, line_op.y1);
        const SkScalar width = std::max<SkScalar>(
            stroke_width, std::abs(line_op.x1 - line_op.x0));
        const SkScalar height = std::max<SkScalar>(
            stroke_width, std::abs(line_op.y1 - line_op.y0));
        const auto [translate_x, translate_y] = TranslateForPaintOpBounds(
            SkRect::MakeXYWH(left, top, width, height), current_translate_x,
            current_translate_y, fallback_x, fallback_y, fallback_width,
            fallback_height);
        AppendFillRectOp(translate_x + left,
                         translate_y + top, width, height,
                         line_op.flags.getColor4f(), exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawPath: {
        const auto& path_op = static_cast<const cc::DrawPathOp&>(op);
        const auto [translate_x, translate_y] = TranslateForPaintOpBounds(
            path_op.path.getBounds(), current_translate_x, current_translate_y,
            fallback_x, fallback_y, fallback_width, fallback_height);
        AppendSkPathOpWithFlags(path_op.path, translate_x, translate_y,
                                path_op.flags,
                                exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawTextBlob:
        AppendTextBlobOp(static_cast<const cc::DrawTextBlobOp&>(op),
                         static_cast<int>(fallback_x + current_translate_x),
                         static_cast<int>(fallback_y + current_translate_y),
                         fallback_width, fallback_height,
                         exported_draw_ops);
        break;
      case cc::PaintOpType::kDrawRecord:
        AppendPaintRecordOps(static_cast<const cc::DrawRecordOp&>(op).record,
                             fallback_x + current_translate_x,
                             fallback_y + current_translate_y,
                             fallback_width, fallback_height,
                             exported_draw_ops);
        break;
      default:
        break;
    }
  }
}

std::vector<std::string> ExtractStyleElementTextForStandaloneRenderer(
    const std::string& head_html) {
  std::vector<std::string> styles;
  size_t search_from = 0;
  while (search_from < head_html.size()) {
    const size_t style_open = head_html.find("<style>", search_from);
    if (style_open == std::string::npos) {
      break;
    }
    const size_t style_text_start = style_open + std::string("<style>").size();
    const size_t style_close = head_html.find("</style>", style_text_start);
    if (style_close == std::string::npos) {
      break;
    }
    styles.push_back(head_html.substr(style_text_start,
                                      style_close - style_text_start));
    search_from = style_close + std::string("</style>").size();
  }
  return styles;
}

std::string ExtractHtmlAttributeForStandaloneRenderer(
    const std::string& tag,
    const std::string& name) {
  const std::string needle = name + "=";
  size_t attr = tag.find(needle);
  if (attr == std::string::npos) {
    return std::string();
  }
  size_t value_start = attr + needle.size();
  if (value_start >= tag.size()) {
    return std::string();
  }
  char quote = tag[value_start];
  if (quote == '"' || quote == '\'') {
    ++value_start;
    const size_t value_end = tag.find(quote, value_start);
    if (value_end == std::string::npos) {
      return std::string();
    }
    return tag.substr(value_start, value_end - value_start);
  }
  size_t value_end = value_start;
  while (value_end < tag.size() && tag[value_end] != ' ' &&
         tag[value_end] != '\t' && tag[value_end] != '\n' &&
         tag[value_end] != '\r' && tag[value_end] != '>') {
    ++value_end;
  }
  return tag.substr(value_start, value_end - value_start);
}

gfx::Rect MapDisplayItemRectToRootForStandaloneRenderer(
    const PaintChunk& chunk,
    const DisplayItem& item) {
  const PropertyTreeState chunk_state = chunk.properties.Unalias();
  FloatClipRect mapped_rect(gfx::RectF(item.VisualRect()));
  if (!GeometryMapper::LocalToAncestorVisualRect(
          chunk_state, PropertyTreeState::Root(), mapped_rect)) {
    return item.VisualRect();
  }
  return gfx::ToEnclosingRect(mapped_rect.Rect());
}

void InstallStyleElementsForStandaloneRenderer(Document& document,
                                               Element& head,
                                               const std::string& head_html) {
  const std::vector<std::string> style_texts =
      ExtractStyleElementTextForStandaloneRenderer(head_html);
  if (style_texts.empty()) {
    head.SetInnerHTMLWithoutTrustedTypes(String::FromUtf8(head_html));
    return;
  }

  head.SetInnerHTMLWithoutTrustedTypes(String());
  for (const std::string& css : style_texts) {
    auto* style = MakeGarbageCollected<HTMLStyleElement>(
        document, CreateElementFlags::ByCreateElement());
    style->setTextContent(String::FromUtf8(css));
    head.appendChild(style);
  }
}

void ExportDrawOpsForStandaloneRenderer(const PaintArtifact& artifact,
                                        LiveFramePaintProbeCache& cache) {
  TraceLiveFrameProbeStage("export begin");
  cache.exported_draw_ops.clear();
  const DisplayItemList& display_items = artifact.GetDisplayItemList();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  TraceLiveFrameProbeStage("export after lists");
  for (wtf_size_t chunk_index = 0; chunk_index < chunks.size();
       ++chunk_index) {
    TraceLiveFrameProbeStage("export before chunk");
    const PaintChunk& chunk = chunks[chunk_index];
    TraceLiveFrameProbeStage("export before chunk transform");
    const TransformPaintPropertyNode& chunk_transform =
        chunk.properties.Transform().Unalias();
    TraceLiveFrameProbeStage("export after chunk transform");
    if (chunk_transform.IsIdentityOr2dTranslation()) {
      const gfx::Vector2dF chunk_translation =
          chunk_transform.Get2dTranslation();
    } else {
    }
    std::fflush(stdout);
    for (wtf_size_t item_index = chunk.begin_index;
         item_index < chunk.end_index && item_index < display_items.size();
         ++item_index) {
      TraceLiveFrameProbeStage("export before item");
      const DisplayItem& item = display_items[item_index];
      const auto* drawing = DynamicTo<DrawingDisplayItem>(item);
      if (!drawing) {
        continue;
      }
      TraceLiveFrameProbeStage("export before paint record size");
      const gfx::Rect mapped_visual_rect =
          MapDisplayItemRectToRootForStandaloneRenderer(chunk, item);
      const int fallback_x = mapped_visual_rect.x();
      const int fallback_y = mapped_visual_rect.y();
      const int fallback_width = mapped_visual_rect.width();
      const int fallback_height = mapped_visual_rect.height();
      TraceLiveFrameProbeStage("export before append paint record ops");
      const bool use_bitmap_record =
          PaintRecordNeedsBitmapExport(drawing->GetPaintRecord());
      if (!use_bitmap_record ||
          !AppendPaintRecordBitmapOp(drawing->GetPaintRecord(), fallback_x,
                                     fallback_y, fallback_width,
                                     fallback_height,
                                     cache.exported_draw_ops)) {
        AppendPaintRecordOps(drawing->GetPaintRecord(), fallback_x, fallback_y,
                             fallback_width, fallback_height,
                             cache.exported_draw_ops);
      }
      TraceLiveFrameProbeStage("export after append paint record ops");
    }
  }
  TraceLiveFrameProbeStage("export done");
}

void EnsureWtfInitializedForStandaloneRenderer() {
  static bool initialized = false;
  if (!initialized) {
    blink::InitializeWtf();
    blink::Length::Initialize();
    blink::CoreInitializer::GetInstance().Initialize();
    initialized = true;
  }
}

LiveFramePaintProbeResult RunLiveFramePaintProbe(const char* body_html) {
  EnsureWtfInitializedForStandaloneRenderer();
  LiveFramePaintProbeCache& cache = ProbeCache();
  const std::string input_html = body_html ? body_html : "";
  if (cache.initialized && cache.body_html == input_html) {
    return cache.result;
  }
  LiveFramePaintProbeResult result;
  TraceLiveFrameProbeStage("before DummyPageHolder");
  if (!cache.holder) {
    cache.holder = new DummyPageHolder(
        gfx::Size(cache.viewport_width, cache.viewport_height));
  }
  TraceLiveFrameProbeStage("after DummyPageHolder");
  Document& document = cache.holder->GetDocument();
  TraceLiveFrameProbeStage("after GetDocument");

  if (!document.documentElement() || !document.body()) {
    TraceLiveFrameProbeStage("missing body");
    return result;
  }

  Element* head = document.head();
  if (!head) {
    head = document.CreateRawElement(html_names::kHeadTag,
                                     CreateElementFlags::ByCreateElement());
    if (document.body()) {
      document.documentElement()->ParserInsertBefore(head, *document.body());
    } else {
      document.documentElement()->ParserAppendChild(head);
    }
  }

  TraceLiveFrameProbeStage("before SetInnerHTML");
  g_standalone_blink_saw_font_draw_text = false;
  const std::string head_open = "<head>";
  const std::string head_close = "</head>";
  const std::string body_close = "</body>";
  const size_t head_start = input_html.find(head_open);
  const size_t head_end = input_html.find(head_close);
  const size_t body_start =
      head_end == std::string::npos
          ? std::string::npos
          : input_html.find("<body", head_end + head_close.size());
  if (head_start != std::string::npos && head_end != std::string::npos &&
      body_start != std::string::npos) {
    const size_t head_content_start = head_start + head_open.size();
    const std::string head_html =
        input_html.substr(head_content_start, head_end - head_content_start);
    const size_t body_open_end = input_html.find('>', body_start);
    const size_t body_content_start =
        body_open_end == std::string::npos ? input_html.size()
                                           : body_open_end + 1;
    size_t body_end = input_html.rfind(body_close);
    if (body_end == std::string::npos || body_end < body_content_start) {
      body_end = input_html.size();
    }
    const std::string body_open_tag =
        body_open_end == std::string::npos
            ? std::string()
            : input_html.substr(body_start, body_open_end - body_start + 1);
    const std::string body_fragment =
        input_html.substr(body_content_start, body_end - body_content_start);
    InstallStyleElementsForStandaloneRenderer(document, *head, head_html);
    const std::string body_class =
        ExtractHtmlAttributeForStandaloneRenderer(body_open_tag, "class");
    if (!body_class.empty()) {
      document.body()->setAttribute(html_names::kClassAttr,
                                    AtomicString(String::FromUtf8(body_class)));
    }
    const std::string body_id =
        ExtractHtmlAttributeForStandaloneRenderer(body_open_tag, "id");
    if (!body_id.empty()) {
      document.body()->setAttribute(html_names::kIdAttr,
                                    AtomicString(String::FromUtf8(body_id)));
    }
    String body_string = String::FromUtf8(body_fragment);
    if (!body_fragment.empty() && body_string.empty()) {
      body_string = String(body_fragment);
    }
    document.body()->SetInnerHTMLWithoutTrustedTypes(body_string);
  } else {
    document.body()->SetInnerHTMLWithoutTrustedTypes(
        String::FromUtf8(input_html));
  }
  TraceLiveFrameProbeStage("after SetInnerHTML");
  DumpNodeForStandaloneRenderer(*document.body(), 0);

  LocalFrameView& frame_view = cache.holder->GetFrameView();
  if (Settings* settings = document.GetSettings()) {
    settings->SetDefaultFontSize(16);
    settings->SetDefaultFixedFontSize(13);
  }
  TraceLiveFrameProbeStage("before active style update");
  document.GetStyleEngine().UpdateActiveStyle();
  TraceLiveFrameProbeStage("after active style update");
  TraceLiveFrameProbeStage("before lifecycle update");
  result.lifecycle_reached_paint_clean =
      frame_view.UpdateAllLifecyclePhasesForTest() ? 1 : 0;
  TraceLiveFrameProbeStage("after lifecycle update");
  if (document.GetLayoutView()) {
    const gfx::Size view_size = document.GetLayoutView()->GetLayoutSize();
  }
  DumpNodeForStandaloneRenderer(*document.body(), 0);
  const PaintArtifact& artifact = frame_view.GetPaintArtifact();
  TraceLiveFrameProbeStage("after GetPaintArtifact");
  TraceLiveFrameProbeStage("before paint chunk count");
  result.paint_chunk_count =
      static_cast<int>(artifact.GetPaintChunks().size());
  TraceLiveFrameProbeStage("after paint chunk count");
  TraceLiveFrameProbeStage("before display item count");
  result.display_item_count =
      static_cast<int>(artifact.GetDisplayItemList().size());
  TraceLiveFrameProbeStage("after display item count");
  ExportDrawOpsForStandaloneRenderer(artifact, cache);
  cache.result = result;
  cache.body_html = input_html;
  cache.initialized = true;
  return result;
}

}  // namespace

void StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(
    int width,
    int height) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const int clamped_width = std::max(1, width);
  const int clamped_height = std::max(1, height);
  if (cache.viewport_width == clamped_width &&
      cache.viewport_height == clamped_height) {
    return;
  }
  cache.viewport_width = clamped_width;
  cache.viewport_height = clamped_height;
  g_standalone_blink_viewport_width = clamped_width;
  g_standalone_blink_viewport_height = clamped_height;
  delete cache.holder;
  cache.holder = nullptr;
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
}

int StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer() {
  return 1;
}

int StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer() {
  return 1;
}

int StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer() {
  return 1;
}

int StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).paint_chunk_count;
}

int StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).display_item_count;
}

int StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).lifecycle_reached_paint_clean;
}

int StandaloneBlinkLiveFrameBridgePaintChunkMetadataAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* x,
    int* y,
    int* width,
    int* height,
    int* begin_display_item_index,
    int* end_display_item_index,
    int* has_text) {
  EnsureWtfInitializedForStandaloneRenderer();
  RunLiveFramePaintProbe(body_html);
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.initialized || !cache.holder) {
    return 0;
  }
  LocalFrameView& frame_view = cache.holder->GetFrameView();
  const PaintArtifact& artifact = frame_view.GetPaintArtifact();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  if (chunk_index < 0 ||
      static_cast<wtf_size_t>(chunk_index) >= chunks.size()) {
    return 0;
  }
  const PaintChunk& chunk = chunks[static_cast<wtf_size_t>(chunk_index)];
  if (x) {
    *x = chunk.bounds.x();
  }
  if (y) {
    *y = chunk.bounds.y();
  }
  if (width) {
    *width = chunk.bounds.width();
  }
  if (height) {
    *height = chunk.bounds.height();
  }
  if (begin_display_item_index) {
    *begin_display_item_index = static_cast<int>(chunk.begin_index);
  }
  if (end_display_item_index) {
    *end_display_item_index = static_cast<int>(chunk.end_index);
  }
  if (has_text) {
    *has_text = (chunk.has_text || g_standalone_blink_saw_font_draw_text) ? 1 : 0;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedDrawOpCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().exported_draw_ops.size());
}

int StandaloneBlinkLiveFrameBridgeExportedDrawOpAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* type,
    float* x,
    float* y,
    float* width,
    float* height,
    float* r,
    float* g,
    float* b,
    float* a,
    float* font_size,
    float* radius_x,
    float* radius_y,
    int* glyph_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (type) {
    *type = op.type;
  }
  if (x) {
    *x = op.x;
  }
  if (y) {
    *y = op.y;
  }
  if (width) {
    *width = op.width;
  }
  if (height) {
    *height = op.height;
  }
  if (r) {
    *r = op.r;
  }
  if (g) {
    *g = op.g;
  }
  if (b) {
    *b = op.b;
  }
  if (a) {
    *a = op.a;
  }
  if (font_size) {
    *font_size = op.font_size;
  }
  if (radius_x) {
    *radius_x = op.radius_x;
  }
  if (radius_y) {
    *radius_y = op.radius_y;
  }
  if (glyph_count) {
    *glyph_count = static_cast<int>(op.glyphs.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedGlyphAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int glyph_index,
    uint32_t* glyph_id,
    float* x,
    float* y) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (glyph_index < 0 || static_cast<size_t>(glyph_index) >= op.glyphs.size()) {
    return 0;
  }
  const LiveExportedGlyph& glyph = op.glyphs[static_cast<size_t>(glyph_index)];
  if (glyph_id) {
    *glyph_id = glyph.glyph_id;
  }
  if (x) {
    *x = glyph.x;
  }
  if (y) {
    *y = glyph.y;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedTextMaskInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* width,
    int* height,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 3 || op.mask_width <= 0 || op.mask_height <= 0 ||
      op.alpha_mask.empty()) {
    return 0;
  }
  if (width) {
    *width = op.mask_width;
  }
  if (height) {
    *height = op.mask_height;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.alpha_mask.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedTextMaskBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !destination || destination_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 3 || op.alpha_mask.empty() ||
      destination_size < static_cast<int>(op.alpha_mask.size())) {
    return 0;
  }
  std::memcpy(destination, op.alpha_mask.data(), op.alpha_mask.size());
  return static_cast<int>(op.alpha_mask.size());
}

int StandaloneBlinkLiveFrameBridgeExportedBitmapInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* width,
    int* height,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 7 || op.mask_width <= 0 || op.mask_height <= 0 ||
      op.rgba_pixels.empty()) {
    return 0;
  }
  if (width) {
    *width = op.mask_width;
  }
  if (height) {
    *height = op.mask_height;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.rgba_pixels.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedBitmapBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !destination || destination_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 7 || op.rgba_pixels.empty() ||
      destination_size < static_cast<int>(op.rgba_pixels.size())) {
    return 0;
  }
  std::memcpy(destination, op.rgba_pixels.data(), op.rgba_pixels.size());
  return static_cast<int>(op.rgba_pixels.size());
}

}  // namespace blink::standalone_renderer_probe
