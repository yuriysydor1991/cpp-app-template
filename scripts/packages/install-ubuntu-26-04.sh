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
    libboost-filesystem-dev
    libboost-program-options-dev
    libboost-thread-dev
    libgmock-dev
    libgtest-dev
    libssl-dev
    libstdc++6
    zlib1g-dev
)

apt_install "${PACKAGES[@]}"

# No Debian or Ubuntu release packages the Wt, so its release the project is
# tested with is built from the sources without the unused Wt features.
cmake_install_from_source https://github.com/emweb/wt.git 4.11.4 \
    -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF -DINSTALL_DOCUMENTATION=OFF \
    -DENABLE_LIBWTDBO=OFF -DENABLE_LIBWTTEST=OFF -DENABLE_OPENGL=OFF \
    -DENABLE_PANGO=OFF -DENABLE_HARU=OFF -DENABLE_SQLITE=OFF \
    -DENABLE_POSTGRES=OFF -DENABLE_FIREBIRD=OFF -DENABLE_MYSQL=OFF \
    -DENABLE_MSSQLSERVER=OFF -DENABLE_QT4=OFF -DENABLE_QT5=OFF -DENABLE_QT6=OFF \
    -DCONNECTOR_FCGI=OFF -DCONNECTOR_ISAPI=OFF

# The built shared libraries go to the /usr/local/lib directory.
${SUDO} ldconfig

log "The required packages are installed"
