#!/bin/bash -e
#
# Builds the FreeBSD pkg package in a Release build directory of its own and
# fails when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-freebsd"
rm -fr "$BD"
cmake -S . -B "$BD" -DCMAKE_BUILD_TYPE=Release -DENABLE_FREEBSD_PKG=ON -DENABLE_PIPER_VOICE_DOWNLOAD=OFF
cmake --build "$BD" -j$(nproc)
( cd "$BD" && cpack -G FREEBSD )
if [ -z "$(find "$BD" -maxdepth 2 -name '*.pkg' -print -quit)" ]; then
  echo "FAIL: CMake/CPack did not produce a FreeBSD .pkg package"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 2 -name '*.pkg')"
