## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

All necessary development packages for the GTKmm-4.0:

```
sudo apt install -y pkg-config libgtkmm-4.0-dev libglib2.0-dev-bin
```

The Vulkan loader and headers, used both for the physical device enumeration and
for rendering the window contents off-screen with Vulkan and exporting them as a
Linux dma-buf for display in the GTK window (plus a runtime Vulkan driver that
supports dma-buf export, e.g. the Mesa GPU drivers):

```
sudo apt install -y libvulkan-dev mesa-vulkan-drivers
```

The branch requires GTK / gtkmm 4.14 or newer (for the `Gdk::DmabufTexture`):
the configure stops on an older gtkmm. With no usable Vulkan runtime at all (no
loader or no driver) or with only a software Vulkan driver (e.g. lavapipe),
the dma-buf export is unavailable and the window falls back to a plain black
background.

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
