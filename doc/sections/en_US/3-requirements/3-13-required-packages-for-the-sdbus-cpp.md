## Required packages for the sdbus-c++

The D-Bus server of this branch is built on the [sdbus-c++](https://github.com/Kistler-Group/sdbus-cpp) library of the 2.x API. Install its development files where the distribution ships the 2.x version (Ubuntu 26.04, Debian 13):

```
sudo apt install -y libsdbus-c++-dev pkg-config libsystemd-dev
```

A system with no sdbus-c++ or with an older one (the 1.x of the Ubuntu 24.04, the EPEL 9 or the Fedora up to 42) gets the sources of the `TEMPLATE_APP_SDBUSCXX_GIT_TAG` release (`v2.1.0` by default) fetched and built into the executable statically, which needs the `pkg-config` tool and the `libsystemd-dev` files. None of the fetched sdbus-c++ files is installed with the project.

On the Ubuntu 24.04 the [scripts/packages/install-ubuntu-24-04.sh](/scripts/packages/install-ubuntu-24-04.sh) script builds the `v2.1.0` release out of its sources and installs it into the system instead, so the configuration finds it there.

The `ENABLE_LIBSDBUSCXX` CMake option is `ON` by default on this branch: the `src/sdbuscxx` example requires the library, so turning the option `OFF` stops the configuration with an explanation, until the `add_subdirectory(sdbuscxx)` call of the `src/CMakeLists.txt` file is dropped together with the `src/sdbuscxx` subdirectory and its usage of the `src/app/applications/Application.cpp` file.

The executable owns the `org.cppapptemplate.SimpleServer` name on the session bus and serves the `CurrentDate` property of the `org.cppapptemplate.SimpleServer1` interface at the `/org/cppapptemplate/SimpleServer` object until the `Ctrl+C`, the `kill` command or another termination signal stops it. The installed `share/dbus-1/services/org.cppapptemplate.SimpleServer.service` file lets the session bus start it on the first call. Query the running server with the `busctl` tool:

```
busctl --user introspect org.cppapptemplate.SimpleServer /org/cppapptemplate/SimpleServer
busctl --user get-property org.cppapptemplate.SimpleServer /org/cppapptemplate/SimpleServer org.cppapptemplate.SimpleServer1 CurrentDate
```

With no session bus the executable exits with a failure status, and the round trip component test skips itself, as it does while another server instance owns the name.
