## Полотно GPU-рендерингу Direct3D для WinUI 3

Ця гілка додає до головного вікна [інтеграції WinUI 3 + C++/WinRT](/doc/sections/uk_UA/4-project-structure/4-9-winui3-cppwinrt-integration.md) полотно для GPU-рендерингу - відповідник віджета GLArea інших гілок GLArea для WinUI 3. WinUI 3 не має власного OpenGL: її поверхнею для власного GPU-рендерингу є XAML-елемент [SwapChainPanel](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.controls.swapchainpanel), яким керує [Direct3D 11](https://learn.microsoft.com/windows/win32/direct3d11/atoc-dx-graphics-direct3d-11). **Лише Windows.**

### Структура

- `src/winui3/gl-area/GLTriangleArea.{h,cpp}` - володіє елементом `SwapChainPanel`, який `WinUI3MainWindow` розміщує під своїм вітальним текстом (320x240), і перебудовує ланцюжок обміну (swap chain) Direct3D за кожної події `SizeChanged` панелі.
- `src/winui3/gl-area/RenderState.{h,cpp}` - пристрій Direct3D 11, композиційний ланцюжок обміну, прив'язаний до панелі через `ISwapChainPanelNative`, і подання цілі рендерингу (render target view). Обробник `SizeChanged` утримує його, тож він існує, доки панель лишається у візуальному дереві.

`RenderState::render()` очищує задній буфер чорним кольором і показує його, лишаючи порожнє полотно. Циклу рендерингу немає: полотно перемальовується лише тоді, коли панель отримує новий розмір. Додай власні команди малювання Direct3D до `render()` (а свої ресурси створюй у `ensure_device()`/`create_swapchain()`) і викликай її з обробника [CompositionTarget::Rendering](https://learn.microsoft.com/windows/windows-app-sdk/api/winrt/microsoft.ui.xaml.media.compositiontarget.rendering), щоб анімувати сцену. Обробку DPI (масштабу композиції) пропущено, щоб відправна точка лишалася мінімальною.

### Збирання

Об'єктна бібліотека `src/winui3/gl-area` збирається лише на Windows, разом із головним вікном, якому вона належить, і лінкується з бібліотеками імпорту `d3d11` і `dxgi` з Windows SDK. Поза Windows вона лишається поза збиранням разом з рештою нативного UI, тож платформонезалежні частини та їхні тести збираються й виконуються як і раніше.
