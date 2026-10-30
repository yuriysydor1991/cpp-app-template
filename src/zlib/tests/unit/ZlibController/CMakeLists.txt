cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_ZlibController
  UTEST_ZlibController.cpp
  ${PROJECT_SOURCE_DIR}/src/zlib/ZlibController.cpp
)

target_include_directories(
  UTEST_ZlibController
  PRIVATE ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_ZlibController
  GTest::gtest_main GTest::gmock ZLIB::ZLIB
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_ZlibController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
