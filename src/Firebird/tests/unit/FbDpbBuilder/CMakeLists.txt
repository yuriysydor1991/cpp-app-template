cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FbDpbBuilder
  UTEST_FbDpbBuilder.cpp
  ${CMAKE_SOURCE_DIR}/src/Firebird/driver/FbDpbBuilder.cpp
)

target_include_directories(
  UTEST_FbDpbBuilder
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FbDpbBuilder
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FbDpbBuilder
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
