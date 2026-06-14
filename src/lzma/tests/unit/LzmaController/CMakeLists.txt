cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_LzmaController
  UTEST_LzmaController.cpp
  ${CMAKE_SOURCE_DIR}/src/lzma/LzmaController.cpp
)

target_include_directories(
  UTEST_LzmaController
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_LzmaController
  GTest::gtest_main GTest::gmock LibLZMA::LibLZMA
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_LzmaController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
