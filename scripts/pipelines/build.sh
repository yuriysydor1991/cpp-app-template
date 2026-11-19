#!/bin/bash -e
#
# Builds the target given, all of them by default.
#
# Usage: build.sh [<target>]

. "$(dirname "$0")/common.sh"

meson compile -C "$BUILDDIR" "$@"
