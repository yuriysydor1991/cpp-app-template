cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_ApplicationContext2LibraryContext  
  UTEST_ApplicationContext2LibraryContext.cpp
  ${CMAKE_SOURCE_DIR}/src/converters/ApplicationContext2LibraryContext.cpp
  ${GENERAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_ApplicationContext2LibraryContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/LibraryContext
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_ApplicationContext2LibraryContext
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_ApplicationContext2LibraryContext
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
