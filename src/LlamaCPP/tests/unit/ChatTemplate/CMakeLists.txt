cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_ChatTemplate
  UTEST_ChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/BuiltinChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/ChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/Gemma4ChatTemplate.cpp
)

target_include_directories(
  UTEST_ChatTemplate
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_ChatTemplate
  GTest::gtest_main GTest::gmock
  llama
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_ChatTemplate
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
