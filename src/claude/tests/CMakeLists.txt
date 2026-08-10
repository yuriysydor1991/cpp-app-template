cmake_minimum_required(VERSION 3.13)

# The mocks of the whole project are gathered under the app tests, so the
# CURLController and the log ones are taken from there rather than duplicated.
set(CLAUDE_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")

add_subdirectory(unit)
