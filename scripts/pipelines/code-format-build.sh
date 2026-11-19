#!/bin/bash -e
#
# Formats the sources and fails when the formatter has changed a tracked file.

. "$(dirname "$0")/common.sh"

cmake --build "$BUILDDIR" --target clang-format

git diff --exit-code
