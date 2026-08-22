cmake_minimum_required(VERSION 3.13)

# The generated icons index is mocked here, so the expectations below hold
# regardless of the Font Awesome release the project has been configured with.
# The real index is exercised by the CTEST_FontAwesomeIcons component test.
add_executable(
  UTEST_FontAwesomeIcons
  UTEST_FontAwesomeIcons.cpp
  ${CMAKE_SOURCE_DIR}/src/fontawesome/icons/FontAwesomeIcons.cpp
  ${CMAKE_SOURCE_DIR}/src/fontawesome/FontAwesomeIcon.cpp
  ${FONTAWESOME_STYLES_SOURCES}
)

target_include_directories(
  UTEST_FontAwesomeIcons
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/FontAwesomeGeneratedIcons
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/fontawesome-decls
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(
  UTEST_FontAwesomeIcons
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET UTEST_FontAwesomeIcons
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 60)
