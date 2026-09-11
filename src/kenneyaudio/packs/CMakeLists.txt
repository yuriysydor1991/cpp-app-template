cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectKenneyPacksObj OBJECT
  KenneyPack.cpp
  KenneyPacks.cpp
)

target_include_directories(
  TemplateProjectKenneyPacksObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectKenneyPacksObj
)
