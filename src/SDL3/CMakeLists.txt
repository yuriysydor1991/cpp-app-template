cmake_minimum_required(VERSION 3.13)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
  TemplateSDL3Obj OBJECT
  SDL3Initer.cpp
  SDL3Context.cpp
  SDL3ContextBuilder.cpp
  OpenGLIniter.cpp
)

target_include_directories(
  TemplateSDL3Obj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL3Obj
  PRIVATE
  SDL3::SDL3
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateSDL3Obj
  SDL3::SDL3
)

add_subdirectory(Painter)
add_subdirectory(Eventer)

if(ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS)
  add_subdirectory(tests)
endif()
