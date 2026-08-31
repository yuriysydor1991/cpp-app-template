#!/bin/bash -e
#
# Produces the snap package: a release configure with the ENABLE_SNAP option
# enabled, then the `snap` target of that build.
#
# snapcraft builds the project from the sources inside its own environment, so
# no build step is performed and the build directory needs no artifacts.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_SNAP one below.
#
# The --install flag installs the produced package with the `sudo snap install
# --dangerous` command.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

SETUP_ARGS=(--buildtype=release "-DENABLE_SNAP=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "${BUILD_ARGS[@]}"

meson compile -C "${BUILD_DIR}" snap

echo "#### Look for the snap package inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.snap" sudo snap install --dangerous
fi
