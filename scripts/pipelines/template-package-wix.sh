#!/bin/bash -e
#
# Builds the WIX MSI package in a Release build directory of its own and fails
# when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-wix"
rm -fr "$BD"
meson setup "$BD" --buildtype=release -DENABLE_WIX=true
meson compile -C "$BD"
meson compile -C "$BD" wix
if [ -z "$(find "$BD" -name '*.msi' -print -quit)" ]; then
  echo "FAIL: Meson did not produce a .msi package"
  exit 1
fi
echo "OK: produced $(find "$BD" -name '*.msi' | head -n1)"
