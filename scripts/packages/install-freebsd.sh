#!/bin/sh -e
#
# Installs the distribution development packages the template branches build
# with on FreeBSD.
#
# A plain sh script, since the bash the project scripts need is not a part of
# the FreeBSD base system and is installed below. The base system ships the
# clang compiler and the OpenSSL library, so neither of them is listed.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

# The local CI pipelines of the scripts/docker/*-run.sh scripts run their jobs
# inside the Linux containers of the Docker, which has no engine for FreeBSD,
# so the --local-pipelines flag of the Linux install scripts is refused here.
case " $* " in
    *" --local-pipelines "*)
        log_fatal "No local CI pipelines tools for FreeBSD: the Docker engine their Linux job containers need runs on Linux alone"
        ;;
esac

PACKAGES="
    autoconf
    automake
    bash
    boost-libs
    cmake
    curl
    firebird40-client
    freeglut
    git
    glew
    gnuplot
    googletest
    gtkmm30
    gtkmm40
    libglvnd
    log4cpp
    meson
    mysql-connector-c++
    opencv
    pkgconf
    postgresql-libpqxx
    qt6-base
    qt6-declarative
    qt6-tools
    qt6-webengine
    qt6-webview
    sdl2
    sdl2_image
    sdl2_net
    sdl2_ttf
    sdl3
    sdl3_image
    sdl3_ttf
    webkit2-gtk_60
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
