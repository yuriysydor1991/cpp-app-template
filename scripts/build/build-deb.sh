#!/bin/bash -e
#
# Produces the DEB package: a Release configure with the ENABLE_DEB option
# enabled, then the `package` target of that build.
#
# The `package` target runs the preinstall step, which builds the project, so
# no separate build step is performed.
#
# Every extra parameter is forwarded to the CMake configure step, so an own
# -D<variable>=<value> override wins over the ENABLE_DEB one below.
#
# The --install flag installs the produced package with the `sudo apt-get
# install` command.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

cmake -B "${BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_DEB=ON \
  "${BUILD_ARGS[@]}"

cmake --build "${BUILD_DIR}" --target package

echo "#### Look for the DEB package inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.deb" sudo apt-get install -y
fi
