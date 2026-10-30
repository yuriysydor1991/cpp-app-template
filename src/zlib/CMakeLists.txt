cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_ZLIB)
  message(
    FATAL_ERROR
    "The src/zlib sources require the zlib library which is turned off by the "
    "ENABLE_ZLIB=OFF parameter. Drop the add_subdirectory(zlib) call from the "
    "src/CMakeLists.txt file together with the whole src/zlib subdirectory and "
    "the zlib example of the src/app/applications/Application.cpp file to "
    "build the project without the zlib library."
  )
endif()

# The FetchContent fallback of the zlib enabler builds the zlibstatic library
# alone, so it takes the ZLIB::ZLIB name of the system wide installed one, and
# it's headers are treated as the installed ones are by the project warnings.
if (NOT TARGET ZLIB::ZLIB)
  set_target_properties(zlibstatic PROPERTIES SYSTEM ON)
  add_library(ZLIB::ZLIB ALIAS zlibstatic)
endif()

add_library(
  TemplateProjectZlibControllerObj OBJECT
  ZlibController.cpp
)

target_include_directories(
  TemplateProjectZlibControllerObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectZlibControllerObj
  PUBLIC ZLIB::ZLIB
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE
  TemplateProjectZlibControllerObj
  ZLIB::ZLIB
)

add_subdirectory(tests)
