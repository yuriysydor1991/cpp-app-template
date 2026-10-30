cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the controller
# messages get into the project log. The model the configure downloads
# recognizes the speech, so the test cases skip themselves without it.
add_executable(
  CTEST_SherpaONNXController
  CTEST_SherpaONNXController.cpp
  ${PROJECT_SOURCE_DIR}/src/SherpaONNX/SherpaONNXController.cpp
  ${PROJECT_SOURCE_DIR}/src/STT/Microphone.cpp
  ${PROJECT_SOURCE_DIR}/src/STT/SpeechListener.cpp
  ${PROJECT_SOURCE_DIR}/src/STT/UtteranceDetector.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_SherpaONNXController
  PRIVATE
    CTEST_SherpaONNXController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
    CTEST_SherpaONNXController_MODEL=\"${PROJECT_STT_MODEL}\"
    CTEST_SherpaONNXController_SPEECH=\"${SHERPAONNX_TEST_SPEECH}\"
    CTEST_SherpaONNXController_UK_SPEECH=\"${SHERPAONNX_TEST_UK_SPEECH}\"
)

target_include_directories(
  CTEST_SherpaONNXController
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_SherpaONNXController
  GTest::gtest_main GTest::gmock
  SherpaONNX::cxx-api ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_SherpaONNXController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
