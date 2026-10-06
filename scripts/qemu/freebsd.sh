#!/bin/bash -e
#
# Starts the FreeBSD virtual machine to build and try the project branches in.
#
# The first run downloads the official FreeBSD VM image, verifies it against
# the release checksums and grows it to the FREEBSD_DISK_SIZE, which the guest
# file system takes over on it's first boot. The later runs start the very
# same disk, so whatever was installed or built inside it stays there.
#
# Log in as root with no password and mount the project repository the host
# shares read only to clone the branch of interest:
#
#   mount -t p9fs cpp-app-template /mnt
#   pkg install -y git && git config --global --add safe.directory /mnt
#   git clone -b app /mnt ~/cpp-app-template
#
# The guest SSH port is forwarded to the FREEBSD_SSH_PORT of the host, so the
# guest answers there once it's sshd is enabled with the
# `sysrc sshd_enable=YES && service sshd start` command.
#
# Every argument is passed to the emulator, e.g. the -vnc 127.0.0.1:1 one shows
# the guest screen over the VNC instead of a window.
#
#   FREEBSD_VERSION    the release to run, 15.1 by default
#   FREEBSD_DISK_SIZE  the disk size of a new machine, 64G by default
#   FREEBSD_SSH_PORT   the host port of the guest SSH one, 2222 by default
#
# The QEMU_* variables of the scripts/qemu/common.sh apply as well.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")

. "${PROJECT_ROOT}/scripts/qemu/common.sh"

FREEBSD_VERSION=${FREEBSD_VERSION:-15.1}
FREEBSD_DISK_SIZE=${FREEBSD_DISK_SIZE:-64G}
FREEBSD_SSH_PORT=${FREEBSD_SSH_PORT:-2222}

IMAGES_URL="https://download.freebsd.org/releases/VM-IMAGES/${FREEBSD_VERSION}-RELEASE/amd64/Latest"
IMAGE="FreeBSD-${FREEBSD_VERSION}-RELEASE-amd64-ufs.qcow2"
VM_DIR="${QEMU_VMS_DIR}/freebsd-${FREEBSD_VERSION}"
DISK="${VM_DIR}/${IMAGE}"

require_tools "${QEMU_SYSTEM}" qemu-img

if [[ ! -f ${DISK} ]] ; then
    require_tools curl sha256sum xz

    mkdir -p "${VM_DIR}"
    cd "${VM_DIR}"

    download "${IMAGES_URL}/${IMAGE}.xz" "${IMAGE}.xz"
    download "${IMAGES_URL}/CHECKSUM.SHA256" CHECKSUM.SHA256

    sha256sum --check --ignore-missing CHECKSUM.SHA256

    log "Unpacking the ${IMAGE}.xz"

    xz --decompress "${IMAGE}.xz"

    qemu-img resize "${DISK}" "${FREEBSD_DISK_SIZE}"
fi

accelerator_args

SHARE_ARGS=()

# Not every emulator build carries the 9P file system support.
if "${QEMU_SYSTEM}" -device help 2> /dev/null | grep -q virtio-9p-pci ; then
    SHARE_ARGS=(-virtfs "local,path=${PROJECT_ROOT},mount_tag=cpp-app-template,security_model=none,readonly=on")
fi

log "Starting the FreeBSD ${FREEBSD_VERSION} off ${DISK}"

exec "${QEMU_SYSTEM}" \
    -name "FreeBSD ${FREEBSD_VERSION}" \
    -machine q35 \
    "${ACCEL_ARGS[@]}" \
    -m "${QEMU_MEMORY}" \
    -smp "${QEMU_CPUS}" \
    -drive "file=${DISK},format=qcow2,if=virtio,discard=unmap" \
    -netdev "user,id=net0,hostfwd=tcp:127.0.0.1:${FREEBSD_SSH_PORT}-:22" \
    -device virtio-net-pci,netdev=net0 \
    "${SHARE_ARGS[@]}" \
    "$@"
