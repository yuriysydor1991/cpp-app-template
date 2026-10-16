cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_PgConnStringMaker
  UTEST_PgConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/PgSQLxx/helpers/PgConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_PgConnStringMaker
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_PgConnStringMaker
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PgConnStringMaker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
