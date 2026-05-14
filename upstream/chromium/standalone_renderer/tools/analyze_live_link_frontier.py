#!/usr/bin/env python3
"""Classify unresolved symbols from the live Blink standalone link probe.

The live Blink cut intentionally links a small real-Blink island against a
standalone boundary file. Link errors are useful, but manually scanning them is
slow and error-prone. This tool extracts the unresolved symbols, groups them by
policy, and emits either a human-readable report or a conservative C++ stub
candidate block for very low-risk patterns.

It does not blindly generate all stubs. Symbols that can affect parsing, style,
layout, paint, GC ownership, or object lifetime are classified for manual
review. The goal is to automate triage and boilerplate, while keeping the cut
honest about what is real Blink and what is a disabled browser/JS edge.
"""

from __future__ import annotations

import argparse
import dataclasses
import json
import re
from collections import Counter, defaultdict
from pathlib import Path
from typing import Iterable


UNDEFINED_RE = re.compile(r"lld-link: error: undefined symbol: (.+)$")
REFERENCED_RE = re.compile(r">>> referenced by (.+)$")


@dataclasses.dataclass(frozen=True)
class SymbolRecord:
    symbol: str
    references: tuple[str, ...]
    category: str
    action: str
    confidence: str
    reason: str


def _namespace_hint(symbol: str) -> str:
    if " blink::" in symbol or symbol.startswith("blink::"):
        return "blink"
    if " base::" in symbol or symbol.startswith("base::"):
        return "base"
    if " mojo::" in symbol or symbol.startswith("mojo::") or "Mojo" in symbol:
        return "mojo"
    if " v8::" in symbol or symbol.startswith("v8::"):
        return "v8"
    if " net::" in symbol or symbol.startswith("net::"):
        return "net"
    if " network::" in symbol or symbol.startswith("network::"):
        return "network"
    if " gfx::" in symbol or symbol.startswith("gfx::"):
        return "gfx"
    if " cc::" in symbol or symbol.startswith("cc::"):
        return "cc"
    if " cppgc::" in symbol or symbol.startswith("cppgc::"):
        return "cppgc"
    return "other"


def parse_link_log(path: Path) -> list[tuple[str, tuple[str, ...]]]:
    """Return unresolved symbols and following reference lines."""

    records: list[tuple[str, tuple[str, ...]]] = []
    current_symbol: str | None = None
    current_refs: list[str] = []

    raw = path.read_bytes()
    if raw.count(b"\x00") > max(8, len(raw) // 20):
        text = raw.decode("utf-16", errors="replace")
    else:
        text = raw.decode("utf-8", errors="replace")

    for raw_line in text.splitlines():
        line = raw_line.strip()
        match = UNDEFINED_RE.search(line)
        if match:
            if current_symbol is not None:
                records.append((current_symbol, tuple(current_refs)))
            current_symbol = match.group(1).strip()
            current_refs = []
            continue

        ref_match = REFERENCED_RE.search(line)
        if ref_match and current_symbol is not None:
            current_refs.append(ref_match.group(1).strip())

    if current_symbol is not None:
        records.append((current_symbol, tuple(current_refs)))

    seen: set[str] = set()
    deduped: list[tuple[str, tuple[str, ...]]] = []
    for symbol, refs in records:
        if symbol in seen:
            continue
        seen.add(symbol)
        deduped.append((symbol, refs))
    return deduped


def classify_symbol(symbol: str, refs: Iterable[str]) -> tuple[str, str, str, str]:
    ref_text = "\n".join(refs)
    ns = _namespace_hint(symbol)

    if "RuntimeEnabledFeaturesBase::is_" in symbol:
        return (
            "runtime_flag",
            "auto_stub",
            "high",
            "Runtime feature flags are process-global booleans; default false is correct for the standalone no-feature path.",
        )

    if "WrapperTypeInfo const &blink::" in symbol and "::wrapper_type_info_" in symbol:
        return (
            "generated_binding_wrapper",
            "auto_stub",
            "medium",
            "Script wrapper metadata can use the standalone dummy wrapper only when the owning object is never exposed to JS.",
        )

    if "struct base::Feature const blink::features::k" in symbol:
        return (
            "feature_constant",
            "auto_stub",
            "high",
            "Blink feature constants can default disabled for standalone unless the feature is rendering-critical.",
        )

    if "blink::switches::k" in symbol:
        return (
            "blink_switch",
            "auto_stub",
            "high",
            "Command-line switches are browser configuration edges; standalone should define inert constants.",
        )

    if ns in {"mojo", "network", "net"} or symbol.startswith("Mojo"):
        return (
            "service_edge",
            "stub_or_cut",
            "high",
            "Network/Mojo/service symbols are outside the renderer runtime contract and should be no-op or cut off.",
        )

    if ns == "base" and any(
        token in symbol
        for token in (
            "SequencedTaskRunner",
            "CommandLine",
            "Histogram",
            "SequenceChecker",
            "SharedMemory",
            "MemoryMappedFile",
            "File::~File",
        )
    ):
        return (
            "base_runtime_edge",
            "stub_or_replace",
            "medium",
            "Base utility leakage should be minimized; simple telemetry/task/file edges can be no-op in v1.",
        )

    if ns == "v8":
        return (
            "v8_no_script_edge",
            "stub_or_cut",
            "medium",
            "V8 symbols should stay inert because v1 does not execute scripts.",
        )

    if any(
        token in symbol
        for token in (
            "MainThreadDebugger",
            "InspectorIssueStorage",
            "AuditsIssue",
            "ReportingContext",
            "Report",
            "DocumentPolicyViolationReportBody",
            "Deprecation::",
            "probe::",
            "ExceptionMessages::",
        )
    ):
        return (
            "diagnostics_reporting",
            "stub_or_cut",
            "high",
            "Inspector/reporting/deprecation paths are observability edges, not rendering inputs.",
        )

    if any(
        token in symbol
        for token in (
            "ContentSecurityPolicy",
            "TrustedType",
            "IsolatedWorldCSP",
            "BindingSecurity",
            "WorldSafeV8Reference",
            "CalculateHttpsState",
        )
    ):
        return (
            "security_js_policy",
            "stub_disabled",
            "medium",
            "No-JS v1 still needs inert policy hooks, but these must default to deny execution and allow internal rendering.",
        )

    if any(
        token in symbol
        for token in (
            "BackForwardCacheBufferLimitTracker",
            "NetworkStateNotifier",
            "BrowserInterfaceBroker",
            "FrameScheduler",
            "AgentGroupScheduler",
            "GetNetworkStateNotifier",
            "GetEmptyBrowserInterfaceBroker",
            "GetNameForFeature",
            "GetDocumentPolicyFeatureInfoMap",
            "PermissionsPolicy",
            "SameDomainOrHost",
        )
    ):
        return (
            "browser_platform_edge",
            "stub_or_cut",
            "high",
            "Browser/platform integration is outside standalone rendering; keep inert unless it affects lifecycle progress.",
        )

    if any(
        token in symbol
        for token in (
            "DOMWindow",
            "ExecutionContext",
            "LocalDOMWindow",
            "Navigator",
            "Screen",
            "History",
            "WindowPerformance",
            "DOMViewport",
            "DOMVisualViewport",
        )
    ):
        return (
            "window_execution_shell",
            "manual_stub",
            "medium",
            "Window/ExecutionContext constructors and lifecycle need case-by-case base/member initialization.",
        )

    if any(
        token in symbol
        for token in (
            "CSSComputedStyleDeclaration",
            "ScrollToOptions",
            "V8FrameCallback",
            "PageTransitionEvent",
            "PopStateEvent",
            "EventTiming",
            "ScopedEventQueue",
            "DocumentLoadTiming",
            "WindowPerformance",
            "Performance::",
            "SoftNavigationHeuristics",
            "SyncScrollAttemptHeuristic",
        )
    ):
        return (
            "cssom_event_side_api",
            "manual_stub",
            "medium",
            "CSSOM/event side APIs are generally not needed for painting but vtables and GC tracing need correct shape.",
        )

    if any(
        token in symbol
        for token in (
            "ScriptController::DisableEval",
            "ScriptController::SetWasmEvalErrorMessage",
            "ToV8ContextMaybeEmpty",
            "ToLocalDOMWindow",
            "ScriptWrappable::ToV8",
            "V8FrameCallback",
            "SerializedScriptValue",
            "ArrayBufferContents",
            "SharedValueConveyor",
        )
    ):
        return (
            "js_binding_inert",
            "stub_disabled",
            "medium",
            "Script-facing helper should be present but inert in no-JS v1.",
        )

    if any(
        token in symbol
        for token in (
            "StyleResolver",
            "Layout",
            "Paint",
            "PaintArtifact",
            "PaintLayer",
            "ComputedStyle",
            "Font",
            "ImageResource",
            "HTMLDocumentParser",
            "HTMLTreeBuilder",
        )
    ):
        return (
            "rendering_core",
            "manual_review",
            "low",
            "This may affect actual parse/style/layout/paint behavior; prefer real Blink source or a deliberate cut.",
        )

    if "live_link_boundary_stubs.obj" in ref_text:
        return (
            "stub_shape_debt",
            "fix_existing_stub",
            "medium",
            "The missing symbol is referenced by the boundary file itself; fix the existing stub shape before adding more.",
        )

    return (
        f"{ns}_uncategorized",
        "manual_review",
        "low",
        "No safe automatic policy matched this symbol.",
    )


def build_records(path: Path) -> list[SymbolRecord]:
    records: list[SymbolRecord] = []
    for symbol, refs in parse_link_log(path):
        category, action, confidence, reason = classify_symbol(symbol, refs)
        records.append(
            SymbolRecord(
                symbol=symbol,
                references=refs,
                category=category,
                action=action,
                confidence=confidence,
                reason=reason,
            )
        )
    return records


def _extract_runtime_flag(symbol: str) -> str | None:
    match = re.search(r"RuntimeEnabledFeaturesBase::(is_[A-Za-z0-9_]+_enabled_)", symbol)
    return match.group(1) if match else None


def _extract_wrapper_owner(symbol: str) -> str | None:
    match = re.search(r"blink::([A-Za-z0-9_]+)::wrapper_type_info_", symbol)
    return match.group(1) if match else None


def _extract_feature_name(symbol: str) -> str | None:
    match = re.search(r"blink::features::(k[A-Za-z0-9_]+)", symbol)
    return match.group(1) if match else None


def _extract_switch_name(symbol: str) -> str | None:
    match = re.search(r"blink::switches::(k[A-Za-z0-9_]+)", symbol)
    return match.group(1) if match else None


def _feature_string(name: str) -> str:
    return name[1:] if name.startswith("k") else name


def _switch_string(name: str) -> str:
    body = name[1:] if name.startswith("k") else name
    out = []
    for index, char in enumerate(body):
        if char.isupper() and index:
            out.append("-")
        out.append(char.lower())
    return "".join(out)


def generate_stub_candidates(records: Iterable[SymbolRecord]) -> str:
    """Generate only simple candidates that still require review."""

    runtime_flags: list[str] = []
    wrapper_owners: list[str] = []
    features: list[str] = []
    switches: list[str] = []

    for record in records:
        if record.action != "auto_stub":
            continue
        if flag := _extract_runtime_flag(record.symbol):
            runtime_flags.append(flag)
        if owner := _extract_wrapper_owner(record.symbol):
            wrapper_owners.append(owner)
        if feature := _extract_feature_name(record.symbol):
            features.append(feature)
        if switch := _extract_switch_name(record.symbol):
            switches.append(switch)

    lines: list[str] = [
        "// Auto-stub candidates generated by analyze_live_link_frontier.py.",
        "// Review before applying. Do not add rendering/layout/paint symbols here.",
        "",
        "namespace blink {",
    ]

    for flag in sorted(set(runtime_flags)):
        lines.append(f"bool RuntimeEnabledFeaturesBase::{flag} = false;")

    if wrapper_owners:
        lines.append("")
        for owner in sorted(set(wrapper_owners)):
            lines.append(
                f"const WrapperTypeInfo& {owner}::wrapper_type_info_ ="
            )
            lines.append("    StandaloneDummyWrapperTypeInfo();")

    if features:
        lines.append("")
        lines.append("namespace features {")
        for feature in sorted(set(features)):
            lines.append(
                f'BASE_FEATURE({feature}, "{_feature_string(feature)}", '
                "base::FEATURE_DISABLED_BY_DEFAULT);"
            )
        lines.append("}  // namespace features")

    if switches:
        lines.append("")
        lines.append("namespace switches {")
        for switch in sorted(set(switches)):
            lines.append(f'extern const char {switch}[] = "{_switch_string(switch)}";')
        lines.append("}  // namespace switches")

    lines.append("}  // namespace blink")
    return "\n".join(lines) + "\n"


def print_report(records: list[SymbolRecord], limit: int | None) -> None:
    counts = Counter(record.category for record in records)
    actions = Counter(record.action for record in records)

    print(f"Unresolved symbols: {len(records)}")
    print("")
    print("By category:")
    for category, count in counts.most_common():
        print(f"  {category}: {count}")
    print("")
    print("By action:")
    for action, count in actions.most_common():
        print(f"  {action}: {count}")
    print("")

    grouped: dict[str, list[SymbolRecord]] = defaultdict(list)
    for record in records:
        grouped[record.action].append(record)

    shown = 0
    for action in sorted(grouped):
        print(f"[{action}]")
        for record in grouped[action]:
            if limit is not None and shown >= limit:
                return
            print(f"  - {record.category}: {record.symbol}")
            print(f"    confidence={record.confidence}; {record.reason}")
            if record.references:
                print(f"    first_ref={record.references[0]}")
            shown += 1
        print("")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--log",
        type=Path,
        default=Path("standalone_renderer/tmp_live_link.log"),
        help="Path to link log produced by compile_live_frame_bridge_probe.py.",
    )
    parser.add_argument("--json", type=Path, help="Write machine-readable report.")
    parser.add_argument(
        "--candidates",
        type=Path,
        help="Write conservative C++ auto-stub candidates.",
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=80,
        help="Maximum detailed symbols to print; use 0 for summary only.",
    )
    args = parser.parse_args()

    if not args.log.exists():
        parser.error(f"link log not found: {args.log}")

    records = build_records(args.log)

    if args.json:
        args.json.write_text(
            json.dumps([dataclasses.asdict(record) for record in records], indent=2),
            encoding="utf-8",
        )

    if args.candidates:
        args.candidates.write_text(generate_stub_candidates(records), encoding="utf-8")

    print_report(records, None if args.limit < 0 else args.limit)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
