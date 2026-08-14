cmake_minimum_required(VERSION 3.13)

if(NOT ENABLE_INTEGRATION_TESTS)
  return()
endif()

add_subdirectory(many-libs)
