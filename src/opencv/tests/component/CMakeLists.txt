cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_opencv
  CTEST_opencv.cpp
  ${CMAKE_SOURCE_DIR}/src/opencv/OpenCVController.cpp
)

target_include_directories(
  CTEST_opencv
  PRIVATE
    ${OPENCV_MOCKS_ROOT}/log
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_opencv
  GTest::gtest_main GTest::gmock
  ${OpenCV_LIBS}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_opencv
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
