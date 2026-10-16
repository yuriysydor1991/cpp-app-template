## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) development packages are documented separately - see [Required packages for the SDL2 development](/doc/sections/en_US/3-requirements/3-12-required-for-the-SDL2-development.md).

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
