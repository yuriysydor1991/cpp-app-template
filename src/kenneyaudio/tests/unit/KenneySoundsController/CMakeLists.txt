cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_KenneySoundsController
  UTEST_KenneySoundsController.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/KenneySound.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/KenneyRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPack.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPacks.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/sounds/KenneySounds.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/player/KenneyRandomSound.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/controller/KenneySoundsController.cpp
  ${KENNEY_AUDIO_OWN_MOCKS_ROOT}/KenneyGeneratedSounds/KenneyGeneratedSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/player/KenneyNoSoundPlayerFactory.cpp
)

target_include_directories(
  UTEST_KenneySoundsController
  PRIVATE ${KENNEY_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_KenneySoundsController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_KenneySoundsController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
