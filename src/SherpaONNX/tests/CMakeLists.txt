cmake_minimum_required(VERSION 3.13)

if (NOT (ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS))
  return()
endif()

# The log mock of the whole project is kept under the app tests, so it is taken
# from there rather than duplicated.
set(SHERPAONNX_APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")
set(SHERPAONNX_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

add_subdirectory(unit)
add_subdirectory(component)
