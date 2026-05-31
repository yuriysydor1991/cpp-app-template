cmake_minimum_required(VERSION 3.16)

if(NOT ENABLE_COMPONENT_TESTS)
  return()
endif()

add_subdirectory(Hostname1QueryHandler)
