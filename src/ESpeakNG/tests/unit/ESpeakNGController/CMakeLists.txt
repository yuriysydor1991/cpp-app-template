cmake_minimum_required(VERSION 3.13)

# The mocked eSpeak NG library takes the place of the real one, whose headers
# alone are used.
add_executable(
  UTEST_ESpeakNGController
  UTEST_ESpeakNGController.cpp
  ${ESPEAKNG_MOCKS_ROOT}/ESpeakNGLibrary/ESpeakNGLibraryMock.cpp
  ${PROJECT_SOURCE_DIR}/src/ESpeakNG/ESpeakNGController.cpp
  ${PROJECT_SOURCE_DIR}/src/TTS/Speech.cpp
)

target_include_directories(
  UTEST_ESpeakNGController
  PRIVATE ${ESPEAKNG_APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_include_directories(
  UTEST_ESpeakNGController
  SYSTEM PRIVATE $<TARGET_PROPERTY:ESpeakNG::espeak-ng,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(
  UTEST_ESpeakNGController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_ESpeakNGController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
