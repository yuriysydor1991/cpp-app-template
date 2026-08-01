cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_QueryMaker
  UTEST_QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/Firebird/sql/QueryMaker.cpp
)

target_include_directories(
  UTEST_QueryMaker
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_QueryMaker
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_QueryMaker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
