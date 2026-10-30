cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_MongoDBDate2String
  UTEST_MongoDBDate2String.cpp
  ${PROJECT_SOURCE_DIR}/src/mongodbcxx/converters/MongoDBDate2String.cpp
)

target_include_directories(
  UTEST_MongoDBDate2String
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_MongoDBDate2String
  GTest::gtest_main GTest::gmock
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_MongoDBDate2String
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
