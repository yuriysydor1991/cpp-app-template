cmake_minimum_required(VERSION 3.13)

# The model the configure downloads estimates the poses, so the test cases
# which need it skip themselves without it.
add_executable(
  CTEST_MoveNetController
  CTEST_MoveNetController.cpp
  ${PROJECT_SOURCE_DIR}/src/MoveNet/MoveNetController.cpp
  ${PROJECT_SOURCE_DIR}/src/MoveNet/MoveNetDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/ONNX/ONNXModel.cpp
)

target_compile_definitions(
  CTEST_MoveNetController
  PRIVATE CTEST_MoveNetController_MODEL=\"${PROJECT_POSE_MODEL}\"
)

target_include_directories(
  CTEST_MoveNetController
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  CTEST_MoveNetController
  GTest::gtest_main GTest::gmock
  onnxruntime::onnxruntime ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_MoveNetController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
