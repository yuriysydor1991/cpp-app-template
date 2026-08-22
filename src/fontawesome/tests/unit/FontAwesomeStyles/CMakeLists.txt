cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FontAwesomeStyles
  UTEST_FontAwesomeStyles.cpp
  ${FONTAWESOME_STYLES_SOURCES}
)

target_include_directories(
  UTEST_FontAwesomeStyles
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FontAwesomeStyles
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FontAwesomeStyles
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
