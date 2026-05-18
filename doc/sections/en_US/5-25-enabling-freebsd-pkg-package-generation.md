## Enabling the FreeBSD pkg package generation support

In order to enable the FreeBSD `.pkg` package creation target on the template project configure it with the `ENABLE_FREEBSD_PKG` option set to `true` (FreeBSD only):

```
# inside the project root directory

meson setup build -DENABLE_FREEBSD_PKG=true \
  -DPROJECT_MAINTAINER='Your Name' \
  -DPROJECT_MAINTAINER_EMAIL='you@example.com'
```

Which in turn will enable the `freebsd-pkg` Meson `custom_target` that under the hood runs `meson install` into a staging directory and invokes the native `pkg create -M <manifest>` on it.

To produce the FreeBSD pkg package run the `freebsd-pkg` target for the build:

```
# inside the project root directory

meson compile -C build freebsd-pkg
```

The artefact is named like `<project>-<version>.pkg` and lands in the build directory. The `PROJECT_MAINTAINER` and `PROJECT_MAINTAINER_EMAIL` options feed the `maintainer:` field of the `+MANIFEST` file. Examine and/or change the FreeBSD pkg generation target parameters in `meson/template-project-freebsd-pkg-enabler/meson.build` or in the `misc/freebsd-pkg.manifest.in` template.

The `pkg(8)` tool is shipped by the FreeBSD base system and is available out of the box on FreeBSD hosts.
