cmake_minimum_required(VERSION 3.13)

# Enabler module for the Firebird client library (fbclient).
#
# Unlike the libcurl/LibXml2/nlohmann-json enablers this one does not delegate
# to the shared template_project_default_3rdparty_enabler: its FetchContent
# fallback is useless for Firebird. Firebird is an autotools project whose root
# CMakeLists.txt is a legacy leftover that requires CMake 2.8.12, resolves its
# modules through the top level CMAKE_SOURCE_DIR and never exports a consumable
# client library target, so adding it as a subproject only breaks the configure
# stage. The development package is the expected and supported path.
#
# The system probe is performed through the project cmake/FindFirebird.cmake
# module, which exposes the Firebird::fbclient imported target the Firebird
# driver links against.

option(
  ENABLE_FIREBIRD
  "Set to ON to enable the Firebird client library (fbclient) integration"
  ON
)

if (NOT ENABLE_FIREBIRD)
  return()
endif()

message(STATUS "Trying to probe system installed Firebird")

find_package(Firebird QUIET)

if (NOT Firebird_FOUND)
  message(
    FATAL_ERROR
    "The Firebird client library (fbclient) development files are not available "
    "in the system. Install them (for example 'sudo apt install -y firebird-dev') "
    "or point the TEMPLATE_APP_FIREBIRD_INCLUDE_HINT and the "
    "TEMPLATE_APP_FIREBIRD_LIB_HINT cache variables at your own Firebird "
    "installation."
  )
endif()

message(STATUS "The project Firebird is made available")
