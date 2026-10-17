## Enabling the libavif library (AVIF)

In order to enable the [libavif](https://github.com/AOMediaCodec/libavif) library (the AVIF / AV1 image format) for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_LIBAVIF` CMake variable.

```
# Inside the source root directory

cmake -S . -B build -DENABLE_LIBAVIF=ON
```

A codec is required to actually encode/decode AVIF; for the FetchContent build enable one with the system installed codec library (e.g. `-DAVIF_CODEC_AOM=SYSTEM` or `-DAVIF_CODEC_DAV1D=SYSTEM`) or with `LOCAL` to fetch and build the codec as well. The FetchContent build leaves the optional libyuv acceleration off (`AVIF_LIBYUV=OFF`), set `-DAVIF_LIBYUV=SYSTEM` to use the system installed one. See the `cmake/enablers/images/template-project-libavif-enabler.cmake` module for the target (`avif`) to link to your targets of interest.
