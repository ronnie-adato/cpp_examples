#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

BAZELISK_VERSION="${BAZELISK_VERSION:-1.20.0}"
MARKDOWNLINT_CLI2_VERSION="${MARKDOWNLINT_CLI2_VERSION:-0.13.0}"

say() {
  printf '\n==> %s\n' "$*"
}

die() {
  echo "error: $*" >&2
  exit 1
}

need_cmd() {
  command -v "$1" >/dev/null 2>&1 || die "missing required command: $1"
}

# Prefer the Ubuntu-latest package name if available (currently clang-format 18 on 24.04)
CLANG_FORMAT_BIN="clang-format"
if command -v clang-format-18 >/dev/null 2>&1; then
  CLANG_FORMAT_BIN="clang-format-18"
elif command -v clang-format >/dev/null 2>&1; then
  CLANG_FORMAT_BIN="clang-format"
else
  die "clang-format not found. Install it (Ubuntu: sudo apt-get install -y clang-format)"
fi

ensure_bazel() {
  if command -v bazel >/dev/null 2>&1; then
    echo "bazel"
    return
  fi

  local tools_dir="$ROOT_DIR/.tools"
  local bazelisk_bin="$tools_dir/bazelisk-$BAZELISK_VERSION"

  mkdir -p "$tools_dir"

  if [[ -x "$bazelisk_bin" ]]; then
    echo "$bazelisk_bin"
    return
  fi

  need_cmd uname
  local os
  os="$(uname -s | tr '[:upper:]' '[:lower:]')"

  local arch
  arch="$(uname -m)"
  case "$arch" in
    x86_64|amd64) arch="amd64" ;;
    aarch64|arm64) arch="arm64" ;;
    *) die "unsupported architecture for bazelisk download: $arch" ;;
  esac

  local url="https://github.com/bazelbuild/bazelisk/releases/download/v${BAZELISK_VERSION}/bazelisk-${os}-${arch}"

  say "Downloading bazelisk v$BAZELISK_VERSION ($os/$arch)"
  if command -v curl >/dev/null 2>&1; then
    curl -fsSL "$url" -o "$bazelisk_bin"
  elif command -v wget >/dev/null 2>&1; then
    wget -qO "$bazelisk_bin" "$url"
  else
    die "need curl or wget to download bazelisk"
  fi
  chmod +x "$bazelisk_bin"

  echo "$bazelisk_bin"
}

say "C++ format check (clang-format)"
# Matches CI: git ls-files '*.cpp' '*.hpp' | xargs -r clang-format -n --Werror
# shellcheck disable=SC2016
git ls-files '*.cpp' '*.hpp' | xargs -r "$CLANG_FORMAT_BIN" -style=file -n --Werror

say "Markdown format check (markdownlint-cli2)"
need_cmd node
need_cmd npx
# Matches CI action globs and config
npx -y "markdownlint-cli2@${MARKDOWNLINT_CLI2_VERSION}" \
  --config ".markdownlint-cli2.yaml" \
  "**/*.md" \
  "**/*.MD"

BAZEL="$(ensure_bazel)"

say "Bazel info"
"$BAZEL" version
"$BAZEL" info

say "Build"
"$BAZEL" build //...

say "Lint (clang-tidy)"
"$BAZEL" build --config=clang-tidy //...

say "Test"
"$BAZEL" test //tests:tests-cpp-examples --test_output=errors

say "Done"
