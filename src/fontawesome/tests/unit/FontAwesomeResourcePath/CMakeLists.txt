cmake_minimum_required(VERSION 3.13)

add_executable(
  UTEST_FontAwesomeResourcePath
  UTEST_FontAwesomeResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/fontawesome/resources/FontAwesomeResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/fontawesome/resources/FontAwesomeQtResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/fontawesome/resources/FontAwesomeGResourcePath.cpp
  ${CMAKE_SOURCE_DIR}/src/fontawesome/FontAwesomeIcon.cpp
  ${FONTAWESOME_STYLES_SOURCES}
)

target_include_directories(
  UTEST_FontAwesomeResourcePath
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/fontawesome-decls
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FontAwesomeResourcePath
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FontAwesomeResourcePath
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
