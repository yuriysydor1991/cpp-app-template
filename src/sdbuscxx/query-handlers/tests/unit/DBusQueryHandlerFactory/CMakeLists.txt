cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_DBusQueryHandlerFactory
  UTEST_DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/query-handlers/DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/query-handlers/Hostname1QueryHandler.cpp
)

target_include_directories(
  UTEST_DBusQueryHandlerFactory
  PRIVATE ${SDBUSCXX_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_DBusQueryHandlerFactory
  GTest::gtest_main GTest::gmock
)

# NOTE: the sdbus-c++ usage requirements are attached to this target by the
# template-project-libsdbuscxx-enabler in the post enabler step.

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DBusQueryHandlerFactory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
