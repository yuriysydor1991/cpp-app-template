cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_LibMain
  UTEST_LibMain.cpp
  ${CMAKE_SOURCE_DIR}/src/lib/libmain/LibMain.cpp
)

target_include_directories(
  UTEST_LibMain
  PRIVATE ${GENERAL_MOCKS_ROOT}/LibraryContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
  PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/facade
)

target_link_libraries(
  UTEST_LibMain
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_LibMain
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
