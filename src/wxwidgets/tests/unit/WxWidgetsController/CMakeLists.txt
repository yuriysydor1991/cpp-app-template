cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_WxWidgetsController
  UTEST_WxWidgetsController.cpp
  ${PROJECT_SOURCE_DIR}/src/wxwidgets/WxWidgetsController.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_WxWidgetsController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_WxWidgetsController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_WxWidgetsController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
