cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_SDL2_AUDIO)
  return()
endif()

add_executable(
  CTEST_KenneySoundPlayer
  CTEST_KenneySoundPlayer.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/KenneySound.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPack.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPacks.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/sounds/KenneySounds.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/player/KenneyRandomSound.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/player/KenneySdlMixerSoundPlayer.cpp
  ${KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  CTEST_KenneySoundPlayer
  PRIVATE ${KENNEY_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_KenneySoundPlayer
  GTest::gtest_main GTest::gmock
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_KenneySoundPlayer
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
