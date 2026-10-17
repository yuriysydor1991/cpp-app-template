#!/bin/bash -e
#
# Installs the distribution development packages the template branches build
# with on the Red Hat family distributions: Fedora and the RHEL with it's
# CentOS Stream, Rocky Linux and AlmaLinux rebuilds.
#
# The --local-pipelines flag adds the tools the local CI pipelines of the
# scripts/docker/*-run.sh scripts run with: the Docker - out of the Docker site
# repository at the RHEL and its rebuilds, which carry none - the rsync and
# the gitlab-ci-local and act out of their release archives, since the
# distributions package neither of the two.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/packages/common.sh"

. /etc/os-release

PACKAGES=(
    autoconf
    automake
    boost-devel
    cmake
    curl
    firebird-devel
    freeglut-devel
    gcc-c++
    git
    glew-devel
    gmock-devel
    gnuplot
    gtest-devel
    gtkmm3.0-devel
    gtkmm4.0-devel
    libcurl-devel
    libglvnd-devel
    libpqxx-devel
    log4cpp-devel
    make
    mesa-libGL-devel
    meson
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
    webkitgtk6.0-devel
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

if [[ ! $* =~ --local-pipelines ]] ; then
    exit 0
fi

LOCAL_PIPELINES_PACKAGES=(
    gnupg2
    rsync
    tar
)

# A Docker installed already is left as it is, whatever its origin.
if ! command -v docker > /dev/null ; then
    if [[ ${ID} == fedora ]] ; then
        LOCAL_PIPELINES_PACKAGES+=(docker-buildx docker-cli moby-engine)
    else
        if [[ ${ID} == rhel ]] ; then
            DOCKER_REPO_DISTRO=rhel
        else
            DOCKER_REPO_DISTRO=centos
        fi

        DOCKER_REPO=$(mktemp)

        curl -fsSL -o "${DOCKER_REPO}" \
            "https://download.docker.com/linux/${DOCKER_REPO_DISTRO}/docker-ce.repo"

        ${DNF_SUDO} install -m 644 "${DOCKER_REPO}" /etc/yum.repos.d/docker-ce.repo

        rm -f "${DOCKER_REPO}"

        LOCAL_PIPELINES_PACKAGES+=(containerd.io docker-buildx-plugin docker-ce docker-ce-cli)
    fi

    DOCKER_INSTALLED=yes
fi

log "Installing the local CI pipelines tools"

${DNF_SUDO} dnf install -y "${LOCAL_PIPELINES_PACKAGES[@]}"

# Unlike the Debian ones, the Red Hat family packages leave the services they
# install stopped and disabled.
if [[ -n ${DOCKER_INSTALLED} && -d /run/systemd/system ]] ; then
    ${DNF_SUDO} systemctl enable --now docker
fi

install_act_release
install_gitlab_ci_local_release

log "The local CI pipelines tools are installed"
