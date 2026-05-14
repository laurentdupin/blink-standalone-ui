#!/usr/bin/env python3
"""Generate tiny standalone Mojom C++ stubs for the renderer cut.

This does not replace Chromium's Mojom generator. It intentionally emits only
the C++ surface needed to compile reduced Blink probe targets when a generated
Mojom header is included only for types, enum constants, or forward
declarations. Runtime IPC bindings stay outside the standalone renderer cut.
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path


GENERATED_SUFFIXES = (
    ".mojom-blink-forward.h",
    ".mojom-blink.h",
    ".mojom-forward.h",
    ".mojom-shared.h",
    ".mojom.h",
)


def header_guard(path: Path) -> str:
    text = "STANDALONE_RENDERER_STUBS_" + "_".join(path.parts).upper()
    return re.sub(r"[^A-Z0-9_]", "_", text) + "_"


def strip_comments(text: str) -> str:
    text = re.sub(r"//.*", "", text)
    return re.sub(r"/\*.*?\*/", "", text, flags=re.S)


def parse_module(text: str) -> str:
    match = re.search(r"\bmodule\s+([A-Za-z0-9_.]+)\s*;", text)
    if not match:
        return "mojom"
    return match.group(1)


def cpp_namespace(module: str, blink: bool) -> str:
    parts = module.split(".")
    if blink:
        parts.append("blink")
    return "::".join(parts)


def parse_enums(text: str) -> list[tuple[str, list[str]]]:
    enums: list[tuple[str, list[str]]] = []
    for match in re.finditer(r"\benum\s+(\w+)\s*\{(.*?)\}\s*;?", text, re.S):
        name = match.group(1)
        values: list[str] = []
        for raw in match.group(2).split(","):
            value = raw.strip()
            if not value:
                continue
            value = value.split("=", 1)[0].strip()
            value = re.sub(r"^\[[^\]]+\]\s*", "", value)
            if re.match(r"^[A-Za-z_]\w*$", value):
                values.append(value)
        enums.append((name, values))
    return enums


def parse_declarations(text: str) -> dict[str, list[str]]:
    declarations = {
        "struct": [],
        "class": [],
        "interface": [],
        "union": [],
    }
    for kind in declarations:
        pattern = rf"\b{kind}\s+(\w+)\b"
        declarations[kind] = sorted(set(re.findall(pattern, text)))
    return declarations


def generated_to_mojom(include_path: str) -> Path:
    path = Path(include_path.replace("\\", "/"))
    text = path.as_posix()
    for suffix in GENERATED_SUFFIXES:
        if text.endswith(suffix):
            return Path(text[: -len(suffix)] + ".mojom")
    raise ValueError(f"unsupported generated Mojom header: {include_path}")


def source_for_include(repo: Path, include_path: str) -> Path:
    mojom = generated_to_mojom(include_path)
    direct = repo / mojom
    if direct.exists():
        return direct
    matches = list(repo.glob(mojom.as_posix()))
    if matches:
        return matches[0]
    raise FileNotFoundError(f"could not locate source Mojom for {include_path}")


def emit_forward(
    namespace: str,
    base_namespace: str,
    declarations: dict[str, list[str]],
    enums: list[tuple[str, list[str]]],
) -> list[str]:
    lines: list[str] = []
    if declarations["struct"]:
        lines.append("#include <memory>")
        lines.append("")
    lines.append(f"namespace {namespace} {{")
    lines.append("")
    for name, _ in enums:
        lines.append(f"enum class {name};")
    for name in declarations["struct"]:
        lines.append(f"struct {name};")
        lines.append(f"using {name}Ptr = std::unique_ptr<{name}>;")
    for name in declarations["union"]:
        lines.append(f"class {name};")
    for name in declarations["interface"]:
        lines.append(f"class {name};")
    for name in declarations["class"]:
        lines.append(f"class {name};")
    lines.append("")
    lines.append(f"}}  // namespace {namespace}")
    if namespace != base_namespace and enums:
        lines.append("")
        lines += emit_enum_aliases(base_namespace, namespace, enums)
    return lines


def emit_enums(namespace: str, enums: list[tuple[str, list[str]]]) -> list[str]:
    lines = [f"namespace {namespace} {{", ""]
    for name, values in enums:
        lines.append(f"enum class {name} {{")
        if values:
            for value in values:
                lines.append(f"  {value},")
            lines.append(f"  kMaxValue = {values[-1]},")
        lines.append("};")
        lines.append("")
    lines.append(f"}}  // namespace {namespace}")
    return lines


def emit_enum_aliases(namespace: str, target_namespace: str, enums: list[tuple[str, list[str]]]) -> list[str]:
    lines = [f"namespace {namespace} {{", ""]
    for name, _ in enums:
        lines.append(f"using {name} = ::{target_namespace}::{name};")
    lines.append("")
    lines.append(f"}}  // namespace {namespace}")
    return lines


def emit_wrapper(
    include_path: str, namespace: str, blink_namespace: str, declarations: dict[str, list[str]]
) -> list[str]:
    forward = include_path.replace(".mojom-blink.h", ".mojom-blink-forward.h")
    forward = forward.replace(".mojom.h", ".mojom-forward.h")
    lines = [f'#include "{forward}"', "", f"namespace {namespace} {{", ""]
    for kind in ("struct", "union", "interface", "class"):
        for name in declarations[kind]:
            lines.append(f"using {name} = ::{blink_namespace}::{name};")
    lines.append("")
    lines.append(f"}}  // namespace {namespace}")
    return lines


def generate(repo: Path, include_path: str) -> str:
    source = source_for_include(repo, include_path)
    source_text = strip_comments(source.read_text(encoding="utf-8"))
    blink = "-blink" in include_path
    namespace = cpp_namespace(parse_module(source_text), blink)
    base_namespace = cpp_namespace(parse_module(source_text), False)
    declarations = parse_declarations(source_text)
    enums = parse_enums(source_text)

    out_path = Path(include_path.replace("\\", "/"))
    guard = header_guard(out_path)
    lines = [f"#ifndef {guard}", f"#define {guard}", ""]

    if include_path.endswith("-forward.h"):
        lines += emit_forward(namespace, base_namespace, declarations, enums)
    elif include_path.endswith("-shared.h"):
        lines += emit_enums(namespace, enums)
    elif include_path.endswith(".mojom-blink.h") or include_path.endswith(".mojom.h"):
        if enums:
            lines += emit_enums(namespace, enums)
            if blink:
                lines.append("")
                lines += emit_enum_aliases(base_namespace, namespace, enums)
        else:
            target_namespace = namespace if blink else base_namespace + "::blink"
            lines += emit_wrapper(include_path, base_namespace, target_namespace, declarations)
    else:
        raise ValueError(f"unsupported generated Mojom header: {include_path}")

    lines += ["", f"#endif  // {guard}", ""]
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo", default=".", type=Path)
    parser.add_argument("--include", help="missing generated Mojom include path")
    parser.add_argument(
        "--from-log",
        type=Path,
        help="scan a compiler log for missing generated Mojom includes",
    )
    parser.add_argument("--stubs-root", default="standalone_renderer/stubs", type=Path)
    parser.add_argument("--check", action="store_true", help="print output instead of writing")
    args = parser.parse_args()

    repo = args.repo.resolve()
    includes: list[str] = []
    if args.include:
        includes.append(args.include.replace("\\", "/"))
    if args.from_log:
        log_text = (repo / args.from_log).read_text(encoding="utf-8", errors="replace")
        includes += re.findall(
            r"fatal error: '([^']+\.mojom(?:-blink)?(?:-forward|-shared)?\.h)' file not found",
            log_text,
        )
    includes = sorted(set(includes))
    if not includes:
        parser.error("provide --include or --from-log with at least one missing Mojom include")

    outputs: list[tuple[Path, str]] = []
    for include_path in includes:
        text = generate(repo, include_path)
        outputs.append((repo / args.stubs_root / include_path, text))

    if args.check:
        for output, text in outputs:
            print(f"// {output}")
            print(text, end="")
        return 0

    for output, text in outputs:
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(text, encoding="utf-8", newline="\n")
        print(output)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
