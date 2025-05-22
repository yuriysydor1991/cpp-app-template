cmake_minimum_required(VERSION 3.13)

add_library(
  TemplateMySQLHelpersObj OBJECT
  MySQLConnStrMaker.cpp
)

target_include_directories(
  TemplateMySQLHelpersObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${MySQL_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateMySQLHelpersObj
)
