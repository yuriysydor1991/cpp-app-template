cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectFreesoundResourcesObj OBJECT
  FreesoundResourcePath.cpp
  FreesoundQtResourcePath.cpp
  FreesoundGResourcePath.cpp
)

target_include_directories(
  TemplateProjectFreesoundResourcesObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectFreesoundResourcesObj
)
