#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES=(
    build-essential
    cmake
    g++
    git
    googletest
    libgl-dev
    libgmock-dev
    libgtest-dev
    libopengl-dev
    libqt6gui6
    libqt6opengl6-dev
    libqt6openglwidgets6
    libqt6quick6
    libqt6quickcontrols2-6
    libssl-dev
    libstdc++6
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
    qt6-base-dev
    qt6-base-dev-tools
    qt6-declarative-dev
    qt6-tools-dev
    qt6-tools-dev-tools
    qtquickcontrols2-5-dev
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
