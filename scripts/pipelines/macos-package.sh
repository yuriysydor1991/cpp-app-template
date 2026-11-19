#!/bin/bash -e
#
# Packs the build into the macOS .dmg and .pkg packages.

. "$(dirname "$0")/common.sh"

cd "$BUILDDIR"

cpack
