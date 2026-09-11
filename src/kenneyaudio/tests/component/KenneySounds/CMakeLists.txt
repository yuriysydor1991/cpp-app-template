cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_KenneySounds
  CTEST_KenneySounds.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/KenneySound.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPack.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPacks.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/sounds/KenneySounds.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/resources/KenneyResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/resources/KenneyQtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/resources/KenneyGResourcePath.cpp
  ${KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_include_directories(
  CTEST_KenneySounds
  PRIVATE ${KENNEY_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_KenneySounds
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_KenneySounds
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
