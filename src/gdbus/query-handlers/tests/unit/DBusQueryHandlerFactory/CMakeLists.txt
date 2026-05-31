cmake_minimum_required(VERSION 3.16)

add_executable(
  UTEST_DBusQueryHandlerFactory
  UTEST_DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/gdbus/query-handlers/DBusQueryHandlerFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/gdbus/query-handlers/Hostname1QueryHandler.cpp
)

target_include_directories(
  UTEST_DBusQueryHandlerFactory
  SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  UTEST_DBusQueryHandlerFactory
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_directories(
  UTEST_DBusQueryHandlerFactory
  PRIVATE ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  UTEST_DBusQueryHandlerFactory
  GTest::gtest_main GTest::gmock ${GTKMM_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DBusQueryHandlerFactory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
