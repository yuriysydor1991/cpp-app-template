cmake_minimum_required(VERSION 3.13)

set(PLOTGENCPP_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

# The log mock of the whole project lives under the app tests, so it is taken
# from there rather than duplicated.
set(PLOTGENCPP_LOG_MOCK_ROOT "${PROJECT_SOURCE_DIR}/src/app/tests/mocks/log")

add_subdirectory(unit)
add_subdirectory(component)
