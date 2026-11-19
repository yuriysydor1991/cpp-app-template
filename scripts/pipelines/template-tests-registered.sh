#!/bin/bash -e
#
# Fails when a test the build files declare has no misc/Jenkinsfile stage.

. "$(dirname "$0")/common.sh"

declared="$( {
  grep -rA3 "gtest_add_tests" --include=CMakeLists.txt src | grep -oE "TARGET[[:space:]]+[A-Za-z0-9_]+" | awk '{print $2}'
  grep -rA1 "add_test(" --include=CMakeLists.txt src | grep -oE "NAME[[:space:]]+[A-Za-z0-9_]+" | awk '{print $2}'
} | sort -u)"
status=0
for t in $declared; do
  if ! grep -qF "$t" misc/Jenkinsfile; then
    echo "FAIL: test $t is declared in the CMake files but not registered in this Jenkinsfile"
    status=1
  fi
done
[ "$status" -eq 0 ] || exit 1
echo "OK: every CMake-declared test is registered in the pipeline"
