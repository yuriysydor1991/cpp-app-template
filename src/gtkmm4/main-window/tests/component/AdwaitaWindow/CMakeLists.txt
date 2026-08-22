cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_AdwaitaWindow  
  CTEST_AdwaitaWindow.cpp
  ${CMAKE_SOURCE_DIR}/src/gtkmm4/main-window/AdwaitaWindow.cpp
)

# The window guards its arguments with an assert first and with a returned
# error second. The test covers the returned error, which is the behaviour of a
# release build, so the asserts are disabled here the same way the unit test
# trees disable them.
target_compile_definitions(
  CTEST_AdwaitaWindow
  PRIVATE NDEBUG=1
)

# The window logs through the LOG* macros, so the test takes the project wide
# header only logging mock instead of linking the real logger into a GUI test.
set(LOG_MOCK_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log")

target_include_directories(
  CTEST_AdwaitaWindow
  PRIVATE
    ${LOG_MOCK_ROOT}
    ${GTKMM_INCLUDE_DIRS}
    ${ADWAITA_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_directories(
  CTEST_AdwaitaWindow
  PRIVATE ${GTKMM_LIBRARY_DIRS} ${ADWAITA_LIBRARY_DIRS}
)

target_link_libraries(
  CTEST_AdwaitaWindow
  ${GTKMM_LIBRARIES} ${ADWAITA_LIBRARIES}
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_AdwaitaWindow
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
