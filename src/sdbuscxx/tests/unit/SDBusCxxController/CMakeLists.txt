cmake_minimum_required(VERSION 3.13)

# Pure unit test: only the unit under test (SDBusCxxController) is compiled,
# against header-replacement mocks (sdbus-c++, the query handler factory and its
# handler interface, ApplicationContext, log). No real sdbus-c++ is linked.
add_executable(
  UTEST_SDBusCxxController
  UTEST_SDBusCxxController.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/SDBusCxxController.cpp
  ${GENERAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_SDBusCxxController
  PRIVATE ${SDBUSCXX_MOCKS_ROOT}/DBusQueryHandlerFactory
  PRIVATE ${SDBUSCXX_MOCKS_ROOT}/IDBusQueryHandler
  PRIVATE ${GENERAL_MOCKS_ROOT}/sdbus-c++
  PRIVATE ${GENERAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_SDBusCxxController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SDBusCxxController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
