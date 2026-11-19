#!/bin/bash -e
#
# Fails when a meson/ submodule is wired via no subdir() call.

. "$(dirname "$0")/common.sh"

wired="$(grep -rh "subdir(" --include=meson.build . | cut -d"'" -f2 | sort -u)"
status=0
for f in $(find meson -mindepth 2 -name meson.build); do
  mod="${f#meson/}"
  mod="${mod%/meson.build}"
  if ! echo "$wired" | grep -qxF "$mod"; then
    echo "FAIL: meson submodule $mod ($f) is not wired via subdir() in the meson build files"
    status=1
  fi
done
[ "$status" -eq 0 ] || exit 1
echo "OK: every meson/ submodule is wired via subdir()"
