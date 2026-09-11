cmake_minimum_required(VERSION 3.13)

if(NOT ENABLE_UNIT_TESTS)
  return()
endif()

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_subdirectory(KenneySound)
add_subdirectory(KenneyPacks)
add_subdirectory(KenneySounds)
add_subdirectory(KenneyResourcePath)
add_subdirectory(KenneyRandomSound)
add_subdirectory(KenneySoundsController)
