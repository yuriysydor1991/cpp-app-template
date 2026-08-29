#!/bin/bash -e
#
# Installs the packages required to build and develop the project, the
# development ones included.
#
# The list is collected from the project documentation, the Dockerfiles and the
# flatpak packager configuration of the branch.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES=(
    build-essential
    clang-format
    clang-tidy
    cmake
    cppcheck
    docker-buildx
    docker.io
    doxygen
    flatpak
    flatpak-builder
    g++
    git
    googletest
    graphviz
    libgl1-mesa-dev
    libgmock-dev
    libgtest-dev
    libsdl2-dev
    libsdl2-doc
    libsdl2-image-2.0-0
    libsdl2-image-dev
    libsdl2-mixer-2.0-0
    libsdl2-mixer-dev
    libsdl2-net-2.0-0
    libsdl2-net-dev
    libsdl2-ttf-dev
    libssl-dev
    libstdc++6
    rpm
    snapd
    valgrind
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
