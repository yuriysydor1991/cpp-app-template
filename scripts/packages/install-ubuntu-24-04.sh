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
    pkg-config
    python3
)

apt_install "${PACKAGES[@]}"

# The release packages no MongoDB C++ driver and a MongoDB C driver older than
# the 2.0.0 one the C++ driver r4.1.0 needs, so both are built from sources.
cmake_install_from_source https://github.com/mongodb/mongo-c-driver.git 2.0.0 \
    -DENABLE_TESTS=OFF -DENABLE_EXAMPLES=OFF

cmake_install_from_source https://github.com/mongodb/mongo-cxx-driver.git r4.1.0 \
    -DBUILD_SHARED_LIBS=ON -DENABLE_TESTS=OFF -DENABLE_UNINSTALL=OFF

# The built shared libraries go to the /usr/local/lib directory.
${SUDO} ldconfig

log "The required packages are installed"
