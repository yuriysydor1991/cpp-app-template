#!/bin/bash -e
#
# Installs the packages required to build and develop the project on the
# Ubuntu 24.04. The install-ubuntu.sh script picks it on that release.
#
# Every package of the list exists in the Ubuntu 24.04 archive. A dependency the
# release packages no usable version of is built out of a pinned release tag
# of its sources with the cmake_install_from_source helper of the common.sh.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/packages/common.sh"

PACKAGES=(
    g++
    git
    libcurl4-openssl-dev
    libgmock-dev
    libgtest-dev
    libopencv-dev
    libxml2-dev
    meson
    ninja-build
    nlohmann-json3-dev
    opencv-data
    pkg-config
)

apt_install "${PACKAGES[@]}"

log "The required packages are installed"
