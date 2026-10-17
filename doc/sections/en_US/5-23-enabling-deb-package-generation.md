## Enabling the DEB package generation support

In order to enable the Debian/Ubuntu `.deb` package creation target on the template project configure it with the `ENABLE_DEB` option set to `true`:

```
# inside the project root directory

meson setup build --prefix=/usr -DENABLE_DEB=true \
  -DPROJECT_MAINTAINER='Your Name' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
```

Which in turn will enable the `deb` Meson `custom_target` that under the hood runs `meson install` into a staging directory and invokes `dpkg-deb --build` on it. The Debian packages install into the `/usr` prefix, so the `--prefix=/usr` parameter replaces the Meson default `/usr/local` one (the configure step reports any other prefix). The package payload belongs to the `root` user, and a package which ships a shared library refreshes the dynamic linker cache through the `ldconfig` trigger.

To produce the DEB package run the `deb` target for the build:

```
# inside the project root directory

meson compile -C build deb
```

The artefact is named like `<project>-<version>-<arch>-<os>.deb` and lands in the build directory, the `<os>` being the destination OS the `PACKAGE_OS` option holds (default: the `ID` and the `VERSION_ID` of the `/etc/os-release` file of the build host, e.g. `ubuntu-24.04`). The `PROJECT_MAINTAINER` and `PROJECT_MAINTAINER_EMAIL` options feed the `Maintainer:` field of the `DEBIAN/control` manifest. Examine and/or change the DEB generation target parameters in `meson/template-project-deb-enabler/meson.build` or in the `misc/deb-control.in` template.

The `dpkg-deb` tool is shipped by the `dpkg` system package which is preinstalled on Debian/Ubuntu hosts.
