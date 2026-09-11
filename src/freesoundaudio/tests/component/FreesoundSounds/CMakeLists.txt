cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_FreesoundSounds
  CTEST_FreesoundSounds.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/FreesoundSound.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategory.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategories.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/sounds/FreesoundSounds.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundQtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundGResourcePath.cpp
  ${FREESOUND_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  CTEST_FreesoundSounds
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_FreesoundSounds
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_FreesoundSounds
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
