cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_DarknetXXController
  UTEST_DarknetXXController.cpp
)

target_compile_definitions(
  UTEST_DarknetXXController
  PRIVATE UTEST_DarknetXXController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_DarknetXXController
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_DarknetXXController
  ${DARKNETXX_TESTS_LIBRARIES}
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_DarknetXXController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
