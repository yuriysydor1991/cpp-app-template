#!/bin/bash -e
#
# Runs the WebAssembly build with the Node.js.

. "$(dirname "$0")/common.sh"

node "$BUILDDIR"/src/*.js --version
