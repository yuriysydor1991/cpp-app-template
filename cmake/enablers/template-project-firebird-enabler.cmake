cmake_minimum_required(VERSION 3.16)

option(
  ENABLE_FIREBIRD
  "Set to ON to enable the Firebird client library (fbclient) (by using system wide available or through the Internet)"
  ON
)

if (NOT ENABLE_FIREBIRD)
  return()
endif()

set(TEMPLATE_APP_FIREBIRD_GIT "https://github.com/FirebirdSQL/firebird.git" CACHE STRING "The Firebird DBMS git source repository")
set(TEMPLATE_APP_FIREBIRD_GIT_TAG "v5.0.4" CACHE STRING "The Firebird project git repository tag of interest")

# The project cmake/FindFirebird.cmake module probes the system installation.
message(STATUS "Trying to probe system installed Firebird")

find_package(Firebird QUIET)

if (Firebird_FOUND)
  message(STATUS "System already contains the Firebird library")
  return()
endif()

message(STATUS "The 'Firebird' is not available in the system")
message(STATUS "Trying to make Firebird library available through the Internet")

# Firebird is an autotools project whose root CMakeLists.txt is a legacy
# leftover, so the template_project_default_3rdparty_enabler FetchContent can
# not add it. The client library alone is built as an external project instead,
# with the binary relocation that makes it look for its libtommath, its
# configuration and its plugins next to itself.
include(ExternalProject)
include(ProcessorCount)

ProcessorCount(fbJobs)

set(fbStageDir ${CMAKE_BINARY_DIR}/_deps/firebird-src/gen/Release/firebird)

ExternalProject_Add(
  FirebirdClient
  GIT_REPOSITORY ${TEMPLATE_APP_FIREBIRD_GIT}
  GIT_TAG ${TEMPLATE_APP_FIREBIRD_GIT_TAG}
  GIT_SHALLOW ON
  GIT_SUBMODULES ""
  UPDATE_DISCONNECTED ON
  SOURCE_DIR ${CMAKE_BINARY_DIR}/_deps/firebird-src
  BUILD_IN_SOURCE ON
  CONFIGURE_COMMAND
    ./autogen.sh --enable-client-only --enable-binreloc
      --with-builtin-tommath --with-builtin-tomcrypt
  BUILD_COMMAND make -j${fbJobs}
  INSTALL_COMMAND ""
  BUILD_BYPRODUCTS ${fbStageDir}/lib/libfbclient.so
)

# The imported target include directory has to exist at the configure time.
file(MAKE_DIRECTORY ${fbStageDir}/include)

add_library(Firebird::fbclient SHARED IMPORTED GLOBAL)

set_target_properties(
  Firebird::fbclient PROPERTIES
  IMPORTED_LOCATION ${fbStageDir}/lib/libfbclient.so
  INTERFACE_INCLUDE_DIRECTORIES ${fbStageDir}/include
)

add_dependencies(Firebird::fbclient FirebirdClient)

message(STATUS "The project Firebird is made available")
