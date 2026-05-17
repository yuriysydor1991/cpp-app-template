## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appOpenCV` branch additionally relies on the system [OpenCV](https://opencv.org/) development files and on the data package that ships the preinstalled Haar cascades, so those have to be installed as well:

```
sudo apt install -y libopencv-dev opencv-data
```

On RPM-based distributions the equivalent packages are `opencv-devel` and `opencv-data`; on FreeBSD they are `graphics/opencv` and `graphics/opencv-data` from `pkg`.
