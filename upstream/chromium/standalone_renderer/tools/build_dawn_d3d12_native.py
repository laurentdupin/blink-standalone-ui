#!/usr/bin/env python3
"""Fetches and builds the pinned Dawn native D3D12 implementation.

This is an intermediate standalone GPU interop tool. It materializes the Dawn
source and native dependencies under the build tree, then builds the Dawn native
D3D12 targets with CMake/Ninja. It does not wire Dawn into the renderer targets
by itself; the output is the input for the next D3D12 Graphite/Viz integration
step.
"""

import argparse
import os
import pathlib
import re
import shutil
import subprocess
import sys


def run(command, cwd=None):
  print("+ " + " ".join(str(part) for part in command), flush=True)
  subprocess.run(command, cwd=cwd, check=True)


def read_cmake_cache_value(cache_path, name):
  if not cache_path.exists():
    return None
  prefix = name + ":"
  for line in cache_path.read_text(encoding="utf-8", errors="ignore").splitlines():
    if line.startswith(prefix):
      _, value = line.split("=", 1)
      return value.strip()
  return None


def cmake_list(value):
  if not value:
    return []
  return [part for part in value.split(";") if part]


def chromium_libcxx_cxx_flags(cache_path):
  include_dirs = cmake_list(read_cmake_cache_value(
      cache_path, "BLINK_STANDALONE_CHROMIUM_LIBCXX_INCLUDE_DIRS"))
  defines = cmake_list(read_cmake_cache_value(
      cache_path, "BLINK_STANDALONE_CHROMIUM_LIBCXX_DEFINES"))
  if include_dirs and not defines:
    defines = [
        "_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE",
        "_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS",
        "_LIBCPP_INSTRUMENTED_WITH_ASAN=0",
        "CR_LIBCXX_REVISION=5abc7f839700f0f17338434e1c1c6a8c87c00c11",
        "ABSL_ALLOCATOR_NOTHROW=1",
        "_HAS_NODISCARD",
    ]
  flags = []
  for include_dir in include_dirs:
    flags.append("/I" + include_dir)
  for define in defines:
    flags.append("/D" + define)
  return " ".join(flags)


def pinned_dawn_revision(repo_root):
  deps_path = repo_root / "upstream" / "chromium" / "third_party" / "skia" / "DEPS"
  text = deps_path.read_text(encoding="utf-8")
  match = re.search(r'"third_party/externals/dawn"\s*:\s*"[^@]+@([0-9a-f]+)"',
                    text)
  if not match:
    raise RuntimeError(f"Could not find pinned Dawn revision in {deps_path}")
  return match.group(1)


def ensure_dawn_checkout(dawn_dir, revision):
  dawn_dir.mkdir(parents=True, exist_ok=True)
  if not (dawn_dir / ".git").exists():
    run(["git", "init"], cwd=dawn_dir)
    run(["git", "remote", "add", "origin",
         "https://dawn.googlesource.com/dawn.git"], cwd=dawn_dir)
  current = subprocess.run(["git", "rev-parse", "HEAD"], cwd=dawn_dir,
                           text=True, stdout=subprocess.PIPE,
                           stderr=subprocess.DEVNULL)
  if current.returncode == 0 and current.stdout.strip() == revision:
    return
  run(["git", "-c", "protocol.version=2", "fetch", "--depth", "1",
       "--filter=blob:none", "origin", revision], cwd=dawn_dir)
  run(["git", "checkout", "--detach", "FETCH_HEAD"], cwd=dawn_dir)


def main():
  parser = argparse.ArgumentParser()
  parser.add_argument("--work-dir",
                      default="build/dawn_d3d12_native",
                      help="Scratch directory for Dawn source/build output.")
  parser.add_argument("--renderer-build-dir",
                      default="build/cmake-generated-v8-chromium-llvm",
                      help="Existing standalone renderer CMake build directory.")
  parser.add_argument("--cc", help="C compiler. Defaults to renderer CMake cache.")
  parser.add_argument("--cxx", help="C++ compiler. Defaults to renderer CMake cache.")
  parser.add_argument("--no-fetch-deps", action="store_true",
                      help="Skip Dawn dependency fetch if already synced.")
  args = parser.parse_args()

  repo_root = pathlib.Path(__file__).resolve().parents[4]
  work_dir = (repo_root / args.work_dir).resolve()
  dawn_dir = work_dir / "dawn"
  dawn_build_dir = work_dir / "cmake_d3d12"
  renderer_build_dir = (repo_root / args.renderer_build_dir).resolve()
  cache_path = renderer_build_dir / "CMakeCache.txt"

  cmake = shutil.which("cmake")
  ninja = shutil.which("ninja")
  if not cmake or not ninja:
    raise RuntimeError("cmake and ninja must be available on PATH")

  cc = args.cc or read_cmake_cache_value(cache_path, "CMAKE_C_COMPILER")
  cxx = args.cxx or read_cmake_cache_value(cache_path, "CMAKE_CXX_COMPILER")
  if not cc or not cxx:
    raise RuntimeError("Could not determine C/C++ compiler; pass --cc and --cxx")
  cxx_flags = chromium_libcxx_cxx_flags(cache_path)

  revision = pinned_dawn_revision(repo_root)
  ensure_dawn_checkout(dawn_dir, revision)

  if not args.no_fetch_deps:
    run([sys.executable, str(dawn_dir / "tools" / "fetch_dawn_dependencies.py"),
         "--directory", str(dawn_dir), "--shallow"])

  configure = [
      cmake,
      "-S", str(dawn_dir),
      "-B", str(dawn_build_dir),
      "-G", "Ninja",
      f"-DCMAKE_MAKE_PROGRAM={ninja}",
      "-DCMAKE_BUILD_TYPE=Release",
      f"-DCMAKE_C_COMPILER={cc}",
      f"-DCMAKE_CXX_COMPILER={cxx}",
      f"-DCMAKE_CXX_FLAGS={cxx_flags}",
      "-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded",
      "-DABSL_MSVC_STATIC_RUNTIME=ON",
      "-DDAWN_ENABLE_D3D12=ON",
      "-DDAWN_ENABLE_D3D11=OFF",
      "-DDAWN_ENABLE_VULKAN=OFF",
      "-DDAWN_ENABLE_DESKTOP_GL=OFF",
      "-DDAWN_ENABLE_OPENGLES=OFF",
      "-DDAWN_ENABLE_METAL=OFF",
      "-DDAWN_BUILD_BENCHMARKS=OFF",
      "-DDAWN_BUILD_SAMPLES=OFF",
      "-DDAWN_BUILD_TESTS=OFF",
      "-DTINT_BUILD_TESTS=OFF",
      "-DTINT_BUILD_HLSL_WRITER=ON",
      "-DDAWN_FETCH_DEPENDENCIES=OFF",
      "-DDAWN_BUILD_MONOLITHIC_LIBRARY=OFF",
      "-DDAWN_FORCE_SYSTEM_COMPONENT_LOAD=ON",
  ]
  run(configure)
  run([cmake, "--build", str(dawn_build_dir), "--target",
       "webgpu_headers_gen", "dawn_proc", "dawn_native", "--parallel", "8"])

  print("dawn_d3d12_native: ok")
  print(f"source={dawn_dir}")
  print(f"build={dawn_build_dir}")
  print(f"generated_headers={dawn_build_dir / 'gen' / 'include'}")
  dawn_libs = [
      dawn_build_dir / "src" / "dawn" / "native" / "dawn_native.lib",
      dawn_build_dir / "src" / "dawn" / "dawn_proc.lib",
      dawn_build_dir / "src" / "dawn" / "common" / "dawn_common.lib",
      dawn_build_dir / "src" / "dawn" / "platform" / "dawn_platform.lib",
      dawn_build_dir / "src" / "dawn" / "utils" / "dawn_system_utils.lib",
  ]
  dawn_libs.extend(sorted((dawn_build_dir / "src" / "tint").glob("*.lib")))
  dawn_libs.extend(sorted((dawn_build_dir / "third_party" / "abseil").rglob("*.lib")))
  print("dawn_libs=" + ";".join(str(lib) for lib in dawn_libs))


if __name__ == "__main__":
  main()
