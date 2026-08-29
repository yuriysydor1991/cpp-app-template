cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_FONTAWESOME
  "Set to ON to make the whole Font Awesome Free icon set available (by reusing an already present checkout or by fetching one through the Internet)"
  ON
)

# The packager manifests carry the very same checkout, so it's coordinates
# stay declared even with the enabler itself switched off.
set(
  TEMPLATE_APP_FONTAWESOME_GIT "https://github.com/FortAwesome/Font-Awesome.git"
  CACHE STRING "The Font Awesome Free icon set git source repository"
)

set(
  TEMPLATE_APP_FONTAWESOME_GIT_TAG "7.3.1"
  CACHE STRING "The Font Awesome project git repository tag of interest"
)

if (NOT ENABLE_FONTAWESOME)
  return()
endif()

include(template-project-fontawesome-index-generator)
include(template-project-fontawesome-resources)

set(
  TEMPLATE_APP_FONTAWESOME_DIR ""
  CACHE PATH "An already available Font Awesome checkout to reuse instead of downloading one (leave empty to download)"
)

set(
  FONTAWESOME_STYLES "solid;regular;brands"
  CACHE STRING "The Font Awesome Free styles (the svgs/ subdirectories) to make available"
)

set(
  FONTAWESOME_QT_RESOURCE_PREFIX "/icons"
  CACHE STRING "The Qt resource system prefix the generated .qrc manifests place the icons under"
)

set(
  FONTAWESOME_GRESOURCE_PREFIX "/ua/org/kytok/template/${PROJECT_BINARY_NAME}/icons"
  CACHE STRING "The GResource prefix the generated .gresource.xml manifests place the icons under"
)

# Font Awesome is an asset repository and not a library: it ships no
# CMakeLists.txt, no find_package module and nothing to link against, so the
# shared template_project_default_3rdparty_enabler (a system probe followed by
# the add_subdirectory of the fetched project) has nothing to do here. The
# checkout carries every icon of every style, hence the shallow single tag
# clone and the escape hatch for an already present copy.
if (TEMPLATE_APP_FONTAWESOME_DIR)
  message(STATUS "Reusing the Font Awesome checkout: ${TEMPLATE_APP_FONTAWESOME_DIR}")

  set(FONTAWESOME_ROOT_DIR "${TEMPLATE_APP_FONTAWESOME_DIR}" CACHE INTERNAL "The Font Awesome checkout root directory")
else()
  message(STATUS "Trying to make the Font Awesome icon set available through the Internet")
  message(STATUS "Font Awesome URL: ${TEMPLATE_APP_FONTAWESOME_GIT}")
  message(STATUS "Font Awesome Tag: ${TEMPLATE_APP_FONTAWESOME_GIT_TAG}")

  include(FetchContent)

  FetchContent_Declare(
      fontawesome
      GIT_REPOSITORY ${TEMPLATE_APP_FONTAWESOME_GIT}
      GIT_TAG        ${TEMPLATE_APP_FONTAWESOME_GIT_TAG}
      GIT_SHALLOW    TRUE
      GIT_PROGRESS   TRUE
  )

  FetchContent_MakeAvailable(fontawesome)

  set(FONTAWESOME_ROOT_DIR "${fontawesome_SOURCE_DIR}" CACHE INTERNAL "The Font Awesome checkout root directory")
endif()

set(FONTAWESOME_SVGS_DIR "${FONTAWESOME_ROOT_DIR}/svgs" CACHE INTERNAL "The per style individual SVG icon files directory")
set(FONTAWESOME_WEBFONTS_DIR "${FONTAWESOME_ROOT_DIR}/webfonts" CACHE INTERNAL "The webfont files directory")
set(FONTAWESOME_SPRITES_DIR "${FONTAWESOME_ROOT_DIR}/sprites" CACHE INTERNAL "The per style SVG sprite sheets directory")
set(FONTAWESOME_METADATA_DIR "${FONTAWESOME_ROOT_DIR}/metadata" CACHE INTERNAL "The icon metadata (categories, aliases, unicode points) directory")
set(FONTAWESOME_LICENSE_FILE "${FONTAWESOME_ROOT_DIR}/LICENSE.txt" CACHE INTERNAL "The Font Awesome Free license file")

if (NOT EXISTS "${FONTAWESOME_SVGS_DIR}")
  message(
    FATAL_ERROR
    "No svgs directory inside the ${FONTAWESOME_ROOT_DIR} Font Awesome checkout. Point the TEMPLATE_APP_FONTAWESOME_DIR variable to a complete Font Awesome Free checkout or leave it empty to download one."
  )
endif()

template_project_fontawesome_probe_version(FONTAWESOME_VERSION)

message(STATUS "Font Awesome Free ${FONTAWESOME_VERSION} icons: ${FONTAWESOME_SVGS_DIR}")

template_project_fontawesome_generate_index()

configure_file(
  "${CMAKE_SOURCE_DIR}/src/fontawesome/fontawesome-decls.h.in"
  "${CMAKE_BINARY_DIR}/fontawesome-decls.h"
)

option(
  FONTAWESOME_GENERATE_FULL_MANIFESTS
  "Set to OFF to skip the generation of the resource manifests carrying the whole available Font Awesome icon set"
  ON
)

if (FONTAWESOME_GENERATE_FULL_MANIFESTS)
  set(FONTAWESOME_FULL_QRC "${CMAKE_BINARY_DIR}/generated/fontawesome/fontawesome-all.qrc" CACHE INTERNAL "The Qt resource manifest carrying the whole available Font Awesome icon set")
  set(FONTAWESOME_FULL_GRESOURCE_XML "${CMAKE_BINARY_DIR}/generated/fontawesome/fontawesome-all.gresource.xml" CACHE INTERNAL "The GResource manifest carrying the whole available Font Awesome icon set")

  template_project_fontawesome_write_qrc("${FONTAWESOME_FULL_QRC}")
  template_project_fontawesome_write_gresource("${FONTAWESOME_FULL_GRESOURCE_XML}" COMPRESSED)
endif()

# The whole icon set stays intact inside the checkout above and only the icons
# an application actually asks for end up inside it's binary. Select them with
# the template_project_fontawesome_write_qrc (Qt) or the
# template_project_fontawesome_write_gresource (Gtkmm) function of the
# template-project-fontawesome-resources module, then hand the written manifest
# over to the resource compiler of the toolkit in use. For example:
#   template_project_fontawesome_write_qrc(
#     "${CMAKE_CURRENT_BINARY_DIR}/fontawesome.qrc"
#     ICONS solid/folder-open solid/gear regular/user brands/github
#   )
