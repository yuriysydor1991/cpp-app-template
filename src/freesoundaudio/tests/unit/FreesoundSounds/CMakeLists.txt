cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FreesoundSounds
  UTEST_FreesoundSounds.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/FreesoundSound.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategory.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategories.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/sounds/FreesoundSounds.cpp
  ${FREESOUND_AUDIO_OWN_MOCKS_ROOT}/FreesoundGeneratedSounds/FreesoundGeneratedSounds.cpp
)

target_include_directories(
  UTEST_FreesoundSounds
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_FreesoundSounds
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FreesoundSounds
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
