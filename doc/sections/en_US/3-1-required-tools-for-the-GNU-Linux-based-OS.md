## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

All necessary development packages for the GTKmm-4.0:

```
sudo apt install -y pkg-config libgtkmm-4.0-dev libglib2.0-dev-bin
```

The Vulkan loader and headers used for the physical device enumeration (plus a
runtime driver, e.g. the Mesa ones, so the enumeration reports a device):

```
sudo apt install -y libvulkan-dev mesa-vulkan-drivers
```

To be able to develop UI in the specialized [Glade](https://en.wikipedia.org/wiki/Glade_Interface_Designer) IDE install it with the command:

```
sudo apt install -y glade
```
