#!/bin/bash -e
#
# Installs the packages required to build and develop the project, the
# development ones included.
#
# The list is collected from the project documentation, the Dockerfiles and the
# flatpak packager configuration of the branch.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

PACKAGES=(
    build-essential
    clang-format
    clang-tidy
    cmake
    cppcheck
    docker-buildx
    docker.io
    doxygen
    flatpak
    flatpak-builder
    g++
    git
    googletest
    graphviz
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
    libvulkan-dev
    mesa-vulkan-drivers
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
    rpm
    snapd
    valgrind
)

APT_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    APT_SUDO="sudo"
fi

log "Installing ${#PACKAGES[@]} packages"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${PACKAGES[@]}"

log "The required packages are installed"
