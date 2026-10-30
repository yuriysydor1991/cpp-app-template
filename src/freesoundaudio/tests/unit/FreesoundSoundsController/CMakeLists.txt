cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FreesoundSoundsController
  UTEST_FreesoundSoundsController.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/FreesoundSound.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/FreesoundRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategory.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategories.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/sounds/FreesoundSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/player/FreesoundRandomSound.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/controller/FreesoundSoundsController.cpp
  ${FREESOUND_AUDIO_OWN_MOCKS_ROOT}/FreesoundGeneratedSounds/FreesoundGeneratedSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/player/FreesoundNoSoundPlayerFactory.cpp
)

target_include_directories(
  UTEST_FreesoundSoundsController
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_FreesoundSoundsController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FreesoundSoundsController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
