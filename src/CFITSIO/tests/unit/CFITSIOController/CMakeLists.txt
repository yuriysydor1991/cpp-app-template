cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_CFITSIOController
  UTEST_CFITSIOController.cpp
  ${CMAKE_SOURCE_DIR}/src/CFITSIO/CFITSIOController.cpp
)

target_include_directories(
  UTEST_CFITSIOController
  PRIVATE ${CFITSIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_CFITSIOController
  GTest::gtest_main GTest::gmock
  CFITSIO::cfitsio
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_CFITSIOController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
