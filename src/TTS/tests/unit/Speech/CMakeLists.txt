cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Speech
  UTEST_Speech.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/Speech.cpp
)

target_include_directories(
  UTEST_Speech
  PRIVATE ${TTS_APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Speech
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Speech
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
