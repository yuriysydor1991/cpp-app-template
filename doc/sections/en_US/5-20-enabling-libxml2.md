## Enabling the libxml2

In order to enable the [libxml2](https://gitlab.gnome.org/GNOME/libxml2) library for the project by probing the system installation set a `true` value to the `ENABLE_LIBXML2` Meson option:

```
# Inside the source root directory

meson setup build -DENABLE_LIBXML2=true
```

The dependency is probed via Meson's `dependency('libxml-2.0', required: true)` (pkg-config first, with a CMake config fallback). The found dependency is appended to the `template_project_extra_deps` variable in `meson/template-project-libxml2-enabler/meson.build` and is linked into the main binary and `applib`.

See [Optional for the libxml2 integration](/doc/sections/en_US/3-11-optional-for-the-libxml2-integration.md) for the system package install command.
