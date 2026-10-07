cmake_minimum_required(VERSION 3.13)

if (NOT (ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS))
  return()
endif()

# The adaptor with the darknetxx core and the real project logger, which the
# darknetxx messages get into.
set(
  DARKNETXX_TESTS_LIBRARIES
  GTest::gtest_main GTest::gmock
  TemplateProjectDarknetXXObj
  TemplateProjectDarknetXXLogObj
  TemplateProjectDefaultLoggerObj
  TemplateProjectRealDefaultLoggerObj
)

add_subdirectory(unit)
add_subdirectory(component)
