#!/bin/bash -e
#
# Produces the AppImage bundle: a release configure with the ENABLE_APPIMAGE option
# enabled, then the `AppImage` target of that build.
#
# The target installs the project with `meson install`, which builds what it
# needs, so no separate build step is performed.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_APPIMAGE one below.
#
# The --install flag installs the produced package with the `sudo install -t
# /usr/local/bin` command.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

SETUP_ARGS=(--buildtype=release "-DENABLE_APPIMAGE=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "${BUILD_ARGS[@]}"

meson compile -C "${BUILD_DIR}" AppImage

echo "#### Look for the AppImage bundle inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.AppImage" sudo install -m 0755 -t /usr/local/bin
fi
