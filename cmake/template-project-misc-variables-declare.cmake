cmake_minimum_required(VERSION 3.13)

set(
  PROJECT_BINARY_NAME ${PROJECT_NAME}
  CACHE STRING "Project main binary name and target"
)

option(
  ENABLE_UNIT_TESTS 
  "Set to ON value if unit tests build and run should be available"
  OFF
)

option(
  GTEST_TRY_SYSTEM_PROBE 
  "Set to ON value if current project CMake files should probe the system GTest"
  ON
)

option(
  ENABLE_DOC_DOXYGEN 
  "Set to ON value if Doxygen documentation generation should be available"
  OFF
)

set(
  DOXYGEN_OUTPUT_LANGUAGE "English"
  CACHE STRING "Sets the Doxygen output language for the generated documentation (see doc/Doxyfile.in)"
)

set(
  DOXYGEN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/doc
  CACHE STRING "Sets the doxygen documentation output directory."
)

option(
  DOXYGEN_DO_INSTALL
  "Set to on if CMake should install the generated documentation during install command executed."
  OFF 
)

set(
  DOXYGEN_OUT_HTML_NAME ${PROJECT_BINARY_NAME}-html
  CACHE STRING "The Doxygen output HTML directory name (for the Doxyfile)"
)

set(
  DOXYGEN_OUT_HTML ${DOXYGEN_OUTPUT_DIR}/${DOXYGEN_OUT_HTML_NAME}
  CACHE STRING "Sets the doxygen documentation output full directory path."
)

option(
  ENABLE_CLANGFORMAT
  "Set to ON if to enable the clang-format command execution target."
  OFF
)

option(
  ENABLE_CPPCHECK
  "Set to ON if to enable the cppcheck execution target."
  OFF
)

option(
  ENABLE_VALGRIND
  "Set to ON if to enable the valgrind memory check execution target."
  OFF
)

string(TIMESTAMP PROJECT_CONFIGURE_DATE "%Y-%m-%d %H:%M:%S")

execute_process(
  COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
  OUTPUT_VARIABLE PROJECT_GIT_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
