#!/bin/bash -e
#
# Formats the sources and fails when the formatter has changed a tracked file.

. "$(dirname "$0")/common.sh"

meson compile -C "$BUILDDIR" clang-format

git diff --exit-code
