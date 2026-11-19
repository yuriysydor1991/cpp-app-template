#!/bin/bash -e
#
# Configures the Debug build of the tests anew, the arguments go to cmake.

. "$(dirname "$0")/common.sh"

rm -fr "$BUILDDIR"

cmake -S . -B "$BUILDDIR" -DCMAKE_BUILD_TYPE=Debug -DENABLE_UNIT_TESTS=ON \
  -DENABLE_SANITIZERS=ON -DENABLE_CPPCHECK=ON \
  -DMAX_LOG_LEVEL=5 -DENABLE_COMPONENT_TESTS=ON -DENABLE_LLAMACPP_MODEL_DOWNLOAD=OFF "$@"
