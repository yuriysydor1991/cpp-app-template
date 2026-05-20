cmake_minimum_required(VERSION 3.13)

# Reuse the application level mocks (the mock log subsystem) for the wxWidgets
# component tests so they stay free of the real logging and wxWidgets libraries.
set(APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")

add_subdirectory(unit)
add_subdirectory(component)
