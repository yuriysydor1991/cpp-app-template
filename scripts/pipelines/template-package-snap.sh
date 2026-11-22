#!/bin/bash -e
#
# Builds the snap package in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-snap"
rm -fr "$BD"
cmake -S . -B "$BD" -DCMAKE_BUILD_TYPE=Release -DENABLE_SNAP=ON -DENABLE_MOVENET_MODEL_DOWNLOAD=OFF
cmake --build "$BD" -j$(nproc)
cmake --build "$BD" --target snap
if [ -z "$(find "$BD" -maxdepth 3 -name '*.snap' -print -quit)" ]; then
  echo "FAIL: CMake did not produce a .snap package"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 3 -name '*.snap')"
