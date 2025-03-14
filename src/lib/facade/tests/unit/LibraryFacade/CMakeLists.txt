cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_LibraryFacade  
  UTEST_LibraryFacade.cpp
  ${CMAKE_SOURCE_DIR}/src/lib/facade/LibraryFacade.cpp
)

target_include_directories(
  UTEST_LibraryFacade
  PRIVATE ${GENERAL_MOCKS_ROOT}/LibraryContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/LibMain
  PRIVATE ${FACADE_MOCK_DIR}/LibFactory
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_SOURCE_DIR}/src/lib/facade
)

target_link_libraries(
  UTEST_LibraryFacade
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_LibraryFacade
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
