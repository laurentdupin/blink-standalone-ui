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
    from PIL import Image, ImageChops
except ImportError as exc:  # pragma: no cover - diagnostic script.
    raise SystemExit("Pillow is required: python -m pip install pillow") from exc

warnings.filterwarnings("ignore", category=DeprecationWarning, module="PIL")


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
        "changed_percent_full_viewport": percent(changed_full, total),
        "changed_percent_union_content_bbox": percent(changed_union, area(content_bbox)),
        "changed_percent_playwright_content_bbox": percent(changed_reference, area(reference_bbox)),
        "missing_content_percent": percent(reported_missing, max(1, reference_content)),
        "extra_content_percent": percent(reported_extra, max(1, reference_content)),
        "mask_missing_content_percent": percent(missing, max(1, reference_content)),
        "mask_extra_content_percent": percent(extra, max(1, reference_content)),
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
