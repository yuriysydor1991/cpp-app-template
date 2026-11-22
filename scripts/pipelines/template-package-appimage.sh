#!/bin/bash -e
#
# Builds the AppImage package in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-appimage"
rm -fr "$BD"
cmake -S . -B "$BD" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DENABLE_APPIMAGE=ON -DENABLE_MEDIAPIPE_MODEL_DOWNLOAD=OFF
cmake --build "$BD" --target appimage
if [ -z "$(find "$BD" -maxdepth 2 -name '*.AppImage' -print -quit)" ]; then
  echo "FAIL: CMake did not produce an .AppImage package"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 2 -name '*.AppImage')"
