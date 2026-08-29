#!/bin/bash -e
#
# Configures the project in the release build type with the AppImage packager
# enabled and produces the package by the `AppImage` target of that build.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_APPIMAGE one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

SETUP_ARGS=(--buildtype=release "-DENABLE_APPIMAGE=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "$@"

meson compile -C "${BUILD_DIR}"

meson compile -C "${BUILD_DIR}" AppImage

echo "#### The AppImage package is inside the ${BUILD_DIR} directory"
