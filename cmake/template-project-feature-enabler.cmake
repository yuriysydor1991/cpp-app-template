cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/tools")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/compile-options")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/compile-options/sanitizers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers/profilers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers/dockerers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers/packagers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers/compression")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers/images")

include(template-project-enabler-function)
include(template-project-git-enabler)

include(template-project-GTest-enabler)
include(template-project-clang-format-target)
include(template-project-valgrind-target)
include(template-project-zlib-enabler)

# packagers
include(template-project-deb-enabler)
include(template-project-flatpak-target)
include(template-project-snap-enabler)
include(template-project-freebsd-pkg-enabler)
include(template-project-wix-enabler)
include(template-project-rpm-enabler)

# The CPack AppImage generator demands the CMake 4.20, so the ENABLE_APPIMAGE
# of such a CMake takes the CPack enabler and leaves the custom target one,
# which every older CMake keeps using, out. The older CMake versions parse the
# CPack enabler file on the user demand alone.
option(
  ENABLE_APPIMAGE_CPACK
  "Set to ON to enable the AppImage package creation with the CPack generator (demands the CMake 4.20)"
  OFF
)

if(ENABLE_APPIMAGE AND CMAKE_VERSION VERSION_GREATER_EQUAL 4.20)
  set(ENABLE_APPIMAGE_CPACK ON)
endif()

if(ENABLE_APPIMAGE_CPACK)
  include(template-project-appimage-cpack-enabler)
else()
  include(template-project-appimage-enabler)
endif()

# compile options
include(template-project-sanitizers)

# analyzers
include(template-project-cppcheck-target)
include(template-project-clang-tidy-target)

# profilers
include(template-project-profiler-gprof)
include(template-project-profiler-valgrind-callgrind)
