cmake_minimum_required(VERSION 3.13)

# The FetchContent fallback of the liblzma enabler builds the liblzma library
# alone, which keeps it's API headers private to it's own build tree, so they
# get exported (as the installed ones are) and it takes the LibLZMA::LibLZMA
# name of the system wide installed one.
if (NOT TARGET LibLZMA::LibLZMA)
  get_target_property(LIBLZMA_SOURCE_DIR liblzma SOURCE_DIR)
  target_include_directories(
    liblzma SYSTEM INTERFACE
    $<BUILD_INTERFACE:${LIBLZMA_SOURCE_DIR}/src/liblzma/api>
  )
  add_library(LibLZMA::LibLZMA ALIAS liblzma)
endif()

add_library(
  TemplateProjectLzmaControllerObj OBJECT
  LzmaController.cpp
)

target_include_directories(
  TemplateProjectLzmaControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectLzmaControllerObj
  PUBLIC LibLZMA::LibLZMA
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectLzmaControllerObj
  LibLZMA::LibLZMA
)

add_subdirectory(tests)
