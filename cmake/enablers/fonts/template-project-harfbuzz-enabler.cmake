cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_HARFBUZZ
    "Enables the HarfBuzz (text shaping) library for the project usage through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_HARFBUZZ)
    return()
endif()

set(TEMPLATE_APP_HARFBUZZ_GIT "https://github.com/harfbuzz/harfbuzz.git" CACHE STRING "The HarfBuzz library git source repository")
set(TEMPLATE_APP_HARFBUZZ_GIT_TAG "14.4.0" CACHE STRING "The HarfBuzz project git repository tag of interest")

# the FreeType glue (<hb-ft.h>) of a FetchContent build: on its own HarfBuzz
# turns it on only for a fetched FreeType, not for a system installed one
if (ENABLE_FREETYPE)
  set(HB_HAVE_FREETYPE ON CACHE BOOL "Build the HarfBuzz FreeType interop helpers")
endif()

template_project_default_3rdparty_enabler(
  NAME harfbuzz
  GIT_REPOSITORY ${TEMPLATE_APP_HARFBUZZ_GIT}
  GIT_TAG ${TEMPLATE_APP_HARFBUZZ_GIT_TAG}
)

# Give the FetchContent built harfbuzz target the name of a system install and,
# as with one, keep the project warnings off its headers.
if (NOT TARGET harfbuzz::harfbuzz)
  add_library(harfbuzz::harfbuzz ALIAS harfbuzz)
  set_target_properties(harfbuzz PROPERTIES SYSTEM ON)
endif()

# Link the following HarfBuzz target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(harfbuzz): harfbuzz::harfbuzz
#   - FetchContent source build:                  harfbuzz::harfbuzz
#     (with the hb-ft.h FreeType glue when ENABLE_FREETYPE is ON too)
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} harfbuzz::harfbuzz)
