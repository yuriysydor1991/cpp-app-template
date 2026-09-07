cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_STEAMWORKS
    "Enables the Steamworks SDK (Steam platform integration) for the project usage through a locally extracted SDK directory"
    OFF
)

if (NOT ENABLE_STEAMWORKS)
    return()
endif()

# The Steamworks SDK is proprietary and is not downloadable without a
# Steamworks account, so there is neither a system probe nor a FetchContent
# fallback here: grab the archive at https://partner.steamgames.com/downloads/list,
# extract it and point the variable below to the 'sdk' directory it contains.
set(
  TEMPLATE_APP_STEAMWORKS_SDK_DIR
  "$ENV{STEAMWORKS_SDK_DIR}"
  CACHE PATH "The extracted Steamworks SDK 'sdk' directory path"
)

if (NOT TEMPLATE_APP_STEAMWORKS_SDK_DIR)
  message(FATAL_ERROR
    "ENABLE_STEAMWORKS is ON but no Steamworks SDK directory is given. "
    "Pass -DTEMPLATE_APP_STEAMWORKS_SDK_DIR=/path/to/sdk or export the "
    "STEAMWORKS_SDK_DIR environment variable.")
endif()

if (WIN32)
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(STEAMWORKS_REDISTRIBUTABLE "redistributable_bin/win64/steam_api64.dll")
    set(STEAMWORKS_IMPORT_LIBRARY "redistributable_bin/win64/steam_api64.lib")
  else()
    set(STEAMWORKS_REDISTRIBUTABLE "redistributable_bin/steam_api.dll")
    set(STEAMWORKS_IMPORT_LIBRARY "redistributable_bin/steam_api.lib")
  endif()
elseif (APPLE)
  set(STEAMWORKS_REDISTRIBUTABLE "redistributable_bin/osx/libsteam_api.dylib")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
  set(STEAMWORKS_REDISTRIBUTABLE "redistributable_bin/linuxarm64/libsteam_api.so")
elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(STEAMWORKS_REDISTRIBUTABLE "redistributable_bin/linux64/libsteam_api.so")
else()
  set(STEAMWORKS_REDISTRIBUTABLE "redistributable_bin/linux32/libsteam_api.so")
endif()

set(STEAMWORKS_INCLUDE_DIR "${TEMPLATE_APP_STEAMWORKS_SDK_DIR}/public")
set(
  TEMPLATE_APP_STEAMWORKS_REDISTRIBUTABLE
  "${TEMPLATE_APP_STEAMWORKS_SDK_DIR}/${STEAMWORKS_REDISTRIBUTABLE}"
)

foreach(STEAMWORKS_REQUIRED_FILE
        "${STEAMWORKS_INCLUDE_DIR}/steam/steam_api.h"
        "${TEMPLATE_APP_STEAMWORKS_REDISTRIBUTABLE}")
  if (NOT EXISTS "${STEAMWORKS_REQUIRED_FILE}")
    message(FATAL_ERROR
      "The '${STEAMWORKS_REQUIRED_FILE}' is missing: the "
      "TEMPLATE_APP_STEAMWORKS_SDK_DIR value does not point to an extracted "
      "Steamworks SDK 'sdk' directory.")
  endif()
endforeach()

message(STATUS "Steamworks SDK found at ${TEMPLATE_APP_STEAMWORKS_SDK_DIR}")

add_library(Steamworks::Steamworks SHARED IMPORTED GLOBAL)

set_target_properties(
  Steamworks::Steamworks PROPERTIES
  IMPORTED_LOCATION "${TEMPLATE_APP_STEAMWORKS_REDISTRIBUTABLE}"
  INTERFACE_INCLUDE_DIRECTORIES "${STEAMWORKS_INCLUDE_DIR}"
)

if (STEAMWORKS_IMPORT_LIBRARY)
  set_target_properties(
    Steamworks::Steamworks PROPERTIES
    IMPORTED_IMPLIB "${TEMPLATE_APP_STEAMWORKS_SDK_DIR}/${STEAMWORKS_IMPORT_LIBRARY}"
  )
endif()

# The Steam client library is loaded from beside the executable, so it goes
# into the installation (and thus into the packages) next to the binary.
install(
  FILES "${TEMPLATE_APP_STEAMWORKS_REDISTRIBUTABLE}"
  DESTINATION ${PROJECT_BINARY_INSTALLATION_DIR}
)

# Link the following Steamworks target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - local SDK directory only: Steamworks::Steamworks
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} Steamworks::Steamworks)
