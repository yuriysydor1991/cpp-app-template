cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_OpenGameArtSound
  UTEST_OpenGameArtSound.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/OpenGameArtSound.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/OpenGameArtRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPack.cpp
)

target_include_directories(
  UTEST_OpenGameArtSound
  PRIVATE ${OPENGAMEART_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_OpenGameArtSound
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_OpenGameArtSound
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
