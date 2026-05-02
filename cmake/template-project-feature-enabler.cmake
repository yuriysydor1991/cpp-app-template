cmake_minimum_required(VERSION 3.13)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/compile-options")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/compile-options/sanitizers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers/dockerers")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/enablers/packagers")

include(template-project-GTest-enabler)
include(template-project-clang-format-target)

# packagers
include(template-project-deb-enabler)

# compile options
include(template-project-sanitizers)

# analyzers
include(template-project-cppcheck-target)
include(template-project-clang-tidy-target)
