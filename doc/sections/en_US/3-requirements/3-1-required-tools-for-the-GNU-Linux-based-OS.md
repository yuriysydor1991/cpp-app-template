## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appDarknetXX` branch additionally needs the development files of the [OpenCV](https://opencv.org/), the [zlib](https://zlib.net/) and the [nlohmann JSON](https://github.com/nlohmann/json) libraries the network core of the [darknetxx](https://github.com/yuriysydor1991/darknetxx) builds with:

```
sudo apt install -y libopencv-dev zlib1g-dev nlohmann-json3-dev
```

The `scripts/packages/install-ubuntu.sh` (or the `scripts/packages/install-debian.sh`) script installs them together with the rest of the required packages. On RPM-based distributions the equivalent packages are `opencv-devel`, `zlib-devel` and `json-devel`; on FreeBSD they are `graphics/opencv` and `devel/nlohmann-json` from `pkg` (the zlib is a part of the base system). The configure fetches the darknetxx sources with the `git` and downloads the network weights, see the [Enabling the darknetxx object detection](/doc/sections/en_US/5-project-build/ai/5-61-enabling-the-darknetxx-object-detection.md) section.
