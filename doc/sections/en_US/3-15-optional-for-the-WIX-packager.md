## Optional for the WIX packager

In order to generate the project MSI installer install the [WiX Toolset](https://wixtoolset.org/) (MS Windows hosts only). The toolset ships the `candle.exe` and `light.exe` command line tools that the `wix` Meson target shells out to.

The recommended installation method on MS Windows is via the `dotnet` global tool:

```
# In a Windows command prompt or PowerShell
dotnet tool install --global wix
```

Alternatively, install the WiX Toolset v3 MSI installer from the [WiX Toolset releases](https://github.com/wixtoolset/wix3/releases). Make sure that the `candle.exe` and `light.exe` executables are visible in your `PATH` so that Meson's `find_program` can pick them up.

Look for the details at the [Enabling the WIX MSI installer generation support](/doc/sections/en_US/5-27-enabling-the-WIX-MSI-installer-generation.md) section.
