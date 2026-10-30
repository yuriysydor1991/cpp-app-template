cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSFMLPainterObj OBJECT
  Painter.cpp
)

target_include_directories(
  TemplateSFMLPainterObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateSFMLPainterObj
  PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateSFMLPainterObj
)
