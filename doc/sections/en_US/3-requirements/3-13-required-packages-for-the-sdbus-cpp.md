## Required packages for the sdbus-c++

The D-Bus calls of this branch go through the [sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp) library of the 2.x API. Install its development files where the distribution ships the 2.x version (Ubuntu 26.04, Debian 13):

```
sudo apt install -y libsdbus-c++-dev pkg-config libsystemd-dev
```

A system with no sdbus-c++ or with an older one (the 1.x of the Ubuntu 24.04, the EPEL 9 or the Fedora up to 42) gets the sources of the `TEMPLATE_APP_SDBUSCXX_GIT_TAG` release (`v2.1.0` by default) fetched and built into the executable statically, which needs the `pkg-config` tool and the `libsystemd-dev` files. None of the fetched sdbus-c++ files is installed with the project.

The `ENABLE_LIBSDBUSCXX` CMake option is `ON` by default on this branch: the `src/sdbuscxx` example requires the library, so turning the option `OFF` stops the configuration with an explanation, until the `add_subdirectory(sdbuscxx)` call of the `src/CMakeLists.txt` file is dropped together with the `src/sdbuscxx` subdirectory and its usage of the `src/app/applications/Application.cpp` file.

The executable reads the `Hostname`, the `PrettyHostname` and the `OperatingSystemPrettyName` properties of the `org.freedesktop.hostname1` service (the `systemd-hostnamed`) on the system bus. With no system bus or no such service it exits with a failure status, and the live component tests skip themselves. The same properties may be checked with the `busctl` tool:

```
busctl get-property org.freedesktop.hostname1 /org/freedesktop/hostname1 org.freedesktop.hostname1 Hostname
```
