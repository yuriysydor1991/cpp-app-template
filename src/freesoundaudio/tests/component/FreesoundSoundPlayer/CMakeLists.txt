cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_SDL2_AUDIO)
  return()
endif()

add_executable(
  CTEST_FreesoundSoundPlayer
  CTEST_FreesoundSoundPlayer.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/FreesoundSound.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategory.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategories.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/sounds/FreesoundSounds.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/player/FreesoundRandomSound.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/player/FreesoundSdlSoundPlayer.cpp
  ${FREESOUND_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  CTEST_FreesoundSoundPlayer
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_FreesoundSoundPlayer
  GTest::gtest_main GTest::gmock
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_FreesoundSoundPlayer
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

# No sound card is needed to prove the sound is decoded, queued and drained, so
# the dummy driver keeps the test runnable on a headless machine.
set_tests_properties(
  ${noArgsTests}
  PROPERTIES
    TIMEOUT 600
    ENVIRONMENT SDL_AUDIODRIVER=dummy
)
