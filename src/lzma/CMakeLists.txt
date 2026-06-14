cmake_minimum_required(VERSION 3.13)

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
