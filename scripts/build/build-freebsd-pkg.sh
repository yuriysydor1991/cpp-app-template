#!/bin/bash -e
#
# Produces the FreeBSD pkg package: a release configure with the ENABLE_FREEBSD_PKG option
# enabled, then the `freebsd-pkg` target of that build.
#
# The target installs the project with `meson install`, which builds what it
# needs, so no separate build step is performed.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_FREEBSD_PKG one below.
#
# The --install flag installs the produced package with the `sudo pkg add`
# command.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

SETUP_ARGS=(--buildtype=release "-DENABLE_FREEBSD_PKG=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "${BUILD_ARGS[@]}"

meson compile -C "${BUILD_DIR}" freebsd-pkg

echo "#### Look for the FreeBSD pkg package inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.pkg" sudo pkg add
fi
