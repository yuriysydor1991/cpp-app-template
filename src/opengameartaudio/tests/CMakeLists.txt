cmake_minimum_required(VERSION 3.13)

# The mocks of the whole project are gathered under the app tests, so the log
# one is taken from there rather than duplicated. The generated sounds index
# stand-in stays here, next to the very subsystem it answers for.
set(OPENGAMEART_AUDIO_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")
set(OPENGAMEART_AUDIO_OWN_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

add_subdirectory(unit)
add_subdirectory(component)
