cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_AudioPlayer
  UTEST_AudioPlayer.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/AudioPlayer.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/Speech.cpp
)

target_compile_definitions(
  UTEST_AudioPlayer
  PRIVATE UTEST_AudioPlayer_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_AudioPlayer
  PRIVATE ${TTS_APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_AudioPlayer
  GTest::gtest_main GTest::gmock
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_AudioPlayer
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
