# shellcheck shell=bash
#
# The helpers every scripts/packages/install-*.sh script shares. Set the
# PROJECT_ROOT and source it.

if [[ -z ${PROJECT_ROOT} ]] ; then
    echo "#### No PROJECT_ROOT var given (packages common.sh)"
    exit 1
fi

. "${PROJECT_ROOT}/scripts/common.sh"

# The package manager and the install commands run through the sudo unless the
# script runs as the root already.
SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    SUDO="sudo"
fi

# Runs the install-<ID>-<VERSION_ID>.sh script of the running distribution
# release, e.g. the install-ubuntu-26-04.sh one on the Ubuntu 26.04, so every
# supported release keeps a package list of its own. Fails with the list of
# the supported releases when the running one has no script.
#
# Usage: exec_release_script [script arguments...]
exec_release_script()
{
    . /etc/os-release

    RELEASE_SCRIPT="${PROJECT_ROOT}/scripts/packages/install-${ID}-${VERSION_ID//./-}.sh"

    if [[ ! -f ${RELEASE_SCRIPT} ]] ; then
        SUPPORTED=("${PROJECT_ROOT}"/scripts/packages/install-*-[0-9]*.sh)
        SUPPORTED=("${SUPPORTED[@]##*/install-}")

        log_fatal "No packages install script for the ${PRETTY_NAME:-${ID}} release." \
            "The supported releases are: ${SUPPORTED[*]%.sh}"
    fi

    exec "${RELEASE_SCRIPT}" "$@"
}

# Refreshes the apt package index and installs the given packages.
#
# Usage: apt_install <package>...
apt_install()
{
    log "Installing $# packages"

    ${SUDO} apt-get update

    ${SUDO} env DEBIAN_FRONTEND=noninteractive apt-get install -y "$@"
}

# Builds and installs a CMake project out of a pinned release tag of its git
# repository, for a dependency the running release packages no usable version
# of. The build runs in a temporary directory, which is removed whatever the
# outcome is. The shared library cache is refreshed afterwards, so the
# installed libraries are found at run time.
#
# Usage: cmake_install_from_source <git URL> <release tag> [CMake options...]
cmake_install_from_source()
(
    SOURCE_URL=$1
    SOURCE_TAG=$2
    shift 2

    BUILD_TMP_DIR=$(mktemp -d)

    trap 'rm -rf "${BUILD_TMP_DIR:?}"' EXIT

    log "Building the ${SOURCE_URL} ${SOURCE_TAG} release from its sources"

    git -c advice.detachedHead=false clone --depth 1 --branch "${SOURCE_TAG}" \
        "${SOURCE_URL}" "${BUILD_TMP_DIR}/src"

    cmake -S "${BUILD_TMP_DIR}/src" -B "${BUILD_TMP_DIR}/build" \
        -DCMAKE_BUILD_TYPE=Release "$@"

    cmake --build "${BUILD_TMP_DIR}/build" -j "$(nproc)"

    ${SUDO} cmake --install "${BUILD_TMP_DIR}/build"

    ${SUDO} ldconfig
)
