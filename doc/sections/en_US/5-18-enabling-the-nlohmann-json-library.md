## Enabling the nlohmann JSON library

In order to enable the [nlohmann JSON](https://github.com/nlohmann/json) header-only library for the project by probing the system installation set a `true` value to the `ENABLE_NLOHMANN_JSON` Meson option:

```
# Inside the source root directory

meson setup build -DENABLE_NLOHMANN_JSON=true
```

The dependency is probed via Meson's `dependency('nlohmann_json', required: true)` (pkg-config first, with a CMake config fallback). The found dependency is appended to the `template_project_extra_deps` variable in `meson/template-project-nlohmann-json-enabler/meson.build` and is linked into the main binary and `applib`.

See [Optional for the nlohmann JSON integration](/doc/sections/en_US/3-17-optional-for-the-nlohmann-json-integration.md) for the system package install command.
