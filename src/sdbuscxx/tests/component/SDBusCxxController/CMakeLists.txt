cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_SDBusCxxController
  CTEST_SDBusCxxController.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/SDBusCxxController.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/query-handlers/DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/query-handlers/Hostname1QueryHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_SDBusCxxController
  PRIVATE ${SDBUSCXX_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_SDBusCxxController
  GTest::gtest_main GTest::gmock
)

# NOTE: the sdbus-c++ usage requirements are attached to this target by the
# template-project-libsdbuscxx-enabler in the post enabler step.

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_SDBusCxxController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
