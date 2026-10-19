cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the llama.cpp
# messages and the controller ones get into the project log.
add_executable(
  CTEST_LlamaCPPController
  CTEST_LlamaCPPController.cpp
  ${CMAKE_SOURCE_DIR}/src/LlamaCPP/BuiltinChatTemplate.cpp
  ${CMAKE_SOURCE_DIR}/src/LlamaCPP/ChatTemplate.cpp
  ${CMAKE_SOURCE_DIR}/src/LlamaCPP/Gemma4ChatTemplate.cpp
  ${CMAKE_SOURCE_DIR}/src/LlamaCPP/LlamaCPPController.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_LlamaCPPController
  PRIVATE
    CTEST_LlamaCPPController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
    CTEST_LlamaCPPController_TEST_MODEL=\"${LLAMACPP_TEST_MODEL}\"
    CTEST_LlamaCPPController_MODEL=\"${PROJECT_LLAMACPP_MODEL_PATH}\"
)

target_include_directories(
  CTEST_LlamaCPPController
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_LlamaCPPController
  GTest::gtest_main GTest::gmock
  llama
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_LlamaCPPController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 1200)
