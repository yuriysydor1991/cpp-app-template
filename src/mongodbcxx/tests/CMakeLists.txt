cmake_minimum_required(VERSION 3.13)

# Reuse the application level mocks (mock log subsystem) in the test
# subdirectories.
set(APP_MOCKS_ROOT "${PROJECT_SOURCE_DIR}/src/app/tests/mocks")

add_subdirectory(unit)
add_subdirectory(component)
