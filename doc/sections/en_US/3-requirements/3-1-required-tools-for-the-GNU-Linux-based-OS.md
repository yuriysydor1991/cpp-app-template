## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The wxWidgets library itself is downloaded and built from source by the CMake FetchContent facility (see the [wxWidgets via FetchContent](/doc/sections/en_US/4-project-structure/4-6-wxwidgets-fetchcontent-integration.md) section), so no wxWidgets package needs to be installed. On GNU/Linux wxWidgets builds its GTK backend, therefore the GTK development packages must be present:

```
sudo apt install -y pkg-config libgtk-3-dev
```
