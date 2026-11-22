cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_SimCCDecoder
  UTEST_SimCCDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/SimCCDecoder.cpp
)

target_include_directories(
  UTEST_SimCCDecoder
  PRIVATE ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_SimCCDecoder
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SimCCDecoder
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
