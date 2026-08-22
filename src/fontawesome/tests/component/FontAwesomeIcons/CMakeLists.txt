cmake_minimum_required(VERSION 3.13)

# Unlike the unit tests above, this one drives the real generated index against
# the very Font Awesome checkout the project has been configured with.
add_executable(
  CTEST_FontAwesomeIcons
  CTEST_FontAwesomeIcons.cpp
  ${FONTAWESOME_SUBSYSTEM_SOURCES}
  ${FONTAWESOME_GENERATED_ICONS_SOURCE}
)

target_compile_definitions(
  CTEST_FontAwesomeIcons
  PRIVATE CTEST_FontAwesomeIcons_QRC=\"${FONTAWESOME_FULL_QRC}\"
  PRIVATE CTEST_FontAwesomeIcons_GRESOURCE_XML=\"${FONTAWESOME_FULL_GRESOURCE_XML}\"
)

target_include_directories(
  CTEST_FontAwesomeIcons
  PRIVATE ${FONTAWESOME_MOCKS_ROOT}/log
  PRIVATE ${CMAKE_SOURCE_DIR}
  PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_FontAwesomeIcons
  GTest::gtest_main GTest::gmock
)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_FontAwesomeIcons
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
