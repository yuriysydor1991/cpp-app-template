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
    gnuplot
    googletest
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
)

apt_install "${PACKAGES[@]}"

# the release packages no Matplot++: its pinned release is built from its sources
cmake_install_from_source https://github.com/alandefreitas/matplotplusplus.git v1.2.2 \
    -DMATPLOTPP_BUILD_EXAMPLES=OFF -DMATPLOTPP_BUILD_TESTS=OFF \
    -DMATPLOTPP_BUILD_SHARED_LIBS=ON

log "The required packages are installed"
