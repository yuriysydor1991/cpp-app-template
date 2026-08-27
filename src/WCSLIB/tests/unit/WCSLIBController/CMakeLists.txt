cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_WCSLIBController
  UTEST_WCSLIBController.cpp
  ${CMAKE_SOURCE_DIR}/src/WCSLIB/WCSLIBController.cpp
)

target_include_directories(
  UTEST_WCSLIBController
  PRIVATE ${WCSLIB_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_WCSLIBController
  GTest::gtest_main GTest::gmock
  WCSLIB::wcslib
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_WCSLIBController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
