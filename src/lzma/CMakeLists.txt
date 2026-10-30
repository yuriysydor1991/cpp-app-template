cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_LIBLZMA)
  message(
    FATAL_ERROR
    "The src/lzma sources require the liblzma library which is turned off by the "
    "ENABLE_LIBLZMA=OFF parameter. Drop the add_subdirectory(lzma) call from the "
    "src/CMakeLists.txt file together with the whole src/lzma subdirectory and "
    "the liblzma example of the src/app/applications/Application.cpp file to "
    "build the project without the liblzma library."
  )
endif()

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
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectLzmaControllerObj
  PUBLIC LibLZMA::LibLZMA
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE
  TemplateProjectLzmaControllerObj
  LibLZMA::LibLZMA
)

add_subdirectory(tests)
