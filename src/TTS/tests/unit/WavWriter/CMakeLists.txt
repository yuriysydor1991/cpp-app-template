cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_WavWriter
  UTEST_WavWriter.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/Speech.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/WavWriter.cpp
)

target_compile_definitions(
  UTEST_WavWriter
  PRIVATE UTEST_WavWriter_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_WavWriter
  PRIVATE ${TTS_APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_WavWriter
  GTest::gtest_main GTest::gmock
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_WavWriter
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
