param(
  [string]$BuildDir = "build/cmake-msvc-static-proof",
  [string]$V8BuildDir = "build/cmake-msvc-release",
  [string]$DawnWorkDir = "build/dawn_probe",
  [int]$Jobs = 8,
  [switch]$SkipV8Build,
  [switch]$SkipDawnBuild,
  [switch]$NoFetchDawnDeps
)

$ErrorActionPreference = "Stop"

function Resolve-RepoPath([string]$Path) {
  if ([System.IO.Path]::IsPathRooted($Path)) {
    return [System.IO.Path]::GetFullPath($Path)
  }
  return [System.IO.Path]::GetFullPath((Join-Path $RepoRoot $Path))
}

function Require-Command([string]$Name) {
  $command = Get-Command $Name -ErrorAction SilentlyContinue
  if (-not $command) {
    throw "Required command '$Name' was not found on PATH. Run from a VS x64 Developer PowerShell/Command Prompt with CMake and Ninja available."
  }
  return $command.Source
}

function Add-GitSafeDirectory([string]$Path) {
  $fullPath = [System.IO.Path]::GetFullPath($Path).Replace('\', '/')
  $count = 0
  if ($env:GIT_CONFIG_COUNT) {
    $count = [int]$env:GIT_CONFIG_COUNT
  }
  [Environment]::SetEnvironmentVariable("GIT_CONFIG_KEY_$count", "safe.directory", "Process")
  [Environment]::SetEnvironmentVariable("GIT_CONFIG_VALUE_$count", $fullPath, "Process")
  [Environment]::SetEnvironmentVariable("GIT_CONFIG_COUNT", [string]($count + 1), "Process")
}

function Invoke-Step([string]$Name, [scriptblock]$Body) {
  Write-Host "==> $Name"
  & $Body
}

$ScriptPath = $MyInvocation.MyCommand.Path
$RepoRoot = [System.IO.Path]::GetFullPath((Join-Path (Split-Path -Parent $ScriptPath) "../../../.."))
Set-Location $RepoRoot

$cmake = Require-Command "cmake"
$ninja = Require-Command "ninja"
$python = Require-Command "python"
$cl = Require-Command "cl"

$BuildDirFull = Resolve-RepoPath $BuildDir
$V8BuildDirFull = Resolve-RepoPath $V8BuildDir
$DawnWorkDirFull = Resolve-RepoPath $DawnWorkDir
$V8WorkRoot = Join-Path $V8BuildDirFull "v8_compat"
$V8OutDir = Join-Path $V8WorkRoot "src/v8/out/chromium_static"
$V8Monolith = Join-Path $V8OutDir "obj/v8_monolith.lib"
$V8HeapHeader = Join-Path $V8WorkRoot "src/v8/include/cppgc/heap.h"

Add-GitSafeDirectory (Join-Path $V8WorkRoot "src/v8")
Add-GitSafeDirectory (Join-Path $V8WorkRoot "depot_tools")
Add-GitSafeDirectory (Join-Path $V8WorkRoot "src/v8/build")
Add-GitSafeDirectory (Join-Path $V8WorkRoot "src/v8/third_party/partition_alloc")
Add-GitSafeDirectory (Join-Path $DawnWorkDirFull "dawn")

if (-not $SkipV8Build) {
  if ((Test-Path $V8Monolith) -and (Test-Path $V8HeapHeader)) {
    Write-Host "V8 compatibility output already exists: $V8Monolith"
  } else {
    Invoke-Step "Configure native MSVC V8 compatibility build" {
      & $cmake -S $RepoRoot -B $V8BuildDirFull -G Ninja `
        -DCMAKE_BUILD_TYPE=Release `
        -DCMAKE_C_COMPILER=cl `
        -DCMAKE_CXX_COMPILER=cl `
        -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded `
        -DBLINK_STANDALONE_USE_VCPKG_DEPS=OFF `
        -DBLINK_STANDALONE_BUILD_SDL_VIEWER=OFF `
        -DBLINK_STANDALONE_V8_TOOLCHAIN=msvc `
        -DBLINK_STANDALONE_V8_COMPAT_ACTION=build `
        -DBLINK_STANDALONE_V8_SYNC_DEPS=ON `
        "-DBLINK_STANDALONE_V8_COMPAT_JOBS=$Jobs"
    }
    Invoke-Step "Build native MSVC V8 compatibility output" {
      & $cmake --build $V8BuildDirFull --target blink_standalone_v8_compat --parallel $Jobs
    }
  }
}

if (-not ((Test-Path $V8Monolith) -and (Test-Path $V8HeapHeader))) {
  throw "Missing V8 compatibility output. Expected '$V8Monolith' and '$V8HeapHeader'. Re-run without -SkipV8Build; first run may need network/depot_tools/CIPD access."
}

if (-not $SkipDawnBuild) {
  $dawnArgs = @(
    (Join-Path $RepoRoot "upstream/chromium/standalone_renderer/tools/build_dawn_d3d12_native.py"),
    "--work-dir", $DawnWorkDirFull,
    "--renderer-build-dir", $V8BuildDirFull,
    "--cc", $cl,
    "--cxx", $cl
  )
  if ($NoFetchDawnDeps) {
    $dawnArgs += "--no-fetch-deps"
  }
  Invoke-Step "Build native MSVC Dawn D3D12 static closure" {
    & $python @dawnArgs
  }
}

$DawnBuildDir = Join-Path $DawnWorkDirFull "cmake_d3d12"
$DawnSourceDir = Join-Path $DawnWorkDirFull "dawn"
$DawnGenIncludeDir = Join-Path $DawnBuildDir "gen/include"
$DawnNativeLib = Join-Path $DawnBuildDir "src/dawn/native/dawn_native.lib"
if (-not ((Test-Path (Join-Path $DawnGenIncludeDir "dawn/webgpu.h")) -and
          (Test-Path (Join-Path $DawnSourceDir "include/dawn/native/DawnNative.h")) -and
          (Test-Path $DawnNativeLib))) {
  throw "Missing Dawn D3D12 static closure under '$DawnWorkDirFull'. Re-run without -SkipDawnBuild; first run may need network access for Dawn dependencies."
}

Invoke-Step "Configure native MSVC static C API package build" {
  & $cmake -S $RepoRoot -B $BuildDirFull -G Ninja `
    -DCMAKE_BUILD_TYPE=Release `
    -DCMAKE_C_COMPILER=cl `
    -DCMAKE_CXX_COMPILER=cl `
    -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded `
    -DBLINK_STANDALONE_USE_VCPKG_DEPS=OFF `
    -DBLINK_STANDALONE_BUILD_SDL_VIEWER=OFF `
    -DBLINK_STANDALONE_V8_TOOLCHAIN=msvc `
    -DBLINK_STANDALONE_V8_COMPAT_ACTION=prepare `
    -DBLINK_STANDALONE_V8_SYNC_DEPS=OFF `
    "-DBLINK_STANDALONE_V8_COMPAT_WORK_ROOT=$V8WorkRoot" `
    "-DBLINK_STANDALONE_V8_COMPAT_OUT_DIR=$V8OutDir"
}

Invoke-Step "Build native MSVC static C API package" {
  & $cmake --build $BuildDirFull --target blink_standalone_renderer_c_api_static_package --parallel $Jobs
}

$PackageDir = Join-Path $BuildDirFull "package/c_api_static"
$Manifest = Join-Path $PackageDir "blink_standalone_renderer_c_api_static_link_manifest.json"
if (-not (Test-Path $Manifest)) {
  throw "Static package manifest was not produced: $Manifest"
}

Invoke-Step "Verify no Blink/ANGLE/Dawn/Tint code sidecars" {
  & $cmake "-DPACKAGE_DIR=$PackageDir" -P (Join-Path $RepoRoot "cmake/verify_static_package_no_code_sidecars.cmake")
}

Write-Host "native_msvc_static_package: ok"
Write-Host "package=$PackageDir"
Write-Host "manifest=$Manifest"
