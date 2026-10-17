cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_OpenGameArtPacks
  UTEST_OpenGameArtPacks.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPack.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPacks.cpp
  ${OPENGAMEART_AUDIO_OWN_MOCKS_ROOT}/OpenGameArtGeneratedSounds/OpenGameArtGeneratedSounds.cpp
)

target_include_directories(
  UTEST_OpenGameArtPacks
  PRIVATE ${OPENGAMEART_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_OpenGameArtPacks
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_OpenGameArtPacks
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
