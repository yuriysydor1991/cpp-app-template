# FindFirebird.cmake
#
# Locates a system installed Firebird client library (fbclient) and exposes it
# through the Firebird::fbclient imported target. The Firebird client ships
# neither a CMake package config nor a reliable pkg-config file across
# distributions, so the library and the headers are discovered with
# find_library()/find_path(). Optional hints may be provided through the cache
# variables declared below.
#
# This module is what lets the standard template_project_default_3rdparty_enabler
# probe Firebird with find_package(Firebird) just like any other dependency.
#
# Result variables:
#   Firebird_FOUND        - TRUE when both the library and the headers are found
#   FIREBIRD_LIBRARY      - full path to the discovered fbclient library
#   FIREBIRD_INCLUDE_DIR  - directory that contains the ibase.h header
#
# Imported target:
#   Firebird::fbclient    - the discovered Firebird client library

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

if (Firebird_FOUND AND NOT TARGET Firebird::fbclient)
  add_library(Firebird::fbclient UNKNOWN IMPORTED GLOBAL)
  set_target_properties(
    Firebird::fbclient PROPERTIES
    IMPORTED_LOCATION "${FIREBIRD_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${FIREBIRD_INCLUDE_DIR}"
  )
endif()

mark_as_advanced(FIREBIRD_INCLUDE_DIR FIREBIRD_LIBRARY)
