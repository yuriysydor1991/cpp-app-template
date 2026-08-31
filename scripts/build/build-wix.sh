#!/bin/bash -e
#
# Produces the WIX MSI installer: a release configure with the ENABLE_WIX option
# enabled, then the `wix` target of that build.
#
# The target only runs the WiX toolset over the configured .wxs file, so the
# project itself is built first.
#
# Every extra parameter is forwarded to the meson setup step, so an own
# -D<option>=<value> override wins over the ENABLE_WIX one below.
#
# The --install flag installs the produced package with the `msiexec //i`
# command.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

SETUP_ARGS=(--buildtype=release "-DENABLE_WIX=true")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "${BUILD_ARGS[@]}"

meson compile -C "${BUILD_DIR}"

meson compile -C "${BUILD_DIR}" wix

echo "#### Look for the WIX MSI installer inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.msi" msiexec //i
fi
