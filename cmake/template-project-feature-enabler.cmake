cmake_minimum_required(VERSION 3.13)

if(ENABLE_UNIT_TESTS)
  enable_testing()
  include(template-project-make-GTest-available)
endif()

if(ENABLE_CLANGFORMAT)
  include(template-project-clang-format-target)
endif()

if(ENABLE_CPPCHECK)
  include(template-project-cppcheck-target)
endif()

if(ENABLE_VALGRIND)
  include(template-project-valgrind-target)
endif()
