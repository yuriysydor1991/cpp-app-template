#!/bin/bash -e
#
# Configures the build of the clang-format target anew, the arguments go to
# meson setup.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

meson setup "$BUILDDIR" -DENABLE_CLANGFORMAT=true "$@"
