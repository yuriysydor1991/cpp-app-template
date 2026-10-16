cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_Log4Cpp5Init
  CTEST_Log4Cpp5Init.cpp
  ${CMAKE_SOURCE_DIR}/src/log/log4cpp5-init/Log4Cpp5Init.cpp
)

target_compile_definitions(
  CTEST_Log4Cpp5Init
  PRIVATE CTEST_Log4Cpp5Init_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_Log4Cpp5Init
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_Log4Cpp5Init
  GTest::gtest_main GTest::gmock LOG4CPP::log4cpp
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Log4Cpp5Init
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
