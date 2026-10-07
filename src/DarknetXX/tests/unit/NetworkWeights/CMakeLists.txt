cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_NetworkWeights
  UTEST_NetworkWeights.cpp
  ${CMAKE_SOURCE_DIR}/src/DarknetXX/weights/Dxxwjz1Weights.cpp
  ${CMAKE_SOURCE_DIR}/src/DarknetXX/weights/NetworkWeights.cpp
  ${CMAKE_SOURCE_DIR}/src/DarknetXX/weights/OrigWeights.cpp
)

target_include_directories(
  UTEST_NetworkWeights
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_NetworkWeights
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_NetworkWeights
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
