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
    libfreetype-dev
    libgl1-mesa-dev
    libgmock-dev
    libgtest-dev
    libsfml-dev
    libssl-dev
    libstdc++6
    libudev-dev
    libx11-dev
    libxcursor-dev
    libxi-dev
    libxrandr-dev
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
