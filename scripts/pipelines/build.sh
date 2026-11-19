#!/bin/bash -e
#
# Builds the target given, all of them by default, with a job per core of the
# macOS or the GNU/Linux host.
#
# Usage: build.sh [<target>]

. "$(dirname "$0")/common.sh"

cmake --build "$BUILDDIR" -j$(sysctl -n hw.ncpu 2>/dev/null || nproc) ${1:+--target "$1"}
