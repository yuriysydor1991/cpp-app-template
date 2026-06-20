## Required packages for the SDL3 development

The template project depends on the [SDL3](https://wiki.libsdl.org/SDL3/FrontPage) library together with the [OpenGL](https://www.opengl.org/) headers. CMake acquires SDL3 through the dedicated `cmake/enablers/template-project-SDL3-enabler.cmake` enabler module which defaults to **FetchContent**: when SDL3 is not installed locally, the enabler clones `libsdl-org/SDL` at the tag pinned in `TEMPLATE_APP_SDL3_GIT_TAG` (default `release-3.2.10`) and builds `SDL3::SDL3` from source as part of the project build. OpenGL is still required from the host (`find_package(OpenGL REQUIRED)`).

### Switching between FetchContent and the system SDL3

The enabler exposes the `SDL3_DISABLE_SYSTEM_PROBE` CMake option:

| Option value | Behaviour |
|---|---|
| `ON` (default for `appSDL3`) | Skip `find_package(SDL3)` and pull SDL3 from FetchContent unconditionally - useful on hosts without `libsdl3-dev`. |
| `OFF` | Probe the system first via `find_package(SDL3 QUIET)`, fall back to FetchContent only when SDL3 is missing. |

Re-point the source or pin a different revision with `TEMPLATE_APP_SDL3_GIT` (URL) and `TEMPLATE_APP_SDL3_GIT_TAG` (git tag / branch / sha) cache strings, e.g.:

```
cmake -S . -B build \
  -DSDL3_DISABLE_SYSTEM_PROBE=OFF \
  -DTEMPLATE_APP_SDL3_GIT_TAG=release-3.2.10
```

The sections below cover the system-install paths if you prefer to opt into `find_package` mode.

### GNU/Linux (Debian/Ubuntu/derivatives)

The minimum set required to configure and build the project is the SDL3 development package (`libsdl3-dev`) and the OpenGL development files (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl3-dev libgl1-mesa-dev
```

If your application is going to use the optional companion SDL3 modules (image loading, font rendering, audio mixing) install them in one go:

```
sudo apt install -y libsdl3-dev libsdl3-doc \
  libsdl3-image0 libsdl3-image-dev \
  libsdl3-ttf0 libsdl3-ttf-dev
```

If `libsdl3-dev` is not yet available in the stable apt repositories (e.g. older Debian / Ubuntu LTS), build it from sources:

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
vcpkg install sdl3 sdl3-image sdl3-ttf
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

The command should print the installed SDL3 version. If it errors out the CMake `find_package(SDL3 REQUIRED)` step will also fail at configure time.
