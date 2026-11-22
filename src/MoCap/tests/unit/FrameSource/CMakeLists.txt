cmake_minimum_required(VERSION 3.13)

# The test writes the image it reads, so it links the imgcodecs module too.
find_package(OpenCV REQUIRED COMPONENTS core imgcodecs videoio)

add_executable(
  UTEST_FrameSource
  UTEST_FrameSource.cpp
  ${PROJECT_SOURCE_DIR}/src/MoCap/FrameSource.cpp
)

target_include_directories(
  UTEST_FrameSource
  PRIVATE ${MOCAP_APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FrameSource
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FrameSource
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
