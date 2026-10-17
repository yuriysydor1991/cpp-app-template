## Implement code straight away!

To proceed the application implementation right away look for the `BlankVulkanRenderer` class' `src/qtvulkan/window/BlankVulkanRenderer.cpp` and/or `BlankVulkanRenderer.h` files: its `startNextFrame()` method records every frame of the `BlankVulkanWindow` (a `QVulkanWindow`), so the Vulkan draw commands of the application go between its render pass begin and end calls.

**But do not forget about the SOLID principles and code decomposing!**

It's preferable to create other directories which would contain implemented components of the application (pipelines, buffers, scenes) and use them from the `BlankVulkanRenderer` class implementation, rather than put all the code inside the renderer class itself.

New Vulkan queries may be introduced as `IDeviceInfoHandler` descendants created by the `DeviceInfoHandlerFactory` (see `src/qtvulkan/device-info`), and the Qt widgets around the Vulkan window are set up in the `Qt6Controller` class.

The `Qt6Controller` class polls the `ApplicationContext::get_stop` flag with a `QTimer` every 100 ms once the window is shown and quits the Qt event loop as soon as the flag is raised, so the Ctrl+C keys combination and the `kill` command close the window and end the process cleanly.
