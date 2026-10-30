cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateFirebirdHelpersObj OBJECT
  FbConnStringMaker.cpp
)

target_include_directories(
  TemplateFirebirdHelpersObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateFirebirdHelpersObj
)
