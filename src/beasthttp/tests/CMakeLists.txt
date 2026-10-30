cmake_minimum_required(VERSION 3.13)

# Reuse the application level mocks (the context and the log subsystem).
set(APP_MOCKS_ROOT "${PROJECT_SOURCE_DIR}/src/app/tests/mocks")

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_subdirectory(component)
