cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_PlotGenCppController
  UTEST_PlotGenCppController.cpp
  ${PROJECT_SOURCE_DIR}/src/plotgencpp/PlotGenCppController.cpp
  ${PROJECT_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  UTEST_PlotGenCppController
  PRIVATE ${PLOTGENCPP_MOCKS_ROOT}/plotgen
  PRIVATE ${PLOTGENCPP_LOG_MOCK_ROOT}
  PRIVATE ${PROJECT_SOURCE_DIR}
  PRIVATE ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  UTEST_PlotGenCppController
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_PlotGenCppController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
