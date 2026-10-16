cmake_minimum_required(VERSION 3.13)

# The libpqxx ships a pkg-config file on every supported OS, which also brings
# it's include directory (/usr/local/include on FreeBSD).
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

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

target_link_libraries(TemplatePgSQLObj PkgConfig::PQXX)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplatePgSQLObj PkgConfig::PQXX
)

add_subdirectory(helpers)
add_subdirectory(sql)
