#!/bin/sh -e
#
# Installs the minimal set of packages required to build and run the project
# locally on FreeBSD.
#
# A plain sh script, since the bash the project scripts need is not a part of
# the FreeBSD base system and is installed below. The base system ships the
# clang compiler and the OpenSSL library, so neither of them is listed.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES="
    bash
    cmake
    git
    glade
    googletest
    gtkmm30
    pkgconf
"

PKG_SUDO=""

if [ "$(id -u)" -ne 0 ] ; then
    PKG_SUDO="sudo"
fi

set -- ${PACKAGES}

log "Installing $# packages"

# The ASSUME_ALWAYS_YES bootstraps the pkg tool itself on a fresh system too.
${PKG_SUDO} env ASSUME_ALWAYS_YES=yes pkg update

${PKG_SUDO} pkg install -y "$@"

log "The required packages are installed"
