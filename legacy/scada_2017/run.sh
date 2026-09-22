#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
TEST_DIR="$ROOT_DIR/ScadaTests"

if [[ ! -d "$TEST_DIR" ]]; then
  echo "ScadaTests directory not found: $TEST_DIR" >&2
  exit 1
fi

cd "$TEST_DIR"

if command -v qmake >/dev/null 2>&1; then
  qmake ScadaTests.pro && make -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)"
else
  echo "qmake not found; please install Qt development tools." >&2
  exit 1
fi

./ScadaTests
