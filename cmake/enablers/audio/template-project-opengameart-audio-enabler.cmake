cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_OPENGAMEART_AUDIO
  "Set to ON to make the OpenGameArt sound effect packs the manifest names available (by reusing an already present directory or by fetching them through the Internet)"
  ON
)

# The packs are read out of the manifest rather than listed here, so the single
# place naming a pack also records where it came from, what it is licensed
# under and the very archive it comes from.
set(
  TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST "${PROJECT_SOURCE_DIR}/misc/opengameart-packs.txt"
  CACHE FILEPATH "The manifest naming every pack together with it's archive URL, it's license and the archive SHA-256 checksum"
)

if (NOT ENABLE_OPENGAMEART_AUDIO)
  return()
endif()

include(template-project-opengameart-audio-index-generator)
include(template-project-opengameart-audio-resources)

set(
  TEMPLATE_APP_OPENGAMEART_AUDIO_DIR ""
  CACHE PATH "An already available OpenGameArt sound packs directory to reuse instead of downloading one (leave empty to download)"
)

set(
  OPENGAMEART_AUDIO_EXTENSIONS "ogg;wav;mp3"
  CACHE STRING "The sound file extensions to pick out of the packs"
)

set(
  OPENGAMEART_AUDIO_QT_RESOURCE_PREFIX "/sounds"
  CACHE STRING "The Qt resource system prefix the generated .qrc manifests place the sounds under"
)

set(
  OPENGAMEART_AUDIO_GRESOURCE_PREFIX "/ua/org/kytok/template/${PROJECT_BINARY_NAME}/sounds"
  CACHE STRING "The GResource prefix the generated .gresource.xml manifests place the sounds under"
)

# The OpenGameArt packs are asset archives and not a library: they ship no
# CMakeLists.txt, no find_package module and nothing to link against, so the
# shared template_project_default_3rdparty_enabler (a system probe followed by
# the add_subdirectory of the fetched project) has nothing to do here. Each
# pack is an own ZIP rather than a single checkout, hence the per pack download
# below and the escape hatch for an already present copy.
template_project_opengameart_audio_read_manifest()

if (TEMPLATE_APP_OPENGAMEART_AUDIO_DIR)
  message(STATUS "Reusing the OpenGameArt sound packs directory: ${TEMPLATE_APP_OPENGAMEART_AUDIO_DIR}")

  set(OPENGAMEART_AUDIO_ROOT_DIR "${TEMPLATE_APP_OPENGAMEART_AUDIO_DIR}" CACHE INTERNAL "The OpenGameArt sound packs root directory")
else()
  set(OPENGAMEART_AUDIO_ROOT_DIR "${PROJECT_BINARY_DIR}/resources/opengameart-audio" CACHE INTERNAL "The OpenGameArt sound packs root directory")

  message(STATUS "Trying to make the OpenGameArt sound packs available through the Internet")

  template_project_opengameart_audio_fetch_packs()
endif()

if (NOT EXISTS "${OPENGAMEART_AUDIO_ROOT_DIR}")
  message(
    FATAL_ERROR
    "No ${OPENGAMEART_AUDIO_ROOT_DIR} OpenGameArt sound packs directory. Point the TEMPLATE_APP_OPENGAMEART_AUDIO_DIR variable to a directory carrying a subdirectory per pack, run the misc/scripts/fetch-opengameart-audio.sh script, or leave the variable empty to let the build download the packs."
  )
endif()

template_project_opengameart_audio_generate_index()

# The packs directory above is a configure time one (the build tree, or the
# flatpak sandbox one), so the install step copies the sounds, the license and
# readme files of every pack and the manifest recording the provenance and the
# license of every pack into the data directory, where the installed
# binary looks for them relative to it's own location first (see
# OpenGameArtRootDirectory).
set(OPENGAMEART_AUDIO_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}/opengameart-audio")
set(OPENGAMEART_AUDIO_INSTALLED_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_BINARY_NAME}/opengameart-audio")

file(
  RELATIVE_PATH OPENGAMEART_AUDIO_INSTALLED_RELATIVE_DIR
  "/${PROJECT_BINARY_INSTALLATION_DIR}" "/${OPENGAMEART_AUDIO_INSTALL_DIR}"
)

set(installPatterns PATTERN "*.txt")

foreach(extension IN LISTS OPENGAMEART_AUDIO_EXTENSIONS)
  list(APPEND installPatterns PATTERN "*.${extension}")
endforeach()

foreach(pack IN LISTS OPENGAMEART_AUDIO_PACKS)
  install(
    DIRECTORY "${OPENGAMEART_AUDIO_ROOT_DIR}/${pack}"
    DESTINATION "${OPENGAMEART_AUDIO_INSTALL_DIR}"
    FILES_MATCHING ${installPatterns}
  )
endforeach()

install(
  FILES "${TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST}"
  DESTINATION "${OPENGAMEART_AUDIO_INSTALL_DIR}"
)

configure_file(
  "${PROJECT_SOURCE_DIR}/src/opengameartaudio/opengameart-audio-decls.h.in"
  "${PROJECT_BINARY_DIR}/opengameart-audio-decls.h"
)

option(
  OPENGAMEART_AUDIO_GENERATE_FULL_MANIFESTS
  "Set to OFF to skip the generation of the resource manifests carrying every available OpenGameArt sound"
  ON
)

if (OPENGAMEART_AUDIO_GENERATE_FULL_MANIFESTS)
  set(OPENGAMEART_AUDIO_FULL_QRC "${PROJECT_BINARY_DIR}/generated/opengameartaudio/opengameart-audio-all.qrc" CACHE INTERNAL "The Qt resource manifest carrying every available OpenGameArt sound")
  set(OPENGAMEART_AUDIO_FULL_GRESOURCE_XML "${PROJECT_BINARY_DIR}/generated/opengameartaudio/opengameart-audio-all.gresource.xml" CACHE INTERNAL "The GResource manifest carrying every available OpenGameArt sound")

  template_project_opengameart_audio_write_qrc("${OPENGAMEART_AUDIO_FULL_QRC}")
  template_project_opengameart_audio_write_gresource("${OPENGAMEART_AUDIO_FULL_GRESOURCE_XML}")
endif()

# Every pack stays intact inside the directory above and only the sounds an
# application actually asks for end up inside it's binary. Select them with the
# template_project_opengameart_audio_write_qrc (Qt) or the
# template_project_opengameart_audio_write_gresource (Gtkmm) function of the
# template-project-opengameart-audio-resources module, then hand the written
# manifest over to the resource compiler of the toolkit in use. For example:
#   template_project_opengameart_audio_write_qrc(
#     "${CMAKE_CURRENT_BINARY_DIR}/opengameart-audio.qrc"
#     SOUNDS interface-sounds/Audio/click_001.ogg interface-sounds/Audio/confirmation_001.ogg
#   )
