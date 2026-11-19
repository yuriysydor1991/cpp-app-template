#!/bin/bash -e
#
# Configures the Release build with the Emscripten tool chain anew, the
# arguments go to cmake.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

emcmake cmake -S . -B "$BUILDDIR" -DCMAKE_BUILD_TYPE=Release "$@"
