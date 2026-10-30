cmake_minimum_required(VERSION 3.13)

# The real default logger is linked in, so the test proves the controller
# messages get into the project log.
add_executable(
  CTEST_ESpeakNGController
  CTEST_ESpeakNGController.cpp
  ${PROJECT_SOURCE_DIR}/src/ESpeakNG/ESpeakNGController.cpp
  ${PROJECT_SOURCE_DIR}/src/TTS/AudioPlayer.cpp
  ${PROJECT_SOURCE_DIR}/src/TTS/Speech.cpp
  ${PROJECT_SOURCE_DIR}/src/TTS/WavWriter.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${PROJECT_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_ESpeakNGController
  PRIVATE CTEST_ESpeakNGController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_ESpeakNGController
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_ESpeakNGController
  GTest::gtest_main GTest::gmock
  ESpeakNG::espeak-ng ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_ESpeakNGController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
