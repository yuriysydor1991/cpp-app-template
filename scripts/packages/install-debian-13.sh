#!/bin/bash -e
#
# Installs the packages required to build and develop the project on the
# Debian 13. The install-debian.sh script picks it on that release.
#
# Every package of the list exists in the Debian 13 archive. A dependency the
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
    libgl-dev
    libgmock-dev
    libgtest-dev
    libopengl-dev
    libqt6gui6
    libqt6openglwidgets6
    libqt6quick6
    libqt6quickcontrols2-6
    libqt6webenginecore6
    libssl-dev
    libstdc++6
    qml6-module-qtqml-workerscript
    qml6-module-qtquick
    qml6-module-qtquick-controls
    qml6-module-qtquick-dialogs
    qml6-module-qtquick-layouts
    qml6-module-qtquick-localstorage
    qml6-module-qtquick-particles
    qml6-module-qtquick-pdf
    qml6-module-qtquick-scene2d
    qml6-module-qtquick-scene3d
    qml6-module-qtquick-shapes
    qml6-module-qtquick-templates
    qml6-module-qtquick-timeline
    qml6-module-qtquick-tooling
    qml6-module-qtquick-virtualkeyboard
    qml6-module-qtquick-window
    qml6-module-qtwebengine
    qt6-base-dev
    qt6-base-dev-tools
    qt6-declarative-dev
    qt6-tools-dev
    qt6-tools-dev-tools
    qt6-webengine-dev
    qt6-webengine-dev-tools
)

apt_install "${PACKAGES[@]}"

log "The required packages are installed"
