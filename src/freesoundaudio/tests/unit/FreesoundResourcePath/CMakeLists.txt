cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FreesoundResourcePath
  UTEST_FreesoundResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/FreesoundSound.cpp
  ${FREESOUND_AUDIO_OWN_MOCKS_ROOT}/FreesoundGeneratedSounds/FreesoundGeneratedSounds.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategory.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundQtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundGResourcePath.cpp
)

target_include_directories(
  UTEST_FreesoundResourcePath
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_FreesoundResourcePath
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FreesoundResourcePath
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
