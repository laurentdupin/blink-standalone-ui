#!/usr/bin/env python3
"""Content-aware image comparison for standalone renderer screenshots.

This intentionally scores the content bounding boxes as well as the full
viewport, because mostly-white pages can otherwise look falsely good.
"""

from __future__ import annotations

import argparse
import json
import warnings
from pathlib import Path
from typing import Iterable, Tuple

try:
    from PIL import Image, ImageChops, ImageFilter
except ImportError as exc:  # pragma: no cover - diagnostic script.
    raise SystemExit("Pillow is required: python -m pip install pillow") from exc

warnings.filterwarnings("ignore", category=DeprecationWarning)


Rgb = Tuple[int, int, int]
BBox = Tuple[int, int, int, int]


def parse_rgb(value: str) -> Rgb:
    named = {"white": (255, 255, 255), "black": (0, 0, 0)}
    if value in named:
        return named[value]
    if value.startswith("#") and len(value) == 7:
        return tuple(int(value[i : i + 2], 16) for i in (1, 3, 5))  # type: ignore[return-value]
    raise ValueError(f"Unsupported background color: {value}")


def auto_corner_background(image: Image.Image) -> Rgb:
    rgb = image.convert("RGB")
    width, height = rgb.size
    corners = [
        rgb.getpixel((0, 0)),
        rgb.getpixel((width - 1, 0)),
        rgb.getpixel((0, height - 1)),
        rgb.getpixel((width - 1, height - 1)),
    ]
    return tuple(sorted(values)[len(values) // 2] for values in zip(*corners))  # type: ignore[return-value]


def is_background(pixel: Rgb, background: Rgb, threshold: int) -> bool:
    return all(abs(int(pixel[i]) - int(background[i])) <= threshold for i in range(3))


def content_mask(image: Image.Image, background: Rgb, threshold: int) -> list[bool]:
    rgb = image.convert("RGB")
    return [not is_background(pixel, background, threshold) for pixel in rgb.getdata()]


def bbox_from_mask(mask: list[bool], width: int, height: int) -> BBox | None:
    xs: list[int] = []
    ys: list[int] = []
    for index, has_content in enumerate(mask):
        if not has_content:
            continue
        xs.append(index % width)
        ys.append(index // width)
    if not xs:
        return None
    return (min(xs), min(ys), max(xs) + 1, max(ys) + 1)


def union_bbox(*boxes: BBox | None) -> BBox | None:
    present = [box for box in boxes if box is not None]
    if not present:
        return None
    return (
        min(box[0] for box in present),
        min(box[1] for box in present),
        max(box[2] for box in present),
        max(box[3] for box in present),
    )


def count_changed(a: Image.Image, b: Image.Image, threshold: int, bbox: BBox | None = None) -> int:
    a_rgb = a.convert("RGB")
    b_rgb = b.convert("RGB")
    if bbox:
        a_rgb = a_rgb.crop(bbox)
        b_rgb = b_rgb.crop(bbox)
    changed = 0
    for left, right in zip(a_rgb.getdata(), b_rgb.getdata()):
        if any(abs(int(left[i]) - int(right[i])) > threshold for i in range(3)):
            changed += 1
    return changed


def count_exact_changed(a: Image.Image, b: Image.Image, bbox: BBox | None = None) -> int:
    a_rgb = a.convert("RGB")
    b_rgb = b.convert("RGB")
    if bbox:
        a_rgb = a_rgb.crop(bbox)
        b_rgb = b_rgb.crop(bbox)
    return sum(1 for left, right in zip(a_rgb.getdata(), b_rgb.getdata()) if left != right)


def changed_mask(a: Image.Image, b: Image.Image, threshold: int) -> list[bool]:
    a_rgb = a.convert("RGB")
    b_rgb = b.convert("RGB")
    return [
        any(abs(int(left[i]) - int(right[i])) > threshold for i in range(3))
        for left, right in zip(a_rgb.getdata(), b_rgb.getdata())
    ]


def text_like_mask(image: Image.Image) -> Image.Image:
    rgb = image.convert("RGB")
    mask = Image.new("L", rgb.size, 0)
    out = []
    for r, g, b in rgb.getdata():
        dark = max(r, g, b) < 120
        neutral = max(r, g, b) - min(r, g, b) < 42
        out.append(255 if dark and neutral else 0)
    mask.putdata(out)
    return mask.filter(ImageFilter.MaxFilter(5))


def edge_like_mask(image: Image.Image, threshold: int) -> Image.Image:
    gray = image.convert("L")
    edges = gray.filter(ImageFilter.FIND_EDGES)
    mask = Image.new("L", gray.size, 0)
    mask.putdata([255 if value > max(18, threshold * 2) else 0 for value in edges.getdata()])
    return mask.filter(ImageFilter.MaxFilter(3))


def union_l_masks(*masks: Image.Image) -> Image.Image:
    if not masks:
        raise ValueError("at least one mask is required")
    result = masks[0]
    for mask in masks[1:]:
        result = ImageChops.lighter(result, mask)
    return result


def count_changed_under_mask(changed: list[bool], mask: Image.Image) -> int:
    return sum(1 for is_changed, value in zip(changed, mask.getdata()) if is_changed and value)


def changed_components(changed: list[bool], width: int, height: int) -> dict:
    seen = bytearray(width * height)
    largest_area = 0
    largest_bbox: BBox | None = None
    small_count = 0
    large_count = 0
    component_count = 0
    for start, is_changed in enumerate(changed):
        if not is_changed or seen[start]:
            continue
        component_count += 1
        stack = [start]
        seen[start] = 1
        area_count = 0
        min_x = width
        min_y = height
        max_x = -1
        max_y = -1
        while stack:
            index = stack.pop()
            area_count += 1
            x = index % width
            y = index // width
            min_x = min(min_x, x)
            min_y = min(min_y, y)
            max_x = max(max_x, x)
            max_y = max(max_y, y)
            if x > 0:
                neighbor = index - 1
                if changed[neighbor] and not seen[neighbor]:
                    seen[neighbor] = 1
                    stack.append(neighbor)
            if x + 1 < width:
                neighbor = index + 1
                if changed[neighbor] and not seen[neighbor]:
                    seen[neighbor] = 1
                    stack.append(neighbor)
            if y > 0:
                neighbor = index - width
                if changed[neighbor] and not seen[neighbor]:
                    seen[neighbor] = 1
                    stack.append(neighbor)
            if y + 1 < height:
                neighbor = index + width
                if changed[neighbor] and not seen[neighbor]:
                    seen[neighbor] = 1
                    stack.append(neighbor)
        if area_count <= 16:
            small_count += 1
        if area_count >= max(128, int(width * height * 0.001)):
            large_count += 1
        if area_count > largest_area:
            largest_area = area_count
            largest_bbox = (min_x, min_y, max_x + 1, max_y + 1)
    return {
        "component_count": component_count,
        "small_component_count": small_count,
        "large_component_count": large_count,
        "largest_diff_component_area": largest_area,
        "largest_diff_component_bbox": largest_bbox,
        "large_component_diff_percent": percent(largest_area, width * height),
    }


def classify_diff(changed_count: int,
                  total: int,
                  text_count: int,
                  edge_count: int,
                  largest_area: int,
                  mask_difference_percent: float) -> str:
    if changed_count == 0:
        return "exact_or_threshold_match"
    text_ratio = text_count / max(1, changed_count)
    edge_ratio = edge_count / max(1, changed_count)
    largest_percent = percent(largest_area, total)
    if mask_difference_percent > 8.0 or largest_percent > 2.0:
        return "missing_resource_or_large_region"
    if text_ratio >= 0.70:
        return "mostly_text_aa"
    if edge_ratio >= 0.70:
        return "mostly_edge_aa"
    if largest_percent > 0.35:
        return "structural_layout_or_paint"
    return "mixed"


def area(bbox: BBox | None) -> int:
    if not bbox:
        return 0
    return max(0, bbox[2] - bbox[0]) * max(0, bbox[3] - bbox[1])


def percent(count: int, total: int) -> float:
    return 0.0 if total <= 0 else (count * 100.0) / total


def write_crops(standalone: Image.Image, reference: Image.Image, bbox: BBox | None, out_dir: Path) -> dict[str, str]:
    if not bbox:
        return {}
    out_dir.mkdir(parents=True, exist_ok=True)
    standalone_crop = standalone.convert("RGB").crop(bbox)
    reference_crop = reference.convert("RGB").crop(bbox)
    width, height = standalone_crop.size
    side_by_side = Image.new("RGB", (width * 2, height), (255, 255, 255))
    side_by_side.paste(standalone_crop, (0, 0))
    side_by_side.paste(reference_crop, (width, 0))
    diff = ImageChops.difference(standalone_crop, reference_crop)
    side_path = out_dir / "cropped_side_by_side_union_content_bbox.png"
    diff_path = out_dir / "cropped_diff_union_content_bbox.png"
    side_by_side.save(side_path)
    diff.save(diff_path)
    return {"cropped_side_by_side_union_content_bbox": str(side_path), "cropped_diff_union_content_bbox": str(diff_path)}


def compare(standalone_path: Path, reference_path: Path, background_mode: str, threshold: int, out_dir: Path) -> dict:
    standalone = Image.open(standalone_path)
    reference = Image.open(reference_path)
    if standalone.size != reference.size:
        reference = reference.resize(standalone.size)
    background = auto_corner_background(reference) if background_mode in {"auto-corners", "sampled-reference-background"} else parse_rgb(background_mode)
    width, height = standalone.size
    total = width * height
    standalone_mask = content_mask(standalone, background, threshold)
    reference_mask = content_mask(reference, background, threshold)
    standalone_content = sum(standalone_mask)
    reference_content = sum(reference_mask)
    standalone_bbox = bbox_from_mask(standalone_mask, width, height)
    reference_bbox = bbox_from_mask(reference_mask, width, height)
    content_bbox = union_bbox(standalone_bbox, reference_bbox)
    changed_full = count_changed(standalone, reference, threshold)
    changed = changed_mask(standalone, reference, threshold)
    changed_union = count_changed(standalone, reference, threshold, content_bbox)
    changed_reference = count_changed(standalone, reference, threshold, reference_bbox)
    exact_changed_full = count_exact_changed(standalone, reference)
    exact_changed_union = count_exact_changed(standalone, reference, content_bbox)
    missing = sum(1 for s, r in zip(standalone_mask, reference_mask) if r and not s)
    extra = sum(1 for s, r in zip(standalone_mask, reference_mask) if s and not r)
    mask_difference = missing + extra
    mask_artifact_suspected = changed_full == 0 and mask_difference > 0
    reported_missing = 0 if mask_artifact_suspected else missing
    reported_extra = 0 if mask_artifact_suspected else extra
    text_mask = union_l_masks(text_like_mask(standalone), text_like_mask(reference))
    edge_mask = union_l_masks(edge_like_mask(standalone, threshold), edge_like_mask(reference, threshold))
    text_changed = count_changed_under_mask(changed, text_mask)
    edge_changed = count_changed_under_mask(changed, edge_mask)
    non_text_changed = max(0, changed_full - text_changed)
    components = changed_components(changed, width, height)
    classification = classify_diff(
        changed_full,
        total,
        text_changed,
        edge_changed,
        components["largest_diff_component_area"],
        percent(mask_difference, total),
    )
    result = {
        "standalone": str(standalone_path),
        "reference": str(reference_path),
        "background": background,
        "threshold": threshold,
        "standalone_non_background_pixels": standalone_content,
        "playwright_non_background_pixels": reference_content,
        "non_background_ratio_standalone": standalone_content / total,
        "non_background_ratio_playwright": reference_content / total,
        "blank_or_nearly_blank": standalone_content < max(16, int(reference_content * 0.02)),
        "content_bbox_standalone": standalone_bbox,
        "content_bbox_playwright": reference_bbox,
        "union_content_bbox": content_bbox,
        "exact_pixel_difference_count": exact_changed_full,
        "exact_pixel_difference_percent": percent(exact_changed_full, total),
        "exact_pixel_difference_count_union_content_bbox": exact_changed_union,
        "exact_pixel_difference_percent_union_content_bbox": percent(exact_changed_union, area(content_bbox)),
        "mask_difference_count": mask_difference,
        "mask_difference_percent": percent(mask_difference, total),
        "mask_artifact_suspected": mask_artifact_suspected,
        "visual_match_under_threshold": changed_full == 0,
        "exact_pixel_identical": exact_changed_full == 0,
        "changed_percent_full_viewport": percent(changed_full, total),
        "changed_percent_union_content_bbox": percent(changed_union, area(content_bbox)),
        "changed_percent_playwright_content_bbox": percent(changed_reference, area(reference_bbox)),
        "thresholded_changed_percent_full_viewport": percent(changed_full, total),
        "thresholded_changed_percent_union_content_bbox": percent(changed_union, area(content_bbox)),
        "thresholded_changed_percent_playwright_content_bbox": percent(changed_reference, area(reference_bbox)),
        "missing_content_percent": percent(reported_missing, max(1, reference_content)),
        "extra_content_percent": percent(reported_extra, max(1, reference_content)),
        "reported_missing_content_percent": percent(reported_missing, max(1, reference_content)),
        "reported_extra_content_percent": percent(reported_extra, max(1, reference_content)),
        "mask_missing_content_percent": percent(missing, max(1, reference_content)),
        "mask_extra_content_percent": percent(extra, max(1, reference_content)),
        "diff_classification": classification,
        "text_explained_diff_percent": percent(text_changed, max(1, changed_full)),
        "non_text_diff_percent": percent(non_text_changed, max(1, changed_full)),
        "edge_diff_percent": percent(edge_changed, max(1, changed_full)),
        "diff_classification_metrics": {
            "mode": "heuristic_dark_text_edge_connected_components",
            "caveat": "classification metadata only; pass/fail metrics are unchanged",
            "changed_pixel_count": changed_full,
            "text_explained_changed_pixel_count": text_changed,
            "edge_changed_pixel_count": edge_changed,
            "non_text_changed_pixel_count": non_text_changed,
            **components,
        },
    }
    result.update(write_crops(standalone, reference, content_bbox, out_dir))
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--standalone", required=True, type=Path)
    parser.add_argument("--playwright", required=True, type=Path)
    parser.add_argument("--out-json", required=True, type=Path)
    parser.add_argument("--out-dir", type=Path)
    parser.add_argument("--compare-background", default="white", help="white, black, auto-corners, sampled-reference-background, or #RRGGBB")
    parser.add_argument("--compare-threshold", default=8, type=int)
    args = parser.parse_args()
    out_dir = args.out_dir or args.out_json.parent
    result = compare(args.standalone, args.playwright, args.compare_background, args.compare_threshold, out_dir)
    args.out_json.parent.mkdir(parents=True, exist_ok=True)
    args.out_json.write_text(json.dumps(result, indent=2), encoding="utf-8")
    print(json.dumps(result, indent=2))


if __name__ == "__main__":
    main()
