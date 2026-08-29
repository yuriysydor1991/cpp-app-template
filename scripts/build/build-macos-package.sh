#!/bin/bash -e
#
# Builds the project in the Release configuration with the macOS packager
# enabled and produces the disk image and the installer by the `package`
# target of that build.
#
# Every extra parameter is forwarded to the CMake configure step, so an own
# -D<variable>=<value> override wins over the ENABLE_MACOS_PACKAGE one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

cmake -B "${BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_MACOS_PACKAGE=ON \
  "$@"

cmake --build "${BUILD_DIR}" -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)"

cmake --build "${BUILD_DIR}" --target package

echo "#### The macOS disk image and installer are inside the ${BUILD_DIR} directory"
