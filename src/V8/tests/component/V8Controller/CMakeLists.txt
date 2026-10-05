cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the JavaScript
# console writes into the project log.
add_executable(
  CTEST_V8Controller
  CTEST_V8Controller.cpp
  ${CMAKE_SOURCE_DIR}/src/V8/V8Console.cpp
  ${CMAKE_SOURCE_DIR}/src/V8/V8Controller.cpp
  ${CMAKE_SOURCE_DIR}/src/V8/V8Platform.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_V8Controller
  PRIVATE CTEST_V8Controller_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_V8Controller
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_V8Controller
  GTest::gtest_main GTest::gmock
  V8::V8
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_V8Controller
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
