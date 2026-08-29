#!/bin/bash -e
#
# Configures the project in the release build type with the DEB packager
# enabled and produces the package by the `deb` target of that build.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_DEB one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

SETUP_ARGS=(--buildtype=release "-DENABLE_DEB=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "$@"

meson compile -C "${BUILD_DIR}"

meson compile -C "${BUILD_DIR}" deb

echo "#### The DEB package is inside the ${BUILD_DIR} directory"
