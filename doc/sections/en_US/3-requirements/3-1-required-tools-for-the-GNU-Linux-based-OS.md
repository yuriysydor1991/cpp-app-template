## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

All necessary development packages for the GTKmm-4.0:

```
sudo apt install -y pkg-config libgtkmm-4.0-dev libglib2.0-dev-bin
```

The Leaflet maps web view is rendered with WebKitGTK, so its development package is required as well:

```
sudo apt install -y libwebkitgtk-6.0-dev
```
