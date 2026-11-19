#!/bin/bash -e
#
# Fails when a test the build files declare has no misc/Jenkinsfile stage.

. "$(dirname "$0")/common.sh"

declared="$(grep -rh "suite:" --include=meson.build src | cut -d"'" -f2 | sort -u)"
status=0
for t in $declared; do
  if ! grep -qF "$t" misc/Jenkinsfile; then
    echo "FAIL: test suite $t is declared in the meson.build files but not registered in this Jenkinsfile"
    status=1
  fi
done
[ "$status" -eq 0 ] || exit 1
echo "OK: every meson-declared test suite is registered in the pipeline"
