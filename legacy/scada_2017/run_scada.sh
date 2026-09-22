#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
SCADA_DIR="$ROOT_DIR/scada"

if [[ ! -d "$SCADA_DIR" ]]; then
  echo "scada directory not found: $SCADA_DIR" >&2
  exit 1
fi

# The program uses paths relative to scada/ (../scada.db, ../configuration_files, ...)
cd "$SCADA_DIR"

if command -v qmake >/dev/null 2>&1; then
  qmake CONFIG+=sdk_no_version_check scada.pro && make -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)"
else
  echo "qmake not found; please install Qt development tools." >&2
  exit 1
fi

./scada
