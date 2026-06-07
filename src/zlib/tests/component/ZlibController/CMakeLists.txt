cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_ZlibController
  CTEST_ZlibController.cpp
  ${CMAKE_SOURCE_DIR}/src/zlib/ZlibController.cpp
)

target_include_directories(
  CTEST_ZlibController
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_ZlibController
  GTest::gtest_main GTest::gmock ZLIB::ZLIB
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_ZlibController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
