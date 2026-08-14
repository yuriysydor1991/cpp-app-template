cmake_minimum_required(VERSION 3.13)

set(
  MANY_LIBS_COUNT "100"
  CACHE STRING
  "Count of the derived library projects the ITEST_many_libs test generates"
)

add_test(
  NAME ITEST_many_libs.noArgs
  COMMAND
    ${CMAKE_CURRENT_SOURCE_DIR}/ITEST_many_libs.sh
      --source-dir ${CMAKE_SOURCE_DIR}
      --work-dir ${CMAKE_CURRENT_BINARY_DIR}/work
      --count ${MANY_LIBS_COUNT}
)

# The test generates, configures, builds and installs MANY_LIBS_COUNT whole
# derived projects and then builds an application against all of them.
set_tests_properties(ITEST_many_libs.noArgs PROPERTIES TIMEOUT 3600)
