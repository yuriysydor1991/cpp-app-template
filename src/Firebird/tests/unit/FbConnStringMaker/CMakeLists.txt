cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FbConnStringMaker
  UTEST_FbConnStringMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/Firebird/helpers/FbConnStringMaker.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_FbConnStringMaker
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FbConnStringMaker
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FbConnStringMaker
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
