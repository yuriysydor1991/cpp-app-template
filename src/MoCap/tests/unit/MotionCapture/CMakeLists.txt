cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MotionCapture
  UTEST_MotionCapture.cpp
  ${PROJECT_SOURCE_DIR}/src/MoCap/MotionCapture.cpp
)

target_include_directories(
  UTEST_MotionCapture
  PRIVATE ${MOCAP_MOCKS_ROOT}/FrameSource
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_MotionCapture
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_MotionCapture
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
