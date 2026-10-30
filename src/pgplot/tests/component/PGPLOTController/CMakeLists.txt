cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_PGPLOTController
  CTEST_PGPLOTController.cpp
  ${PROJECT_SOURCE_DIR}/src/pgplot/PGPLOTController.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_PGPLOTController
  PRIVATE ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_PGPLOTController
  GTest::gtest_main GTest::gmock PGPLOT::cpgplot
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_PGPLOTController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

# The giza fonts come from the fontconfig, the process wide caches of which
# the leak sanitizer of the ENABLE_SANITIZERS builds would report otherwise.
set_tests_properties(
  ${noArgsTests} PROPERTIES
  TIMEOUT 600
  ENVIRONMENT "LSAN_OPTIONS=suppressions=${CMAKE_CURRENT_SOURCE_DIR}/lsan.supp"
)
