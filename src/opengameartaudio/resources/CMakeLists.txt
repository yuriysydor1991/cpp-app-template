cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectOpenGameArtResourcesObj OBJECT
  OpenGameArtResourcePath.cpp
  OpenGameArtQtResourcePath.cpp
  OpenGameArtGResourcePath.cpp
)

target_include_directories(
  TemplateProjectOpenGameArtResourcesObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenGameArtResourcesObj
)
