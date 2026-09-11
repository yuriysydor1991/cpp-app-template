cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FreesoundCategories
  UTEST_FreesoundCategories.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategory.cpp
  ${CMAKE_SOURCE_DIR}/src/freesoundaudio/categories/FreesoundCategories.cpp
  ${FREESOUND_AUDIO_OWN_MOCKS_ROOT}/FreesoundGeneratedSounds/FreesoundGeneratedSounds.cpp
)

target_include_directories(
  UTEST_FreesoundCategories
  PRIVATE ${FREESOUND_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_FreesoundCategories
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FreesoundCategories
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
