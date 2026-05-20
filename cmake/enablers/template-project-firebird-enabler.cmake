cmake_minimum_required(VERSION 3.13)

# Reusable enabler module for the Firebird client library (fbclient).
#
# Kept in a separate file (just like the libcurl and the LibXml2 enablers) so it
# may be reused across components and branches. Including this module defines
# the imported target `Firebird::fbclient` that components link against.
#
# The Firebird client library does not ship a CMake package config nor a
# reliable pkg-config file across distributions, so the library and the headers
# are discovered with find_library()/find_path(). Optional hints may be provided
# through the cache variables declared below.

option(
  ENABLE_FIREBIRD
  "Set to ON to enable the Firebird client library (fbclient) integration"
  ON
)

if (NOT ENABLE_FIREBIRD)
  return()
endif()

set(
  TEMPLATE_APP_FIREBIRD_INCLUDE_HINT ""
  CACHE PATH "Optional directory hint that contains the Firebird ibase.h header"
)

set(
  TEMPLATE_APP_FIREBIRD_LIB_HINT ""
  CACHE PATH "Optional directory hint that contains the Firebird client library"
)

find_path(
  FIREBIRD_INCLUDE_DIR
  NAMES ibase.h
  HINTS ${TEMPLATE_APP_FIREBIRD_INCLUDE_HINT}
  PATH_SUFFIXES firebird
)

find_library(
  FIREBIRD_LIBRARY
  NAMES fbclient fbclient_ms
  HINTS ${TEMPLATE_APP_FIREBIRD_LIB_HINT}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  Firebird
  REQUIRED_VARS FIREBIRD_LIBRARY FIREBIRD_INCLUDE_DIR
)

if (NOT Firebird_FOUND)
  message(FATAL_ERROR
    "The Firebird client library (fbclient) was not found. Install the "
    "development package (for example 'sudo apt install -y firebird-dev'), or "
    "provide the TEMPLATE_APP_FIREBIRD_INCLUDE_HINT and "
    "TEMPLATE_APP_FIREBIRD_LIB_HINT cache hints. Configure with "
    "-DENABLE_FIREBIRD=OFF only if you are removing the Firebird integration.")
endif()

if (NOT TARGET Firebird::fbclient)
  add_library(Firebird::fbclient UNKNOWN IMPORTED)
  set_target_properties(
    Firebird::fbclient PROPERTIES
    IMPORTED_LOCATION "${FIREBIRD_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${FIREBIRD_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(FIREBIRD_INCLUDE_DIR FIREBIRD_LIBRARY)
