#!/bin/bash -e
#
# Builds the deb package in a Release build directory of its own and fails when
# none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-deb"
rm -fr "$BD"
meson setup "$BD" --buildtype=release -DENABLE_DEB=true
meson compile -C "$BD"
meson compile -C "$BD" deb
if [ -z "$(find "$BD" -name '*.deb' -print -quit)" ]; then
  echo "FAIL: Meson did not produce a .deb package"
  exit 1
fi
echo "OK: produced $(find "$BD" -name '*.deb' | head -n1)"
