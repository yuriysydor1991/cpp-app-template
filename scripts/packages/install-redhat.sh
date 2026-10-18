#!/bin/bash -e
#
# Installs the minimal set of packages required to build and run the project
# locally on the Red Hat family distributions: Fedora and the RHEL with it's
# CentOS Stream, Rocky Linux and AlmaLinux rebuilds.
#
# These distributions package no RHVoice, so the pinned release of it is built
# out of it's sources by the rhvoice_install_from_source function below.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/common.sh"

. /etc/os-release

PACKAGES=(
    cmake
    gcc-c++
    git
    gmock-devel
    gtest-devel
    make
    openssl-devel
    pkgconf-pkg-config
    SDL2-devel
)

RHVOICE_TAG="1.18.4"

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

# Every RHVoice voice and language is a git submodule of it's own, so the
# submodules of the build tools, of the English and the Ukrainian languages
# and of the Alan, Anatol and Natalia voices are taken alone, and the empty
# directories of the rest are dropped. The CMake build of it installs no
# headers, which are copied by hand, and the /usr/local/lib64 directory it
# installs the libraries into is no library path of these distributions.
rhvoice_install_from_source()
(
    BUILD_TMP_DIR=$(mktemp -d)

    trap 'rm -rf "${BUILD_TMP_DIR:?}"' EXIT

    log "Building the RHVoice ${RHVOICE_TAG} release from its sources"

    git -c advice.detachedHead=false clone --depth 1 --branch "${RHVOICE_TAG}" \
        https://github.com/RHVoice/RHVoice.git "${BUILD_TMP_DIR}/src"

    git -C "${BUILD_TMP_DIR}/src" submodule update --init --depth 1 -- \
        cmake/thirdParty/CCache cmake/thirdParty/sanitizers external/libs/sonic \
        data/languages/English data/languages/Ukrainian \
        data/voices/alan data/voices/anatol data/voices/natalia

    rmdir "${BUILD_TMP_DIR}"/src/data/{languages,voices}/* 2> /dev/null || true

    # The CCache module of it asks for a CMake 2.8 compatibility, which the
    # CMake 4 refuses unless the policy minimum is raised.
    cmake -S "${BUILD_TMP_DIR}/src" -B "${BUILD_TMP_DIR}/build" \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5

    cmake --build "${BUILD_TMP_DIR}/build" -j "$(nproc)"

    ${DNF_SUDO} cmake --install "${BUILD_TMP_DIR}/build"

    ${DNF_SUDO} install -m 644 -t /usr/local/include \
        "${BUILD_TMP_DIR}"/src/src/include/RHVoice{,_common}.h

    echo /usr/local/lib64 | ${DNF_SUDO} tee /etc/ld.so.conf.d/local-lib64.conf > /dev/null

    ${DNF_SUDO} ldconfig
)

rhvoice_install_from_source

log "The required packages are installed"
