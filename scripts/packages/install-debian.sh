#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES=(
    autoconf
    automake
    btop
    build-essential
    cmake
    curl
    fdupes
    ffmpeg
    firebird-dev
    freeglut3-dev
    g++
    git
    gnuplot
    googletest
    htop
    libboost-all-dev
    libcurl4-openssl-dev
    libgl-dev
    libgl1-mesa-dev
    libglew-dev
    libgmock-dev
    libgstreamer1.0-dev
    libgstreamerd-3-dev
    libgstreamermm-1.0-dev
    libgtest-dev
    libgtkmm-3.0-dev
    libgtkmm-4.0-dev
    liblog4cpp5-dev
    libmysqlcppconn-dev
    libnotify-dev
    libopencv-dev
    libopencv-dnn-dev
    libopencv-imgcodecs-dev
    libopencv-imgproc-dev
    libopengl-dev
    libpqxx-dev
    libqt6gui6
    libqt6opengl6-dev
    libqt6openglwidgets6
    libqt6quick6
    libqt6quickcontrols2-6
    libqt6webenginecore6
    libsdl2-dev
    libsdl2-image-dev
    libsdl2-net-dev
    libsdl2-ttf-dev
    libsdl3-dev
    libsdl3-image-dev
    libsdl3-ttf-dev
    libssl-dev
    libstdc++6
    libwebkitgtk-6.0-dev
    mesa-common-dev
    meson
    nano
    nmap
    opencv-data
    pkg-config
    qml-module-qtquick-controls2
    qml-module-qtquick-dialogs
    qml-module-qtquick-layouts
    qml-module-qtquick-shapes
    qml-module-qtquick2
    qml6-module-qtqml-workerscript
    qml6-module-qtquick
    qml6-module-qtquick-controls
    qml6-module-qtquick-templates
    qml6-module-qtquick-window
    qml6-module-qtwebview
    qt6-base-dev
    qt6-base-dev-tools
    qt6-declarative-dev
    qt6-tools-dev
    qt6-tools-dev-tools
    qt6-webengine-dev
    qt6-webengine-dev-tools
    qt6-webview-dev
    qtquickcontrols2-5-dev
    traceroute
    wget
    whois
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
