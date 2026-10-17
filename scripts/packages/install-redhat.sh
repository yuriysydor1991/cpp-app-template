#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally on the Red Hat family distributions: Fedora and the RHEL with it's
# CentOS Stream, Rocky Linux and AlmaLinux rebuilds.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

. /etc/os-release

PACKAGES=(
    cmake
    gcc-c++
    git
    gmock-devel
    gtest-devel
    make
    openssl-devel
    pkgconf-pkg-config
    systemd-devel
)

# The sdbus-cpp-devel package of the EPEL 9 and the Fedora up to 42 is the 1.x
# one the code isn't written for, so the configure fetches the sdbus-c++ 2
# sources while the system carries no newer one.
if dnf -q list --available sdbus-cpp-devel 2>/dev/null | grep -q -E '\s2\.' ; then
    PACKAGES+=(sdbus-cpp-devel)
fi

DNF_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    DNF_SUDO="sudo"
fi

# The RHEL and it's rebuilds carry a part of the packages in the EPEL and the
# CRB repositories alone, which the epel-release package and it's crb tool
# enable.
if [[ ${ID} != fedora ]] ; then
    ${DNF_SUDO} dnf install -y \
        "https://dl.fedoraproject.org/pub/epel/epel-release-latest-${VERSION_ID%%.*}.noarch.rpm"

    ${DNF_SUDO} crb enable
fi

log "Installing ${#PACKAGES[@]} packages"

${DNF_SUDO} dnf install -y "${PACKAGES[@]}"

log "The required packages are installed"
