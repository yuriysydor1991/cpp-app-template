cmake_minimum_required(VERSION 3.13)

# Reuse the application level mocks (mock log subsystem) and expose the Firebird
# component mocks to the test subdirectories.
set(APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")
set(FIREBIRD_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

add_subdirectory(unit)
add_subdirectory(component)
