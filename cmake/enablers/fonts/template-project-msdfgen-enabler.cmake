cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_MSDFGEN
    "Enables the msdfgen (multi-channel signed distance field glyphs) library for the project usage through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_MSDFGEN)
    return()
endif()

set(TEMPLATE_APP_MSDFGEN_GIT "https://github.com/Chlumsky/msdfgen.git" CACHE STRING "The msdfgen library git source repository")
set(TEMPLATE_APP_MSDFGEN_GIT_TAG "v1.13" CACHE STRING "The msdfgen project git repository tag of interest")

# msdfgen defaults that break a plain consumer build: the vcpkg toolchain, the
# Skia library, the tinyxml2 (SVG input) and the libpng (PNG output)
# dependencies, and the standalone generator executable next to the library.
set(MSDFGEN_USE_VCPKG OFF CACHE BOOL "Use vcpkg package manager to link project dependencies")
set(MSDFGEN_USE_SKIA OFF CACHE BOOL "Build with the Skia library")
set(MSDFGEN_DISABLE_SVG ON CACHE BOOL "Disable SVG support")
set(MSDFGEN_DISABLE_PNG ON CACHE BOOL "Disable PNG support")
set(MSDFGEN_BUILD_STANDALONE OFF CACHE BOOL "Build the msdfgen standalone executable")

template_project_default_3rdparty_enabler(
  NAME msdfgen
  GIT_REPOSITORY ${TEMPLATE_APP_MSDFGEN_GIT}
  GIT_TAG ${TEMPLATE_APP_MSDFGEN_GIT_TAG}
)

# As with a system install, keep the project warnings off the headers of the
# FetchContent build.
if (TARGET msdfgen-ext)
  set_target_properties(msdfgen-core msdfgen-ext PROPERTIES SYSTEM ON)
endif()

# The msdfgen font loading depends on FreeType: keep ENABLE_FREETYPE on (or a
# system FreeType available) so the dependency resolves.
#
# Link the following msdfgen target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(msdfgen): msdfgen::msdfgen
#   - FetchContent source build:                 msdfgen::msdfgen
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} msdfgen::msdfgen)
