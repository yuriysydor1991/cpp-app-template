#!/bin/bash -e
#
# Runs the test suite given, all of them by default.
#
# Usage: test.sh [<suite>]

. "$(dirname "$0")/common.sh"

if [ -n "$1" ]; then
  # fails when the suite has no tests
  meson test -C "$BUILDDIR" --list --suite "$1" > /dev/null
  set -- --logbase "$1" --suite "$1"
fi

meson test -C "$BUILDDIR" --no-rebuild --print-errorlogs "$@"
