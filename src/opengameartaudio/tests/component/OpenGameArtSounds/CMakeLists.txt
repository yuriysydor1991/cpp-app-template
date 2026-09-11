cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_OpenGameArtSounds
  CTEST_OpenGameArtSounds.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/OpenGameArtSound.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPack.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPacks.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/sounds/OpenGameArtSounds.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/resources/OpenGameArtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/resources/OpenGameArtQtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/resources/OpenGameArtGResourcePath.cpp
  ${OPENGAMEART_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  CTEST_OpenGameArtSounds
  PRIVATE ${OPENGAMEART_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_OpenGameArtSounds
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_OpenGameArtSounds
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
