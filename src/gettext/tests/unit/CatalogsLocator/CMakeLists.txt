cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_CatalogsLocator
  UTEST_CatalogsLocator.cpp
  ${CMAKE_SOURCE_DIR}/src/gettext/CatalogsLocator.cpp
)

target_compile_definitions(
  UTEST_CatalogsLocator
  PRIVATE UTEST_CatalogsLocator_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  UTEST_CatalogsLocator
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_CatalogsLocator
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_CatalogsLocator
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
