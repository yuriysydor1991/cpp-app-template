cmake_minimum_required(VERSION 3.13)

include(template-project-3d-assets)

option(
  ENABLE_QUATERNIUS_ASSETS
  "Enables the Quaternius (CC0 low-poly models, characters and animations) 3D assets fetch through their OpenGameArt submissions"
  OFF
)

if (NOT ENABLE_QUATERNIUS_ASSETS)
  return()
endif()

set(TEMPLATE_APP_QUATERNIUS_ASSETS_URL "https://opengameart.org/content" CACHE STRING "The OpenGameArt submission pages address")
set(QUATERNIUS_PACKS "universal-animation-library" CACHE STRING "The Quaternius packs (OpenGameArt submission names) to fetch")

# Fetches the archives the submission page lists and keeps the pack intact:
#
#   template_project_add_asset(PROVIDER QUATERNIUS ID <submission>)
#
# Quaternius hands the packs out as Google Drive folders at quaternius.com,
# while the OpenGameArt submissions carry them as single archives. A
# submission may offer several licenses to choose from, one allowed is enough.
function(template_project_quaternius_asset assetDir id licenseVar)
  set(packPage "${TEMPLATE_APP_QUATERNIUS_ASSETS_URL}/${id}")

  template_project_assets_read("${packPage}" page)

  string(REGEX MATCHALL "license-icon'><a href='[^']*'[^>]*><img[^>]*><div class='license-name'>[^<]*" licenses "${page}")
  string(REGEX MATCHALL "href=\"[^\"]*\" type=\"application/(zip|x-7z-compressed)" archives "${page}")

  set(license "")

  foreach(licenseEntry IN LISTS licenses)
    string(REGEX MATCH "href='([^']*)'.*'license-name'>(.*)$" matched "${licenseEntry}")
    template_project_assets_license_allowed("${CMAKE_MATCH_1}" allowed)

    if (allowed)
      set(license "${CMAKE_MATCH_2} (${CMAKE_MATCH_1})")
      break()
    endif()
  endforeach()

  if (NOT archives OR NOT license)
    message(FATAL_ERROR "The ${packPage} submission names no archive under a license of the ASSETS_ALLOWED_LICENSES list")
  endif()

  foreach(archiveEntry IN LISTS archives)
    string(REGEX MATCH "href=\"([^\"]*)\"" matched "${archiveEntry}")

    template_project_assets_download("${CMAKE_MATCH_1}" "${assetDir}.archive" SHOW_PROGRESS)
    template_project_assets_unpack("${assetDir}.archive" "${assetDir}")
  endforeach()

  set(${licenseVar} "Source: ${packPage}\nLicense: ${license}\n" PARENT_SCOPE)
endfunction()

foreach(pack IN LISTS QUATERNIUS_PACKS)
  template_project_add_asset(PROVIDER QUATERNIUS ID "${pack}")
endforeach()
