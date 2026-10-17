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
    libgtkmm-3.0-dev
    libssl-dev
    libstdc++6
    pkg-config
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

# The Glade UI designer is optional: the build does not need it, and some
# releases (Ubuntu 26.04) ship no glade package at all.
if ! ${APT_SUDO} apt-get install -y glade ; then
    log "The optional glade package is not available, the UI file may be edited by hand"
fi

log "The required packages are installed"
