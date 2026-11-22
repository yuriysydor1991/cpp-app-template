cmake_minimum_required(VERSION 3.13)

# The model the configure downloads estimates the poses, so the test cases
# which need it skip themselves without it.
add_executable(
  CTEST_OpenPoseController
  CTEST_OpenPoseController.cpp
  ${PROJECT_SOURCE_DIR}/src/OpenPose/HeatmapDecoder.cpp
  ${PROJECT_SOURCE_DIR}/src/OpenPose/OpenPoseController.cpp
)

target_compile_definitions(
  CTEST_OpenPoseController
  PRIVATE CTEST_OpenPoseController_MODEL=\"${PROJECT_POSE_MODEL}\"
)

target_include_directories(
  CTEST_OpenPoseController
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  CTEST_OpenPoseController
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_OpenPoseController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
