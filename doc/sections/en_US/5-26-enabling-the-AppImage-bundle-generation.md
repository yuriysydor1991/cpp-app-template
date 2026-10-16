## Enabling the AppImage bundle generation support

In order to enable the portable [AppImage](https://appimage.org/) bundle creation target on the template project configure it with the `ENABLE_APPIMAGE` option set to `true`:

```
# inside the project root directory

meson setup build --prefix=/usr -DENABLE_APPIMAGE=true
```

Which in turn will enable the `AppImage` Meson `custom_target`. It runs `meson install` into an `AppDir` staging tree, copies the generated `AppRun` launcher, the `*.desktop` file and the icon it names into the `AppDir` root and packs the tree into a portable bundle with the `appimagetool`. The `--prefix=/usr` gives the bundle the standard `AppDir/usr/bin` layout (the `AppRun` launcher finds the executable under the default `/usr/local` prefix as well).

To produce the AppImage bundle run the `AppImage` target for the build:

```
# inside the project root directory

meson compile -C build AppImage
```

The artefact is named like `<project>-<version>-<arch>.AppImage` and lands in the build directory. Examine and/or change the AppImage generation target parameters in `meson/template-project-AppImage-enabler/meson.build`, in `misc/AppRun.meson.in` or in the `misc/template-project.desktop.meson.in` and `misc/template-project.icon.svg.meson.in` templates.

The produced bundle starts as any other executable (for example, `./build/CppAppTemplate-0.11.0-x86_64.AppImage --version`). The `scripts/build/build-appimage.sh` script performs the whole configure and build sequence, its `--install` flag copies the bundle into the `${HOME}/.local/bin` directory.

See [Optional for the AppImage packager](/doc/sections/en_US/3-18-optional-for-the-AppImage-packager.md) for the `appimagetool` install commands.
