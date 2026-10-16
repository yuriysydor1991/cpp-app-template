cmake_minimum_required(VERSION 3.13)

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
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectZlibControllerObj
  PUBLIC ZLIB::ZLIB
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectZlibControllerObj
  ZLIB::ZLIB
)

add_subdirectory(tests)
