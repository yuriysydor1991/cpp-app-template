cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the controller
# messages get into the project log. The Kokoro model the configure downloads
# speaks the speech, so the test cases skip themselves without it.
add_executable(
  CTEST_SherpaONNXController
  CTEST_SherpaONNXController.cpp
  ${CMAKE_SOURCE_DIR}/src/SherpaONNX/KokoroModel.cpp
  ${CMAKE_SOURCE_DIR}/src/SherpaONNX/SherpaONNXController.cpp
  ${CMAKE_SOURCE_DIR}/src/SherpaONNX/SherpaONNXModel.cpp
  ${CMAKE_SOURCE_DIR}/src/SherpaONNX/VitsModel.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/AudioPlayer.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/Speech.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/WavWriter.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_SherpaONNXController
  PRIVATE CTEST_SherpaONNXController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_SherpaONNXController
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
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
