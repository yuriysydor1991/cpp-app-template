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
    glade
    glib2-devel
    gmock-devel
    gtest-devel
    gtkmm4.0-devel
    make
    openssl-devel
    pkgconf-pkg-config
    webkitgtk6.0-devel
)

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
