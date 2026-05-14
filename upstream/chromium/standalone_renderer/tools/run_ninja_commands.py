#!/usr/bin/env python3
"""Run a Ninja `-t commands` dump without using Ninja as the executor.

This is a local workaround for Windows environments where ninja.exe can parse
the graph but hangs after child processes finish. It intentionally supports only
the generated Chromium/GN command stream used by the standalone renderer probe.
"""

from __future__ import annotations

import argparse
import os
import pathlib
import re
import subprocess
import sys
import time


def _windows_executable(command: str) -> str:
    if command.startswith('"'):
        end = command.find('"', 1)
        if end != -1:
            return command[1:end]
    return command.split(None, 1)[0]


def _ascii(text: str) -> str:
    return text.encode("ascii", "replace").decode("ascii")


def _ninja_files(out_dir: pathlib.Path) -> list[pathlib.Path]:
    ninja_files = [out_dir / "toolchain.ninja"]
    ninja_files.extend(
        p for p in out_dir.rglob("*.ninja") if p.name != "toolchain.ninja"
    )
    return ninja_files


def _merge_ninja_lines(path: pathlib.Path) -> list[str]:
        raw = path.read_text(encoding="utf-8", errors="replace").splitlines()
        merged: list[str] = []
        current = ""
        for line in raw:
            if line.endswith("$"):
                current += line[:-1]
            else:
                merged.append(current + line)
                current = ""
        if current:
            merged.append(current)
        return merged


def _expand_ninja_value(value: str, variables: dict[str, str]) -> str:
        value = value.replace("$ ", " ").replace("$$", "$")

        def repl(match: re.Match[str]) -> str:
            name = match.group(1) or match.group(2)
            return variables.get(name, match.group(0))

        previous = None
        while previous != value:
            previous = value
            value = re.sub(r"\$\{([^}]+)\}|\$([A-Za-z0-9_]+)", repl, value)
        value = re.sub(r"\$\{[^}]+\}", "", value)
        return value.replace("$:", ":")


def _parse_build(line: str) -> tuple[list[str], str, list[str]] | None:
        if not line.startswith("build ") or ": " not in line:
            return None
        left, right = line[6:].split(": ", 1)
        outputs = left.split()
        parts = right.split()
        if not parts:
            return None
        rule = parts[0]
        inputs: list[str] = []
        for part in parts[1:]:
            if part in ("|", "||"):
                break
            inputs.append(part)
        return outputs, rule, inputs

def _collect_rules(out_dir: pathlib.Path) -> dict[str, dict[str, str]]:
    rules: dict[str, dict[str, str]] = {}
    for ninja_file in _ninja_files(out_dir):
        if not ninja_file.exists():
            continue
        current_rule = None
        for line in _merge_ninja_lines(ninja_file):
            if line.startswith("rule "):
                current_rule = line.split(None, 1)[1].strip()
                rules.setdefault(current_rule, {})
                continue
            if current_rule and line.startswith("  "):
                if "=" in line:
                    key, value = line.strip().split("=", 1)
                    key = key.strip()
                    value = value.strip()
                    if key in ("command", "rspfile", "rspfile_content"):
                        rules[current_rule][key] = value
                continue
            current_rule = None
    return rules


def materialize_rspfiles(out_dir: pathlib.Path) -> int:
    count = 0
    rules = _collect_rules(out_dir)

    for ninja_file in _ninja_files(out_dir):
        if not ninja_file.exists():
            continue
        rspfile = None
        for line in _merge_ninja_lines(ninja_file):
            if line.startswith("rule "):
                rspfile = None
                continue

            if line.startswith("  rspfile = "):
                rspfile = line.split("=", 1)[1].strip()
                continue
            if line.startswith("  rspfile_content = ") and rspfile:
                content = line.split("=", 1)[1].strip()
                path = out_dir / rspfile
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(content, encoding="utf-8")
                count += 1
                rspfile = None
                continue
            if line and not line.startswith("  "):
                rspfile = None

    for ninja_file in _ninja_files(out_dir):
        if not ninja_file.exists():
            continue
        lines = _merge_ninja_lines(ninja_file)
        file_vars: dict[str, str] = {}
        index = 0
        while index < len(lines):
            if (
                not lines[index].startswith((" ", "build ", "rule ", "subninja "))
                and "=" in lines[index]
            ):
                key, value = lines[index].split("=", 1)
                file_vars[key.strip()] = value.strip()
                index += 1
                continue
            parsed = _parse_build(lines[index])
            if not parsed:
                index += 1
                continue
            outputs, rule, inputs = parsed
            index += 1
            edge_vars: dict[str, str] = dict(file_vars)
            edge_vars.update({
                "in": " ".join(inputs),
                "in_newline": "\n".join(inputs),
                "out": " ".join(outputs),
            })
            while index < len(lines) and lines[index].startswith("  "):
                if "=" in lines[index]:
                    key, value = lines[index].strip().split("=", 1)
                    edge_vars[key.strip()] = value.strip()
                index += 1

            rule_vars = rules.get(rule)
            if not rule_vars or "rspfile" not in rule_vars or "rspfile_content" not in rule_vars:
                continue
            rsp_path = out_dir / _expand_ninja_value(rule_vars["rspfile"], edge_vars)
            content = _expand_ninja_value(rule_vars["rspfile_content"], edge_vars)
            rsp_path.parent.mkdir(parents=True, exist_ok=True)
            rsp_path.write_text(content, encoding="utf-8")
            count += 1
    return count


def command_outputs(out_dir: pathlib.Path) -> dict[str, list[pathlib.Path]]:
    rules = _collect_rules(out_dir)
    outputs_by_command: dict[str, list[pathlib.Path]] = {}

    for ninja_file in _ninja_files(out_dir):
        if not ninja_file.exists():
            continue
        lines = _merge_ninja_lines(ninja_file)
        file_vars: dict[str, str] = {}
        index = 0
        while index < len(lines):
            if (
                not lines[index].startswith((" ", "build ", "rule ", "subninja "))
                and "=" in lines[index]
            ):
                key, value = lines[index].split("=", 1)
                file_vars[key.strip()] = value.strip()
                index += 1
                continue
            parsed = _parse_build(lines[index])
            if not parsed:
                index += 1
                continue
            outputs, rule, inputs = parsed
            index += 1
            edge_vars: dict[str, str] = dict(file_vars)
            edge_vars.update({
                "in": " ".join(inputs),
                "in_newline": "\n".join(inputs),
                "out": " ".join(outputs),
            })
            while index < len(lines) and lines[index].startswith("  "):
                if "=" in lines[index]:
                    key, value = lines[index].strip().split("=", 1)
                    edge_vars[key.strip()] = value.strip()
                index += 1

            command = rules.get(rule, {}).get("command")
            if not command:
                continue
            expanded_command = _expand_ninja_value(command, edge_vars)
            output_paths = [out_dir / output for output in outputs if not output.startswith("|")]
            if output_paths:
                outputs_by_command.setdefault(expanded_command, []).extend(output_paths)
    return outputs_by_command


def _ensure_command_output_dirs(out_dir: pathlib.Path, cmd: str) -> None:
    for match in re.finditer(r'/(?:Fo|OUT:)(?:"([^"]+)"|([^\s]+))', cmd):
        output = match.group(1) or match.group(2)
        if not output:
            continue
        path = pathlib.Path(output)
        if not path.is_absolute():
            path = out_dir / path
        path.parent.mkdir(parents=True, exist_ok=True)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out-dir", required=True, type=pathlib.Path)
    parser.add_argument("--commands", required=True, type=pathlib.Path)
    parser.add_argument("--log", required=True, type=pathlib.Path)
    parser.add_argument("--progress", required=True, type=pathlib.Path)
    parser.add_argument("--start", type=int)
    parser.add_argument("--limit", type=int)
    parser.add_argument("--skip-existing", action="store_true")
    parser.add_argument("--timeout", type=int, default=600)
    parser.add_argument("--retries", type=int, default=1)
    args = parser.parse_args()

    out_dir = args.out_dir.resolve()
    commands_path = args.commands.resolve()
    log_path = args.log.resolve()
    progress_path = args.progress.resolve()

    rsp_count = materialize_rspfiles(out_dir)
    outputs_by_command = command_outputs(out_dir) if args.skip_existing else {}
    commands = commands_path.read_text(encoding="utf-8", errors="replace").splitlines()

    if args.start is not None:
        start = args.start
    elif progress_path.exists():
        start = int(progress_path.read_text(encoding="utf-8").strip() or "0")
    else:
        start = 0

    end = len(commands) if args.limit is None else min(len(commands), start + args.limit)
    log_path.parent.mkdir(parents=True, exist_ok=True)

    with log_path.open("a", encoding="utf-8", errors="replace") as log:
        log.write(f"materialized_rspfiles={rsp_count}\n")
        log.write(f"run_range={start}:{end} total={len(commands)}\n")
        log.flush()

        for index in range(start, end):
            cmd = commands[index]
            marker = f"[{index + 1}/{len(commands)}]"
            outputs = outputs_by_command.get(cmd, [])
            if outputs and all(path.exists() for path in outputs):
                progress_path.write_text(str(index + 1), encoding="utf-8")
                log.write(f"\n{marker} SKIP existing outputs\n")
                continue
            for output in outputs:
                output.parent.mkdir(parents=True, exist_ok=True)
            _ensure_command_output_dirs(out_dir, cmd)
            print(marker, _ascii(cmd[:220]), flush=True)
            log.write(f"\n{marker} {cmd}\n")
            log.flush()

            for attempt in range(args.retries + 1):
                if attempt:
                    log.write(f"retry={attempt}\n")
                    print(f"{marker} retry {attempt}", flush=True)
                    log.flush()
                    time.sleep(min(2 * attempt, 10))

                begin = time.time()
                try:
                    env = os.environ.copy()
                    if "mojom_parser.py" in cmd:
                        env["CHROMIUM_STANDALONE_SERIAL_MOJOM"] = "1"
                    executable = pathlib.Path(_windows_executable(cmd))
                    if not executable.is_absolute():
                        executable = out_dir / executable
                    result = subprocess.run(
                        cmd,
                        executable=str(executable),
                        cwd=out_dir,
                        env=env,
                        # Avoid cmd.exe's ~8k command-line limit. Windows
                        # CreateProcess accepts Chromium's expanded compiler
                        # command lines here even when cmd.exe refuses them.
                        shell=False,
                        text=True,
                        capture_output=True,
                        encoding="utf-8",
                        errors="replace",
                        timeout=args.timeout,
                    )
                except subprocess.TimeoutExpired as exc:
                    log.write(f"TIMEOUT after {args.timeout}s\n")
                    if exc.stdout:
                        log.write(exc.stdout)
                    if exc.stderr:
                        log.write(exc.stderr)
                    log.flush()
                    print(f"{marker} TIMEOUT after {args.timeout}s", flush=True)
                    return 124

                elapsed = time.time() - begin
                if result.stdout:
                    log.write(result.stdout)
                if result.stderr:
                    log.write(result.stderr)
                log.write(f"exit={result.returncode} elapsed={elapsed:.2f}s\n")
                log.flush()

                if not result.returncode:
                    break
            else:
                print(f"{marker} FAILED exit={result.returncode}", flush=True)
                progress_path.write_text(str(index), encoding="utf-8")
                return result.returncode

            progress_path.write_text(str(index + 1), encoding="utf-8")

    print(f"completed {start}:{end} of {len(commands)}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
