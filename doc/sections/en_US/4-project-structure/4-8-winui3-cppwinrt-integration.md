## WinUI 3 + C++/WinRT integration

This branch fast-starts a [Microsoft WinUI 3](https://learn.microsoft.com/windows/apps/winui/winui3/) desktop application written with [C++/WinRT](https://learn.microsoft.com/windows/uwp/cpp-and-winrt-apis/) on top of the [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/). WinUI 3 is a **Windows-only** UI stack, so the component keeps everything that can be platform independent platform independent and hides the native UI behind a single launch seam.

### Layout

- `src/winui3/WinUI3Controller.{h,cpp}` - the WinUI free orchestration object. It validates the application context and launches the GUI through the `run_winui_application()` launch seam (`src/winui3/WinUI3Launcher.h`). Builds and is unit/component tested on every platform.
- `src/winui3/helpers/WindowConfig.{h,cpp}` - a WinUI independent holder for the window title / texts / sizes, unit tested in isolation.
- `src/winui3/app/WinUI3App.{h,cpp}` - the native C++/WinRT application object (it also provides the XAML type metadata of the WinUI 3 controls through `IXamlMetadataProvider`, the job of the XAML compiler generated code otherwise) and the real `run_winui_application()` definition. **Windows only.**
- `src/winui3/app/WinUI3AppStub.cpp` - a non-Windows definition of `run_winui_application()` so the executable still builds, links and runs (printing a notice) off Windows. The real WinUI 3 window only opens on Windows.
- `src/winui3/main-window/WinUI3MainWindow.{h,cpp}` - the WinUI 3 window, built programmatically (no XAML file) from `WindowConfig`. **Windows only.**

`Application::run()` (`src/app/applications/Application.cpp`) creates a `WinUI3Controller` and delegates to it, exactly like the other GUI branches delegate to their controller.

### Building it

The native UI is set up by the CMake enabler `cmake/enablers/template-project-WinUI3-enabler.cmake`, controlled by:

- `ENABLE_WINUI3` (default `ON`) - set to `OFF` to drop the WinUI 3 integration.
- `TEMPLATE_APP_WINAPPSDK_VERSION` / `TEMPLATE_APP_CPPWINRT_VERSION` / `TEMPLATE_APP_WEBVIEW2_VERSION` - the Windows App SDK, C++/WinRT and WebView2 (a Windows App SDK dependency) NuGet package versions restored on Windows.
- `WINUI3_CPPWINRT_GEN` (default `<build directory>/winui3-cppwinrt`) - the output directory of the generated C++/WinRT projection headers.

On Windows the enabler restores the Windows App SDK, C++/WinRT and WebView2 NuGet packages (the NuGet CLI is required), generates the C++/WinRT projection headers (`winrt/*.h`) of the Windows SDK, Windows App SDK and WebView2 metadata with the restored `cppwinrt.exe` (again only when the package versions change) and exposes the `winui3::sdk` target (C++20, `/bigobj`) the native UI links against; the Windows SDK must be present (Visual Studio 2022 with the *Desktop development with C++* workload). The Windows executable is a GUI subsystem one (`WIN32_EXECUTABLE`, the entry point stays the standard `main()`), so no console window opens behind the GUI; its console output (e.g. of `--help`) shows when redirected, e.g. `<executable> --help | more`. On every other host the enabler is a no-op and the stub launch seam is built instead, so the portable code keeps building and testing.

> WinUI 3 with CMake is not the Microsoft default (Visual Studio drives WinUI 3 through MSBuild/.vcxproj). The executable here is an unpackaged, code-only (no XAML markup compiler) WinUI 3 application: `run_winui_application()` bootstraps the Windows App SDK runtime with `MddBootstrapInitialize2()` (the Windows App SDK runtime of the same major.minor version must be installed on the machine, otherwise the bootstrapper offers its download), and the build copies `Microsoft.WindowsAppRuntime.Bootstrap.dll` next to the executable and installs it along with it.

### Tests

`UTEST_WindowConfig`, `UTEST_WinUI3Controller` (unit) and `CTEST_WinUI3` (component) exercise the WinUI free parts through the launch seam, so they run on any platform. They are registered in the Windows `misc/Jenkinsfile` pipeline next to the application tests.
