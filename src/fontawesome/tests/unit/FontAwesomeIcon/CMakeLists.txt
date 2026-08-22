cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FontAwesomeIcon
  UTEST_FontAwesomeIcon.cpp
  ${CMAKE_SOURCE_DIR}/src/fontawesome/FontAwesomeIcon.cpp
  ${FONTAWESOME_STYLES_SOURCES}
)

target_include_directories(
  UTEST_FontAwesomeIcon
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/fontawesome-decls
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FontAwesomeIcon
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FontAwesomeIcon
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
