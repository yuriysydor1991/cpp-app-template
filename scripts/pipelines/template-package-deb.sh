#!/bin/bash -e
#
# Builds the deb package in a Release build directory of its own and fails when
# none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-deb"
rm -fr "$BD"
cmake -S . -B "$BD" -DCMAKE_BUILD_TYPE=Release -DENABLE_DEB=ON -DENABLE_SHERPA_ONNX_MODEL_DOWNLOAD=OFF
cmake --build "$BD" -j$(nproc)
( cd "$BD" && cpack -G DEB )
if [ -z "$(find "$BD" -maxdepth 2 -name '*.deb' -print -quit)" ]; then
  echo "FAIL: CMake/CPack did not produce a .deb package"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 2 -name '*.deb')"
