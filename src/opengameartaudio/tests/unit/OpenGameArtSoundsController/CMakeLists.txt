cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_OpenGameArtSoundsController
  UTEST_OpenGameArtSoundsController.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/OpenGameArtSound.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/OpenGameArtRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPack.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPacks.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/sounds/OpenGameArtSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/player/OpenGameArtRandomSound.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/controller/OpenGameArtSoundsController.cpp
  ${OPENGAMEART_AUDIO_OWN_MOCKS_ROOT}/OpenGameArtGeneratedSounds/OpenGameArtGeneratedSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/player/OpenGameArtNoSoundPlayerFactory.cpp
)

target_include_directories(
  UTEST_OpenGameArtSoundsController
  PRIVATE ${OPENGAMEART_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_OpenGameArtSoundsController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_OpenGameArtSoundsController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
