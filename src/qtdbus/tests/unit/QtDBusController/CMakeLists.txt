cmake_minimum_required(VERSION 3.16)

# Pure unit test: only the unit under test (QtDBusController) is compiled,
# against header-replacement mocks (the query handler factory and its handler
# interface, log). The native Qt6::DBus is real (it ships with qt6-base) but no
# live bus is touched - run()'s orchestration is driven through the mocks.
add_executable(
  UTEST_QtDBusController
  UTEST_QtDBusController.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/QtDBusController.cpp
  ${CMAKE_SOURCE_DIR}/src/qtdbus/SystemInformation.cpp
)

target_include_directories(
  UTEST_QtDBusController
  PRIVATE ${QTDBUS_MOCKS_ROOT}/DBusQueryHandlerFactory
  PRIVATE ${QTDBUS_MOCKS_ROOT}/IDBusQueryHandler
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_QtDBusController
  GTest::gtest_main GTest::gmock Qt6::Core Qt6::DBus
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_QtDBusController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
