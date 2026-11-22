cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_PersonDetector
  UTEST_PersonDetector.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/PersonDetector.cpp
  ${PROJECT_SOURCE_DIR}/src/ONNX/ONNXModel.cpp
)

target_include_directories(
  UTEST_PersonDetector
  PRIVATE ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_PersonDetector
  GTest::gtest_main GTest::gmock
  onnxruntime::onnxruntime ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PersonDetector
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
