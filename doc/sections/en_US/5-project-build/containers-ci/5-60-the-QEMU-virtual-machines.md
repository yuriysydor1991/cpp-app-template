## The QEMU virtual machines

The [scripts/qemu](/scripts/qemu) directory holds the scripts starting the FreeBSD and the MS Windows virtual machines with the [QEMU](https://www.qemu.org/) emulator, so the project branches are built and tried on those systems right from a Linux host:

| Script | Starts |
| --- | --- |
| [freebsd.sh](/scripts/qemu/freebsd.sh) | the FreeBSD machine off the official VM image, which the first run downloads and verifies |
| [windows.sh](/scripts/qemu/windows.sh) | the MS Windows machine, which the first run installs off the given installation ISO |

The host needs the `qemu-system-x86` and the `qemu-utils` packages, and the MS Windows machine the `ovmf` (the UEFI firmware) and the `swtpm` (the TPM 2.0 the MS Windows 11 demands) ones as well. The guest runs at the native speed only for a user of the `kvm` group, the CPU is emulated otherwise.

Every machine is kept under the `~/.local/share/CppAppTemplate/qemu` directory and every run continues the very same disk, so whatever was installed or built inside a guest stays there. Erasing the directory of a machine starts it anew.

The arguments of the scripts are passed to the emulator, e.g. the `-vnc 127.0.0.1:1` one shows the guest screen over the VNC instead of a window.

### FreeBSD

```
# inside the project root directory

scripts/qemu/freebsd.sh
```

Log in as `root` with no password. The host project repository is shared with the guest read only, so a branch of interest is a clone away:

```
# inside the FreeBSD guest

mount -t p9fs cpp-app-template /mnt
pkg install -y git
git config --global --add safe.directory /mnt
git clone -b app /mnt ~/cpp-app-template

cd ~/cpp-app-template
scripts/packages/install-freebsd.sh
scripts/build/release.sh
```

The guest SSH port is forwarded to the `127.0.0.1:2222` one of the host, which answers once the `sysrc sshd_enable=YES && service sshd start` command enables the guest SSH server and the `adduser` one creates a user to log in as.

| Variable | Default | Meaning |
| --- | --- | --- |
| `FREEBSD_VERSION` | `15.1` | the FreeBSD release to download and start |
| `FREEBSD_DISK_SIZE` | `64G` | the disk size of a new machine |
| `FREEBSD_SSH_PORT` | `2222` | the host port of the guest SSH one |

### MS Windows

MS Windows comes with no freely downloadable disk image, so the first run takes the installation ISO from the Microsoft site and boots the installer off it, while the later runs start the installed system:

```
# inside the project root directory

scripts/qemu/windows.sh ~/Downloads/Win11_English_x64.iso

scripts/qemu/windows.sh
```

The machine disk, network card and pointer are the devices the installer carries the drivers of, so no driver disk is needed. The guest RDP port is forwarded to the `127.0.0.1:13389` one of the host and the guest SSH port to the `127.0.0.1:2223` one.

With the Samba `smbd` installed on the host the project repository is shared as the `\\10.0.2.4\qemu` network folder. The MS Windows 11 refuses such a guest access share by default, which an administrator PowerShell of the guest allows:

```
Set-SmbClientConfiguration -RequireSecuritySignature $false -EnableInsecureGuestLogons $true
```

| Variable | Default | Meaning |
| --- | --- | --- |
| `WINDOWS_VM` | `windows` | the machine name, which keeps a few installations side by side |
| `WINDOWS_DISK_SIZE` | `128G` | the disk size of a new machine |
| `WINDOWS_RDP_PORT` | `13389` | the host port of the guest RDP one |
| `WINDOWS_SSH_PORT` | `2223` | the host port of the guest SSH one |
| `WINDOWS_OVMF_CODE`, `WINDOWS_OVMF_VARS` | the Debian, Ubuntu and Fedora firmware paths | the Secure Boot capable OVMF firmware and it's variables template |

### The common variables

| Variable | Default | Meaning |
| --- | --- | --- |
| `QEMU_VMS_DIR` | `~/.local/share/CppAppTemplate/qemu` | the directory keeping the machines and the downloads |
| `QEMU_MEMORY` | `8G` | the guest memory size |
| `QEMU_CPUS` | the half of the host cores | the guest CPU cores |
| `QEMU_SYSTEM` | `qemu-system-x86_64` | the emulator to start |
