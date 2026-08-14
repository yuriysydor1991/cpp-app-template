cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectRealDefaultLoggerObj OBJECT
  RealDefaultLogger.cpp
)

target_include_directories(
  TemplateProjectRealDefaultLoggerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The objects become a part of the project shared library as well.
set_target_properties(
  TemplateProjectRealDefaultLoggerObj
  PROPERTIES POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectRealDefaultLoggerObj
)
