#!/bin/bash -e
#
# Produces the FreeBSD pkg package: a Release configure with the ENABLE_FREEBSD_PKG option
# enabled, then the `package` target of that build.
#
# The `package` target runs the preinstall step, which builds the project, so
# no separate build step is performed.
#
# Every extra parameter is forwarded to the CMake configure step, so an own
# -D<variable>=<value> override wins over the ENABLE_FREEBSD_PKG one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

cmake -B "${BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_FREEBSD_PKG=ON \
  "$@"

cmake --build "${BUILD_DIR}" --target package

echo "#### Look for the FreeBSD pkg package inside the ${BUILD_DIR} directory"
