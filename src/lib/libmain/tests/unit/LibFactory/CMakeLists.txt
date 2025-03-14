cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_LibFactory
  UTEST_LibFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/lib/libmain/LibFactory.cpp
)

target_include_directories(
  UTEST_LibFactory
  PRIVATE ${GENERAL_MOCKS_ROOT}/LibraryContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/LibMain
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/facade
)

target_link_libraries(
  UTEST_LibFactory
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_LibFactory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
