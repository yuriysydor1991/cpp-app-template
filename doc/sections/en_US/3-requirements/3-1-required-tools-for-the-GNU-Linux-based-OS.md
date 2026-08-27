## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appCFITSIO` branch additionally probes the system [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) and [WCSLIB](https://www.atnf.csiro.au/people/mcalabre/WCS/) development files with `pkg-config`, so those are worth installing as well:

```
sudo apt install -y pkg-config libcfitsio-dev wcslib-dev
```

On RPM-based distributions the equivalent packages are `pkgconf-pkg-config`, `cfitsio-devel` and `wcslib-devel`; on FreeBSD they are `devel/pkgconf`, `astro/cfitsio` and `astro/wcslib` from `pkg`. Without the CFITSIO one its sources get fetched and built from the Internet instead, which additionally requires the zlib development files (`zlib1g-dev`). The WCSLIB one is mandatory: that library ships an autotools build alone, so there is nothing for `FetchContent` to build.
