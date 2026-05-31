cmake_minimum_required(VERSION 3.16)

# Component test: the real Hostname1QueryHandler reads from the live system bus.
# giomm needs Gio::init() before any Gio::DBus usage, so the test provides its
# own main() and links GTest::gtest (not gtest_main).
add_executable(
  CTEST_Hostname1QueryHandler
  CTEST_Hostname1QueryHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/gdbus/query-handlers/DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/gdbus/query-handlers/Hostname1QueryHandler.cpp
)

target_include_directories(
  CTEST_Hostname1QueryHandler
  SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  CTEST_Hostname1QueryHandler
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_directories(
  CTEST_Hostname1QueryHandler
  PRIVATE ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  CTEST_Hostname1QueryHandler
  GTest::gtest GTest::gmock ${GTKMM_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_Hostname1QueryHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
