cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_DataLocator
  UTEST_DataLocator.cpp
  ${PROJECT_SOURCE_DIR}/src/app/DataLocator.cpp
)

target_include_directories(
  UTEST_DataLocator
  PRIVATE ${APP_MOCKS_ROOT}/project-global-decls
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_DataLocator
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DataLocator
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
