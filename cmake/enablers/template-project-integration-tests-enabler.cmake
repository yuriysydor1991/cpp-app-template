cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_INTEGRATION_TESTS
  "Set to ON value if the integration tests build and run should be available"
  OFF
)

if(NOT ENABLE_INTEGRATION_TESTS)
  return()
endif()

enable_testing()
