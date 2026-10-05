cmake_minimum_required(VERSION 3.13)

# The log mock of the whole project is kept under the app tests, so it is taken
# from there rather than duplicated.
set(V8_LOG_MOCK_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks/log")
set(V8_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

add_subdirectory(unit)
add_subdirectory(component)
