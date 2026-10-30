#!/bin/bash -e

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

${BUILD_SCRIPTS_ROOT}/webassembly-configure.sh "$@"

${BUILD_SCRIPTS_ROOT}/webassembly-build.sh "$@"

${BUILD_SCRIPTS_ROOT}/webassembly-install.sh "$@"
