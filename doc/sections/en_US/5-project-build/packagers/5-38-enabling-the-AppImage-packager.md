## Enabling the AppImage packager

In order to enable the project's `appimage` target designed to generate the project's [AppImage](https://appimage.org/) single file distributive, configure project with enabled `ENABLE_APPIMAGE` CMake variable:

```
# inside the project root directory

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DENABLE_APPIMAGE=ON
```

Next, build the `appimage` target:

```
# inside the project root directory

cmake --build build --target appimage
```

The target installs the project into the `AppDir` directory of the build root with the `DESTDIR` set, so it builds whatever the install step needs on its own, and then packs that `AppDir` with the `appimagetool` command. The package file is generated inside the project build root directory. For example, if the project name wasn't changed and its version is `0.14.0` the package name may look like `CppAppTemplate-0.14.0-x86_64.AppImage`.

The produced package is a single executable file which needs no installation at all:

```
# inside the project build root directory

chmod +x CppAppTemplate-0.14.0-x86_64.AppImage

./CppAppTemplate-0.14.0-x86_64.AppImage
```

The `CMAKE_INSTALL_PREFIX` of the configure step above is the prefix the binary is placed under inside the `AppDir`, not a directory of the host, as the whole `AppDir` becomes the file system root of the running package.

The `AppDir` gets the three files the AppImage format requires beside the installed project: the `AppRun` startup script, the desktop entry and the icon it names. All the three are configured by the CMake from the templates of the [misc/packagers](/misc/packagers) directory:

- [appimage.AppRun.in](/misc/packagers/appimage/appimage.AppRun.in) - the `AppRun` script, which exports the `LD_LIBRARY_PATH` of the packaged libraries and starts the project binary;
- [desktop.entry.in](/misc/packagers/desktop/desktop.entry.in) - the desktop entry the desktop environments integrate the package with;
- [desktop.icon.svg.in](/misc/packagers/desktop/desktop.icon.svg.in) - the icon the desktop entry names.

The desktop entry and the icon are the ones every package of a windowed application carries: the `ENABLE_DESKTOP_APPLICATION` variable sets the `Terminal` key of the desktop entry (`false` for a windowed application, `true` for a console one), while the `TEMPLATE_PROJECT_DESKTOP_CATEGORIES` and the `DESKTOP_ICON_SRC` ones tune the categories and the icon - see the [desktop application packaging section](/doc/sections/en_US/5-project-build/packagers/5-46-enabling-the-desktop-application-packaging.md).

The following cache variable may optionally be overridden in order to tune the produced package:

- `TEMPLATE_PROJECT_APPIMAGE_ARCHITECTURE` - the destination CPU architecture (default: the `CMAKE_SYSTEM_PROCESSOR` variable of the CMake). Other typical values are `aarch64`, `armhf`, `i686`.

The destination CPU architecture ends up in the package file name and is given to the `appimagetool` as the `ARCH` environment variable it requires. Override it when cross compiling the project, so the package the CMake names is the package the `appimagetool` embeds.

In order to examine details of the AppImage package configuration visit the [cmake/enablers/packagers/template-project-appimage-enabler.cmake](/cmake/enablers/packagers/template-project-appimage-enabler.cmake) file.

> **Runtime note.** Unlike the flatpak and the snap packagers, which build the project inside their own sandboxes with the dependencies they install themselves, the `appimagetool` packs the installed project alone. The libraries of the host the project links against are therefore expected on the machine the package runs, unless they are installed into the `AppDir` by the project itself. Build the package on the oldest distribution the package is meant to run on to keep the `glibc` requirement of the binary as low as possible.
