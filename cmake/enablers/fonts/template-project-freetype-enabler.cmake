cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_FREETYPE
    "Enables the FreeType (TrueType/OpenType font rasterization) library for the project usage through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_FREETYPE)
    return()
endif()

# original repo @ https://gitlab.freedesktop.org/freetype/freetype.git
set(TEMPLATE_APP_FREETYPE_GIT "https://github.com/freetype/freetype.git" CACHE STRING "The FreeType library git source repository")
set(TEMPLATE_APP_FREETYPE_GIT_TAG "VER-2-14-3" CACHE STRING "The FreeType project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME Freetype
  GIT_REPOSITORY ${TEMPLATE_APP_FREETYPE_GIT}
  GIT_TAG ${TEMPLATE_APP_FREETYPE_GIT_TAG}
)

# Give the FetchContent built freetype target the name of a system install and,
# as with one, keep the project warnings off its headers.
if (NOT TARGET Freetype::Freetype)
  add_library(Freetype::Freetype ALIAS freetype)
  set_target_properties(freetype PROPERTIES SYSTEM ON)
endif()

# Link the following FreeType target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(Freetype): Freetype::Freetype
#   - FetchContent source build:                  Freetype::Freetype
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} Freetype::Freetype)
