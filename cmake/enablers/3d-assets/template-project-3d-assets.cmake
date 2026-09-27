cmake_minimum_required(VERSION 3.13)

include_guard(GLOBAL)

set(
  TEMPLATE_APP_ASSETS_DIR "${CMAKE_BINARY_DIR}/assets"
  CACHE PATH "The directory the 3D assets are fetched into (or reused from): a <type>s/<name> subdirectory per asset and a licenses/<type>s/<name>.txt record of its source and license"
)

set(
  ASSETS_ALLOWED_LICENSES "creativecommons.org/publicdomain/zero/1.0"
  CACHE STRING "The license URLs (or their parts) an asset has to be published under to be fetched, the CC0 alone by default"
)

# Makes an asset of a provider available under the TEMPLATE_APP_ASSETS_DIR
# directory and records its source and license:
#
#   template_project_add_asset(
#     PROVIDER <POLYHAVEN|KENNEY|QUATERNIUS|GLTF_SAMPLE>
#     ID <the asset id at the provider>
#     [TYPE <MODEL|TEXTURE|HDRI>]  # MODEL by default, names the <type>s subdirectory
#     [NAME <name>]                # the ID by default, names the asset subdirectory
#     [<the provider options>...]
#   )
#
# A provider is the template_project_<provider>_asset function its
# ENABLE_<PROVIDER>_ASSETS enabler defines. An already present asset directory
# is reused as is: delete it to fetch the asset anew.
function(template_project_add_asset)
  if (CMAKE_VERSION VERSION_LESS 3.19)
    message(FATAL_ERROR "The 3D assets demand the CMake 3.19 or newer, while this one is ${CMAKE_VERSION}")
  endif()

  cmake_parse_arguments(ARG "" "PROVIDER;ID;TYPE;NAME" "" ${ARGN})

  string(TOLOWER "${ARG_PROVIDER}" provider)

  if (NOT COMMAND template_project_${provider}_asset)
    message(FATAL_ERROR "No '${ARG_PROVIDER}' 3D assets provider available, set the ENABLE_${ARG_PROVIDER}_ASSETS variable ON")
  endif()

  if (NOT ARG_TYPE)
    set(ARG_TYPE MODEL)
  endif()

  if (NOT ARG_NAME)
    set(ARG_NAME "${ARG_ID}")
  endif()

  string(TOLOWER "${ARG_TYPE}s" typeDir)

  set(assetDir "${TEMPLATE_APP_ASSETS_DIR}/${typeDir}/${ARG_NAME}")

  if (EXISTS "${assetDir}")
    message(STATUS "3D asset already available: ${assetDir}")
    return()
  endif()

  message(STATUS "Fetching the ${ARG_PROVIDER} ${ARG_ID} 3D asset")

  # an interrupted fetch leaves no directory to be taken for a complete one
  set(partDir "${assetDir}.part")

  file(REMOVE_RECURSE "${partDir}")

  cmake_language(CALL template_project_${provider}_asset "${partDir}" "${ARG_ID}" license ${ARG_UNPARSED_ARGUMENTS})

  file(WRITE "${TEMPLATE_APP_ASSETS_DIR}/licenses/${typeDir}/${ARG_NAME}.txt" "${license}")
  file(RENAME "${partDir}" "${assetDir}")

  message(STATUS "3D asset available: ${assetDir}")
endfunction()

# The rest of the arguments go to the file(DOWNLOAD) command as they are.
function(template_project_assets_download url destination)
  file(
    DOWNLOAD "${url}" "${destination}"
    STATUS downloadStatus
    TLS_VERIFY ON
    ${ARGN}
  )

  list(GET downloadStatus 0 downloadCode)

  if (NOT downloadCode EQUAL 0)
    list(GET downloadStatus 1 downloadError)
    file(REMOVE "${destination}")
    message(FATAL_ERROR "Fail to download ${url}: ${downloadError}")
  endif()
endfunction()

# Refuses a relative path which leads out of the asset directory.
function(template_project_assets_download_into assetDir path url)
  if (IS_ABSOLUTE "${path}" OR path MATCHES "(^|/)\\.\\.(/|$)")
    message(FATAL_ERROR "Refusing the '${path}' asset file leading out of the ${assetDir} directory")
  endif()

  template_project_assets_download("${url}" "${assetDir}/${path}" ${ARGN})
endfunction()

function(template_project_assets_read url outVar)
  set(pageFile "${CMAKE_BINARY_DIR}/CMakeFiles/template-project-assets-page.tmp")

  template_project_assets_download("${url}" "${pageFile}" ${ARGN})

  file(READ "${pageFile}" content)
  file(REMOVE "${pageFile}")

  set(${outVar} "${content}" PARENT_SCOPE)
endfunction()

# Unpacks a ZIP or a 7z archive and removes it. The Windows made archives
# carry the DOS read-only attribute on some directories, which the extraction
# turns into directories nothing may be created in or removed from, hence the
# extraction aside and the copy dropping the archive permissions.
function(template_project_assets_unpack archive destination)
  set(unpackDir "${destination}.unpacked")

  file(REMOVE_RECURSE "${unpackDir}")
  file(MAKE_DIRECTORY "${unpackDir}")

  execute_process(
    COMMAND "${CMAKE_COMMAND}" -E tar xf "${archive}"
    WORKING_DIRECTORY "${unpackDir}"
    RESULT_VARIABLE extractResult
  )

  file(REMOVE "${archive}")

  if (NOT extractResult EQUAL 0)
    file(REMOVE_RECURSE "${unpackDir}")
    message(FATAL_ERROR "Fail to unpack the ${archive} archive")
  endif()

  file(COPY "${unpackDir}/" DESTINATION "${destination}" NO_SOURCE_PERMISSIONS)
  file(REMOVE_RECURSE "${unpackDir}")
endfunction()

function(template_project_assets_license_allowed licenseUrl outVar)
  foreach(allowed IN LISTS ASSETS_ALLOWED_LICENSES)
    string(FIND "${licenseUrl}" "${allowed}" position)

    if (NOT position EQUAL -1)
      set(${outVar} TRUE PARENT_SCOPE)
      return()
    endif()
  endforeach()

  set(${outVar} FALSE PARENT_SCOPE)
endfunction()
