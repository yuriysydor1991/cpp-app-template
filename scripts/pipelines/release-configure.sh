#!/bin/bash -e
#
# Configures the Release build anew, the arguments go to cmake.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

cmake -S . -B "$BUILDDIR" -DCMAKE_BUILD_TYPE=Release -DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF "$@"
