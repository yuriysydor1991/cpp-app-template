cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_BuiltinChatTemplate
  UTEST_BuiltinChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/BuiltinChatTemplate.cpp
)

target_include_directories(
  UTEST_BuiltinChatTemplate
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_BuiltinChatTemplate
  GTest::gtest_main GTest::gmock
  llama
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_BuiltinChatTemplate
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
