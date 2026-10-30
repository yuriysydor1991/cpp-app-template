cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FreesoundRootDirectory
  UTEST_FreesoundRootDirectory.cpp
  ${PROJECT_SOURCE_DIR}/src/freesoundaudio/FreesoundRootDirectory.cpp
)

target_include_directories(
  UTEST_FreesoundRootDirectory
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_FreesoundRootDirectory
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FreesoundRootDirectory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
