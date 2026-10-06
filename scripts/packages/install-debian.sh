#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES=(
    build-essential
    cmake
    g++
    git
    googletest
    libgmock-dev
    libgtest-dev
    libsdl2-dev
    libssl-dev
    libstdc++6
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

${APT_SUDO} apt-get update

# The whisper.cpp development package arrived with the Ubuntu 26.04 and the
# Debian forky releases, while the older ones get it's sources fetched and
# built by the project configure instead.
if apt-cache show libwhisper-dev > /dev/null 2>&1 ; then
    PACKAGES+=(libwhisper-dev)
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
