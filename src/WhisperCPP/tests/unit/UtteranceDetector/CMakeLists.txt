cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_UtteranceDetector
  UTEST_UtteranceDetector.cpp
  ${CMAKE_SOURCE_DIR}/src/WhisperCPP/UtteranceDetector.cpp
)

target_include_directories(
  UTEST_UtteranceDetector
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_UtteranceDetector
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_UtteranceDetector
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
