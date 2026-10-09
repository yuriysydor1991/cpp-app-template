cmake_minimum_required(VERSION 3.13)

# The test cases translate with the catalog of an own text domain, so they
# depend on no translation of the project po directory.
set(CTEST_GettextController_CATALOG_DIR "${CMAKE_CURRENT_BINARY_DIR}/locale/uk/LC_MESSAGES")
set(CTEST_GettextController_CATALOG "${CTEST_GettextController_CATALOG_DIR}/CTEST_GettextController.mo")

add_custom_command(
  OUTPUT ${CTEST_GettextController_CATALOG}
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CTEST_GettextController_CATALOG_DIR}
  COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} --check -o ${CTEST_GettextController_CATALOG} ${CMAKE_CURRENT_SOURCE_DIR}/uk.po
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/uk.po
  VERBATIM
)

add_custom_target(CTEST_GettextController_catalog DEPENDS ${CTEST_GettextController_CATALOG})

# The real default logger is linked in, so the test proves the controller
# reports into the project log.
add_executable(
  CTEST_GettextController
  CTEST_GettextController.cpp
  ${CMAKE_SOURCE_DIR}/src/gettext/CatalogsLocator.cpp
  ${CMAKE_SOURCE_DIR}/src/gettext/GettextController.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/DefaultLogger.cpp
  ${CMAKE_SOURCE_DIR}/src/log/default-logger/real-default-logger/RealDefaultLogger.cpp
)

target_compile_definitions(
  CTEST_GettextController
  PRIVATE CTEST_GettextController_DATA_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)

target_include_directories(
  CTEST_GettextController
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  CTEST_GettextController
  GTest::gtest_main GTest::gmock
  Intl::Intl
)

add_dependencies(CTEST_GettextController CTEST_GettextController_catalog)

include(GoogleTest)

gtest_add_tests(
  TARGET CTEST_GettextController
  TEST_SUFFIX .noArgs
  TEST_LIST noArgsTests
)

set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 600)
