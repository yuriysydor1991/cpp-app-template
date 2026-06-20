## Enabling the zlib library

In order to enable the [zlib](https://www.zlib.net/) compression library (deflate, gzip, zip) for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_ZLIB` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_ZLIB=ON
```

See the `cmake/enablers/compression/template-project-zlib-enabler.cmake` module for the targets (`ZLIB::ZLIB` for a system install, `zlibstatic`/`zlib` for the FetchContent build) to link to your targets of interest.
