#!/bin/bash -e
#
# Configures the Debug build with the clang-tidy checks anew, the arguments go
# to cmake.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

cmake -S . -B "$BUILDDIR" -DCMAKE_BUILD_TYPE=Debug -DENABLE_CLANG_TIDY=ON \
  -DMAX_LOG_LEVEL=5 -DENABLE_MEDIAPIPE_MODEL_DOWNLOAD=OFF "$@"
