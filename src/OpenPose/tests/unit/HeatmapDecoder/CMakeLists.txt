cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_HeatmapDecoder
  UTEST_HeatmapDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/OpenPose/HeatmapDecoder.cpp
)

target_include_directories(
  UTEST_HeatmapDecoder
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_HeatmapDecoder
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_HeatmapDecoder
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
