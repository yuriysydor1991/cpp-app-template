#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally.
#
# The PGPLOT interface comes from the free giza-dev package, since the non-free
# pgplot5-dev one conflicts with it (and is absent from the Ubuntu 24.04).

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES=(
    build-essential
    cmake
    g++
    git
    giza-dev
    googletest
    libgmock-dev
    libgtest-dev
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
