#!/bin/bash -e
#
# Builds the RPM package in a Release build directory of its own and fails when
# none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-rpm"
rm -fr "$BD"
cmake -S . -B "$BD" -DCMAKE_BUILD_TYPE=Release -DENABLE_RPM=ON -DENABLE_LLAMACPP_MODEL_DOWNLOAD=OFF
cmake --build "$BD" -j$(nproc)
( cd "$BD" && cpack -G RPM )
if [ -z "$(find "$BD" -maxdepth 2 -name '*.rpm' -print -quit)" ]; then
  echo "FAIL: CMake/CPack did not produce a .rpm package"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 2 -name '*.rpm')"
