#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally on the Red Hat family distributions: Fedora and the RHEL with it's
# CentOS Stream, Rocky Linux and AlmaLinux rebuilds.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

. /etc/os-release

PACKAGES=(
    autoconf
    automake
    boost-devel
    btop
    cmake
    curl
    fdupes
    ffmpeg-free
    firebird-devel
    freeglut-devel
    gcc-c++
    git
    glew-devel
    gmock-devel
    gnuplot
    gstreamer1-devel
    gstreamermm-devel
    gtest-devel
    gtkmm3.0-devel
    gtkmm4.0-devel
    htop
    libcurl-devel
    libglvnd-devel
    libnotify-devel
    libpqxx-devel
    log4cpp-devel
    make
    mesa-libGL-devel
    meson
    nano
    nmap
    opencv-data
    opencv-devel
    openssl-devel
    pkgconf-pkg-config
    qt6-qtbase-devel
    qt6-qtdeclarative
    qt6-qtdeclarative-devel
    qt6-qttools-devel
    qt6-qtwebengine-devel
    qt6-qtwebview
    qt6-qtwebview-devel
    SDL2-devel
    SDL2_image-devel
    SDL2_net-devel
    SDL2_ttf-devel
    SDL3-devel
    SDL3_image-devel
    SDL3_ttf-devel
    traceroute
    webkitgtk6.0-devel
    wget
    whois
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
