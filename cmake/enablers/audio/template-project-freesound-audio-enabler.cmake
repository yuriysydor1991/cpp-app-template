cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_FREESOUND_AUDIO
  "Set to ON to make the curated Freesound sounds available (by reusing an already present directory or by fetching them through the Internet)"
  ON
)

# The categories are read out of the manifest rather than listed here, so the
# single place naming a sound also records where it came from and what it is
# licensed under.
set(FREESOUND_AUDIO_CATEGORIES "" CACHE INTERNAL "The categories the sounds manifest groups the sounds into")

set(
  TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST "${CMAKE_SOURCE_DIR}/misc/freesound-sounds.txt"
  CACHE FILEPATH "The manifest naming every sound together with it's download URL and it's license"
)

if (NOT ENABLE_FREESOUND_AUDIO)
  return()
endif()

include(template-project-freesound-audio-index-generator)
include(template-project-freesound-audio-resources)

set(
  TEMPLATE_APP_FREESOUND_AUDIO_DIR ""
  CACHE PATH "An already available sounds directory to reuse instead of downloading one (leave empty to download)"
)

set(
  FREESOUND_AUDIO_EXTENSIONS "ogg;wav;mp3;flac"
  CACHE STRING "The sound file extensions to pick out of the sounds directory"
)

set(
  FREESOUND_AUDIO_QT_RESOURCE_PREFIX "/sounds"
  CACHE STRING "The Qt resource system prefix the generated .qrc manifests place the sounds under"
)

set(
  FREESOUND_AUDIO_GRESOURCE_PREFIX "/ua/org/kytok/template/${PROJECT_BINARY_NAME}/sounds"
  CACHE STRING "The GResource prefix the generated .gresource.xml manifests place the sounds under"
)

# Freesound is a database of single submissions and not a library: it ships no
# CMakeLists.txt, no find_package module and nothing to link against, so the
# shared template_project_default_3rdparty_enabler (a system probe followed by
# the add_subdirectory of the fetched project) has nothing to do here. Its
# sounds carry a license each rather than one license for the whole database,
# hence the per sound manifest below and the escape hatch for an already
# present copy.
template_project_freesound_audio_read_manifest()

if (TEMPLATE_APP_FREESOUND_AUDIO_DIR)
  message(STATUS "Reusing the Freesound sounds directory: ${TEMPLATE_APP_FREESOUND_AUDIO_DIR}")

  set(FREESOUND_AUDIO_ROOT_DIR "${TEMPLATE_APP_FREESOUND_AUDIO_DIR}" CACHE INTERNAL "The Freesound sounds root directory")
else()
  set(FREESOUND_AUDIO_ROOT_DIR "${CMAKE_BINARY_DIR}/resources/freesound-audio" CACHE INTERNAL "The Freesound sounds root directory")

  message(STATUS "Trying to make the Freesound sounds available through the Internet")

  template_project_freesound_audio_fetch_sounds()
endif()

if (NOT EXISTS "${FREESOUND_AUDIO_ROOT_DIR}")
  message(
    FATAL_ERROR
    "No ${FREESOUND_AUDIO_ROOT_DIR} Freesound sounds directory. Point the TEMPLATE_APP_FREESOUND_AUDIO_DIR variable to a directory carrying a subdirectory per category, run the misc/scripts/fetch-freesound-audio.sh script, or leave the variable empty to let the build download the sounds."
  )
endif()

template_project_freesound_audio_generate_index()

configure_file(
  "${CMAKE_SOURCE_DIR}/src/freesoundaudio/freesound-audio-decls.h.in"
  "${CMAKE_BINARY_DIR}/freesound-audio-decls.h"
)

option(
  FREESOUND_AUDIO_GENERATE_FULL_MANIFESTS
  "Set to OFF to skip the generation of the resource manifests carrying every available Freesound sound"
  ON
)

if (FREESOUND_AUDIO_GENERATE_FULL_MANIFESTS)
  set(FREESOUND_AUDIO_FULL_QRC "${CMAKE_BINARY_DIR}/generated/freesoundaudio/freesound-audio-all.qrc" CACHE INTERNAL "The Qt resource manifest carrying every available Freesound sound")
  set(FREESOUND_AUDIO_FULL_GRESOURCE_XML "${CMAKE_BINARY_DIR}/generated/freesoundaudio/freesound-audio-all.gresource.xml" CACHE INTERNAL "The GResource manifest carrying every available Freesound sound")

  template_project_freesound_audio_write_qrc("${FREESOUND_AUDIO_FULL_QRC}")
  template_project_freesound_audio_write_gresource("${FREESOUND_AUDIO_FULL_GRESOURCE_XML}")
endif()

# Every sound stays intact inside the directory above and only the ones an
# application actually asks for end up inside it's binary. Select them with the
# template_project_freesound_audio_write_qrc (Qt) or the
# template_project_freesound_audio_write_gresource (Gtkmm) function of the
# template-project-freesound-audio-resources module, then hand the written
# manifest over to the resource compiler of the toolkit in use. For example:
#   template_project_freesound_audio_write_qrc(
#     "${CMAKE_CURRENT_BINARY_DIR}/freesound-audio.qrc"
#     SOUNDS interface/click.ogg interface/notification.ogg
#   )
