cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_KenneyRandomSound
  UTEST_KenneyRandomSound.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/KenneySound.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPack.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPacks.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/sounds/KenneySounds.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/player/KenneyRandomSound.cpp
  ${KENNEY_AUDIO_OWN_MOCKS_ROOT}/KenneyGeneratedSounds/KenneyGeneratedSounds.cpp
)

target_include_directories(
  UTEST_KenneyRandomSound
  PRIVATE ${KENNEY_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_KenneyRandomSound
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_KenneyRandomSound
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
