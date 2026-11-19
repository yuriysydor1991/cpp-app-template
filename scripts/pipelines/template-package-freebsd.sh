#!/bin/bash -e
#
# Builds the FreeBSD pkg package in a Release build directory of its own and
# fails when none appears.

. "$(dirname "$0")/common.sh"

BD="$BUILDDIR-pkg-freebsd"
rm -fr "$BD"
meson setup "$BD" --buildtype=release -DENABLE_FREEBSD_PKG=true
meson compile -C "$BD"
meson compile -C "$BD" freebsd-pkg
if [ -z "$(find "$BD" -name '*.pkg' -print -quit)" ]; then
  echo "FAIL: Meson did not produce a FreeBSD .pkg package"
  exit 1
fi
echo "OK: produced $(find "$BD" -name '*.pkg' | head -n1)"
