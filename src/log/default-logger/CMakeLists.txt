cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectDefaultLoggerObj OBJECT
  DefaultLogger.cpp
)

target_include_directories(
  TemplateProjectDefaultLoggerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

# The objects become a part of the project shared library, so they must be
# relocatable and they must follow its hidden visibility: the logger is an
# implementation detail and its symbols would otherwise clash with the
# identically named ones of any other library derived from this template.
set_target_properties(
  TemplateProjectDefaultLoggerObj
  PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  CXX_VISIBILITY_PRESET hidden
)

add_subdirectory(real-default-logger)
add_subdirectory(tests)
