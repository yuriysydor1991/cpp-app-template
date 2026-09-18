cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_STB_TRUETYPE
    "Enables the stb_truetype (single header font rasterization) library for the project usage through FetchContent by internet"
    OFF
)

if (NOT ENABLE_STB_TRUETYPE)
    return()
endif()

set(TEMPLATE_APP_STB_GIT "https://github.com/nothings/stb.git" CACHE STRING "The stb libraries git source repository")
set(TEMPLATE_APP_STB_GIT_TAG "master" CACHE STRING "The stb project git repository tag/branch of interest")

# stb ships headers only, with neither a build nor a package to probe for
template_project_default_3rdparty_enabler(
  NAME stb
  GIT_REPOSITORY ${TEMPLATE_APP_STB_GIT}
  GIT_TAG ${TEMPLATE_APP_STB_GIT_TAG}
  DISABLE_SYSTEM_PROBE
)

FetchContent_GetProperties(stb)

# SYSTEM keeps the project warnings off the stb code compiled inside a project source
add_library(stb_truetype INTERFACE)
target_include_directories(stb_truetype SYSTEM INTERFACE "${stb_SOURCE_DIR}")

# Link the following stb_truetype target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - FetchContent source download: stb_truetype
# and define STB_TRUETYPE_IMPLEMENTATION in exactly one source file before it
# includes <stb_truetype.h>. For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} stb_truetype)
