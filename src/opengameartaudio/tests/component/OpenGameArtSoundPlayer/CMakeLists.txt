cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_SDL2_AUDIO)
  return()
endif()

add_executable(
  CTEST_OpenGameArtSoundPlayer
  CTEST_OpenGameArtSoundPlayer.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/OpenGameArtSound.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/OpenGameArtRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPack.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPacks.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/sounds/OpenGameArtSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/player/OpenGameArtRandomSound.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/player/OpenGameArtSdlMixerSoundPlayer.cpp
  ${OPENGAMEART_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  CTEST_OpenGameArtSoundPlayer
  PRIVATE ${OPENGAMEART_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_OpenGameArtSoundPlayer
  GTest::gtest_main GTest::gmock
  ${TEMPLATE_APP_SDL2_MIXER_TARGET}
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_OpenGameArtSoundPlayer
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
