#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally.
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

if [[ ! $* =~ --local-pipelines ]] ; then
    exit 0
fi

LOCAL_PIPELINES_PACKAGES=(
    gitlab-ci-local
    rsync
)

# A Docker of another origin - the docker-ce of the Docker site or the snap
# one - is left as it is, since the docker.io package conflicts with it.
if ! command -v docker > /dev/null ||
    dpkg-query -W -f '${Status}' docker.io 2> /dev/null | grep -q ' installed$' ; then
    LOCAL_PIPELINES_PACKAGES+=(docker.io docker-buildx)
fi

log "Installing the local CI pipelines tools"

# A half downloaded repository file would break every later apt-get call, so
# it is downloaded aside first.
GITLAB_CI_LOCAL_SOURCES=$(mktemp)

curl -fsSL -o "${GITLAB_CI_LOCAL_SOURCES}" \
    https://gitlab-ci-local-ppa.firecow.dk/gitlab-ci-local.sources

${APT_SUDO} install -m 644 "${GITLAB_CI_LOCAL_SOURCES}" \
    /etc/apt/sources.list.d/gitlab-ci-local.sources

rm -f "${GITLAB_CI_LOCAL_SOURCES}"

${APT_SUDO} apt-get update

${APT_SUDO} apt-get install -y "${LOCAL_PIPELINES_PACKAGES[@]}"

install_act_release

log "The local CI pipelines tools are installed"
