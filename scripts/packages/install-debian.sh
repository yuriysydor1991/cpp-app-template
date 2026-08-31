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
    libgl1-mesa-dev
    libgmock-dev
    libgtest-dev
    libsdl3-dev
    libsdl3-image-dev
    libsdl3-image0
    libsdl3-ttf-dev
    libsdl3-ttf0
    libssl-dev
    libstdc++6
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
