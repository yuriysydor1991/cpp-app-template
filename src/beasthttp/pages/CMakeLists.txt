cmake_minimum_required(VERSION 3.13)

add_library(
  TemplatePagesBuildersObj OBJECT
  PageBuilder.cpp
)

target_include_directories(
  TemplatePagesBuildersObj 
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplatePagesBuildersObj
  PUBLIC Boost::boost
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplatePagesBuildersObj
)
