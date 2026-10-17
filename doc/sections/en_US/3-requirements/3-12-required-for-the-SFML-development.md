## Required packages for the SFML development

The template project depends on the [SFML](https://www.sfml-dev.org/) multimedia library (the `graphics`, `window` and `system` modules). The CMake `template-project-SFML-enabler` first probes a system installation with `find_package(SFML 2.6 COMPONENTS graphics window system)` and, when it is missing, transparently falls back to fetching and building SFML from its upstream git repository through the CMake `FetchContent` facility (pinned to the `2.6.2` tag by default). The template sources use the SFML 2 API, so the probe accepts an SFML 2.6 installation only and skips an installed SFML 3 (e.g. the `libsfml-dev` of Ubuntu 26.04 or the current vcpkg `sfml` port), which leads to the `FetchContent` build as well.

So a system wide SFML is **optional**: install it to speed up the configuration step, or let the `FetchContent` fallback build it for you (which additionally needs the X11/OpenGL/FreeType development headers listed below).

### GNU/Linux (Debian/Ubuntu/derivatives)

Where the distribution ships SFML 2.6 (e.g. Ubuntu 24.04, Debian 13) the fastest path is to install the SFML development package so that the system probe succeeds and no source build is required:

```
sudo apt install -y libsfml-dev
```

If you prefer (or are forced to) let the `FetchContent` fallback build SFML from source, install the toolchain together with the SFML build dependencies instead:

```
sudo apt install -y git g++ cmake \
  libx11-dev libxrandr-dev libxcursor-dev libudev-dev \
  libgl1-mesa-dev libfreetype-dev
```

### Other GNU/Linux distributions

- **Fedora / RHEL / openSUSE**: `SFML-devel` (or the toolchain plus `libX11-devel`, `libXrandr-devel`, `libXcursor-devel`, `systemd-devel`, `mesa-libGL-devel` and `freetype-devel` for the source build).
- **Arch Linux**: `sfml` (or `libx11`, `libxrandr`, `libxcursor`, `systemd-libs`, `mesa` and `freetype2` for the source build).

### MS Windows

Use the [vcpkg](https://vcpkg.io/) package manager or download the prebuilt development binaries from the [official SFML download page](https://www.sfml-dev.org/download.php). With vcpkg the install command is:

```
vcpkg install sfml
```

Pass the vcpkg toolchain file to CMake during configuration so the `find_package(SFML)` call picks up the binaries:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

If neither a system SFML nor vcpkg is available the `FetchContent` fallback still builds SFML from source, provided the platform C++ toolchain is installed.

### Tuning the SFML enabler

- `ENABLE_SFML` (`ON` by default) is there for the projects that drop the SFML integration: the template sources (`src/SFML`, the `SFMLController` usage of the `Application` class and their tests) use SFML unconditionally, so `-DENABLE_SFML=OFF` works only together with their removal.
- `-DTEMPLATE_APP_SFML_GIT_TAG=<tag>` selects a different SFML revision for the `FetchContent` build (defaults to `2.6.2`).

### Verifying the SFML installation

A quick way to confirm that a system SFML is reachable from `pkg-config`:

```
pkg-config --modversion sfml-graphics
```

The command should print the installed SFML version. If it errors out the CMake `find_package(SFML ...)` probe will not find a system SFML and the `FetchContent` fallback will be used instead.
