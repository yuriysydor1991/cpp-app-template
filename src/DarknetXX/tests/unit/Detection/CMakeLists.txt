cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Detection
  UTEST_Detection.cpp
  ${CMAKE_SOURCE_DIR}/src/DarknetXX/Detection.cpp
)

target_include_directories(
  UTEST_Detection
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Detection
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Detection
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
