## Required packages for the SDL2 development

The template project depends on the [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) library together with the [OpenGL](https://www.opengl.org/) headers. CMake acquires SDL2 through the dedicated `cmake/enablers/template-project-SDL2-enabler.cmake` enabler module: it probes the system SDL2 first (`find_package(SDL2 QUIET)`) and, when none is installed, clones `libsdl-org/SDL` at the tag pinned in `TEMPLATE_APP_SDL2_GIT_TAG` (default `release-2.32.10`) through **FetchContent** and builds `SDL2::SDL2` from source as part of the project build. OpenGL is still required from the host (`find_package(OpenGL REQUIRED)`).

### The system SDL2 or the FetchContent build

An installed SDL2 always wins the probe. To build the pinned sources on a host with `libsdl2-dev` installed anyway, hide the system package from the probe with the standard `CMAKE_DISABLE_FIND_PACKAGE_SDL2` CMake variable. Re-point the source or pin a different revision with `TEMPLATE_APP_SDL2_GIT` (URL) and `TEMPLATE_APP_SDL2_GIT_TAG` (git tag / branch / sha) cache strings, e.g.:

```
cmake -S . -B build \
  -DCMAKE_DISABLE_FIND_PACKAGE_SDL2=ON \
  -DTEMPLATE_APP_SDL2_GIT_TAG=release-2.32.10
```

The SDL2 source build compiles the video backends only for the windowing systems whose development files it finds, so install them before the configuration (e.g. `libx11-dev libxext-dev libwayland-dev libxkbcommon-dev libegl-dev` on Debian/Ubuntu), otherwise the application exits with the "No available video device" error.

The `ENABLE_SDL2` CMake option (`ON` by default) is there for the projects that drop the SDL2 integration: the template sources (`src/SDL2`, the `SDL2Controller` usage of the `Application` class and their tests) use SDL2 unconditionally, so switching it `OFF` works only together with their removal.

### GNU/Linux (Debian/Ubuntu/derivatives)

The minimum set required to configure and build the project with the system SDL2 is the SDL2 development package (`libsdl2-dev`) and the OpenGL development files (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl2-dev libgl1-mesa-dev
```

The template itself uses none of the companion SDL2 modules. If your application is going to use them (image loading, font rendering, audio mixing, networking) install them in one go:

```
sudo apt install -y libsdl2-dev libsdl2-doc \
  libsdl2-image-2.0-0 libsdl2-image-dev \
  libsdl2-mixer-2.0-0 libsdl2-mixer-dev \
  libsdl2-net-2.0-0 libsdl2-net-dev \
  libsdl2-ttf-dev
```

### Other GNU/Linux distributions

- **Fedora / RHEL / openSUSE**: `SDL2-devel` (+ optional `SDL2_image-devel`, `SDL2_mixer-devel`, `SDL2_net-devel`, `SDL2_ttf-devel`) and `mesa-libGL-devel`.
- **Arch Linux**: `sdl2` (+ optional `sdl2_image`, `sdl2_mixer`, `sdl2_net`, `sdl2_ttf`) and `mesa`.

### MS Windows

Use the [vcpkg](https://vcpkg.io/) package manager or download the prebuilt development binaries from the [official SDL2 release page](https://github.com/libsdl-org/SDL/releases). With vcpkg the install command is:

```
vcpkg install sdl2
```

Add the companion module ports (`sdl2-image`, `sdl2-mixer`, `sdl2-net`, `sdl2-ttf`) only when the application uses them. Pass the vcpkg toolchain file to CMake during configuration so the `find_package(SDL2)` call picks up the binaries:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

### Verifying the SDL2 installation

A quick way to confirm that SDL2 is reachable from `pkg-config` after installation:

```
pkg-config --modversion sdl2
```

The command should print the installed SDL2 version. If it errors out the CMake `find_package(SDL2 QUIET)` probe won't find SDL2 either and the configuration falls back to the FetchContent build.
