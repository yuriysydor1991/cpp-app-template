cmake_minimum_required(VERSION 3.13)

# The models the configure downloads estimate the poses, so the test cases
# which need them skip themselves without them.
add_executable(
  CTEST_RTMPoseController
  CTEST_RTMPoseController.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/PersonDetector.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/PoseCrop.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/PoseModel.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/RTMPoseController.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/SimCCDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/ONNX/ONNXModel.cpp
)

target_compile_definitions(
  CTEST_RTMPoseController
  PRIVATE CTEST_RTMPoseController_MODEL=\"${PROJECT_POSE_MODEL}\"
)

target_include_directories(
  CTEST_RTMPoseController
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  CTEST_RTMPoseController
  GTest::gtest_main GTest::gmock
  onnxruntime::onnxruntime ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_RTMPoseController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
