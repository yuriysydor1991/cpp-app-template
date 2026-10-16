cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_executable(
  CTEST_MongoDBController
  CTEST_MongoDBController.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/MongoDBController.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/helpers/QueryMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/helpers/MongoDBConnStringMaker.cpp
  ${CMAKE_SOURCE_DIR}/src/mongodbcxx/converters/MongoDBDate2String.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_MongoDBController
  PRIVATE ${APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  CTEST_MongoDBController
  GTest::gtest_main GTest::gmock
  mongo::mongocxx_shared mongo::bsoncxx_shared
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_MongoDBController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
