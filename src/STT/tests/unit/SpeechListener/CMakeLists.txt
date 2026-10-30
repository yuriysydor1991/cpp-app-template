cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_SpeechListener
  UTEST_SpeechListener.cpp
  ${PROJECT_SOURCE_DIR}/src/STT/SpeechListener.cpp
  ${PROJECT_SOURCE_DIR}/src/STT/UtteranceDetector.cpp
)

target_include_directories(
  UTEST_SpeechListener
  PRIVATE ${STT_MOCKS_ROOT}/Microphone
  PRIVATE ${STT_APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_link_libraries(
  UTEST_SpeechListener
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_SpeechListener
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
