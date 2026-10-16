cmake_minimum_required(VERSION 3.13)

# Reuse the application level mocks (mock log subsystem) and expose the MySQL
# component mocks to the test subdirectories.
set(APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")
set(MYSQL_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

add_subdirectory(unit)
add_subdirectory(component)
