cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_CFITSIO
    "Enables the CFITSIO (FITS astronomy image format) library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_CFITSIO)
    return()
endif()

set(TEMPLATE_APP_CFITSIO_GIT "https://github.com/HEASARC/cfitsio.git" CACHE STRING "The CFITSIO library git source repository")
set(TEMPLATE_APP_CFITSIO_GIT_TAG "cfitsio-4.7.0" CACHE STRING "The CFITSIO project git repository tag/branch of interest")

# Every CFITSIO installation ships a cfitsio.pc file, while a CMake package one
# comes with the upstream CMake install only, so the system probe here is a
# pkg-config one instead of the find_package based probe of the enabler
# function used below.
find_package(PkgConfig QUIET)

if (PkgConfig_FOUND)
    pkg_check_modules(CFITSIO QUIET IMPORTED_TARGET GLOBAL cfitsio)
endif()

if (TARGET PkgConfig::CFITSIO)
    message(STATUS "System already contains the CFITSIO ${CFITSIO_VERSION} library")

    add_library(CFITSIO::cfitsio ALIAS PkgConfig::CFITSIO)
else()
    # The fetched sources build and install their own test and helper programs
    # by default, which the project has no use for. Their zlib dependency is a
    # required one, so keep a system zlib available for that path.
    set(TESTS OFF CACHE BOOL "Build the CFITSIO test programs")
    set(UTILS OFF CACHE BOOL "Build the CFITSIO helper programs")

    template_project_default_3rdparty_enabler(
      NAME cfitsio
      GIT_REPOSITORY ${TEMPLATE_APP_CFITSIO_GIT}
      GIT_TAG ${TEMPLATE_APP_CFITSIO_GIT_TAG}
      DISABLE_SYSTEM_PROBE
    )

    # The fetched sources declare the plain cfitsio target, since the
    # namespaced name is written by their install step alone.
    add_library(CFITSIO::cfitsio ALIAS cfitsio)
endif()

# Both of the paths above provide the very same CFITSIO::cfitsio target, so
# link it to your target(s) of interest (e.g. the ${PROJECT_BINARY_NAME}
# executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} CFITSIO::cfitsio)
