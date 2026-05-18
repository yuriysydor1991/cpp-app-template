## Enabling the WIX MSI installer generation support

In order to enable the Windows `.msi` installer creation target on the template project configure it with the `ENABLE_WIX` option set to `true` (MS Windows host only):

```
# inside the project root directory

meson setup build -DENABLE_WIX=true \
  -DPROJECT_MAINTAINER='Your Name'
```

Which in turn will enable the `wix` Meson `custom_target` driven by the [WiX Toolset](https://wixtoolset.org/) command line tools `candle.exe` and `light.exe`. On a non-Windows host the `.wxs` source file is still configured into the build directory but the actual MSI build is skipped.

To produce the MSI installer run the `wix` target for the build:

```
# inside the project root directory

meson compile -C build wix
```

The artefact is named like `<project>-<version>-win-<arch>.msi` and lands in the build directory. The `PROJECT_MAINTAINER` option feeds the `Manufacturer` field of the WiX source. Examine and/or change the WIX generation target parameters in `meson/template-project-wix-enabler/meson.build` or in the `misc/wix.wxs.in` template.

See [Optional for the WIX packager](/doc/sections/en_US/3-15-optional-for-the-WIX-packager.md) for the WiX Toolset install hints.
