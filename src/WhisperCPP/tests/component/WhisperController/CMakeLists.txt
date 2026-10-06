cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the whisper.cpp
# messages and the controller ones get into the project log.
add_executable(
  CTEST_WhisperController
  CTEST_WhisperController.cpp
  ${CMAKE_SOURCE_DIR}/src/WhisperCPP/Microphone.cpp
  ${CMAKE_SOURCE_DIR}/src/WhisperCPP/UtteranceDetector.cpp
  ${CMAKE_SOURCE_DIR}/src/WhisperCPP/WhisperController.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_WhisperController
  PRIVATE
    CTEST_WhisperController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
    CTEST_WhisperController_TEST_MODEL=\"${WHISPERCPP_TEST_MODEL}\"
    CTEST_WhisperController_SPEECH=\"${WHISPERCPP_TEST_SPEECH}\"
    CTEST_WhisperController_MODEL=\"${PROJECT_WHISPER_MODEL_PATH}\"
)

target_include_directories(
  CTEST_WhisperController
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_WhisperController
  GTest::gtest_main GTest::gmock
  whisper ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_WhisperController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
