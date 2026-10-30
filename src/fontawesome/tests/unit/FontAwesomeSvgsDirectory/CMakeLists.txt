cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FontAwesomeSvgsDirectory
  UTEST_FontAwesomeSvgsDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/fontawesome/FontAwesomeSvgsDirectory.cpp
)

target_include_directories(
  UTEST_FontAwesomeSvgsDirectory
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_FontAwesomeSvgsDirectory
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FontAwesomeSvgsDirectory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
