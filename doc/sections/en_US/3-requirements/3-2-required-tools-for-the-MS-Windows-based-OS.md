## Required tools for the MS Windows based OS

In order to build project binaries download the Visual Studio installer from the download page [https://visualstudio.microsoft.com/downloads/](https://visualstudio.microsoft.com/downloads/) and enable the **Desktop development with C++** workload. For the WinUI 3 GUI of this branch also install the **Windows App SDK C++ templates** component (Visual Studio 2022 is required for WinUI 3 / C++/WinRT).

Separately each project may be downloaded and installed from different sources (**may require additional tools download and install**): 
- The Git versioning system at [https://git-scm.com/downloads/win](https://git-scm.com/downloads/win)
- The CMake build system at [https://cmake.org/download/](https://cmake.org/download/)
- The Windows 10/11 SDK at [https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)
- The Windows App SDK (WinUI 3) - installed through the Visual Studio installer or restored as the `Microsoft.WindowsAppSDK` NuGet package; see the [WinUI 3 + C++/WinRT integration](/doc/sections/en_US/4-project-structure/4-8-winui3-cppwinrt-integration.md) section
- The NuGet CLI at [https://www.nuget.org/downloads](https://www.nuget.org/downloads) - used to restore the Windows App SDK and C++/WinRT packages
