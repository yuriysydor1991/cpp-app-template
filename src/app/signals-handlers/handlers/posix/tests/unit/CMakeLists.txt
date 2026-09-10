cmake_minimum_required(VERSION 3.13)

if(NOT ENABLE_UNIT_TESTS)
  return()
endif()

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_subdirectory(ContinueSignalsHandler)
add_subdirectory(IgnoredSignalsHandler)
add_subdirectory(PauseSignalsHandler)
add_subdirectory(ReloadSignalsHandler)
add_subdirectory(StopSignalsHandler)
add_subdirectory(UserSignalsHandler)
