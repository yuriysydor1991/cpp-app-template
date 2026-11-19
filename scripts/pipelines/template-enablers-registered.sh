#!/bin/bash -e
#
# Fails when an enabler of the cmake/enablers directory is included nowhere.

. "$(dirname "$0")/common.sh"

included="$( { cat cmake/template-project-feature-enabler.cmake cmake/template-project-feature-enabler-post.cmake; find cmake/enablers -name "*.cmake" -exec cat {} +; } | grep "include(" | sed "s/.*include(//; s/).*//" | tr -d " " | sort -u )"
status=0
for f in $(find cmake/enablers -name "*.cmake" | sort); do
  mod="$(basename "$f" .cmake)"
  if ! echo "$included" | grep -qx "$mod"; then
    echo "FAIL: enabler $mod ($f) is not registered in the template-project-feature-enabler files"
    status=1
  fi
done
[ "$status" -eq 0 ] || exit 1
echo "OK: every enabler under cmake/enablers is registered"
