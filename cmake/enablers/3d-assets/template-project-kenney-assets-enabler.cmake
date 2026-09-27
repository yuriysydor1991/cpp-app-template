cmake_minimum_required(VERSION 3.13)

include(template-project-3d-assets)

option(
  ENABLE_KENNEY_ASSETS
  "Enables the Kenney (CC0 low-poly game kits) 3D assets fetch"
  OFF
)

if (NOT ENABLE_KENNEY_ASSETS)
  return()
endif()

set(TEMPLATE_APP_KENNEY_ASSETS_URL "https://kenney.nl/assets" CACHE STRING "The Kenney assets pages address")
set(KENNEY_PACKS "castle-kit" CACHE STRING "The Kenney 3D packs to fetch")

# Fetches the pack archive the pack page names and keeps the pack intact:
#
#   template_project_add_asset(PROVIDER KENNEY ID <pack>)
#
# The archive address carries a content hash the site regenerates on every
# pack update, hence it is read out of the page instead of written down.
function(template_project_kenney_asset assetDir id licenseVar)
  set(packPage "${TEMPLATE_APP_KENNEY_ASSETS_URL}/${id}")

  template_project_assets_read("${packPage}" page)

  string(REGEX MATCH "License</td>[ \t\r\n]*<td[^>]*><a href='([^']*)'[^>]*>([^<]*)</a>" license "${page}")
  set(licenseUrl "${CMAKE_MATCH_1}")
  set(licenseName "${CMAKE_MATCH_2}")

  string(REGEX MATCH "https://[^\"' \t\r\n]*/assets/${id}/[^\"' \t\r\n]*\\.zip" packUrl "${page}")

  if (NOT license OR NOT packUrl)
    message(FATAL_ERROR "The Kenney ${id} pack page at ${packPage} names no license or pack archive, check the pack name against ${TEMPLATE_APP_KENNEY_ASSETS_URL}")
  endif()

  template_project_assets_license_allowed("${licenseUrl}" allowed)

  if (NOT allowed)
    message(FATAL_ERROR "The Kenney ${id} pack is licensed under the ${licenseName} (${licenseUrl}), which the ASSETS_ALLOWED_LICENSES list lacks")
  endif()

  template_project_assets_download("${packUrl}" "${assetDir}.archive" SHOW_PROGRESS)
  template_project_assets_unpack("${assetDir}.archive" "${assetDir}")

  set(${licenseVar} "Source: ${packPage}\nLicense: ${licenseName} (${licenseUrl})\n" PARENT_SCOPE)
endfunction()

foreach(pack IN LISTS KENNEY_PACKS)
  template_project_add_asset(PROVIDER KENNEY ID "${pack}")
endforeach()
