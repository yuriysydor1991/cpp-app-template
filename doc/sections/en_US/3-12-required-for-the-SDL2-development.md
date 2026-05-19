## Required packages for the SDL2 development

The template project depends on the [SDL2](https://en.wikipedia.org/wiki/Simple_DirectMedia_Layer) library together with the [OpenGL](https://www.opengl.org/) headers. The CMake configuration step probes them via `find_package(SDL2 REQUIRED)` and `find_package(OpenGL REQUIRED)` so both must be present on the host system at configure time.

### GNU/Linux (Debian/Ubuntu/derivatives)

The minimum set required to configure and build the project is the SDL2 development package (`libsdl2-dev`) and the OpenGL development files (`libgl1-mesa-dev`):

```
sudo apt install -y libsdl2-dev libgl1-mesa-dev
```

If your application is going to use the optional companion SDL2 modules (image loading, font rendering, audio mixing, networking) install them in one go:

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
vcpkg install sdl2 sdl2-image sdl2-mixer sdl2-net sdl2-ttf
```

Pass the vcpkg toolchain file to CMake during configuration so the `find_package(SDL2)` call picks up the binaries:

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
```

### Verifying the SDL2 installation

A quick way to confirm that SDL2 is reachable from `pkg-config` after installation:

```
pkg-config --modversion sdl2
```

The command should print the installed SDL2 version. If it errors out the CMake `find_package(SDL2 REQUIRED)` step will also fail at configure time.
