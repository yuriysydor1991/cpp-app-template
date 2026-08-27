cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_WCSLIB
    "Enables the WCSLIB (the FITS World Coordinate System) library for the project (system installation only)"
    ON
)

if (NOT ENABLE_WCSLIB)
    return()
endif()

# WCSLIB ships an autotools build only (no upstream CMake project to fetch and
# no CMake package config), so it is probed from the system exclusively through
# it's pkg-config file - install wcslib-dev (Debian/Ubuntu), wcslib-devel
# (Fedora/openSUSE) or astro/wcslib (FreeBSD) on the host.
find_package(PkgConfig REQUIRED)

pkg_check_modules(WCSLIB REQUIRED IMPORTED_TARGET GLOBAL wcslib)

message(STATUS "WCSLIB ${WCSLIB_VERSION} found: ${WCSLIB_INCLUDE_DIRS}")

add_library(WCSLIB::wcslib ALIAS PkgConfig::WCSLIB)

# Link the WCSLIB::wcslib target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} WCSLIB::wcslib)
