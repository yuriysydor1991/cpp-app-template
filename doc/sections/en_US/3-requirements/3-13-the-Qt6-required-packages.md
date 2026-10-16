## The Qt6 required packages

In order to be able to use the Qt6 resources install them with command that may look like next (GNU/Linux based OS):

```
# all the Qt6 required packages

sudo apt install -y qt6-base-dev qt6-base-dev-tools
```

This branch reaches Vulkan through the native [Qt6](https://www.qt.io/development/qt-framework/qt6) [QVulkanInstance](https://doc.qt.io/qt-6/qvulkaninstance.html) which lives in the Qt GUI module (`Qt6::Gui`), and hosts the Vulkan window inside a top level Qt widget (`Qt6::Widgets`): only the Qt6 Core, Gui and Widgets modules are used, all of which ship with the `qt6-base-dev` package above - no Qt Quick/QML modules are required.

The Vulkan headers (the core `VkInstance`/`VkPhysicalDevice` types referenced by the sources, located by CMake's `FindVulkan`) are provided by the Vulkan loader development package:

```
sudo apt install -y libvulkan-dev
```

At run time the executable needs a [Vulkan](https://www.vulkan.org/) capable driver (an Installable Client Driver) and a Qt platform plugin that supports Vulkan (for example the `xcb` plugin under an X11 session). On a machine without a discrete GPU the Mesa software rasterizer (lavapipe) provides a usable software device:

```
sudo apt install -y mesa-vulkan-drivers
```

When no usable Vulkan instance can be created (no driver, or a platform plugin without Vulkan support) the executable logs the corresponding error and exits with a non-zero status; otherwise it logs the enumerated physical devices and their properties through its LOGI logging calls.

The Qt6 is mandatory on this branch: the `Application` class runs the `Qt6Controller`, so configuring with the `-DENABLE_QT6=OFF` stops with an error. Take the `app` branch for an application with no Qt6 in it.
