cmake_minimum_required(VERSION 3.22.1)

if(NOT ENABLE_UNIT_TESTS)
  return()
endif()

# disabling the asserts for the tests
add_compile_options(-DNDEBUG=1)

add_subdirectory(Application)
add_subdirectory(ApplicationContext)
