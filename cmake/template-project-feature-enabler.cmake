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

# The Wt4 framework is enabled here and not in the post enabler file, because
# the src/wt4 component compiles against it and the whole src subdirectory is
# added after this file is included.
include(template-project-Wt4-enabler)

include(template-project-GTest-enabler)
include(template-project-clang-format-target)
include(template-project-valgrind-target)

# packagers
include(template-project-deb-enabler)
include(template-project-flatpak-target)
include(template-project-snap-enabler)
include(template-project-freebsd-pkg-enabler)
include(template-project-wix-enabler)
include(template-project-rpm-enabler)
include(template-project-appimage-general-enabler)

# compile options
include(template-project-sanitizers)

# analyzers
include(template-project-cppcheck-target)
include(template-project-clang-tidy-target)

# profilers
include(template-project-profiler-gprof)
include(template-project-profiler-valgrind-callgrind)
