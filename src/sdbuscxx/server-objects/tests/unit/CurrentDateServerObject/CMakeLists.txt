cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_CurrentDateServerObject
  UTEST_CurrentDateServerObject.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/server-objects/CurrentDateServerObject.cpp
)

target_include_directories(
  UTEST_CurrentDateServerObject
  PRIVATE ${SDBUSCXX_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_CurrentDateServerObject
  GTest::gtest_main GTest::gmock
)

# NOTE: the sdbus-c++ usage requirements are attached to this target by the
# template-project-libsdbuscxx-enabler in the post enabler step.

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_CurrentDateServerObject
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
