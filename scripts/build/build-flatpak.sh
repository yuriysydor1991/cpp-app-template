#!/bin/bash -e
#
# Configures the project in the release build type with the flatpak packager
# enabled and produces the package by the `flatpak` target of that build.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_FLATPAK one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

SETUP_ARGS=(--buildtype=release "-DENABLE_FLATPAK=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "$@"

meson compile -C "${BUILD_DIR}"

meson compile -C "${BUILD_DIR}" flatpak

echo "#### The flatpak package is inside the ${BUILD_DIR} directory"
