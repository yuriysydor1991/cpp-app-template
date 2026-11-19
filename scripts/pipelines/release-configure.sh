#!/bin/bash -e
#
# Configures the Release build anew, the arguments go to meson setup.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

meson setup "$BUILDDIR" --buildtype=release "$@"
