cmake_minimum_required(VERSION 3.13)

# Change the PROJECT_NAME var value to change executable name
set(
  PROJECT_NAME "CppAppTemplate"
  CACHE STRING "Project general name with an executable name"
)

project(
  ${PROJECT_NAME}
  VERSION 0.4.0
  DESCRIPTION "A C++ Template project for you!"
  HOMEPAGE_URL "http://www.kytok.org.ua/"
  LANGUAGES CXX
)

find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

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

string(TIMESTAMP PROJECT_CONFIGURE_DATE "%Y-%m-%d %H:%M:%S")

execute_process(
  COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
  OUTPUT_VARIABLE PROJECT_GIT_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(ENABLE_UNIT_TESTS)
  enable_testing()
  include(template-project-make-GTest-available)
endif()

message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "PROJECT_BINARY_NAME: ${PROJECT_BINARY_NAME}")

add_subdirectory(src)
add_subdirectory(doc)
