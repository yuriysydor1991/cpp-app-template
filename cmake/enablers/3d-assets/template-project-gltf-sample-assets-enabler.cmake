cmake_minimum_required(VERSION 3.13)

include(template-project-3d-assets)

option(
  ENABLE_GLTF_SAMPLE_ASSETS
  "Enables the Khronos glTF Sample Assets (the glTF renderer test models) fetch"
  OFF
)

if (NOT ENABLE_GLTF_SAMPLE_ASSETS)
  return()
endif()

set(TEMPLATE_APP_GLTF_SAMPLE_ASSETS_URL "https://raw.githubusercontent.com/KhronosGroup/glTF-Sample-Assets/main" CACHE STRING "The Khronos glTF Sample Assets repository files address (with the branch or commit of interest)")
set(GLTF_SAMPLE_VARIANT "glTF-Binary" CACHE STRING "The glTF sample models variant: glTF-Binary, glTF, glTF-Embedded, glTF-Draco, ...")
set(GLTF_SAMPLE_MODELS "WaterBottle" CACHE STRING "The glTF sample models to fetch")

# Gives the URI back with its %XX escapes decoded.
function(template_project_gltf_sample_decode_uri uri outVar)
  while (uri MATCHES "%([0-9A-Fa-f][0-9A-Fa-f])")
    set(escape "${CMAKE_MATCH_1}")
    math(EXPR code "0x${escape}")
    string(ASCII ${code} character)
    string(REPLACE "%${escape}" "${character}" uri "${uri}")
  endwhile()

  set(${outVar} "${uri}" PARENT_SCOPE)
endfunction()

# Fetches the model file of the VARIANT (GLTF_SAMPLE_VARIANT by default)
# together with the buffers and images it refers to, once every license of the
# model is on the ASSETS_ALLOWED_LICENSES list:
#
#   template_project_add_asset(PROVIDER GLTF_SAMPLE ID <model> [VARIANT <variant>])
#
# The models carry a license per author and per part, all of them binding.
function(template_project_gltf_sample_asset assetDir id licenseVar)
  cmake_parse_arguments(ARG "" "VARIANT" "" ${ARGN})

  if (NOT ARG_VARIANT)
    set(ARG_VARIANT "${GLTF_SAMPLE_VARIANT}")
  endif()

  string(REPLACE " " "%20" model "${id}")
  set(modelUrl "${TEMPLATE_APP_GLTF_SAMPLE_ASSETS_URL}/Models/${model}")

  template_project_assets_read("${modelUrl}/metadata.json" metadata)

  string(JSON legalCount LENGTH "${metadata}" legal)

  if (legalCount EQUAL 0)
    message(FATAL_ERROR "The glTF sample ${id} model records no license")
  endif()

  set(record "Source: ${modelUrl}\n")
  math(EXPR lastLegal "${legalCount} - 1")

  foreach(index RANGE ${lastLegal})
    foreach(field license licenseUrl artist year what)
      string(JSON ${field} GET "${metadata}" legal ${index} ${field})
    endforeach()

    template_project_assets_license_allowed("${licenseUrl}" allowed)

    if (NOT allowed)
      message(FATAL_ERROR "The glTF sample ${id} model carries the ${license} license (${licenseUrl}) for the '${what}' by ${artist}, which the ASSETS_ALLOWED_LICENSES list lacks")
    endif()

    string(APPEND record "License: ${license} (${licenseUrl}) - ${what} by ${artist}, ${year}\n")
  endforeach()

  # the variants carrying Binary in their name are the .glb ones
  set(extension gltf)

  if (ARG_VARIANT MATCHES "Binary")
    set(extension glb)
  endif()

  set(variantUrl "${modelUrl}/${ARG_VARIANT}")
  set(modelFile "${assetDir}/${id}.${extension}")

  template_project_assets_download("${variantUrl}/${model}.${extension}" "${modelFile}" SHOW_PROGRESS)

  if (extension STREQUAL gltf)
    file(READ "${modelFile}" gltf)

    foreach(section buffers images)
      string(JSON count ERROR_VARIABLE noSection LENGTH "${gltf}" ${section})

      if (noSection OR count EQUAL 0)
        continue()
      endif()

      math(EXPR last "${count} - 1")

      foreach(index RANGE ${last})
        string(JSON uri ERROR_VARIABLE noUri GET "${gltf}" ${section} ${index} uri)

        # a buffer view image or an embedded data: one has no file to fetch
        if (noUri OR uri MATCHES "^data:")
          continue()
        endif()

        template_project_gltf_sample_decode_uri("${uri}" path)
        string(REPLACE " " "%20" remotePath "${path}")

        template_project_assets_download_into("${assetDir}" "${path}" "${variantUrl}/${remotePath}")
      endforeach()
    endforeach()
  endif()

  set(${licenseVar} "${record}" PARENT_SCOPE)
endfunction()

foreach(model IN LISTS GLTF_SAMPLE_MODELS)
  template_project_add_asset(PROVIDER GLTF_SAMPLE ID "${model}")
endforeach()
