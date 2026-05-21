## Cocoa (AppKit) + Objective-C++ integration

This branch fast-starts a native macOS desktop application written with the [Cocoa](https://developer.apple.com/documentation/appkit) / AppKit framework in [Objective-C++](https://en.wikipedia.org/wiki/Objective-C%2B%2B) (`.mm` translation units that mix C++ and Objective-C). Cocoa is a **macOS-only** UI stack, so the component keeps everything that can be platform independent platform independent and hides the native UI behind a single launch seam.

### Requirements

A macOS host with the Xcode command line tools (`xcode-select --install`) provides clang with the Objective-C++ frontend and the Cocoa framework. CMake (>= 3.13) drives the build natively: it compiles `.mm` as Objective-C++ and links `-framework Cocoa`.

### Layout

- `src/cocoa/CocoaIniter.{h,cpp}` - the Cocoa free orchestration object. It validates the application context and launches the GUI through the `run_cocoa_application()` launch seam (`src/cocoa/CocoaLauncher.h`). Builds and is unit/component tested on every platform.
- `src/cocoa/helpers/WindowConfig.{h,cpp}` - a Cocoa independent holder for the window title / texts / sizes, unit tested in isolation.
- `src/cocoa/app/CocoaApp.mm` - the native AppKit application delegate and the real `run_cocoa_application()` definition. **macOS only.**
- `src/cocoa/app/CocoaAppStub.cpp` - a non-Apple definition of `run_cocoa_application()` so the executable still builds, links and runs (printing a notice) off macOS. The real Cocoa window only opens on macOS.
- `src/cocoa/main-window/CocoaMainWindow.{h,mm}` - the AppKit `NSWindow`, built programmatically (no .xib/.nib file) from `WindowConfig`. **macOS only.**

`Application::run()` (`src/app/Application.cpp`) creates a `CocoaIniter` and delegates to it, exactly like the other GUI branches delegate to their initer.

### Building it

The native UI is set up by the CMake enabler `cmake/enablers/template-project-Cocoa-enabler.cmake`, controlled by `ENABLE_COCOA` (default `ON`). On macOS it enables the `OBJCXX` language, finds the Cocoa framework and exposes the `cocoa::sdk` target (linked with `-framework Cocoa`, compiled with `-fobjc-arc` for Automatic Reference Counting). On every other host it is a no-op and the stub launch seam is built instead, so the portable code keeps building and testing. On macOS the executable is produced as a `.app` bundle (`MACOSX_BUNDLE`).

### Packaging

`cmake/enablers/packagers/template-project-macos-package-enabler.cmake` (configure with `-DENABLE_MACOS_PACKAGE=ON`) wires up two CPack generators: `DragNDrop` (a `.dmg` disk image with the `.app` and a drag-to-Applications link) and `productbuild` (a `.pkg` installer). Run `cpack` in the build directory to produce both. Set `TEMPLATE_PROJECT_PRODUCTBUILD_IDENTITY` to a *Developer ID Installer* identity to sign the `.pkg`.

### Tests

`UTEST_WindowConfig`, `UTEST_CocoaIniter` (unit) and `CTEST_Cocoa` (component) exercise the Cocoa free parts through the launch seam, so they run on any platform. They are registered in the macOS `misc/Jenkinsfile` pipeline next to the application tests.
