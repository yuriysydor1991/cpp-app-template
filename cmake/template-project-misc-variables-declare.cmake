cmake_minimum_required(VERSION 3.13)

set(
  PROJECT_LIBRARY_NAME "${PROJECT_NAME}Lib"
  CACHE STRING "Project main library name and target"
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
  DOXYGEN_MAIN_PAGE_MD "README.md"
  CACHE STRING "Sets the Doxygen main README file to place into documentation the home page."
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
  DOXYGEN_OUT_HTML_NAME ${PROJECT_LIBRARY_NAME}-html
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
  COMPILE_WARNINGS_AS_ERRORS
  "Set to ON if to pass -Werror compile parameter to the GCC compiler."
  OFF
)

option(
  ENABLE_COMPILER_CODE_ANALYZER
  "Set to ON if to pass -fanalyzer compile parameter to the GCC compiler. May dramatically increase the compile time."
  OFF
)

option(
  ENABLE_CLANG_TIDY
  "Set to ON if enable the clang-tidy code check target."
  OFF
)

option(
  ENABLE_DEB
  "Set to ON to enable the deb package creation from the project build artifacts"
  OFF
)

string(TIMESTAMP PROJECT_CONFIGURE_DATE "%Y-%m-%d %H:%M:%S")

execute_process(
  COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
  OUTPUT_VARIABLE PROJECT_GIT_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
