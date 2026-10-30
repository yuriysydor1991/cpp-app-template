cmake_minimum_required(VERSION 3.13)

add_executable(
  CTEST_MatPlotxxController
  CTEST_MatPlotxxController.cpp
  ${PROJECT_SOURCE_DIR}/src/matplotxx/MatPlotxxController.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_MatPlotxxController
  PRIVATE ${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  CTEST_MatPlotxxController
  GTest::gtest_main GTest::gmock Matplot++::matplot
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_MatPlotxxController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

# The tests draw through the gnuplot application, which prints the plot of the
# window-less runs onto it's standard output with the dumb terminal.
set_tests_properties(
  ${noArgsTests} PROPERTIES TIMEOUT 600 ENVIRONMENT GNUTERM=dumb
)
