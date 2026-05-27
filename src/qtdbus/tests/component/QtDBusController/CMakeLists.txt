cmake_minimum_required(VERSION 3.16)

# Component test: the real QtDBusController, factory and handler are exercised
# against a live system bus. A QCoreApplication is required by Qt6::DBus, so the
# test provides its own main() and links GTest::gtest (not gtest_main).
add_executable(
  CTEST_QtDBusController
  CTEST_QtDBusController.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/QtDBusController.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/query-handlers/DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/query-handlers/Hostname1QueryHandler.cpp
)

target_include_directories(
  CTEST_QtDBusController
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_QtDBusController
  GTest::gtest GTest::gmock Qt6::Core Qt6::DBus
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_QtDBusController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
