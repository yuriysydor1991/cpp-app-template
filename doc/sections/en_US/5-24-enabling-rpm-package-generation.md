## Enabling the RPM package generation support

In order to enable the Fedora/RHEL/openSUSE `.rpm` package creation target on the template project configure it with the `ENABLE_RPM` option set to `true`:

```
# inside the project root directory

meson setup build -DENABLE_RPM=true \
  -DPROJECT_MAINTAINER='Your Name' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
```

Which in turn will enable the `rpm` Meson `custom_target` that under the hood runs `meson install` into a staging directory and invokes `rpmbuild -bb` on the generated `.spec` file. The `.spec` file copies the staged tree into its buildroot and packs the files listed from that tree, so the package follows the configured `--prefix` (the default `/usr/local`, or `/usr` for a distribution style package configured with the `--prefix=/usr` parameter).

To produce the RPM package run the `rpm` target for the build:

```
# inside the project root directory

meson compile -C build rpm
```

The artefact is named like `<project>-<version>-1.<arch>.rpm` and lands in the build directory. The `PROJECT_MAINTAINER` and `PROJECT_MAINTAINER_EMAIL` options feed the `Packager:` field of the `.spec` file. Examine and/or change the RPM generation target parameters in `meson/template-project-rpm-enabler/meson.build` or in the `misc/rpm.spec.in` template.

See [Optional for the rpm packager](/doc/sections/en_US/3-14-optional-for-the-rpm-packager.md) for the `rpm-build` install command.
