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
# The bundle gets the standard AppDir/usr/bin layout of the /usr prefix.
#
# The --install flag installs the produced package with the `install` command
# into the ${HOME}/.local/bin directory.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

SETUP_ARGS=(--buildtype=release --prefix=/usr "-DENABLE_APPIMAGE=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "${BUILD_ARGS[@]}"

meson compile -C "${BUILD_DIR}" AppImage

echo "#### Look for the AppImage bundle inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.AppImage" install -D -m 755 -t "${HOME}/.local/bin"
fi
