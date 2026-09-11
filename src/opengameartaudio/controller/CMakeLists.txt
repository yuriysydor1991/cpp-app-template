cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectOpenGameArtSoundsControllerObj OBJECT
  OpenGameArtSoundsController.cpp
)

target_include_directories(
  TemplateProjectOpenGameArtSoundsControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectOpenGameArtSoundsControllerObj
)
