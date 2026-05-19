cmake_minimum_required(VERSION 3.13)

set(SDL_BACKEND_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")
set(APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")

add_subdirectory(unit)
add_subdirectory(component)
