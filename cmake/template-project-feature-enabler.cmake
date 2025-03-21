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

if(ENABLE_CLANG_TIDY)
  include(template-project-clang-tidy-target)
endif()

if(ENABLE_DEB)
  include(template-project-deb-enabler)
endif()

if(ENABLE_FLATPAK)
  include(template-project-flatpak-target)
endif()
