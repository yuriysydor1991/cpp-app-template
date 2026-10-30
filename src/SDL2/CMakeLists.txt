cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateSDL2Obj OBJECT
  SDL2Controller.cpp
  SDL2Context.cpp
  SDL2ContextBuilder.cpp
  OpenGLIniter.cpp
)

target_include_directories(
  TemplateSDL2Obj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateSDL2Obj
  PUBLIC
  SDL2::SDL2
  ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateSDL2Obj
)

add_subdirectory(Painter)
add_subdirectory(Eventer)

if(ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS)
  add_subdirectory(tests)
endif()
