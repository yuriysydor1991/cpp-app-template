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
    libfreetype-dev
    libgl-dev
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
    libudev-dev
    libx11-dev
    libxcursor-dev
    libxrandr-dev
)

apt_install "${PACKAGES[@]}"

# the release packages SFML 3 only, while PlotGenCpp uses the SFML 2 API: the
# pinned SFML 2.6 release is built with the development files installed above
cmake_install_from_source https://github.com/SFML/SFML.git 2.6.2 \
    -DBUILD_SHARED_LIBS=ON -DSFML_BUILD_AUDIO=OFF -DSFML_BUILD_NETWORK=OFF \
    -DSFML_BUILD_EXAMPLES=OFF -DSFML_BUILD_DOC=OFF

log "The required packages are installed"
