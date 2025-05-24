cmake_minimum_required(VERSION 3.13)

set(MySQL_INCLUDE_DIRS "/usr/include/cppconn")
set(MySQL_LIBRARIES "mysqlcppconn")

# doesn't work
find_package(MySQL COMPONENTS ConnectorCpp)

add_library(
  TemplateMySQLCppConnObj OBJECT
  MySQLController.cpp
)

target_include_directories(
  TemplateMySQLCppConnObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${MySQL_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateMySQLCppConnObj
  ${MySQL_LIBRARIES}
)

add_subdirectory(helpers)
add_subdirectory(sql)
