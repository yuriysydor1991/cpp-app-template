#!/bin/bash -e
#
# Configures the Debug build with the clang-tidy checks anew, the arguments go
# to meson setup.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

meson setup "$BUILDDIR" --buildtype=debug -DENABLE_CLANG_TIDY=true \
  -DENABLE_UNIT_TESTS=true -DENABLE_COMPONENT_TESTS=true \
  -DMAX_LOG_LEVEL=5 "$@"
