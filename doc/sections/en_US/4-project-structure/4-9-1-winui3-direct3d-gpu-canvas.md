## WinUI 3 Direct3D GPU canvas

This branch adds a GPU rendering canvas to the main window of the [WinUI 3 + C++/WinRT integration](/doc/sections/en_US/4-project-structure/4-9-winui3-cppwinrt-integration.md) - the WinUI 3 counterpart of the GLArea widget of the other GLArea branches. WinUI 3 has no native OpenGL: its surface for custom GPU rendering is the [SwapChainPanel](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.swapchainpanel) XAML control driven by [Direct3D 11](https://learn.microsoft.com/windows/win32/direct3d11/atoc-dx-graphics-direct3d-11). **Windows only.**

### Layout

- `src/winui3/gl-area/GLTriangleArea.{h,cpp}` - owns the `SwapChainPanel` the `WinUI3MainWindow` places below its welcome text (320x240), and rebuilds the Direct3D swap chain on every `SizeChanged` event of the panel.
- `src/winui3/gl-area/RenderState.{h,cpp}` - the Direct3D 11 device, the composition swap chain bound to the panel through `ISwapChainPanelNative` and the render target view. The `SizeChanged` handler keeps it alive, so it lives as long as the panel stays in the visual tree.

`RenderState::render()` clears the back buffer to black and presents it, leaving a blank canvas. There is no render loop: the canvas is drawn again only when the panel gets a new size. Add your Direct3D draw commands to `render()` (and create your resources in `ensure_device()`/`create_swapchain()`), and call it from a [CompositionTarget::Rendering](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.media.compositiontarget.rendering) handler to animate the scene. The DPI (composition scale) handling is left out to keep the starting point minimal.

### Building it

The `src/winui3/gl-area` object library is built on Windows only, along with the main window it belongs to, and links the `d3d11` and `dxgi` import libraries of the Windows SDK. Off Windows it stays out of the build together with the rest of the native UI, so the platform independent parts and their tests build and run as before.
