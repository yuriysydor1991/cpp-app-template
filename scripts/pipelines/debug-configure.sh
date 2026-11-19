#!/bin/bash -e
#
# Configures the Debug build of the tests anew, the arguments go to meson
# setup.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

meson setup "$BUILDDIR" --buildtype=debug -DENABLE_UNIT_TESTS=true \
  -DENABLE_SANITIZERS=true -DENABLE_CPPCHECK=true \
  -DMAX_LOG_LEVEL=5 -DENABLE_COMPONENT_TESTS=true "$@"
