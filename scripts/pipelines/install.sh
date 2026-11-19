#!/bin/bash -e
#
# Installs the build into the install-try directory inside it.

. "$(dirname "$0")/common.sh"

meson install -C "$BUILDDIR" --destdir "$(pwd)/$BUILDDIR/install-try"
