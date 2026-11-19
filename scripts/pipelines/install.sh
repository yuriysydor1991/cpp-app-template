#!/bin/bash -e
#
# Installs the build into the install-try directory inside it.

. "$(dirname "$0")/common.sh"

cmake --install "$BUILDDIR" --prefix "$BUILDDIR/install-try"
