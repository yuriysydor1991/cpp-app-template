cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_CFITSIOController
  CTEST_CFITSIOController.cpp
  ${CMAKE_SOURCE_DIR}/src/CFITSIO/CFITSIOController.cpp
)

target_compile_definitions(
  CTEST_CFITSIOController
  PRIVATE CTEST_CFITSIOController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_CFITSIOController
  PRIVATE ${CFITSIO_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  CTEST_CFITSIOController
  GTest::gtest_main GTest::gmock
  CFITSIO::cfitsio
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_CFITSIOController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
