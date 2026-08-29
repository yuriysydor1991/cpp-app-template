#!/bin/bash -e
#
# Produces the flatpak bundle: a release configure with the ENABLE_FLATPAK option
# enabled, then the `flatpak` target of that build.
#
# flatpak-builder builds the project from the sources inside its own sandbox,
# so no build step is performed and the build directory needs no artifacts.
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

meson compile -C "${BUILD_DIR}" flatpak

echo "#### Look for the flatpak bundle inside the ${BUILD_DIR} directory"
