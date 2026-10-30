cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_DisabledFbClient
  UTEST_DisabledFbClient.cpp
  ${PROJECT_SOURCE_DIR}/src/Firebird/driver/DisabledFbClient.cpp
)

target_include_directories(
  UTEST_DisabledFbClient
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_DisabledFbClient
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DisabledFbClient
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
