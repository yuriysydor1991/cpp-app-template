cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_PgSQL
  UTEST_PgSQL.cpp
  ${CMAKE_SOURCE_DIR}/src/PgSQLxx/PgSQL.cpp
  ${CMAKE_SOURCE_DIR}/src/PgSQLxx/sql/QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/PgSQLxx/helpers/PgConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_PgSQL
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_PgSQL
  GTest::gtest_main GTest::gmock TemplatePqxx
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PgSQL
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
