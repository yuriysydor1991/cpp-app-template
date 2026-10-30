cmake_minimum_required(VERSION 3.13)

include(template-project-make-SQLiteCpp-available)

add_library(
  TemplateSQLiteControllerObj OBJECT
  SQLiteController.cpp
)

get_target_property(SQLITECPP_INCLUDE_DIRS SQLiteCpp INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(
  TemplateSQLiteControllerObj 
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
    ${SQLITECPP_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateSQLiteControllerObj
  SQLiteCpp
  sqlite3
  pthread
  dl
)

add_subdirectory(sqlmaker)
add_subdirectory(tests)
