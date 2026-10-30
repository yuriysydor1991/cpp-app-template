#!/bin/bash -e

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

if [[ $* =~ --no-reconfigure ]] ; then
    log "User issued --no-reconfigure"
    exit 0
fi

delete_previous_build "${WEBASSEMBLY_BUILD_DIR}"

log "Trying to WebAssembly-configure project ${PROJECT_ROOT} inside ${WEBASSEMBLY_BUILD_DIR}"

filter_script_args yes "$@"

# The page lands in the web server root itself, next to its loader and module.
emcmake cmake -B "${WEBASSEMBLY_BUILD_DIR}" -S "${PROJECT_ROOT}" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX="${WEBASSEMBLY_INSTALL_PREFIX}" \
  -DPROJECT_BINARY_INSTALLATION_DIR=. \
  "${CMAKE_ARGS[@]}"

log "Configuring done"
