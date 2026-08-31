#!/bin/bash -e
#
# Produces the RPM package: a Release configure with the ENABLE_RPM option
# enabled, then the `package` target of that build.
#
# The `package` target runs the preinstall step, which builds the project, so
# no separate build step is performed.
#
# Every extra parameter is forwarded to the CMake configure step, so an own
# -D<variable>=<value> override wins over the ENABLE_RPM one below.
#
# The --install flag installs the produced package with the `sudo dnf install`
# command.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

cmake -B "${BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_RPM=ON \
  "${BUILD_ARGS[@]}"

cmake --build "${BUILD_DIR}" --target package

echo "#### Look for the RPM package inside the ${BUILD_DIR} directory"

if [[ $* =~ --install ]] ; then
    install_built_package "*.rpm" sudo dnf install -y
fi
