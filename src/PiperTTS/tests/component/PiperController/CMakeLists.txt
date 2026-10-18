cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the controller
# messages get into the project log.
add_executable(
  CTEST_PiperController
  CTEST_PiperController.cpp
  ${CMAKE_SOURCE_DIR}/src/PiperTTS/PiperController.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/AudioPlayer.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/Speech.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/WavWriter.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_PiperController
  PRIVATE CTEST_PiperController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_PiperController
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_PiperController
  GTest::gtest_main GTest::gmock
  Piper::piper ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_PiperController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
