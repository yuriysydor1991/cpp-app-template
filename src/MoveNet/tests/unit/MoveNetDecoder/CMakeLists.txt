cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MoveNetDecoder
  UTEST_MoveNetDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/MoveNet/MoveNetDecoder.cpp
)

target_include_directories(
  UTEST_MoveNetDecoder
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_MoveNetDecoder
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_MoveNetDecoder
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
