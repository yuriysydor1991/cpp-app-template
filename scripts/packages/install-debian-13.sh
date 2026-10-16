#!/bin/bash -e
#
# Installs the packages required to build and develop the project on the
# Debian 13. The install-debian.sh script picks it on that release.
#
# Every package of the list exists in the Debian 13 archive. A dependency the
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
    libcurl4-openssl-dev
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
    nlohmann-json3-dev
)

apt_install "${PACKAGES[@]}"

log "The required packages are installed"
