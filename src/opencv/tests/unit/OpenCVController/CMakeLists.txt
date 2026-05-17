cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_OpenCVController
  UTEST_OpenCVController.cpp
  ${CMAKE_SOURCE_DIR}/src/opencv/OpenCVController.cpp
)

target_include_directories(
  UTEST_OpenCVController
  PRIVATE ${OPENCV_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_OpenCVController
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_OpenCVController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
