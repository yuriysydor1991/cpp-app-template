## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with Meson, Ninja and Git.

```
sudo apt install -y git g++ meson ninja-build pkg-config
```

The branch ships with optional Meson enablers for several third-party libraries (all OFF by default). Install only what you intend to turn on with the corresponding `-DENABLE_*=true` meson option. See [Meson extra features](/doc/sections/en_US/5-19-meson-extra-features.md) for the full matrix.

```
# libcurl integration (-DENABLE_LIBCURL=true)
sudo apt install -y libcurl4-openssl-dev

# libxml2 integration (-DENABLE_LIBXML2=true)
sudo apt install -y libxml2-dev

# nlohmann_json integration (-DENABLE_NLOHMANN_JSON=true)
sudo apt install -y nlohmann-json3-dev

# OpenCV integration (-DENABLE_OPENCV=true) - includes the preinstalled Haar cascades
sudo apt install -y libopencv-dev opencv-data
```

The [scripts/packages](/scripts/packages) directory holds the scripts which install every package the project needs in one go. The [install-ubuntu.sh](/scripts/packages/install-ubuntu.sh) and [install-debian.sh](/scripts/packages/install-debian.sh) ones run the script of the running release - the [install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh), the [install-ubuntu-26-04.sh](/scripts/packages/install-ubuntu-26-04.sh) or the [install-debian-13.sh](/scripts/packages/install-debian-13.sh) one - since every release names and versions its packages its own way, and fail with the list of the supported releases on any other one. A dependency a release packages no usable version of is built by its script out of a pinned release tag of the dependency sources. The [install-redhat.sh](/scripts/packages/install-redhat.sh) script covers Fedora, RHEL and its rebuilds, and the [install-freebsd.sh](/scripts/packages/install-freebsd.sh) one covers FreeBSD:

```
scripts/packages/install-ubuntu.sh
```
