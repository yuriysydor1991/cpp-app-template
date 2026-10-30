cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSDL3PainterObj OBJECT
  Painter.cpp
)

target_include_directories(
  TemplateSDL3PainterObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL3PainterObj
  PRIVATE
  SDL3::SDL3
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateSDL3PainterObj
)
