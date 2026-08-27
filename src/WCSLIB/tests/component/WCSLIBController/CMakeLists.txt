cmake_minimum_required(VERSION 3.13)

# The component test converts the coordinates of a real FITS file, so it builds
# the CFITSIO controller next to the WCSLIB one. That is the test alone: the
# two components hold no reference to each other.
add_executable(
  CTEST_WCSLIBController
  CTEST_WCSLIBController.cpp
  ${CMAKE_SOURCE_DIR}/src/WCSLIB/WCSLIBController.cpp
  ${CMAKE_SOURCE_DIR}/src/CFITSIO/CFITSIOController.cpp
  ${CMAKE_SOURCE_DIR}/src/CFITSIO/CFITSIOContext.cpp
)

target_compile_definitions(
  CTEST_WCSLIBController
  PRIVATE CTEST_WCSLIBController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_WCSLIBController
  PRIVATE ${WCSLIB_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  CTEST_WCSLIBController
  GTest::gtest_main GTest::gmock
  WCSLIB::wcslib
  CFITSIO::cfitsio
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_WCSLIBController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
