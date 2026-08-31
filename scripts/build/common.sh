if [[ -z ${PROJECT_ROOT} ]] ; then
    echo "#### No PROJECT_ROOT var given (scripts common.sh)"
    exit 1
fi

BUILD_DIR="${PROJECT_ROOT}/build/release"

# Drops the script own control flags from the forwarded arguments, leaving
# BUILD_ARGS with what the build system may receive.
filter_script_args()
{
    BUILD_ARGS=()

    for arg in "$@" ; do
        if [[ ${arg} != --install ]] ; then
            BUILD_ARGS+=("${arg}")
        fi
    done
}

# Installs the last built package the name pattern matches inside the build
# directory. The rest of the arguments is the installer command the package
# path is appended to.
install_built_package()
{
    PACKAGE_PATTERN=$1
    shift

    PACKAGE=$(find "${BUILD_DIR}" -name "${PACKAGE_PATTERN}" -print0 |
        xargs -0 -r ls -t | head -n1)

    if [[ -z ${PACKAGE} ]] ; then
        echo "#### No ${PACKAGE_PATTERN} package inside ${BUILD_DIR}"
        exit 1
    fi

    echo "#### Installing ${PACKAGE}"

    "$@" "${PACKAGE}"
}
