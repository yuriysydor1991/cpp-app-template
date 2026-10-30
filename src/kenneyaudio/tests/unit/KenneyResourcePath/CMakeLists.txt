cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_KenneyResourcePath
  UTEST_KenneyResourcePath.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/KenneySound.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/KenneyRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/packs/KenneyPack.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/resources/KenneyResourcePath.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/resources/KenneyQtResourcePath.cpp
  ${PROJECT_SOURCE_DIR}/src/kenneyaudio/resources/KenneyGResourcePath.cpp
)

target_include_directories(
  UTEST_KenneyResourcePath
  PRIVATE ${KENNEY_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_KenneyResourcePath
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_KenneyResourcePath
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
