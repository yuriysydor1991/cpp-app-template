cmake_minimum_required(VERSION 3.13)

# The mocked libpiper takes the place of the real one, whose header alone is
# used.
add_executable(
  UTEST_PiperController
  UTEST_PiperController.cpp
  ${PIPER_MOCKS_ROOT}/PiperLibrary/PiperLibraryMock.cpp
  ${PROJECT_SOURCE_DIR}/src/PiperTTS/PiperController.cpp
  ${PROJECT_SOURCE_DIR}/src/TTS/Speech.cpp
)

target_compile_definitions(
  UTEST_PiperController
  PRIVATE UTEST_PiperController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_PiperController
  PRIVATE ${PIPER_APP_MOCKS_ROOT}/log
  PRIVATE ${PROJECT_SOURCE_DIR}
)

target_include_directories(
  UTEST_PiperController
  SYSTEM PRIVATE $<TARGET_PROPERTY:Piper::piper,INTERFACE_INCLUDE_DIRECTORIES>
)

# The header comes with the Piper build.
add_dependencies(UTEST_PiperController piper_external)

target_link_libraries(
  UTEST_PiperController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PiperController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
