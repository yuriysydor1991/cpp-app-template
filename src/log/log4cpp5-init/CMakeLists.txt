cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateLog4Cpp5ControllerObj OBJECT
  Log4Cpp5Init.cpp
)

target_include_directories(
  TemplateLog4Cpp5ControllerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateLog4Cpp5ControllerObj
)
