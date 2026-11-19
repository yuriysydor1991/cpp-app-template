#!/bin/bash -e
#
# Builds the RPM package in a Release build directory of its own and fails when
# none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-rpm"
rm -fr "$BD"
meson setup "$BD" --buildtype=release -DENABLE_RPM=true
meson compile -C "$BD"
meson compile -C "$BD" rpm
if [ -z "$(find "$BD" -name '*.rpm' -print -quit)" ]; then
  echo "FAIL: Meson did not produce a .rpm package"
  exit 1
fi
echo "OK: produced $(find "$BD" -name '*.rpm' | head -n1)"
