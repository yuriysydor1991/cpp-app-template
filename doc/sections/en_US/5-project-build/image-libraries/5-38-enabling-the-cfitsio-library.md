## Enabling the CFITSIO library (FITS)

In order to enable the [CFITSIO](https://heasarc.gsfc.nasa.gov/fitsio/) library (the FITS astronomy image format) for the project by using the installed system one or by fetching it through the available connection set an `ON` value to the `ENABLE_CFITSIO` CMake variable (it is the default one for the `appCFITSIO` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_CFITSIO=ON
cmake --build build --target all
```

The [cmake/enablers/images/template-project-cfitsio-enabler.cmake](/cmake/enablers/images/template-project-cfitsio-enabler.cmake) module probes the system installation with `pkg-config`, since every CFITSIO installation ships a `cfitsio.pc` file while a CMake package one comes with the upstream CMake install alone. When no system installation is found the sources of the `TEMPLATE_APP_CFITSIO_GIT_TAG` tag get fetched from the `TEMPLATE_APP_CFITSIO_GIT` repository instead, which requires the zlib development files to be available.

Both of the paths provide the very same `CFITSIO::cfitsio` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} CFITSIO::cfitsio)
```

### The controller

The `cfitsioi::CFITSIOController` class of the [src/CFITSIO/CFITSIOController.h](/src/CFITSIO/CFITSIOController.h) file wraps the main CFITSIO image calls, holding a single open FITS file per instance:

| Method | The CFITSIO call behind it |
| --- | --- |
| `open` | `fits_open_file` |
| `create_image` | `fits_create_file` and `fits_create_img` |
| `close` | `fits_close_file` |
| `get_image_size` | `fits_get_img_param` |
| `get_hdu_count` | `fits_get_num_hdus` |
| `read` | `fits_read_img` |
| `write` | `fits_write_img` |
| `read_keyword` | `fits_read_key` |
| `write_keyword` | `fits_update_key`, with a string and a floating point overload |
| `read_header` | `fits_hdr2str` |
| `last_error` | `fits_get_errstatus` |

Nothing throws: every method reports it's outcome through the return value and leaves the CFITSIO status code of the performed call in the `last_status` accessor.

```
auto fits = cfitsioi::CFITSIOController::create();

fits->create_image("/tmp/image.fits", {8, 4});
fits->write(cfitsioi::CFITSIOController::pixels_buffer(8 * 4, 42.0));
fits->write_keyword("OBJECT", "M31");
fits->close();

fits->open("/tmp/image.fits");

const auto pixels = fits->read();
const auto [width, height] = fits->get_image_size();
```

The `read_header` call hands the whole header over as the keyrecords string the FITS WCS parsers take, so see [Enabling the WCSLIB library (FITS WCS)](/doc/sections/en_US/5-project-build/image-libraries/5-39-enabling-the-wcslib-library.md) for the component that maps those pixels onto the sky.

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file performs that very round-trip, so replace it's body with your own FITS handling code.
