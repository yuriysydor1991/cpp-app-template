## Enabling the WCSLIB library (FITS WCS)

In order to enable the [WCSLIB](https://www.atnf.csiro.au/people/mcalabre/WCS/) library (the FITS World Coordinate System, which maps the image pixels onto the sky) for the project set an `ON` value to the `ENABLE_WCSLIB` CMake variable (it is the default one for the `appCFITSIO` branch):

```
# Inside the source root directory

cmake -S . -B build -DENABLE_WCSLIB=ON
cmake --build build --target all
```

The [cmake/enablers/images/template-project-wcslib-enabler.cmake](/cmake/enablers/images/template-project-wcslib-enabler.cmake) module probes the system installation with `pkg-config` and provides the `WCSLIB::wcslib` target, so link it to your target(s) of interest:

```
target_link_libraries(${PROJECT_BINARY_NAME} WCSLIB::wcslib)
```

Unlike the [CFITSIO one](/doc/sections/en_US/5-project-build/image-libraries/5-38-enabling-the-cfitsio-library.md), the module has no fetch-from-the-Internet path: WCSLIB ships an autotools build alone, so there is no upstream CMake project for `FetchContent` to build. Install `wcslib-dev` (Debian/Ubuntu), `wcslib-devel` (Fedora/openSUSE) or `astro/wcslib` (FreeBSD) on the host instead.

### The controller

The `wcslibi::WCSLIBController` class of the [src/WCSLIB/WCSLIBController.h](/src/WCSLIB/WCSLIBController.h) file wraps the main WCSLIB calls, holding the coordinate representations of a single FITS header per instance:

| Method | The WCSLIB call behind it |
| --- | --- |
| `parse` | `wcspih` |
| `select` | `wcsset` |
| `release` | `wcsvfree` |
| `to_world` | `wcsp2s` |
| `to_pixel` | `wcss2p` |
| `last_error` | `wcshdr_errmsg` and `wcs_errmsg` |

The `get_representations_count`, `get_axes_count`, `get_axis_type` and `get_rejected_count` accessors read the parsed `wcsprm` structs out, so the WCSLIB headers stay inside the implementation and the including code needs none of them.

Nothing throws: every method reports it's outcome through the return value and leaves the WCSLIB status code of the performed call in the `last_status` accessor.

The controller is a component of it's own and holds no reference to the CFITSIO one, so it takes the header as a plain keyrecords string - the very form the `cfitsioi::CFITSIOController::read_header` call returns:

```
auto fits = cfitsioi::CFITSIOController::create();
auto wcs = wcslibi::WCSLIBController::create();

fits->open("/tmp/image.fits");

wcs->parse(fits->read_header());

const auto world = wcs->to_world({4.5, 2.5});
const auto pixel = wcs->to_pixel(world);
```

A pixel coordinate counts from `1.0`, as the FITS standard does, and a world one carries degrees for the celestial axes. Both of them hold one value per axis of the selected representation, so `get_axes_count` tells how many.

The `app::Application::run` method of the [src/app/applications/Application.cpp](/src/app/applications/Application.cpp) file writes a tangential projection image, reads it's header back and converts the reference pixel of it into the sky coordinates, so replace it's body with your own coordinate handling code.
