cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_CocoaController
  UTEST_CocoaController.cpp
  ${PROJECT_SOURCE_DIR}/src/cocoa/CocoaController.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_CocoaController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_CocoaController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_CocoaController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
