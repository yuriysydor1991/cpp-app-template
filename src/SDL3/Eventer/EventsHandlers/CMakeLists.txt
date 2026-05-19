cmake_minimum_required(VERSION 3.13)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
  TemplateSDL3EventsHandlersObj OBJECT
  EventQuitHandler.cpp
  EventsHandlersFactory.cpp
)

target_include_directories(
  TemplateSDL3EventsHandlersObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL3EventsHandlersObj
  PRIVATE
  SDL3::SDL3
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSDL3EventsHandlersObj
)
