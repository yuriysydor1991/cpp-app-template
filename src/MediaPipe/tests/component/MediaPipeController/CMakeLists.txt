cmake_minimum_required(VERSION 3.13)

# The model the configure downloads estimates the poses, so the test cases
# which need it skip themselves without it.
add_executable(
  CTEST_MediaPipeController
  CTEST_MediaPipeController.cpp
  ${PROJECT_SOURCE_DIR}/src/MediaPipe/LandmarksDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/MediaPipe/MediaPipeController.cpp
)

target_compile_definitions(
  CTEST_MediaPipeController
  PRIVATE CTEST_MediaPipeController_MODEL=\"${PROJECT_POSE_MODEL}\"
)

target_include_directories(
  CTEST_MediaPipeController
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  CTEST_MediaPipeController
  GTest::gtest_main GTest::gmock
  MediaPipe::mediapipe ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_MediaPipeController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
