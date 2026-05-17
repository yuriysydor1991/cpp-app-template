## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with Meson, Ninja and Git.

```
sudo apt install -y git g++ meson ninja-build pkg-config
```

The branch ships with optional Meson enablers for several third-party libraries (all OFF by default). Install only what you intend to turn on with the corresponding `-DENABLE_*=true` meson option. See [Meson extra features](/doc/sections/en_US/5-19-meson-extra-features.md) for the full matrix.

```
# libcurl integration (-DENABLE_LIBCURL=true)
sudo apt install -y libcurl4-openssl-dev

# libxml2 integration (-DENABLE_LIBXML2=true)
sudo apt install -y libxml2-dev

# nlohmann_json integration (-DENABLE_NLOHMANN_JSON=true)
sudo apt install -y nlohmann-json3-dev

# OpenCV integration (-DENABLE_OPENCV=true) - includes the preinstalled Haar cascades
sudo apt install -y libopencv-dev opencv-data
```
