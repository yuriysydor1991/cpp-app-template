cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_SimpleLogger  
  CTEST_SimpleLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/simple-logger/SimpleLogger.cpp
)

target_compile_definitions(
  CTEST_SimpleLogger
  PRIVATE CTEST_SimpleLogger_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_SimpleLogger
  PRIVATE 
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_SimpleLogger
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_SimpleLogger
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
