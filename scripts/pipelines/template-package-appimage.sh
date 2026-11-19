#!/bin/bash -e
#
# Builds the AppImage package in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-appimage"
rm -fr "$BD"
meson setup "$BD" --buildtype=release --prefix=/usr -DENABLE_APPIMAGE=true
meson compile -C "$BD" AppImage
if [ -z "$(find "$BD" -maxdepth 1 -name '*.AppImage' -print -quit)" ]; then
  echo "FAIL: Meson did not produce an .AppImage package"
  exit 1
fi
echo "OK: produced $(find "$BD" -maxdepth 1 -name '*.AppImage')"
