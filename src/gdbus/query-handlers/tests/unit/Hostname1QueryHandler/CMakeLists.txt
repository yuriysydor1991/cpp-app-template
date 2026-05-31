cmake_minimum_required(VERSION 3.16)

# Pure unit test: the handle() orchestration is exercised against an overridden
# fetch_properties() seam, so no live D-Bus is touched. giomm is linked only
# because the (unused at run time) real fetch_properties() is compiled in.
add_executable(
  UTEST_Hostname1QueryHandler
  UTEST_Hostname1QueryHandler.cpp
  ${CMAKE_SOURCE_DIR}/src/gdbus/query-handlers/Hostname1QueryHandler.cpp
)

target_include_directories(
  UTEST_Hostname1QueryHandler
  SYSTEM PRIVATE ${GTKMM_INCLUDE_DIRS}
)

target_include_directories(
  UTEST_Hostname1QueryHandler
  PRIVATE ${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_directories(
  UTEST_Hostname1QueryHandler
  PRIVATE ${GTKMM_LIBRARY_DIRS}
)

target_link_libraries(
  UTEST_Hostname1QueryHandler
  GTest::gtest_main GTest::gmock ${GTKMM_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Hostname1QueryHandler
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
