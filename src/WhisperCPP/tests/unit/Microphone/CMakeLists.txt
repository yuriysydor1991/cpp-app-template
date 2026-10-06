cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_Microphone
  UTEST_Microphone.cpp
  ${CMAKE_SOURCE_DIR}/src/WhisperCPP/Microphone.cpp
)

target_compile_definitions(
  UTEST_Microphone
  PRIVATE UTEST_Microphone_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_Microphone
  PRIVATE ${WHISPERCPP_APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_Microphone
  GTest::gtest_main GTest::gmock
  ${TEMPLATE_APP_SDL2_AUDIO_TARGET}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_Microphone
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
