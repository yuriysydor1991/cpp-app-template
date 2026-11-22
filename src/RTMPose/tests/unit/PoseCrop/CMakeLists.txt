cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_PoseCrop
  UTEST_PoseCrop.cpp
  ${PROJECT_SOURCE_DIR}/src/RTMPose/PoseCrop.cpp
)

target_include_directories(
  UTEST_PoseCrop
  PRIVATE ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_PoseCrop
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PoseCrop
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
