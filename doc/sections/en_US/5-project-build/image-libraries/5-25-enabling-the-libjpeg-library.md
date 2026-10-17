## Enabling the libjpeg library

In order to enable the [libjpeg-turbo](https://libjpeg-turbo.org/) library (the JPG/JPEG image format) for the project by using the installed system one set an `ON` value to the `ENABLE_LIBJPEG` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_LIBJPEG=ON
```

libjpeg-turbo can not be built through the CMake FetchContent (it refuses the `add_subdirectory()` integration), so it is probed from the system exclusively (install `libjpeg-dev` on Debian/Ubuntu, `libjpeg-turbo-devel` on Fedora/RHEL or `jpeg-turbo` on Homebrew and FreeBSD) - there is no FetchContent fallback and the configure stops with an error which names the package when it is missing. See the `cmake/enablers/images/template-project-libjpeg-enabler.cmake` module for the target (`JPEG::JPEG`) to link to your targets of interest.
