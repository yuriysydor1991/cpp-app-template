cmake_minimum_required(VERSION 3.16)

add_executable(
  UTEST_DBusQueryHandlerFactory
  UTEST_DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/query-handlers/DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/query-handlers/Hostname1QueryHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/SystemInformation.cpp
)

target_include_directories(
  UTEST_DBusQueryHandlerFactory
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_DBusQueryHandlerFactory
  GTest::gtest_main GTest::gmock Qt6::Core Qt6::DBus
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DBusQueryHandlerFactory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
