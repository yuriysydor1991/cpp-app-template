cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_WinUI3
  CTEST_WinUI3.cpp
  ${PROJECT_SOURCE_DIR}/src/winui3/WinUI3Controller.cpp
  ${PROJECT_SOURCE_DIR}/src/winui3/helpers/WindowConfig.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_WinUI3
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_WinUI3
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_WinUI3
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
