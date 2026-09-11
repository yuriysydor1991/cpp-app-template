cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectKenneyResourcesObj OBJECT
  KenneyResourcePath.cpp
  KenneyQtResourcePath.cpp
  KenneyGResourcePath.cpp
)

target_include_directories(
  TemplateProjectKenneyResourcesObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectKenneyResourcesObj
)
