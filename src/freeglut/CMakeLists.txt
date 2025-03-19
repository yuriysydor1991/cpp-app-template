cmake_minimum_required(VERSION 3.13)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
  TemplateFreeGlutObj OBJECT
  FreeGlutIniter.cpp
)

target_include_directories(
  TemplateFreeGlutObj
  PRIVATE 
  ${GLUT_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateFreeGlutObj
  PRIVATE ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateFreeGlutObj
)
