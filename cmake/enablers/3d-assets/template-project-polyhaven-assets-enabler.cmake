cmake_minimum_required(VERSION 3.13)

include(template-project-3d-assets)

option(
  ENABLE_POLYHAVEN_ASSETS
  "Enables the Poly Haven (CC0 models, PBR textures and HDRIs) assets fetch through the Poly Haven API"
  OFF
)

if (NOT ENABLE_POLYHAVEN_ASSETS)
  return()
endif()

set(TEMPLATE_APP_POLYHAVEN_API_URL "https://api.polyhaven.com" CACHE STRING "The Poly Haven API address")
set(POLYHAVEN_RESOLUTION "1k" CACHE STRING "The Poly Haven assets resolution: 1k, 2k, 4k or 8k")
set(POLYHAVEN_MODELS "Barrel_01" CACHE STRING "The Poly Haven models to fetch")
set(POLYHAVEN_TEXTURES "" CACHE STRING "The Poly Haven textures to fetch")

# Fetches the files the API lists for the FILES <map>/<extension> entries
# (gltf/gltf by default: the glTF scene with its buffer and textures) in the
# RESOLUTION given, each checked against its MD5 sum:
#
#   template_project_add_asset(
#     PROVIDER POLYHAVEN ID <asset> [TYPE <MODEL|TEXTURE|HDRI>]
#     [RESOLUTION <1k|2k|4k|8k>] [FILES <map>/<extension>...]
#   )
#
# e.g. FILES hdri/hdr for an HDRI or FILES Diffuse/jpg nor_gl/png for single
# texture maps.
function(template_project_polyhaven_asset assetDir id licenseVar)
  cmake_parse_arguments(ARG "" "RESOLUTION" "FILES" ${ARGN})

  if (NOT ARG_RESOLUTION)
    set(ARG_RESOLUTION "${POLYHAVEN_RESOLUTION}")
  endif()

  if (NOT ARG_FILES)
    set(ARG_FILES gltf/gltf)
  endif()

  # the API terms demand every request to name the software making it
  set(userAgent HTTPHEADER "User-Agent: ${PROJECT_BINARY_NAME}/${PROJECT_VERSION}")

  template_project_assets_read("${TEMPLATE_APP_POLYHAVEN_API_URL}/files/${id}" files ${userAgent})

  foreach(file IN LISTS ARG_FILES)
    string(REPLACE "/" ";" entry "${file}")
    list(INSERT entry 1 "${ARG_RESOLUTION}")

    string(JSON url ERROR_VARIABLE noFile GET "${files}" ${entry} url)

    if (noFile)
      message(FATAL_ERROR "The Poly Haven ${id} asset has no ${file} file in the ${ARG_RESOLUTION} resolution")
    endif()

    string(JSON md5 GET "${files}" ${entry} md5)
    get_filename_component(fileName "${url}" NAME)

    template_project_assets_download("${url}" "${assetDir}/${fileName}" EXPECTED_MD5 "${md5}" ${userAgent})

    string(JSON includes ERROR_VARIABLE noIncludes LENGTH "${files}" ${entry} include)

    if (noIncludes OR includes EQUAL 0)
      continue()
    endif()

    math(EXPR lastInclude "${includes} - 1")

    foreach(index RANGE ${lastInclude})
      string(JSON path MEMBER "${files}" ${entry} include ${index})
      string(JSON url GET "${files}" ${entry} include "${path}" url)
      string(JSON md5 GET "${files}" ${entry} include "${path}" md5)

      template_project_assets_download_into("${assetDir}" "${path}" "${url}" EXPECTED_MD5 "${md5}" ${userAgent})
    endforeach()
  endforeach()

  set(${licenseVar} "Source: https://polyhaven.com/a/${id}\nLicense: CC0 (https://polyhaven.com/license)\n" PARENT_SCOPE)
endfunction()

foreach(model IN LISTS POLYHAVEN_MODELS)
  template_project_add_asset(PROVIDER POLYHAVEN ID "${model}")
endforeach()

foreach(texture IN LISTS POLYHAVEN_TEXTURES)
  template_project_add_asset(PROVIDER POLYHAVEN ID "${texture}" TYPE TEXTURE)
endforeach()
