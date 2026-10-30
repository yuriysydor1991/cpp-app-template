cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_QueryMaker
  UTEST_QueryMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/mongodbcxx/helpers/QueryMaker.cpp
)

target_include_directories(
  UTEST_QueryMaker
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_QueryMaker
  GTest::gtest_main GTest::gmock
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_QueryMaker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
