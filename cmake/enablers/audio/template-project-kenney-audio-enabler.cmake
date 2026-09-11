cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_KENNEY_AUDIO
  "Set to ON to make the Kenney CC0 sound effect packs available (by reusing an already present directory or by fetching them through the Internet)"
  ON
)

# The packager manifests carry the very same packs, so their coordinates stay
# declared even with the enabler itself switched off.
set(
  KENNEY_AUDIO_PACKS "interface-sounds;impact-sounds;digital-audio;ui-audio"
  CACHE STRING "The Kenney CC0 sound effect packs to make available"
)

set(
  TEMPLATE_APP_KENNEY_AUDIO_URL_TEMPLATE "https://kenney.nl/media/pages/assets/<pack>/<pack>.zip"
  CACHE STRING "The per pack download URL, the <pack> placeholder standing for the pack name. Verify it against kenney.nl before the first fetch."
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
if (TEMPLATE_APP_KENNEY_AUDIO_DIR)
  message(STATUS "Reusing the Kenney sound packs directory: ${TEMPLATE_APP_KENNEY_AUDIO_DIR}")

  set(KENNEY_AUDIO_ROOT_DIR "${TEMPLATE_APP_KENNEY_AUDIO_DIR}" CACHE INTERNAL "The Kenney sound packs root directory")
else()
  set(KENNEY_AUDIO_ROOT_DIR "${CMAKE_BINARY_DIR}/resources/kenney-audio" CACHE INTERNAL "The Kenney sound packs root directory")

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

configure_file(
  "${CMAKE_SOURCE_DIR}/src/kenneyaudio/kenney-audio-decls.h.in"
  "${CMAKE_BINARY_DIR}/kenney-audio-decls.h"
)

option(
  KENNEY_AUDIO_GENERATE_FULL_MANIFESTS
  "Set to OFF to skip the generation of the resource manifests carrying every available Kenney sound"
  ON
)

if (KENNEY_AUDIO_GENERATE_FULL_MANIFESTS)
  set(KENNEY_AUDIO_FULL_QRC "${CMAKE_BINARY_DIR}/generated/kenneyaudio/kenney-audio-all.qrc" CACHE INTERNAL "The Qt resource manifest carrying every available Kenney sound")
  set(KENNEY_AUDIO_FULL_GRESOURCE_XML "${CMAKE_BINARY_DIR}/generated/kenneyaudio/kenney-audio-all.gresource.xml" CACHE INTERNAL "The GResource manifest carrying every available Kenney sound")

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
