cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_WinUI3Controller
  UTEST_WinUI3Controller.cpp
  ${PROJECT_SOURCE_DIR}/src/winui3/WinUI3Controller.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_WinUI3Controller
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_WinUI3Controller
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_WinUI3Controller
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
