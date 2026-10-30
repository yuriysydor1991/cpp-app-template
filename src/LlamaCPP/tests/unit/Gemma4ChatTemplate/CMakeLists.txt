cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Gemma4ChatTemplate
  UTEST_Gemma4ChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/Gemma4ChatTemplate.cpp
)

target_include_directories(
  UTEST_Gemma4ChatTemplate
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Gemma4ChatTemplate
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Gemma4ChatTemplate
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
