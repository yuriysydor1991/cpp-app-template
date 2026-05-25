cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_executable(
  CTEST_plotgencpp
  CTEST_plotgencpp.cpp
  ${CMAKE_SOURCE_DIR}/src/plotgencpp/PlotGenCppController.cpp
  ${CMAKE_SOURCE_DIR}/src/app/ApplicationContext.cpp
)

target_include_directories(
  CTEST_plotgencpp
  PRIVATE
    ${PLOTGENCPP_MOCKS_ROOT}/plotgen
    ${PLOTGENCPP_MOCKS_ROOT}/log
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_plotgencpp
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_plotgencpp
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
