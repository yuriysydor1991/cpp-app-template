cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_WhisperController
  UTEST_WhisperController.cpp
  ${CMAKE_SOURCE_DIR}/src/WhisperCPP/UtteranceDetector.cpp
  ${CMAKE_SOURCE_DIR}/src/WhisperCPP/WhisperController.cpp
)

target_compile_definitions(
  UTEST_WhisperController
  PRIVATE UTEST_WhisperController_MODEL=\"${WHISPERCPP_TEST_MODEL}\"
)

target_include_directories(
  UTEST_WhisperController
  PRIVATE ${WHISPERCPP_MOCKS_ROOT}/Microphone
  PRIVATE ${WHISPERCPP_APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_WhisperController
  GTest::gtest_main GTest::gmock
  whisper
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_WhisperController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
