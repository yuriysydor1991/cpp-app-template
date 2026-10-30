cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_FreesoundSounds
  CTEST_FreesoundSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/FreesoundSound.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/FreesoundRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategory.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategories.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/sounds/FreesoundSounds.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundResourcePath.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundQtResourcePath.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/resources/FreesoundGResourcePath.cpp
  ${FREESOUND_AUDIO_GENERATED_SOUNDS_SOURCE}
)

target_compile_definitions(
  CTEST_FreesoundSounds
  PRIVATE CTEST_FreesoundSounds_QRC=\"${FREESOUND_AUDIO_FULL_QRC}\"
  PRIVATE CTEST_FreesoundSounds_GRESOURCE_XML=\"${FREESOUND_AUDIO_FULL_GRESOURCE_XML}\"
  PRIVATE CTEST_FreesoundSounds_MANIFEST=\"${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST}\"
)

target_include_directories(
  CTEST_FreesoundSounds
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
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
