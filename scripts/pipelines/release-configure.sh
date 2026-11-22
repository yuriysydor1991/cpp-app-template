#!/bin/bash -e
#
# Configures the Release build anew, the arguments go to cmake.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

cmake -S . -B "$BUILDDIR" -DCMAKE_BUILD_TYPE=Release -DENABLE_MEDIAPIPE_MODEL_DOWNLOAD=OFF "$@"
