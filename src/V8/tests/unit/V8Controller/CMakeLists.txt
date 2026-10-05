cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_V8Controller
  UTEST_V8Controller.cpp
  ${CMAKE_SOURCE_DIR}/src/V8/V8Controller.cpp
  ${CMAKE_SOURCE_DIR}/src/V8/V8Platform.cpp
)

target_include_directories(
  UTEST_V8Controller
  PRIVATE ${V8_MOCKS_ROOT}/V8Console
  PRIVATE ${V8_LOG_MOCK_ROOT}
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_V8Controller
  GTest::gtest_main GTest::gmock
  V8::V8
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_V8Controller
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
