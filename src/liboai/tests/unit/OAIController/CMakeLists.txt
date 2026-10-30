cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_OAIController
  UTEST_OAIController.cpp
  ${PROJECT_SOURCE_DIR}/src/liboai/OAIController.cpp
)

target_include_directories(
  UTEST_OAIController
  PRIVATE ${LIBOAI_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_OAIController
  GTest::gtest_main GTest::gmock
  oai::oai
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_OAIController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
