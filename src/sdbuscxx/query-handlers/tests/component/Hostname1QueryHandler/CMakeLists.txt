cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_Hostname1QueryHandler
  CTEST_Hostname1QueryHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/query-handlers/Hostname1QueryHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/query-handlers/DBusQueryHandlerFactory.cpp
)

target_include_directories(
  CTEST_Hostname1QueryHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_Hostname1QueryHandler
  GTest::gtest_main GTest::gmock ${SDBUSCPP_LINK_TARGET}
)

# NOTE: the sdbus-c++ usage requirements are attached to this target by the
# template-project-libsdbuscxx-enabler in the post enabler step.

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Hostname1QueryHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
