cmake_minimum_required(VERSION 3.13)

include(template-project-MySQLCppConn)

add_library(
  TemplateMySQLCppConnObj OBJECT
  MySQLController.cpp
)

message(STATUS "MySQL_INCLUDE_DIRS: ${MySQL_INCLUDE_DIRS}")
message(STATUS "MySQL_LIBRARIES: ${MySQL_LIBRARIES}")

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
