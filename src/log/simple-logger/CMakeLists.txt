cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateProjectSimpleLoggerObj OBJECT
  SimpleLogger.cpp
)

target_include_directories(
  TemplateProjectSimpleLoggerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectSimpleLoggerObj
)
