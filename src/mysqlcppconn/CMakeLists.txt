cmake_minimum_required(VERSION 3.13)

# The legacy JDBC API headers of the MySQL Connector/C++: /usr/include on the
# Debian based OS (libmysqlcppconn-dev), the jdbc subdirectory of the include
# directory for the 8.0+ Connector/C++ builds (FreeBSD, the MySQL repository).
find_path(
  MySQL_INCLUDE_DIRS
  NAMES mysql_driver.h
  PATH_SUFFIXES jdbc mysql-cppconn/jdbc mysql-cppconn-8/jdbc
  DOC "The MySQLCppConn includes path"
)

find_library(
  MySQL_LIBRARIES
  NAMES mysqlcppconn
  DOC "The MySQLCppConn libraries"
)

if (NOT MySQL_INCLUDE_DIRS OR NOT MySQL_LIBRARIES)
  message(
    FATAL_ERROR
    "No MySQL Connector/C++ found. "
    "Install it by using command (GNU/Linux based):\n"
    "sudo apt install -y libmysqlcppconn-dev\n"
    "or point the MySQL_INCLUDE_DIRS and MySQL_LIBRARIES variables to it."
  )
endif()

add_library(
  TemplateMySQLCppConnObj OBJECT
  MySQLController.cpp
)

message(STATUS "MySQL_INCLUDE_DIRS: ${MySQL_INCLUDE_DIRS}")
message(STATUS "MySQL_LIBRARIES: ${MySQL_LIBRARIES}")

target_include_directories(
  TemplateMySQLCppConnObj 
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    ${MySQL_INCLUDE_DIRS}
)

target_include_directories(
  ${PROJECT_BINARY_NAME} 
  PRIVATE ${MySQL_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateMySQLCppConnObj
  ${MySQL_LIBRARIES}
)

add_subdirectory(helpers)
add_subdirectory(sql)
add_subdirectory(tests)
