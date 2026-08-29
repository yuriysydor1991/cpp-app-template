#!/bin/bash -e
#
# Builds the project in the Release configuration with the flatpak packager
# enabled and produces the package by the `flatpak` target of that build.
#
# Every parameter of the release-configure.sh and the release-build.sh scripts
# is accepted and forwarded, so an own -D<variable>=<value> override wins over
# the ENABLE_FLATPAK one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

${BUILD_SCRIPTS_ROOT}/release-configure.sh -DENABLE_FLATPAK=ON "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target flatpak "$@"

log "The flatpak package is inside the ${RELEASE_BUILD_DIR} directory"
