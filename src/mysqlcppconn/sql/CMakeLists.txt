cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateMySQLQueryMakerObj OBJECT
  QueryMaker.cpp
)

target_include_directories(
  TemplateMySQLQueryMakerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${MySQL_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateMySQLQueryMakerObj
)
