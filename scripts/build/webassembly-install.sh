#!/bin/bash -e

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "$(dirname "$0")")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

if ! [[ $* =~ '--install' ]] ; then
    log "No install flag given, omiting"
    exit 0
fi

check_build_dir "${WEBASSEMBLY_BUILD_DIR}"

log "Trying to install ${WEBASSEMBLY_BUILD_DIR}"

filter_script_args no "$@"

sudo cmake --install "${WEBASSEMBLY_BUILD_DIR}" "${CMAKE_ARGS[@]}"
