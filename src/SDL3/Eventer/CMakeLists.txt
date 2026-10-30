cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSDL3EventsObj OBJECT
  EventsController.cpp
)

target_include_directories(
  TemplateSDL3EventsObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL3EventsObj
  PRIVATE
  SDL3::SDL3
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateSDL3EventsObj
)

add_subdirectory(EventsHandlers)
