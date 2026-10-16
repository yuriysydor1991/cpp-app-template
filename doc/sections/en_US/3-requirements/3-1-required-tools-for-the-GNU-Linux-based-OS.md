## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appLZMA` branch additionally relies on the system [liblzma](https://tukaani.org/xz/) (XZ Utils) development files, so those have to be installed as well:

```
sudo apt install -y liblzma-dev
```

On RPM-based distributions the equivalent package is `xz-devel`; the FreeBSD base system ships the liblzma library already.
