cmake_minimum_required(VERSION 3.13)

find_package(Git REQUIRED)

execute_process(
  COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
  OUTPUT_VARIABLE PROJECT_GIT_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND "${GIT_EXECUTABLE}" branch --show-current
  OUTPUT_VARIABLE PROJECT_CURRENT_BRANCH_NAME
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

file(
  GLOB_RECURSE 
  ALLSOURCES 
  LIST_DIRECTORIES false 
  CONFIGURE_DEPENDS
  "src/*.h" "src/*.cpp"
)

# The Objective-C++ sources of the macOS Cocoa window: formatted by the
# clang-format target, but kept away from the C++ only cppcheck one.
file(
  GLOB_RECURSE
  OBJCXXSOURCES
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "src/*.mm"
)
