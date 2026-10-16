## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appCFITSIO` branch additionally probes the system [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) and [WCSLIB](https://www.atnf.csiro.au/people/mcalabre/WCS/) development files with `pkg-config`, so those are worth installing as well:

```
sudo apt install -y pkg-config libcfitsio-dev wcslib-dev
```

On RPM-based distributions the equivalent packages are `pkgconf-pkg-config`, `cfitsio-devel` and `wcslib-devel`; on FreeBSD they are `devel/pkgconf`, `astro/cfitsio` and `astro/wcslib` from `pkg`. Without the CFITSIO one its sources get fetched and built from the Internet instead, which additionally requires the zlib development files (`zlib1g-dev`). Without the WCSLIB one its source archive gets fetched and built by its own `configure` script instead, which requires a C compiler, GNU `make` (both come with `build-essential`) and a build directory path without spaces.

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
