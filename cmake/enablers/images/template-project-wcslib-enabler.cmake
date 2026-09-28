cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_WCSLIB
    "Enables the WCSLIB (the FITS World Coordinate System) library for the project usage through system installed one or the one built from the sources fetched by internet"
    ON
)

if (NOT ENABLE_WCSLIB)
    return()
endif()

set(TEMPLATE_APP_WCSLIB_URL "https://www.atnf.csiro.au/computing/software/wcs/wcslib-releases/wcslib-8.9.tar.bz2" CACHE STRING "The WCSLIB library source archive")
set(TEMPLATE_APP_WCSLIB_URL_HASH "SHA256=82ac09ce5091b0bf06cec8f5cdeec1dabe1d06ba5dfb7ff2bdb0c1680488807b" CACHE STRING "The WCSLIB library source archive hash")

# Every WCSLIB installation ships a wcslib.pc file, the one built below
# included, so both of the paths are probed through the pkg-config.
find_package(PkgConfig REQUIRED)

pkg_check_modules(WCSLIB QUIET IMPORTED_TARGET GLOBAL wcslib)

if (TARGET PkgConfig::WCSLIB)
    message(STATUS "System already contains the WCSLIB ${WCSLIB_VERSION} library")
else()
    # WCSLIB ships an autotools build alone (no upstream CMake project to add),
    # so the fetched sources are built by their own configure script into a
    # position independent static library the -pie executable links in.
    template_project_autotools_3rdparty_build(
      NAME wcslib
      URL ${TEMPLATE_APP_WCSLIB_URL}
      URL_HASH ${TEMPLATE_APP_WCSLIB_URL_HASH}
      CONFIGURE_ARGS
        "CFLAGS=-O2 -fPIC"
        --disable-flex
        --disable-fortran
        --disable-shared
        --disable-utils
        --without-pgplot
        --without-cfitsio
    )

    list(APPEND CMAKE_PREFIX_PATH ${TEMPLATE_PROJECT_AUTOTOOLS_INSTALL_DIR})

    pkg_check_modules(WCSLIB REQUIRED IMPORTED_TARGET GLOBAL wcslib)

    message(STATUS "The project wcslib is made available")
endif()

add_library(WCSLIB::wcslib ALIAS PkgConfig::WCSLIB)

# Both of the paths above provide the very same WCSLIB::wcslib target, so link
# it to your target(s) of interest (e.g. the ${PROJECT_BINARY_NAME} executable
# or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} WCSLIB::wcslib)
