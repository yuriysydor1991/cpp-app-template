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

The artefact is named like `<project>-<version>-<arch>-<os>.msi` and lands in the build directory, the `<arch>` being the CPU the installer is built for in the WiX terms (`x64`, `arm64` or `x86`) and the `<os>` the destination OS the `PACKAGE_OS` option holds (default: the NT version of the build host, the `windows-10.0` the Windows 10 and 11 share). The `PROJECT_MAINTAINER` option feeds the `Manufacturer` field of the WiX source. Examine and/or change the WIX generation target parameters in `meson/enablers/packagers/template-project-wix-enabler/meson.build` or in the `misc/wix.wxs.in` template.

See [Optional for the WIX packager](/doc/sections/en_US/3-15-optional-for-the-WIX-packager.md) for the WiX Toolset install hints.
