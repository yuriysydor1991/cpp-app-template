## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

All necessary development packages for the GTKmm-3.0:

```
sudo apt install -y pkg-config libgtkmm-3.0-dev
```

To be able to develop UI in the specialized [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) IDE install it with the command (the build does not need it, and Ubuntu 26.04 ships no glade package, so only the `scripts/packages/install-ubuntu-24-04.sh` and `scripts/packages/install-debian-13.sh` scripts install it):

```
sudo apt install -y glade
```

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
