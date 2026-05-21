cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_CocoaIniter
  UTEST_CocoaIniter.cpp
  ${CMAKE_SOURCE_DIR}/src/cocoa/CocoaIniter.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_CocoaIniter
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_CocoaIniter
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_CocoaIniter
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
