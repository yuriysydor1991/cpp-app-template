#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally.
#
# No Debian or Ubuntu release packages the Wt any more, so the project
# configure fetches and builds its sources, for which the Boost and the zlib
# development packages are installed below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES=(
    build-essential
    cmake
    g++
    git
    googletest
    libboost-filesystem-dev
    libboost-program-options-dev
    libboost-thread-dev
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
    zlib1g-dev
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
