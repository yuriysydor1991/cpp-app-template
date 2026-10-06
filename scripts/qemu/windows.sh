#!/bin/bash -e
#
# Starts the MS Windows virtual machine to build and try the project branches
# in.
#
# MS Windows comes with no freely downloadable disk image, so the first run
# takes the installation ISO (from the Microsoft site) as it's first argument,
# creates the WINDOWS_DISK_SIZE disk and boots the installer off the ISO. The
# later runs start the installed system off the very same disk, while an ISO
# given to them is attached as a CD-ROM.
#
# The machine boots the UEFI firmware with the Secure Boot and the TPM 2.0 the
# MS Windows 11 demands, which the OVMF firmware and the swtpm emulator
# provide. It's disk, network card and pointer are the devices the installer
# carries the drivers of, so no driver disk is needed.
#
# Where the host has the Samba smbd, the project repository of the host is
# shared as the \\10.0.2.4\qemu network folder. The guest RDP and SSH ports
# are forwarded to the WINDOWS_RDP_PORT and the WINDOWS_SSH_PORT of the host.
#
# The rest of the arguments is passed to the emulator.
#
#   WINDOWS_VM         the machine name, a few installations live side by
#                      side under different ones, windows by default
#   WINDOWS_DISK_SIZE  the disk size of a new machine, 128G by default
#   WINDOWS_RDP_PORT   the host port of the guest RDP one, 13389 by default
#   WINDOWS_SSH_PORT   the host port of the guest SSH one, 2223 by default
#   WINDOWS_OVMF_CODE  the Secure Boot capable OVMF firmware and the variables
#   WINDOWS_OVMF_VARS  template of it, looked for at the distributions paths
#
# The QEMU_* variables of the scripts/qemu/common.sh apply as well.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/qemu/common.sh"

WINDOWS_VM=${WINDOWS_VM:-windows}
WINDOWS_DISK_SIZE=${WINDOWS_DISK_SIZE:-128G}
WINDOWS_RDP_PORT=${WINDOWS_RDP_PORT:-13389}
WINDOWS_SSH_PORT=${WINDOWS_SSH_PORT:-2223}

VM_DIR="${QEMU_VMS_DIR}/${WINDOWS_VM}"
DISK="${VM_DIR}/disk.qcow2"
VARS="${VM_DIR}/OVMF_VARS.fd"
TPM_DIR="${VM_DIR}/tpm"
# The socket paths are limited to about a hundred characters.
TPM_SOCKET="${XDG_RUNTIME_DIR:-/tmp}/CppAppTemplate-${WINDOWS_VM}-swtpm.sock"

ISO_ARGS=()

if [[ ${1,,} == *.iso ]] ; then
    [[ -f $1 ]] || log_fatal "No ${1} ISO found"

    ISO_ARGS=(-drive "file=$(realpath "$1"),format=raw,media=cdrom")
    shift
fi

require_tools "${QEMU_SYSTEM}" qemu-img

# The Debian/Ubuntu ovmf and the Fedora edk2-ovmf firmware with the Microsoft
# keys enrolled.
for pair in \
    /usr/share/OVMF/OVMF_CODE_4M.secboot.fd:/usr/share/OVMF/OVMF_VARS_4M.ms.fd \
    /usr/share/edk2/ovmf/OVMF_CODE.secboot.fd:/usr/share/edk2/ovmf/OVMF_VARS.secboot.fd
do
    if [[ -z ${WINDOWS_OVMF_CODE} && -f ${pair%%:*} ]] ; then
        WINDOWS_OVMF_CODE=${pair%%:*}
        WINDOWS_OVMF_VARS=${WINDOWS_OVMF_VARS:-${pair##*:}}
    fi
done

[[ -f ${WINDOWS_OVMF_CODE} && -f ${WINDOWS_OVMF_VARS} ]] ||
    log_fatal "No Secure Boot OVMF firmware found, install the ovmf package or" \
        "point the WINDOWS_OVMF_CODE and WINDOWS_OVMF_VARS to it"

if [[ ! -f ${DISK} ]] ; then
    [[ ${#ISO_ARGS[@]} -gt 0 ]] ||
        log_fatal "The first run installs the system: $0 <installation ISO>"

    mkdir -p "${VM_DIR}"

    qemu-img create -f qcow2 "${DISK}" "${WINDOWS_DISK_SIZE}"
fi

if [[ ! -f ${VARS} ]] ; then
    cp "${WINDOWS_OVMF_VARS}" "${VARS}"
fi

accelerator_args

TPM_ARGS=()

if command -v swtpm > /dev/null ; then
    mkdir -p "${TPM_DIR}"

    # The emulator ends together with the machine, which is it's only client.
    swtpm socket --tpm2 --tpmstate "dir=${TPM_DIR}" \
        --ctrl "type=unixio,path=${TPM_SOCKET}" --terminate --daemon

    TPM_ARGS=(
        -chardev "socket,id=chrtpm,path=${TPM_SOCKET}"
        -tpmdev emulator,id=tpm0,chardev=chrtpm
        -device tpm-tis,tpmdev=tpm0
    )
else
    log "No swtpm found, the MS Windows 11 installer refuses a machine with no TPM"
fi

NETDEV="user,id=net0,hostfwd=tcp:127.0.0.1:${WINDOWS_RDP_PORT}-:3389,hostfwd=tcp:127.0.0.1:${WINDOWS_SSH_PORT}-:22"

if command -v smbd > /dev/null || [[ -x /usr/sbin/smbd ]] ; then
    NETDEV+=",smb=${PROJECT_ROOT}"
fi

log "Starting the ${WINDOWS_VM} machine off ${DISK}"

exec "${QEMU_SYSTEM}" \
    -name "${WINDOWS_VM}" \
    -machine q35,smm=on \
    "${ACCEL_ARGS[@]}" \
    -m "${QEMU_MEMORY}" \
    -smp "${QEMU_CPUS}" \
    -global driver=cfi.pflash01,property=secure,value=on \
    -drive "if=pflash,format=raw,unit=0,readonly=on,file=${WINDOWS_OVMF_CODE}" \
    -drive "if=pflash,format=raw,unit=1,file=${VARS}" \
    "${TPM_ARGS[@]}" \
    -drive "file=${DISK},format=qcow2" \
    "${ISO_ARGS[@]}" \
    -netdev "${NETDEV}" \
    -device e1000e,netdev=net0 \
    -device qemu-xhci \
    -device usb-tablet \
    -rtc base=localtime \
    "$@"
