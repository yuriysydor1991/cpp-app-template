#!/bin/bash -e
#
# Produces the macOS disk image and installer: a Release configure with the ENABLE_MACOS_PACKAGE option
# enabled, then the `package` target of that build.
#
# The `package` target runs the preinstall step, which builds the project, so
# no separate build step is performed.
#
# Every extra parameter is forwarded to the CMake configure step, so an own
# -D<variable>=<value> override wins over the ENABLE_MACOS_PACKAGE one below.
#
# The --install flag installs the produced package with the `sudo installer
# -pkg` command.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

cmake -B "${BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_MACOS_PACKAGE=ON \
  "${BUILD_ARGS[@]}"

cmake --build "${BUILD_DIR}" --target package

echo "#### Look for the macOS disk image and installer inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.pkg" sudo installer -target / -pkg
fi
