#!/bin/bash -e
#
# Builds the project in the Release configuration with the RPM packager
# enabled and produces the package by the `package` target of that build.
#
# Every parameter of the release-configure.sh and the release-build.sh scripts
# is accepted and forwarded, so an own -D<variable>=<value> override wins over
# the ENABLE_RPM one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

${BUILD_SCRIPTS_ROOT}/release-configure.sh -DENABLE_RPM=ON "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target package "$@"

log "The RPM package is inside the ${RELEASE_BUILD_DIR} directory"
