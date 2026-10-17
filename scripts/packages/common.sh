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

# The local CI pipelines tools no distribution packages are installed out of
# the release archives of their projects into this directory, each one checked
# against what its release publishes first. A later run updates them to the
# latest release.
RELEASE_TOOLS_BIN_DIR=/usr/local/bin

RELEASE_TOOLS_SUDO="${SUDO}"

# Installs the latest act release - the GitHub Actions pipeline runner of the
# scripts/docker/github-actions-run.sh - checked against the checksums file of
# the release.
install_act_release()
{
    case "$(uname -m)" in
        x86_64)
            ACT_ARCH=x86_64
            ;;
        aarch64|arm64)
            ACT_ARCH=arm64
            ;;
        *)
            log_fatal "No act release archive for the $(uname -m) architecture"
            ;;
    esac

    ACT_ARCHIVE="act_Linux_${ACT_ARCH}.tar.gz"
    ACT_RELEASE_URL=https://github.com/nektos/act/releases/latest/download

    log "Installing the latest act release into ${RELEASE_TOOLS_BIN_DIR}"

    RELEASE_TMP_DIR=$(mktemp -d)

    curl -fsSL -o "${RELEASE_TMP_DIR}/checksums.txt" "${ACT_RELEASE_URL}/checksums.txt"
    curl -fsSL -o "${RELEASE_TMP_DIR}/${ACT_ARCHIVE}" "${ACT_RELEASE_URL}/${ACT_ARCHIVE}"

    (
        cd "${RELEASE_TMP_DIR}" || exit 1
        grep " ${ACT_ARCHIVE}\$" checksums.txt | sha256sum -c -
    )

    tar -xzf "${RELEASE_TMP_DIR}/${ACT_ARCHIVE}" -C "${RELEASE_TMP_DIR}" act

    ${RELEASE_TOOLS_SUDO} install -m 755 "${RELEASE_TMP_DIR}/act" "${RELEASE_TOOLS_BIN_DIR}/act"

    rm -fr "${RELEASE_TMP_DIR}"

    "${RELEASE_TOOLS_BIN_DIR}/act" --version
}

# Installs the latest gitlab-ci-local release - the GitLab CI/CD pipeline
# runner of the scripts/docker/gitlab-ci-run.sh - for the distributions with
# no apt to take it from the apt repository of the project. The release
# archive is checked against its signature with the very key that repository
# is signed with.
install_gitlab_ci_local_release()
{
    case "$(uname -m)" in
        x86_64)
            GITLAB_CI_LOCAL_ARCH=amd64
            ;;
        aarch64|arm64)
            GITLAB_CI_LOCAL_ARCH=arm64
            ;;
        *)
            log_fatal "No gitlab-ci-local release archive for the $(uname -m) architecture"
            ;;
    esac

    GITLAB_CI_LOCAL_ARCHIVE="gitlab-ci-local-linux-${GITLAB_CI_LOCAL_ARCH}.tar.gz"
    GITLAB_CI_LOCAL_RELEASE_URL=https://github.com/firecow/gitlab-ci-local/releases/latest/download

    log "Installing the latest gitlab-ci-local release into ${RELEASE_TOOLS_BIN_DIR}"

    RELEASE_TMP_DIR=$(mktemp -d)

    curl -fsSL -o "${RELEASE_TMP_DIR}/pubkey.asc" https://gitlab-ci-local-ppa.firecow.dk/pubkey.gpg
    curl -fsSL -o "${RELEASE_TMP_DIR}/${GITLAB_CI_LOCAL_ARCHIVE}.asc" \
        "${GITLAB_CI_LOCAL_RELEASE_URL}/${GITLAB_CI_LOCAL_ARCHIVE}.asc"
    curl -fsSL -o "${RELEASE_TMP_DIR}/${GITLAB_CI_LOCAL_ARCHIVE}" \
        "${GITLAB_CI_LOCAL_RELEASE_URL}/${GITLAB_CI_LOCAL_ARCHIVE}"

    # The gpgv takes the binary keyring alone, while the dearmoring with an
    # empty home of its own leaves the ~/.gnupg of the user untouched.
    mkdir -m 700 "${RELEASE_TMP_DIR}/gnupg"

    GNUPGHOME="${RELEASE_TMP_DIR}/gnupg" gpg --batch \
        --dearmor -o "${RELEASE_TMP_DIR}/pubkey.gpg" "${RELEASE_TMP_DIR}/pubkey.asc"

    gpgv --keyring "${RELEASE_TMP_DIR}/pubkey.gpg" \
        "${RELEASE_TMP_DIR}/${GITLAB_CI_LOCAL_ARCHIVE}.asc" \
        "${RELEASE_TMP_DIR}/${GITLAB_CI_LOCAL_ARCHIVE}"

    tar -xzf "${RELEASE_TMP_DIR}/${GITLAB_CI_LOCAL_ARCHIVE}" -C "${RELEASE_TMP_DIR}" gitlab-ci-local

    ${RELEASE_TOOLS_SUDO} install -m 755 "${RELEASE_TMP_DIR}/gitlab-ci-local" \
        "${RELEASE_TOOLS_BIN_DIR}/gitlab-ci-local"

    rm -fr "${RELEASE_TMP_DIR}"

    "${RELEASE_TOOLS_BIN_DIR}/gitlab-ci-local" --version
}

# Installs the tools the local CI pipelines of the scripts/docker/*-run.sh
# scripts run with on an apt based release when the --local-pipelines flag is
# among the given arguments: the Docker, the rsync, the gitlab-ci-local out of
# the apt repository of its project and the act out of its release archive,
# since the distributions package neither of the two.
#
# Usage: apt_install_local_pipelines_tools "$@"
apt_install_local_pipelines_tools()
{
    if [[ ! $* =~ --local-pipelines ]] ; then
        return 0
    fi

    LOCAL_PIPELINES_PACKAGES=(
        curl
        gitlab-ci-local
        rsync
    )

    # A Docker of another origin - the docker-ce of the Docker site or the
    # snap one - is left as it is, since the docker.io package conflicts with
    # it.
    if ! command -v docker > /dev/null ||
        dpkg-query -W -f '${Status}' docker.io 2> /dev/null | grep -q ' installed$' ; then
        LOCAL_PIPELINES_PACKAGES+=(docker.io docker-buildx)
    fi

    log "Installing the local CI pipelines tools"

    # A half downloaded repository file would break every later apt-get call,
    # so it is downloaded aside first.
    GITLAB_CI_LOCAL_SOURCES=$(mktemp)

    curl -fsSL -o "${GITLAB_CI_LOCAL_SOURCES}" \
        https://gitlab-ci-local-ppa.firecow.dk/gitlab-ci-local.sources

    ${SUDO} install -m 644 "${GITLAB_CI_LOCAL_SOURCES}" \
        /etc/apt/sources.list.d/gitlab-ci-local.sources

    rm -f "${GITLAB_CI_LOCAL_SOURCES}"

    apt_install "${LOCAL_PIPELINES_PACKAGES[@]}"

    install_act_release

    log "The local CI pipelines tools are installed"
}
