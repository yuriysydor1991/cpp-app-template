cmake_minimum_required(VERSION 3.13)

# The mocked RHVoice library takes the place of the real one, whose headers
# alone are used.
add_executable(
  UTEST_RHVoiceController
  UTEST_RHVoiceController.cpp
  ${RHVOICE_MOCKS_ROOT}/RHVoiceLibrary/RHVoiceLibraryMock.cpp
  ${CMAKE_SOURCE_DIR}/src/RHVoice/RHVoiceController.cpp
  ${CMAKE_SOURCE_DIR}/src/TTS/Speech.cpp
)

target_include_directories(
  UTEST_RHVoiceController
  PRIVATE ${RHVOICE_APP_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_include_directories(
  UTEST_RHVoiceController
  SYSTEM PRIVATE $<TARGET_PROPERTY:RHVoice::RHVoice,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(
  UTEST_RHVoiceController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_RHVoiceController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
