## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

All necessary development packages for the GTKmm-4.0:

```
sudo apt install -y pkg-config libgtkmm-4.0-dev libglib2.0-dev-bin
```

The Vulkan loader and headers, used both for the physical device enumeration and
for rendering the window contents off-screen with Vulkan and exporting them as a
Linux dma-buf for display in the GTK window (plus a runtime Vulkan driver that
supports dma-buf export, e.g. the Mesa GPU drivers):

```
sudo apt install -y libvulkan-dev mesa-vulkan-drivers
```

The dma-buf display additionally needs GTK / gtkmm 4.14 or newer (for the
`Gdk::DmabufTexture`). With only a software Vulkan driver (e.g. lavapipe), the
dma-buf export is unavailable and the window falls back to a plain black
background.

To be able to develop UI in the specialized [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) IDE install it with the command:

```
sudo apt install -y glade
```
