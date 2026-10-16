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
    curl
    g++
    git
    googletest
    libgmock-dev
    libgtest-dev
    libsdl2-dev
    libssl-dev
    libstdc++6
)

apt_install "${PACKAGES[@]}"

# The release packages no whisper.cpp library, so the v1.9.4 one the project
# configure probes for is built out of its sources.
cmake_install_from_source https://github.com/ggml-org/whisper.cpp.git v1.9.4 \
    -DWHISPER_BUILD_TESTS=OFF -DWHISPER_BUILD_EXAMPLES=OFF -DWHISPER_BUILD_SERVER=OFF

log "The required packages are installed"
