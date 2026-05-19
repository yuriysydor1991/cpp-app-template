cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSDL3EventsObj OBJECT
  EventsController.cpp
)

target_include_directories(
  TemplateSDL3EventsObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL3EventsObj
  PRIVATE
  SDL3::SDL3
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSDL3EventsObj
)

add_subdirectory(EventsHandlers)
