cmake_minimum_required(VERSION 3.13)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
  TemplateSDL2EventsObj OBJECT
  EventsController.cpp
)

target_include_directories(
  TemplateSDL2EventsObj 
  PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL2EventsObj 
  PRIVATE 
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSDL2EventsObj
)

add_subdirectory(EventsHandlers)
