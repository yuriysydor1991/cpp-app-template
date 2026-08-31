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
    glade
    googletest
    libglib2.0-dev-bin
    libgmock-dev
    libgtest-dev
    libgtkmm-4.0-dev
    libssl-dev
    libstdc++6
    libwebkitgtk-6.0-dev
    pkg-config
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
