cmake_minimum_required(VERSION 3.13)

# doesn't work
# find_package(MySQL REQUIRED COMPONENTS ConnectorCpp)

set(MySQL_INCLUDE_DIRS "/usr/include/cppconn")
set(MySQL_LIBRARIES "mysqlcppconn")

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
