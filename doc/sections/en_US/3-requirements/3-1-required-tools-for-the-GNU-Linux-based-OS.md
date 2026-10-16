## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appZlib` branch additionally relies on the system [zlib](https://www.zlib.net/) development files, so those have to be installed as well:

```
sudo apt install -y zlib1g-dev
```

On RPM-based distributions the equivalent package is `zlib-devel`; the FreeBSD base system ships the zlib library already.
