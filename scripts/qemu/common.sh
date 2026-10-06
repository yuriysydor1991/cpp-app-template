# The part the QEMU virtual machine scripts share: the place the machines are
# kept at, their hardware and the helpers starting them.
#
# Every setting is an environment variable, so a VAR=value prefix of a single
# run overrides it:
#
#   QEMU_VMS_DIR  the directory of the machine disks, firmware variables and
#                 downloads, ${XDG_DATA_HOME}/CppAppTemplate/qemu by default
#   QEMU_MEMORY   the guest memory size, 8G by default
#   QEMU_CPUS     the guest CPU cores, the half of the host ones by default
#   QEMU_SYSTEM   the emulator to start, qemu-system-x86_64 by default

if [[ -z ${PROJECT_ROOT} ]] ; then
    echo "#### No PROJECT_ROOT var given (scripts/qemu/common.sh)"
    exit 1
fi

. "${PROJECT_ROOT}/scripts/common.sh"

QEMU_VMS_DIR=${QEMU_VMS_DIR:-${XDG_DATA_HOME:-${HOME}/.local/share}/CppAppTemplate/qemu}
QEMU_MEMORY=${QEMU_MEMORY:-8G}
QEMU_CPUS=${QEMU_CPUS:-$(( $(nproc) > 1 ? $(nproc) / 2 : 1 ))}
QEMU_SYSTEM=${QEMU_SYSTEM:-qemu-system-x86_64}

require_tools()
{
    for tool in "$@" ; do
        command -v "${tool}" > /dev/null ||
            log_fatal "No ${tool} found, install it first"
    done
}

# The KVM acceleration with the host CPU model where the /dev/kvm is usable,
# the many times slower emulation otherwise.
accelerator_args()
{
    if [[ -r /dev/kvm && -w /dev/kvm ]] ; then
        ACCEL_ARGS=(-accel kvm -cpu host)
    else
        log "No usable /dev/kvm (the kvm group membership?), emulating the CPU"
        ACCEL_ARGS=(-accel tcg -cpu max)
    fi
}

# Downloads the URL through a temporary file, so an interrupted download is
# never taken for the complete one.
download()
{
    log "Downloading ${1}"

    curl -fL --retry 3 -o "${2}.part" "${1}"

    mv "${2}.part" "${2}"
}
