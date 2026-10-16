cmake_minimum_required(VERSION 3.13)

# The libpqxx ships a pkg-config file on every supported OS, which also brings
# it's include directory (/usr/local/include on FreeBSD).
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

# The shared libpqxx 7.10.0 of Ubuntu 26.04 frees it's pqxx::type_name strings
# twice at the program exit (abort), so the static archive is linked whenever
# the OS ships one.
find_library(PQXX_STATIC_LIBRARY libpqxx.a HINTS ${PQXX_LIBRARY_DIRS})

add_library(TemplatePqxx INTERFACE)

if(PQXX_STATIC_LIBRARY)
  pkg_check_modules(PQ REQUIRED IMPORTED_TARGET libpq)
  target_include_directories(TemplatePqxx INTERFACE ${PQXX_INCLUDE_DIRS})
  target_link_libraries(
    TemplatePqxx INTERFACE ${PQXX_STATIC_LIBRARY} PkgConfig::PQ
  )
else()
  target_link_libraries(TemplatePqxx INTERFACE PkgConfig::PQXX)
endif()

message(STATUS "libpqxx: ${PQXX_VERSION} ${PQXX_STATIC_LIBRARY}")

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

target_link_libraries(TemplatePgSQLObj TemplatePqxx)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplatePgSQLObj TemplatePqxx
)

add_subdirectory(helpers)
add_subdirectory(sql)
add_subdirectory(tests)
