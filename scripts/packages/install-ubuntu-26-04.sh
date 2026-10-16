#!/bin/bash -e
#
# Installs the distribution development packages the template branches build
# with on the Ubuntu 26.04, so the branches build locally. The install-ubuntu.sh
# script picks it on that release. The libraries no release packages usably -
# wxWidgets, Wt, SQLiteCpp, the MongoDB drivers, MatPlot++, sdbus-c++, PLplot,
# whisper.cpp and liboai - come from the download fallbacks of their branches.
#
# Every package of the list exists in the Ubuntu 26.04 archive.
# The release packages no qml6-module-qtquick-nativestyle, which the Qt6
# branches use with the native style only, so the list goes without it.
#
# The --local-pipelines flag adds the tools the local CI pipelines of the
# scripts/docker/*-run.sh scripts run with: the Docker, the rsync, the
# gitlab-ci-local out of the apt repository of its project and the act out of
# its release archive, since the distributions package neither of the two.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/packages/common.sh"

PACKAGES=(
    autoconf
    automake
    build-essential
    clang-format
    clang-tidy
    cmake
    cppcheck
    curl
    doxygen
    firebird-dev
    freeglut3-dev
    g++
    gettext
    git
    giza-dev
    gnuplot
    googletest
    graphviz
    libadwaita-1-dev
    libboost-all-dev
    libcfitsio-dev
    libcurl4-openssl-dev
    libepoxy-dev
    libgl-dev
    libgl1-mesa-dev
    libglew-dev
    libglib2.0-dev-bin
    libglm-dev
    libgmock-dev
    libgtest-dev
    libgtk-3-dev
    libgtkmm-3.0-dev
    libgtkmm-4.0-dev
    liblog4cpp5-dev
    liblzma-dev
    libmysqlcppconn-dev
    libnode-dev
    libopencv-dev
    libopencv-dnn-dev
    libopencv-imgcodecs-dev
    libopencv-imgproc-dev
    libopengl-dev
    libpqxx-dev
    libsdl2-dev
    libsdl2-image-dev
    libsdl2-mixer-dev
    libsdl2-net-dev
    libsdl2-ttf-dev
    libsdl3-dev
    libsdl3-image-dev
    libsdl3-ttf-dev
    libsfml-dev
    libssl-dev
    libstdc++6
    libsystemd-dev
    libvulkan-dev
    libwebkitgtk-6.0-dev
    libxml2-dev
    mesa-common-dev
    meson
    ninja-build
    nlohmann-json3-dev
    opencv-data
    pkg-config
    qml-module-qtquick-controls2
    qml-module-qtquick-dialogs
    qml-module-qtquick-layouts
    qml-module-qtquick-shapes
    qml-module-qtquick2
    qml6-module-qtcharts
    qml6-module-qtlocation
    qml6-module-qtpositioning
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
    qml6-module-qtwebview
    qt6-base-dev
    qt6-base-dev-tools
    qt6-charts-dev
    qt6-declarative-dev
    qt6-declarative-private-dev
    qt6-location-dev
    qt6-positioning-dev
    qt6-tools-dev
    qt6-tools-dev-tools
    qt6-webengine-dev
    qt6-webengine-dev-tools
    qt6-webview-dev
    qtquickcontrols2-5-dev
    valgrind
    wcslib-dev
    zlib1g-dev
)

apt_install "${PACKAGES[@]}"

log "The required packages are installed"

apt_install_local_pipelines_tools "$@"
