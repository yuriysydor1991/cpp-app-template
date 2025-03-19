cmake_minimum_required(VERSION 3.13)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
  TemplateSDL2Obj OBJECT
  SDL2Initer.cpp
)

target_include_directories(
  TemplateSDL2Obj 
  PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL2Obj 
  PRIVATE 
  ${SDL2_LIBRARIES}
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSDL2Obj
)
