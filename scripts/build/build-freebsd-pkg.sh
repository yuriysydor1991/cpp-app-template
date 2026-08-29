#!/bin/bash -e
#
# Builds the project in the Release configuration with the FreeBSD pkg packager
# enabled and produces the package by the `package` target of that build.
#
# Every parameter of the release-configure.sh and the release-build.sh scripts
# is accepted and forwarded, so an own -D<variable>=<value> override wins over
# the ENABLE_FREEBSD_PKG one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

${BUILD_SCRIPTS_ROOT}/release-configure.sh -DENABLE_FREEBSD_PKG=ON "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target package "$@"

log "The FreeBSD pkg package is inside the ${RELEASE_BUILD_DIR} directory"
