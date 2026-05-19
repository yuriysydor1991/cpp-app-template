cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSDL2EventsHandlersObj OBJECT
  EventQuitHandler.cpp
  EventsHandlersFactory.cpp
)

target_include_directories(
  TemplateSDL2EventsHandlersObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL2EventsHandlersObj
  PRIVATE
  SDL2::SDL2
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSDL2EventsHandlersObj
)
