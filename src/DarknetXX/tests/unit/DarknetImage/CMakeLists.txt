cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_DarknetImage
  UTEST_DarknetImage.cpp
)

# The test includes the darknetxx headers, so it compiles the way the adaptor
# sources do (see the src/DarknetXX/CMakeLists.txt).
target_include_directories(
  UTEST_DarknetImage
  SYSTEM PRIVATE ${DARKNETXX_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}
)

target_compile_definitions(
  UTEST_DarknetImage
  PRIVATE ${DARKNETXX_COMPILE_DEFINITIONS}
)

target_link_libraries(
  UTEST_DarknetImage
  ${DARKNETXX_TESTS_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DarknetImage
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
