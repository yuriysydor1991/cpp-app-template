cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_LandmarksDecoder
  UTEST_LandmarksDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/MediaPipe/LandmarksDecoder.cpp
)

target_include_directories(
  UTEST_LandmarksDecoder
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_LandmarksDecoder
  GTest::gtest_main GTest::gmock
  MediaPipe::mediapipe ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_LandmarksDecoder
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
