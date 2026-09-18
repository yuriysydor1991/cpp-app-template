cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_FONTCONFIG
    "Enables the Fontconfig (system font lookup and matching) library for the project (system installation only)"
    OFF
)

if (NOT ENABLE_FONTCONFIG)
    return()
endif()

# Fontconfig ships the Meson and the autotools builds only (no upstream CMake /
# FetchContent target), so it is probed from the system exclusively - install
# libfontconfig-dev (Debian/Ubuntu), fontconfig-devel (Fedora/openSUSE) or
# fontconfig (Arch) on the host.
find_package(Fontconfig REQUIRED)

message(STATUS "Fontconfig ${Fontconfig_VERSION} found: ${Fontconfig_INCLUDE_DIRS}")

# Link the following Fontconfig target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(Fontconfig): Fontconfig::Fontconfig
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} Fontconfig::Fontconfig)
