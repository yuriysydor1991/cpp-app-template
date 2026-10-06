#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally on the Red Hat family distributions: Fedora and the RHEL with it's
# CentOS Stream, Rocky Linux and AlmaLinux rebuilds.
#
# Neither the PGPLOT library nor it's giza drop-in replacement is a Fedora or an
# EPEL package, so the giza is to be built from it's sources and the
# TEMPLATE_APP_PGPLOT_ROOT CMake variable pointed to it's installation prefix.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

. /etc/os-release

PACKAGES=(
    cairo-devel
    cmake
    gcc-c++
    git
    gmock-devel
    gtest-devel
    make
    openssl-devel
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

log "Build the giza (https://github.com/danieljprice/giza) for the PGPLOT and" \
    "configure with the -DTEMPLATE_APP_PGPLOT_ROOT=<it's installation prefix>"
