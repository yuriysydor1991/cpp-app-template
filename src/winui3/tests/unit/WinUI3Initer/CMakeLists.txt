cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_WinUI3Initer
  UTEST_WinUI3Initer.cpp
  ${CMAKE_SOURCE_DIR}/src/winui3/WinUI3Initer.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_WinUI3Initer
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_WinUI3Initer
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_WinUI3Initer
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
