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

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_DIR="${PROJECT_ROOT}/build/release"

cmake -B "${BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DENABLE_MACOS_PACKAGE=ON \
  "$@"

cmake --build "${BUILD_DIR}" --target package

echo "#### Look for the macOS disk image and installer inside the ${BUILD_DIR} directory"
