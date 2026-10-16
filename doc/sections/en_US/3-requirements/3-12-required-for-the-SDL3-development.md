## Required packages for the SDL3 development

The template project depends on the [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) library together with the [OpenGL](https://www.opengl.org/) headers. CMake acquires SDL3 through the dedicated `cmake/enablers/template-project-SDL3-enabler.cmake` enabler module: it probes the system SDL3 first (`find_package(SDL3 QUIET)`) and, when none is installed, clones `libsdl-org/SDL` at the tag pinned in `TEMPLATE_APP_SDL3_GIT_TAG` (default `release-3.2.10`) through **FetchContent** and builds `SDL3::SDL3` from source as part of the project build. OpenGL is still required from the host (`find_package(OpenGL REQUIRED)`).

### The system SDL3 or the FetchContent build

An installed SDL3 always wins the probe. To build the pinned sources on a host with `libsdl3-dev` installed anyway, hide the system package from the probe with the standard `CMAKE_DISABLE_FIND_PACKAGE_SDL3` CMake variable. Re-point the source or pin a different revision with `TEMPLATE_APP_SDL3_GIT` (URL) and `TEMPLATE_APP_SDL3_GIT_TAG` (git tag / branch / sha) cache strings, e.g.:

```
cmake -S . -B build \
  -DCMAKE_DISABLE_FIND_PACKAGE_SDL3=ON \
  -DTEMPLATE_APP_SDL3_GIT_TAG=release-3.2.10
```

The SDL3 source build compiles the video backends only for the windowing systems whose development files it finds, so install them before the configuration, otherwise the application exits with the "No available video device" error. On Debian/Ubuntu:

```
sudo apt install -y libx11-dev libxext-dev libxrandr-dev libxcursor-dev \
  libxi-dev libxfixes-dev libxss-dev libxtst-dev libwayland-dev \
  libxkbcommon-dev libegl-dev libdecor-0-dev libdbus-1-dev libudev-dev
```

The `ENABLE_SDL3` CMake option (`ON` by default) is there for the projects that drop the SDL3 integration: the template sources (`src/SDL3`, the `SDL3Controller` usage of the `Application` class and their tests) use SDL3 unconditionally, so switching it `OFF` works only together with their removal.

The sections below cover the system-install paths.

### GNU/Linux (Debian/Ubuntu/derivatives)

The minimum set required to configure and build the project with the system SDL3 is the SDL3 development package (`libsdl3-dev`, packaged since Debian 13 and Ubuntu 25.04) and the OpenGL development files (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl3-dev libgl1-mesa-dev
```

The template itself uses none of the companion SDL3 modules. If your application is going to use them (image loading, font rendering) install them in one go:

```
sudo apt install -y libsdl3-dev libsdl3-doc \
  libsdl3-image0 libsdl3-image-dev \
  libsdl3-ttf0 libsdl3-ttf-dev
```

If `libsdl3-dev` is not available in the apt repositories (e.g. Ubuntu 24.04), either let the FetchContent build above take care of it or build and install it from sources (with the windowing system development packages above installed):

```
git clone --depth 1 --branch release-3.2.10 https://github.com/libsdl-org/SDL.git
cmake -S SDL -B SDL/build -DCMAKE_BUILD_TYPE=Release -DSDL_STATIC=OFF -DSDL_SHARED=ON
cmake --build SDL/build --parallel
sudo cmake --install SDL/build
sudo ldconfig
```

### Other GNU/Linux distributions

- **Fedora / RHEL / openSUSE**: `SDL3-devel` (+ optional `SDL3_image-devel`, `SDL3_ttf-devel`) and `mesa-libGL-devel`.
- **Arch Linux**: `sdl3` (+ optional `sdl3_image`, `sdl3_ttf`) and `mesa`.

### MS Windows

Use the [vcpkg](https://vcpkg.io/) package manager or download the prebuilt development binaries from the [official SDL3 release page](https://github.com/libsdl-org/SDL/releases). With vcpkg the install command is:

```
vcpkg install sdl3
```

Pass the vcpkg toolchain file to CMake during configuration so the `find_package(SDL3)` call picks up the binaries:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

### Verifying the SDL3 installation

A quick way to confirm that SDL3 is reachable from `pkg-config` after installation:

```
pkg-config --modversion sdl3
```

The command should print the installed SDL3 version. If it errors out the CMake `find_package(SDL3 QUIET)` probe won't find SDL3 either and the configuration falls back to the FetchContent build.
