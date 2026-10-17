cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_KenneyRootDirectory
  UTEST_KenneyRootDirectory.cpp
  ${CMAKE_SOURCE_DIR}/src/kenneyaudio/KenneyRootDirectory.cpp
)

target_include_directories(
  UTEST_KenneyRootDirectory
  PRIVATE ${KENNEY_AUDIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  UTEST_KenneyRootDirectory
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_KenneyRootDirectory
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
