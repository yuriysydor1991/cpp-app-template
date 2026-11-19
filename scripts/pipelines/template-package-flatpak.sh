#!/bin/bash -e
#
# Builds the flatpak bundle in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-flatpak"
rm -fr "$BD"
cmake -S . -B "$BD" -DCMAKE_BUILD_TYPE=Release -DENABLE_FLATPAK=ON -DENABLE_LLAMACPP_MODEL_DOWNLOAD=OFF
cmake --build "$BD" -j$(nproc)
cmake --build "$BD" --target flatpak
if [ -z "$(find "$BD" -maxdepth 2 -name '*.flatpak' -print -quit)" ]; then
  echo "FAIL: CMake did not produce a .flatpak bundle"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 2 -name '*.flatpak')"
