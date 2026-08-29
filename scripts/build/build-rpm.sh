#!/bin/bash -e
#
# Produces the RPM package: a release configure with the ENABLE_RPM option
# enabled, then the `rpm` target of that build.
#
# The target installs the project with `meson install`, which builds what it
# needs, so no separate build step is performed.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_RPM one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

SETUP_ARGS=(--buildtype=release "-DENABLE_RPM=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "$@"

meson compile -C "${BUILD_DIR}" rpm

echo "#### Look for the RPM package inside the ${BUILD_DIR} directory"
