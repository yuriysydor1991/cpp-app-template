cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_SDBusCxxController
  UTEST_SDBusCxxController.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/SDBusCxxController.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/server-objects/DBusServerObjectFactory.cpp
  ${CMAKE_SOURCE_DIR}/src/sdbuscxx/server-objects/CurrentDateServerObject.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_SDBusCxxController
  PRIVATE ${SDBUSCXX_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_SDBusCxxController
  GTest::gtest_main GTest::gmock
)

# NOTE: the sdbus-c++ usage requirements are attached to this target by the
# template-project-libsdbuscxx-enabler in the post enabler step, because the
# SDBusCpp::sdbus-c++ target is not available yet while this file is processed.

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SDBusCxxController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
