#!/bin/bash -e
#
# Installs the packages required to build and develop the project on the
# Ubuntu 26.04. The install-ubuntu.sh script picks it on that release.
#
# Every package of the list exists in the Ubuntu 26.04 archive. A dependency the
# release packages no usable version of is built out of a pinned release tag
# of its sources with the cmake_install_from_source helper of the common.sh.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/packages/common.sh"

PACKAGES=(
    build-essential
    cmake
    g++
    git
    googletest
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
    qt6-base-dev
    qt6-base-dev-tools
)

apt_install "${PACKAGES[@]}"

log "The required packages are installed"
