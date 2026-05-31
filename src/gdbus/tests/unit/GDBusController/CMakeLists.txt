cmake_minimum_required(VERSION 3.16)

# Pure unit test: only the unit under test (GDBusController) is compiled,
# against header-replacement mocks (the query handler factory and its handler
# interface, log). giomm is real (it ships with gtkmm-4.0) but no live bus is
# touched - run()'s orchestration is driven through the mocks.
add_executable(
  UTEST_GDBusController
  UTEST_GDBusController.cpp
  ${CMAKE_SOURCE_DIR}/src/gdbus/GDBusController.cpp
)

target_include_directories(
  UTEST_GDBusController
  SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  UTEST_GDBusController
  PRIVATE ${GDBUS_MOCKS_ROOT}/DBusQueryHandlerFactory
  PRIVATE ${GDBUS_MOCKS_ROOT}/IDBusQueryHandler
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_directories(
  UTEST_GDBusController
  PRIVATE ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  UTEST_GDBusController
  GTest::gtest_main GTest::gmock ${GTKMM_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_GDBusController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
