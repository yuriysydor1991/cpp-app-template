cmake_minimum_required(VERSION 3.13)

# The branch includes it ahead of the src subdirectory as well, so the second
# include of the feature-enabler-post.cmake probes nothing again.
include_guard(GLOBAL)

option(
    ENABLE_ZLIB
    "Enables the zlib compression library (deflate, gzip, zip) for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_ZLIB)
    return()
endif()

set(TEMPLATE_APP_ZLIB_GIT "https://github.com/madler/zlib.git" CACHE STRING "The zlib library git source repository")
set(TEMPLATE_APP_ZLIB_GIT_TAG "v1.3.1" CACHE STRING "The zlib project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME ZLIB
  GIT_REPOSITORY ${TEMPLATE_APP_ZLIB_GIT}
  GIT_TAG ${TEMPLATE_APP_ZLIB_GIT_TAG}
)

# Link one of the following zlib targets to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(ZLIB): ZLIB::ZLIB
#   - FetchContent source build:              zlibstatic (static) or zlib (shared)
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE ZLIB::ZLIB)
#
# See doc/sections/en_US/5-project-build/compression/5-23-enabling-the-zlib-library.md (and the uk_UA copy)
# for copy-paste C++ usage examples: one-shot in-memory compression, gzip (.gz)
# files, raw deflate / zlib / gzip stream selection via windowBits, and a note
# on .zip archives via minizip.
