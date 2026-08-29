#!/bin/bash -e
#
# Produces the flatpak bundle: a Release configure with the ENABLE_FLATPAK option
# enabled, then the `flatpak` target of that build.
#
# flatpak-builder builds the project from the sources inside its own sandbox,
# so no build step is performed and the build directory needs no artifacts.
# The application dependencies are the sandbox ones too, hence the host configure
# runs with the toolkit enablers off and requires the flatpak tools alone.
#
# Every parameter of the release-configure.sh and the release-build.sh scripts
# is accepted and forwarded, so an own -D<variable>=<value> override wins over
# the ENABLE_FLATPAK one below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

${BUILD_SCRIPTS_ROOT}/release-configure.sh -DENABLE_FLATPAK=ON \
  -DENABLE_GTKMM4=OFF -DENABLE_LIBADWAITA=OFF "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target flatpak "$@"

log "Look for the flatpak bundle inside the ${RELEASE_BUILD_DIR} directory"
