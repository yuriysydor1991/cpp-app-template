cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_LlamaCPPController
  UTEST_LlamaCPPController.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/BuiltinChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/ChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/Gemma4ChatTemplate.cpp
  ${PROJECT_SOURCE_DIR}/src/LlamaCPP/LlamaCPPController.cpp
)

target_compile_definitions(
  UTEST_LlamaCPPController
  PRIVATE UTEST_LlamaCPPController_MODEL=\"${LLAMACPP_TEST_MODEL}\"
)

target_include_directories(
  UTEST_LlamaCPPController
  PRIVATE ${LLAMACPP_APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_LlamaCPPController
  GTest::gtest_main GTest::gmock
  llama
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_LlamaCPPController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
