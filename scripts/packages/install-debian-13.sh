#!/bin/bash -e
#
# Installs the packages required to build and develop the project on the
# Debian 13. The install-debian.sh script picks it on that release.
#
# Every package of the list exists in the Debian 13 archive. A dependency the
# release packages no usable version of is built out of a pinned release tag
# of its sources with the cmake_install_from_source helper of the common.sh.
#
# The RHVoice packages (librhvoice-dev and the rhvoice-* voices) live in the
# non-free component of the Debian archive alone, since a part of the voices
# forbids the commercial use or the modifications. Enable it ahead of the run
# by appending the non-free to the "Components: main" line of the
# /etc/apt/sources.list.d/debian.sources file (or to the "deb" lines of the
# /etc/apt/sources.list one on the older installations).

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
    librhvoice-dev
    libsdl2-dev
    libssl-dev
    libstdc++6
    rhvoice-english
    rhvoice-ukrainian
)

apt_install "${PACKAGES[@]}"

log "The required packages are installed"
