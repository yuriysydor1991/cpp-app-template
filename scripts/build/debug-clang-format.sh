#!/bin/bash -e

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

"${BUILD_SCRIPTS_ROOT}/debug-configure.sh" -DENABLE_CLANGFORMAT=ON "$@"

"${BUILD_SCRIPTS_ROOT}/debug-build.sh" --target clang-format "$@"
