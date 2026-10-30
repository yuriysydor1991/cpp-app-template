cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_KenneySounds
  CTEST_KenneySounds.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/KenneySound.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/KenneyRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPack.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPacks.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/sounds/KenneySounds.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/resources/KenneyResourcePath.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/resources/KenneyQtResourcePath.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/resources/KenneyGResourcePath.cpp
  ${KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_compile_definitions(
  CTEST_KenneySounds
  PRIVATE CTEST_KenneySounds_QRC=\"${KENNEY_AUDIO_FULL_QRC}\"
  PRIVATE CTEST_KenneySounds_GRESOURCE_XML=\"${KENNEY_AUDIO_FULL_GRESOURCE_XML}\"
)

target_include_directories(
  CTEST_KenneySounds
  PRIVATE ${KENNEY_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
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
