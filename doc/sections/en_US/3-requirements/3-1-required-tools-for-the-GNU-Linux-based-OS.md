## Required tools for the GNU/Linux based OS

In order to build minimum template project install the GCC C++ compiler with CMake and Git.

```
sudo apt install -y git g++ cmake
```

The `appCFITSIO` branch additionally probes the system [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) development files with `pkg-config`, so those two are worth installing as well:

```
sudo apt install -y pkg-config libcfitsio-dev
```

On RPM-based distributions the equivalent packages are `pkgconf-pkg-config` and `cfitsio-devel`; on FreeBSD they are `devel/pkgconf` and `astro/cfitsio` from `pkg`. Without them the CFITSIO sources get fetched and built from the Internet instead, which additionally requires the zlib development files (`zlib1g-dev`).
