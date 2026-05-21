## WinUI 3 + C++/WinRT integration

This branch fast-starts a [Microsoft WinUI 3](https://learn.microsoft.com/windows/apps/winui/winui3/) desktop application written with [C++/WinRT](https://learn.microsoft.com/windows/uwp/cpp-and-winrt-apis/) on top of the [Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/). WinUI 3 is a **Windows-only** UI stack, so the component keeps everything that can be platform independent platform independent and hides the native UI behind a single launch seam.

### Layout

- `src/winui3/WinUI3Initer.{h,cpp}` - the WinUI free orchestration object. It validates the application context and launches the GUI through the `run_winui_application()` launch seam (`src/winui3/WinUI3Launcher.h`). Builds and is unit/component tested on every platform.
- `src/winui3/helpers/WindowConfig.{h,cpp}` - a WinUI independent holder for the window title / texts / sizes, unit tested in isolation.
- `src/winui3/app/WinUI3App.{h,cpp}` - the native C++/WinRT application object and the real `run_winui_application()` definition. **Windows only.**
- `src/winui3/app/WinUI3AppStub.cpp` - a non-Windows definition of `run_winui_application()` so the executable still builds, links and runs (printing a notice) off Windows. The real WinUI 3 window only opens on Windows.
- `src/winui3/main-window/WinUI3MainWindow.{h,cpp}` - the WinUI 3 window, built programmatically (no XAML file) from `WindowConfig`. **Windows only.**

`Application::run()` (`src/app/Application.cpp`) creates a `WinUI3Initer` and delegates to it, exactly like the other GUI branches delegate to their initer.

### Building it

The native UI is set up by the CMake enabler `cmake/enablers/template-project-WinUI3-enabler.cmake`, controlled by:

- `ENABLE_WINUI3` (default `ON`) - set to `OFF` to drop the WinUI 3 integration.
- `TEMPLATE_APP_WINAPPSDK_VERSION` / `TEMPLATE_APP_CPPWINRT_VERSION` - the Windows App SDK and C++/WinRT NuGet package versions restored on Windows.

On Windows the enabler restores the Windows App SDK + C++/WinRT NuGet packages (the NuGet CLI is required) and exposes the `winui3::sdk` target the native UI links against; the C++/WinRT projection (`cppwinrt.exe`) and the Windows SDK must be present (Visual Studio 2022 with the *Desktop development with C++* workload and the Windows App SDK). On every other host the enabler is a no-op and the stub launch seam is built instead, so the portable code keeps building and testing.

> WinUI 3 with CMake is not the Microsoft default (Visual Studio drives WinUI 3 through MSBuild/.vcxproj). The CMake setup here is a starting point: the portable orchestration, the launch seam, the tests and the WIX packaging are wired up; finish the Windows App SDK / `cppwinrt` projection wiring on a Windows host to produce the native window.

### Tests

`UTEST_WindowConfig`, `UTEST_WinUI3Initer` (unit) and `CTEST_WinUI3` (component) exercise the WinUI free parts through the launch seam, so they run on any platform. They are registered in the Windows `misc/Jenkinsfile` pipeline next to the application tests.
