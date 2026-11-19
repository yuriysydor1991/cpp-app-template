#!/bin/bash -e
#
# Configures the build of the clang-format target, the arguments go to cmake.

. "$(dirname "$0")/common.sh"

cmake -S . -B "$BUILDDIR" -DCMAKE_BUILD_TYPE=Debug -DENABLE_CLANGFORMAT=ON \
  -DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF "$@"
