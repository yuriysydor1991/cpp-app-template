cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_PLplotDevicePicker
  UTEST_PLplotDevicePicker.cpp
  ${PROJECT_SOURCE_DIR}/src/plplot/PLplotDevicePicker.cpp
)

target_include_directories(
  UTEST_PLplotDevicePicker
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_PLplotDevicePicker
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PLplotDevicePicker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
