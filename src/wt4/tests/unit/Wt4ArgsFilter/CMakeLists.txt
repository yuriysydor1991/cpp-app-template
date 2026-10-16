cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Wt4ArgsFilter
  UTEST_Wt4ArgsFilter.cpp
  ${CMAKE_SOURCE_DIR}/src/wt4/Wt4ArgsFilter.cpp
)

target_include_directories(
  UTEST_Wt4ArgsFilter
  PRIVATE ${APP_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Wt4ArgsFilter
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Wt4ArgsFilter
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
