#!/bin/bash -e
#
# Builds the project in the Release configuration with the FreeBSD pkg packager
# enabled and produces the package by the `package` target of that build.
#
# Every extra parameter is forwarded to the CMake configure step, so an own
# -D<variable>=<value> override wins over the ENABLE_FREEBSD_PKG one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

cmake -B "${BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_FREEBSD_PKG=ON \
  "$@"

cmake --build "${BUILD_DIR}" -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)"

cmake --build "${BUILD_DIR}" --target package

echo "#### The FreeBSD pkg package is inside the ${BUILD_DIR} directory"
