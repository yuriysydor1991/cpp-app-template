#!/bin/bash -e
#
# Builds the snap package in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-snap"
rm -fr "$BD"
meson setup "$BD" --buildtype=release -DENABLE_SNAP=true
meson compile -C "$BD"
meson compile -C "$BD" snap
if [ -z "$(find "$BD" -name '*.snap' -print -quit)" ]; then
  echo "FAIL: Meson did not produce a .snap package"
  exit 1
fi
echo "OK: produced $(find "$BD" -name '*.snap' | head -n1)"
