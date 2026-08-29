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

# The objects become a part of the project shared library, so they must be
# relocatable and they must follow its hidden visibility: the logger is an
# implementation detail and its symbols would otherwise clash with the
# identically named ones of any other library derived from this template.
set_target_properties(
  TemplateProjectRealDefaultLoggerObj
  PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  CXX_VISIBILITY_PRESET hidden
)
