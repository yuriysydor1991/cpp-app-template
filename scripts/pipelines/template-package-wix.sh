#!/bin/bash -e
#
# Builds the WIX MSI package in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-wix"
rm -fr "$BD"
cmake -S . -B "$BD" -DCMAKE_BUILD_TYPE=Release -DENABLE_WIX=ON -DENABLE_MEDIAPIPE_MODEL_DOWNLOAD=OFF
cmake --build "$BD" -j$(nproc)
( cd "$BD" && cpack -G WIX )
if [ -z "$(find "$BD" -maxdepth 2 -name '*.msi' -print -quit)" ]; then
  echo "FAIL: CMake/CPack did not produce a .msi package"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 2 -name '*.msi')"
