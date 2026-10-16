cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_PgSQL
  CTEST_PgSQL.cpp
  ${CMAKE_SOURCE_DIR}/src/PgSQLxx/PgSQL.cpp
  ${CMAKE_SOURCE_DIR}/src/PgSQLxx/sql/QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/PgSQLxx/helpers/PgConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_PgSQL
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_PgSQL
  GTest::gtest_main GTest::gmock TemplatePqxx
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_PgSQL
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
