cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_WindowConfig
  UTEST_WindowConfig.cpp
  ${CMAKE_SOURCE_DIR}/src/wxwidgets/helpers/WindowConfig.cpp
)

target_include_directories(
  UTEST_WindowConfig
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_WindowConfig
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_WindowConfig
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
