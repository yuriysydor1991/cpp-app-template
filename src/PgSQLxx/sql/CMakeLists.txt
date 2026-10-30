cmake_minimum_required(VERSION 3.13)

add_library(
  TemplatePgSQLxxSQLObj OBJECT
  QueryMaker.cpp
)

target_include_directories(
  TemplatePgSQLxxSQLObj 
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplatePgSQLxxSQLObj
)
