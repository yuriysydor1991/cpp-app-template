cmake_minimum_required(VERSION 3.13)

# Reuse the application level mocks (the mock log subsystem and the mock
# application context) for the Wt4 tests.
set(APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")

add_subdirectory(unit)
