## Enabling the OpenCV

In order to enable the [OpenCV](https://opencv.org/) computer vision library for the project by probing the system installation set a `true` value to the `ENABLE_OPENCV` Meson option:

```
# Inside the source root directory

meson setup build -DENABLE_OPENCV=true
```

The dependency is probed via Meson's `dependency('opencv4', required: true)` (pkg-config first, with a CMake config fallback). The found dependency is appended to the `template_project_extra_deps` variable in `meson/template-project-OpenCV-enabler/meson.build` and is linked into the main binary and `applib`.

See [Optional for the OpenCV integration](/doc/sections/en_US/3-12-optional-for-the-OpenCV-integration.md) for the system package install command.
