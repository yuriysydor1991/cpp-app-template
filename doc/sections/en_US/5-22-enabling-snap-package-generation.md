## Enabling the snap package generation support

In order to enable the [snap](https://snapcraft.io/) package creation target on the template project configure it with the `ENABLE_SNAP` option set to `true`:

```
# inside the project root directory

meson setup build -DENABLE_SNAP=true
```

Which in turn will enable the `snap` Meson `custom_target` driven by the `snapcraft` command line tool.

To produce the snap package run the `snap` target for the build:

```
# inside the project root directory

meson compile -C build snap
```

The artefact is named like `<project>_<version>_<arch>.snap` and lands in the build directory. Examine and/or change the snap generation target parameters in `meson/template-project-snap-enabler/meson.build` or in the `misc/snap/snapcraft.yaml.meson.in` template.

See [Optional for the snap packager](/doc/sections/en_US/3-13-optional-for-the-snap-packager.md) for the `snapcraft` install command.
