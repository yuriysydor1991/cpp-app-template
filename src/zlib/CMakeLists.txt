cmake_minimum_required(VERSION 3.13)

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
