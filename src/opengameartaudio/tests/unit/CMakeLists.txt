cmake_minimum_required(VERSION 3.13)

if(NOT ENABLE_UNIT_TESTS)
  return()
endif()

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_subdirectory(OpenGameArtSound)
add_subdirectory(OpenGameArtPacks)
add_subdirectory(OpenGameArtSounds)
add_subdirectory(OpenGameArtResourcePath)
add_subdirectory(OpenGameArtRandomSound)
add_subdirectory(OpenGameArtSoundsController)
