## Enabling the AppImage bundle generation support

In order to enable the portable [AppImage](https://appimage.org/) bundle creation target on the template project configure it with the `ENABLE_APPIMAGE` option set to `true`:

```
# inside the project root directory

meson setup build -DENABLE_APPIMAGE=true
```

Which in turn will enable the `AppImage` Meson `custom_target`. It runs `meson install` into an `AppDir` staging tree, copies the generated `AppRun` launcher and `*.desktop` file into the right places and emits a portable bundle.

To produce the AppImage bundle run the `AppImage` target for the build:

```
# inside the project root directory

meson compile -C build AppImage
```

The artefact is named like `<project>-<version>-<arch>.AppImage` and lands in the build directory. Examine and/or change the AppImage generation target parameters in `meson/template-project-AppImage-enabler/meson.build`, in `misc/AppRun.meson.in` or in the `misc/template-project.desktop.meson.in` template.

The target does not depend on any external AppImage-specific tooling - it uses the built-in `tar` command to assemble the bundle.
