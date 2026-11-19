#!/bin/bash -e
#
# Builds the flatpak bundle in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-flatpak"
rm -fr "$BD"
meson setup "$BD" --buildtype=release -DENABLE_FLATPAK=true
meson compile -C "$BD"
meson compile -C "$BD" flatpak
if [ -z "$(find "$BD" -name '*.flatpak' -print -quit)" ]; then
  echo "FAIL: Meson did not produce a .flatpak bundle"
  exit 1
fi
echo "OK: produced $(find "$BD" -name '*.flatpak' | head -n1)"
