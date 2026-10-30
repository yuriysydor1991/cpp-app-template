cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Wt4Context
  UTEST_Wt4Context.cpp
  ${PROJECT_SOURCE_DIR}/src/wt4/Wt4Context.cpp
  ${APP_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_Wt4Context
  PRIVATE ${APP_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Wt4Context
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Wt4Context
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
