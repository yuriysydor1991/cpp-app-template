cmake_minimum_required(VERSION 3.13)

add_library(
  TemplatePgSQLObj OBJECT
  PgSQL.cpp
)

target_include_directories(
  TemplatePgSQLObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplatePgSQLObj pqxx
)

add_subdirectory(helpers)
add_subdirectory(sql)
