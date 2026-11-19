#!/bin/bash -e
#
# Runs the tests the regular expression matches, the ones of the <name> suite
# by default, with the JUnit report in the <name>.junit.xml file.
#
# Usage: test.sh <name> [<regular expression>]

. "$(dirname "$0")/common.sh"

cd "$BUILDDIR"

ctest -R "${2:-$1\.}" --no-tests=error --output-on-failure \
  --output-junit "$BDJUNITOUT/$1.junit.xml"
