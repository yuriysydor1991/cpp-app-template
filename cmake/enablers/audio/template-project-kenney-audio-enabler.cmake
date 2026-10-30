cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_KENNEY_AUDIO
  "Set to ON to make the Kenney CC0 sound effect packs available (by reusing an already present directory or by fetching them through the Internet)"
  ON
)

# The packs are read out of the manifest rather than listed here, so the single
# place naming a pack also pins the very archive it comes from.
set(
  TEMPLATE_APP_KENNEY_AUDIO_MANIFEST "${PROJECT_SOURCE_DIR}/misc/kenney-packs.txt"
  CACHE FILEPATH "The manifest naming every pack together with it's archive URL and the archive SHA-256 checksum"
)

if (NOT ENABLE_KENNEY_AUDIO)
  return()
endif()

include(template-project-kenney-audio-index-generator)
include(template-project-kenney-audio-resources)

set(
  TEMPLATE_APP_KENNEY_AUDIO_DIR ""
  CACHE PATH "An already available Kenney sound packs directory to reuse instead of downloading one (leave empty to download)"
)

set(
  KENNEY_AUDIO_EXTENSIONS "ogg;wav;mp3"
  CACHE STRING "The sound file extensions to pick out of the packs"
)

set(
  KENNEY_AUDIO_QT_RESOURCE_PREFIX "/sounds"
  CACHE STRING "The Qt resource system prefix the generated .qrc manifests place the sounds under"
)

set(
  KENNEY_AUDIO_GRESOURCE_PREFIX "/ua/org/kytok/template/${PROJECT_BINARY_NAME}/sounds"
  CACHE STRING "The GResource prefix the generated .gresource.xml manifests place the sounds under"
)

# The Kenney packs are asset archives and not a library: they ship no
# CMakeLists.txt, no find_package module and nothing to link against, so the
# shared template_project_default_3rdparty_enabler (a system probe followed by
# the add_subdirectory of the fetched project) has nothing to do here. Each
# pack is an own ZIP rather than a single checkout, hence the per pack download
# below and the escape hatch for an already present copy.
template_project_kenney_audio_read_manifest()

if (TEMPLATE_APP_KENNEY_AUDIO_DIR)
  message(STATUS "Reusing the Kenney sound packs directory: ${TEMPLATE_APP_KENNEY_AUDIO_DIR}")

  set(KENNEY_AUDIO_ROOT_DIR "${TEMPLATE_APP_KENNEY_AUDIO_DIR}" CACHE INTERNAL "The Kenney sound packs root directory")
else()
  set(KENNEY_AUDIO_ROOT_DIR "${PROJECT_BINARY_DIR}/resources/kenney-audio" CACHE INTERNAL "The Kenney sound packs root directory")

  message(STATUS "Trying to make the Kenney sound packs available through the Internet")

  template_project_kenney_audio_fetch_packs()
endif()

if (NOT EXISTS "${KENNEY_AUDIO_ROOT_DIR}")
  message(
    FATAL_ERROR
    "No ${KENNEY_AUDIO_ROOT_DIR} Kenney sound packs directory. Point the TEMPLATE_APP_KENNEY_AUDIO_DIR variable to a directory carrying a subdirectory per pack, run the misc/scripts/fetch-kenney-audio.sh script, or leave the variable empty to let the build download the packs."
  )
endif()

template_project_kenney_audio_generate_index()

# The packs directory above is a configure time one (the build tree, or the
# flatpak sandbox one), so the install step copies the sounds and the license
# of every pack into the data directory, where the installed binary looks for
# them relative to it's own location first (see KenneyRootDirectory).
set(KENNEY_AUDIO_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}/kenney-audio")
set(KENNEY_AUDIO_INSTALLED_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_BINARY_NAME}/kenney-audio")

file(
  RELATIVE_PATH KENNEY_AUDIO_INSTALLED_RELATIVE_DIR
  "/${PROJECT_BINARY_INSTALLATION_DIR}" "/${KENNEY_AUDIO_INSTALL_DIR}"
)

set(installPatterns PATTERN "License.txt")

foreach(extension IN LISTS KENNEY_AUDIO_EXTENSIONS)
  list(APPEND installPatterns PATTERN "*.${extension}")
endforeach()

foreach(pack IN LISTS KENNEY_AUDIO_PACKS)
  install(
    DIRECTORY "${KENNEY_AUDIO_ROOT_DIR}/${pack}"
    DESTINATION "${KENNEY_AUDIO_INSTALL_DIR}"
    FILES_MATCHING ${installPatterns}
  )
endforeach()

configure_file(
  "${PROJECT_SOURCE_DIR}/src/kenneyaudio/kenney-audio-decls.h.in"
  "${PROJECT_BINARY_DIR}/kenney-audio-decls.h"
)

option(
  KENNEY_AUDIO_GENERATE_FULL_MANIFESTS
  "Set to OFF to skip the generation of the resource manifests carrying every available Kenney sound"
  ON
)

if (KENNEY_AUDIO_GENERATE_FULL_MANIFESTS)
  set(KENNEY_AUDIO_FULL_QRC "${PROJECT_BINARY_DIR}/generated/kenneyaudio/kenney-audio-all.qrc" CACHE INTERNAL "The Qt resource manifest carrying every available Kenney sound")
  set(KENNEY_AUDIO_FULL_GRESOURCE_XML "${PROJECT_BINARY_DIR}/generated/kenneyaudio/kenney-audio-all.gresource.xml" CACHE INTERNAL "The GResource manifest carrying every available Kenney sound")

  template_project_kenney_audio_write_qrc("${KENNEY_AUDIO_FULL_QRC}")
  template_project_kenney_audio_write_gresource("${KENNEY_AUDIO_FULL_GRESOURCE_XML}")
endif()

# Every pack stays intact inside the directory above and only the sounds an
# application actually asks for end up inside it's binary. Select them with the
# template_project_kenney_audio_write_qrc (Qt) or the
# template_project_kenney_audio_write_gresource (Gtkmm) function of the
# template-project-kenney-audio-resources module, then hand the written
# manifest over to the resource compiler of the toolkit in use. For example:
#   template_project_kenney_audio_write_qrc(
#     "${CMAKE_CURRENT_BINARY_DIR}/kenney-audio.qrc"
#     SOUNDS interface-sounds/click_001.ogg interface-sounds/confirmation_001.ogg
#   )
