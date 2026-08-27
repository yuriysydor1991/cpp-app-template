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

### The context

Both of the custom components operate by the `cfitsioi::CFITSIOContext` class of the [src/CFITSIO/CFITSIOContext.h](/src/CFITSIO/CFITSIOContext.h) file. It is a plain data holder, declared the very way the `app::ApplicationContext` is: private members reachable through a `get_` and a `set_` prefixed access methods pair alone.

| Field | What holds it |
| --- | --- |
| `path` | the FITS file to read or to write |
| `image_size` | the image width and height, refilled on every read |
| `pixels` | the image pixels, read into and written out of |
| `header` | the FITS keyrecords string the WCS parser takes |
| `keywords` | the text valued header keywords, by their names |
| `numeric_keywords` | the header keywords the write puts in unquoted |
| `hdu_count` | the blocks the read file is built of |
| `read_header_only` | raise it to read the header and skip the image |
| `write_header_only` | raise it to update the header of an existing file |

The `get_pixels` and the `get_keywords` accessors hand a modifiable reference out, so the controller reads straight into the context and copies no whole image on the way.

A read fills the `keywords` alone, since a keyword arrives out of a file as it's text; the `numeric_keywords` are the write side of the pair, holding the values that must reach the header unquoted, the way the WCS parsers need them.

An instance travels from the CFITSIO component to the WCSLIB one carrying the data alone, so neither of the two components holds a reference to the other.

### The controller

The whole surface of the `cfitsioi::CFITSIOController` class of the [src/CFITSIO/CFITSIOController.h](/src/CFITSIO/CFITSIOController.h) file is a `read` and a `write` call, both of them taking a single context and nothing else: every parameter of an operation and every result of it lives in that context.

| Call | What it does | The CFITSIO calls behind it |
| --- | --- | --- |
| `read` | fills the context out of the file it points at | `fits_open_file`, `fits_get_num_hdus`, `fits_hdr2str`, `fits_get_hdrspace`, `fits_read_keyn`, `fits_read_key`, `fits_get_img_param`, `fits_read_img`, `fits_close_file` |
| `write` | writes the context out into the file it points at | `fits_create_file`, `fits_create_img`, `fits_write_img`, `fits_update_key`, `fits_close_file` |
| `last_error` | describes the status the failed call left behind | `fits_get_errstatus` |

The file gets opened and closed inside a call, so an instance holds no data and no file of it's own in between. A whole write creates the image anew and overwrites an already existing file, while a header only one opens that file and updates it's keywords in place.

Nothing throws: both of the calls report their outcome through the return value and leave the CFITSIO status code of the failed call in the `last_status` accessor.

```
auto ctx = cfitsioi::CFITSIOContext::create();
auto fits = cfitsioi::CFITSIOController::create();

ctx->set_path("/tmp/image.fits");
ctx->set_image_size({8, 4});
ctx->set_pixels(cfitsioi::CFITSIOContext::pixels_buffer(8 * 4, 42.0));
ctx->set_keywords({{"OBJECT", "M31"}});
ctx->set_numeric_keywords({{"CRVAL1", 202.4695}});

fits->write(ctx);

auto reading = cfitsioi::CFITSIOContext::create();

reading->set_path("/tmp/image.fits");

fits->read(reading);

const auto& pixels = reading->get_pixels();
const auto [width, height] = reading->get_image_size();
const auto object = reading->get_keywords().at("OBJECT");
```

A read fills the context with the whole header as the keyrecords string the FITS WCS parsers take, so see [Enabling the WCSLIB library (FITS WCS)](/doc/sections/en_US/5-project-build/image-libraries/5-39-enabling-the-wcslib-library.md) for the component that maps those pixels onto the sky.

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file reads the FITS image the `--image` (or `-i`) command line parameter points at and reports about it through the project logger, so replace it's body with your own FITS handling code.
