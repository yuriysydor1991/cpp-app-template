cmake_minimum_required(VERSION 3.13)

if(NOT ENABLE_UNIT_TESTS)
  return()
endif()

set(FACADE_MOCK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/mocks)

add_subdirectory(unit)
