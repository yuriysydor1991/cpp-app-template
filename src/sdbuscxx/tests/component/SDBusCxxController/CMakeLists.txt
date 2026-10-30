cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_SDBusCxxController
  CTEST_SDBusCxxController.cpp
  ${PROJECT_SOURCE_DIR}/src/sdbuscxx/SDBusCxxController.cpp
  ${PROJECT_SOURCE_DIR}/src/sdbuscxx/server-objects/DBusServerObjectFactory.cpp
  ${PROJECT_SOURCE_DIR}/src/sdbuscxx/server-objects/CurrentDateServerObject.cpp
  ${GENERAL_MOCKS_ROOT}/ApplicationContext/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_SDBusCxxController
  PRIVATE ${GENERAL_MOCKS_ROOT}/ApplicationContext
  PRIVATE ${GENERAL_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_SDBusCxxController
  GTest::gtest_main GTest::gmock
  ${SDBUSCPP_LINK_TARGET}
)

# The sdbus-c++ usage requirements come with the SDBUSCPP_LINK_TARGET the
# template-project-libsdbuscxx-enabler declares before the src directory.

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_SDBusCxxController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
