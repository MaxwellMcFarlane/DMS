#!/usr/bin/env bash
# Builds (if needed) and launches the SCADA GUI. See README.md.
set -euo pipefail
exec "$(cd "$(dirname "$0")/../.." && pwd)/bin/scada"
