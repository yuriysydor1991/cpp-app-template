cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_ChatGPTController
  UTEST_ChatGPTController.cpp
  ${CMAKE_SOURCE_DIR}/src/chatgpt/ChatGPTController.cpp
)

target_include_directories(
  UTEST_ChatGPTController
  PRIVATE ${CHATGPT_MOCKS_ROOT}/CURLController
  PRIVATE ${CHATGPT_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_ChatGPTController
  GTest::gtest_main GTest::gmock
  nlohmann_json::nlohmann_json
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_ChatGPTController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
