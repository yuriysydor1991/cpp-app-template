cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_OpenGameArtResourcePath
  UTEST_OpenGameArtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/OpenGameArtSound.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/packs/OpenGameArtPack.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/resources/OpenGameArtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/resources/OpenGameArtQtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/opengameartaudio/resources/OpenGameArtGResourcePath.cpp
)

target_include_directories(
  UTEST_OpenGameArtResourcePath
  PRIVATE ${OPENGAMEART_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_OpenGameArtResourcePath
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_OpenGameArtResourcePath
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
