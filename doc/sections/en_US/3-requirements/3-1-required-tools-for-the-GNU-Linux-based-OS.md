## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake pkg-config libsystemd-dev
```

The `pkg-config` tool and the `libsystemd-dev` files are the ones the [sdbus-c++](/doc/sections/en_US/3-requirements/3-13-required-packages-for-the-sdbus-cpp.md) library of this branch is built and linked with.
