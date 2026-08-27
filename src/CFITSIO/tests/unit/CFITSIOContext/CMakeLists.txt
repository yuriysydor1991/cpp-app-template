cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_CFITSIOContext
  UTEST_CFITSIOContext.cpp
  ${CMAKE_SOURCE_DIR}/src/CFITSIO/CFITSIOContext.cpp
)

target_include_directories(
  UTEST_CFITSIOContext
  PRIVATE ${CFITSIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_CFITSIOContext
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_CFITSIOContext
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
