if [[ -z ${PROJECT_ROOT} ]] ; then
    echo "#### No PROJECT_ROOT var given (packages common.sh)"
    exit 1
fi

. "${PROJECT_ROOT}/scripts/common.sh"

# The local CI pipelines tools no distribution packages are installed out of
# the release archives of their projects into this directory, each one checked
# against what its release publishes first. A later run updates them to the
# latest release.
RELEASE_TOOLS_BIN_DIR=/usr/local/bin

RELEASE_TOOLS_SUDO=""

if [[ ${EUID} -ne 0 ]] ; then
    RELEASE_TOOLS_SUDO="sudo"
fi

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
