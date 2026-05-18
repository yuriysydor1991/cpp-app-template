## Enabling the libcurl

In order to enable the [libcurl](https://curl.se/) library for the project by probing the system installation set a `true` value to the `ENABLE_LIBCURL` Meson option:

```
# Inside the source root directory

meson setup build -DENABLE_LIBCURL=true
```

The dependency is probed via Meson's `dependency('libcurl', required: true)` (pkg-config first, with a CMake config fallback). The found dependency is appended to the `template_project_extra_deps` variable in `meson/template-project-libcurl-enabler/meson.build` and is linked into the main binary and `applib`.

See [Optional for the libcurl integration](/doc/sections/en_US/3-16-optional-for-the-libcurl-integration.md) for the system package install command.
