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
    build-essential
    cmake
    g++
    git
    googletest
    libdecor-0-dev
    libegl-dev
    libgl1-mesa-dev
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
    libwayland-dev
    libx11-dev
    libxcursor-dev
    libxext-dev
    libxfixes-dev
    libxi-dev
    libxkbcommon-dev
    libxrandr-dev
    libxss-dev
)

apt_install "${PACKAGES[@]}"

# the release packages no SDL3: the pinned SDL3 release is built with the video
# backends of the windowing system files installed above
cmake_install_from_source https://github.com/libsdl-org/SDL.git release-3.2.10 \
    -DSDL_SHARED=ON -DSDL_STATIC=OFF -DSDL_TEST_LIBRARY=OFF
${SUDO} ldconfig

log "The required packages are installed"
