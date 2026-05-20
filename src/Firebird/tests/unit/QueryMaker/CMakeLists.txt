cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FirebirdQueryMaker
  UTEST_QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/Firebird/sql/QueryMaker.cpp
)

target_include_directories(
  UTEST_FirebirdQueryMaker
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FirebirdQueryMaker
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FirebirdQueryMaker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
