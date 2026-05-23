cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Hostname1QueryHandler
  UTEST_Hostname1QueryHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/query-handlers/Hostname1QueryHandler.cpp
)

target_include_directories(
  UTEST_Hostname1QueryHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/sdbus-c++
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_Hostname1QueryHandler
  GTest::gtest_main GTest::gmock
)

# The handler source is compiled against the header-only sdbus-c++ mock
# (${GENERAL_MOCKS_ROOT}/sdbus-c++); the real sdbus-c++ is intentionally not
# linked for the unit tier. The live bus path is covered by the component test.

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Hostname1QueryHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
