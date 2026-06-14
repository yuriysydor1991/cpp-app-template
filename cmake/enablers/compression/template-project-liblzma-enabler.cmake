cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_LIBLZMA
    "Enables the liblzma (XZ Utils) compression library (.xz / LZMA2, legacy .lzma) for the project usage through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_LIBLZMA)
    return()
endif()

set(TEMPLATE_APP_LIBLZMA_GIT "https://github.com/tukaani-project/xz.git" CACHE STRING "The liblzma (XZ Utils) library git source repository")
set(TEMPLATE_APP_LIBLZMA_GIT_TAG "v5.4.6" CACHE STRING "The liblzma (XZ Utils) project git repository tag of interest")

template_project_default_3rdparty_enabler(
  NAME LibLZMA
  GIT_REPOSITORY ${TEMPLATE_APP_LIBLZMA_GIT}
  GIT_TAG ${TEMPLATE_APP_LIBLZMA_GIT_TAG}
)

# Link one of the following liblzma targets to your target(s) of interest (e.g.
# the ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(LibLZMA): LibLZMA::LibLZMA
#   - FetchContent source build:                 liblzma
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} LibLZMA::LibLZMA)
#
# See doc/sections/en_US/5-34-enabling-the-liblzma-library.md (and the uk_UA
# copy) for copy-paste C++ usage examples: one-shot in-memory .xz compression
# and decompression and streaming compression via lzma_stream.
