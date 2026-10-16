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
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
    libsystemd-dev
    pkgconf
)

apt_install "${PACKAGES[@]}"

# The release packages the sdbus-c++ 1.4.0 only, the sources use its 2.x API.
cmake_install_from_source https://github.com/Kistler-Group/sdbus-cpp.git v2.1.0 -DBUILD_SHARED_LIBS=ON

log "The required packages are installed"
