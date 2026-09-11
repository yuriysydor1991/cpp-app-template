cmake_minimum_required(VERSION 3.13)

# Selects the sounds to hand over to a GUI resource system and gives their
# "<category>/<path>" aliases back. The alias is what the code refers to a sound by
# (see the FreesoundSound::alias accessor) and, at the same time, the path of it's
# sound file relative to the FREESOUND_AUDIO_ROOT_DIR directory.
#
#   template_project_freesound_audio_select_sounds(
#     ALIASES_VAR <variable>
#     [CATEGORIES  <category>...]          # every sound of the given categories
#     [SOUNDS <category>/<path>...]   # the single sounds of interest
#   )
#
# Requesting neither CATEGORIES nor SOUNDS selects the whole available sound set.
function(template_project_freesound_audio_select_sounds)
  set(FCN_KEYWORDS_SINGLE ALIASES_VAR)
  set(FCN_KEYWORDS_MULTI CATEGORIES SOUNDS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_ALIASES_VAR)
    message(FATAL_ERROR "No ALIASES_VAR output variable given to select the Freesound sounds into")
  endif()

  if (NOT ARG_CATEGORIES AND NOT ARG_SOUNDS)
    set(ARG_CATEGORIES ${FREESOUND_AUDIO_CATEGORIES})
  endif()

  set(aliases "")

  foreach(category IN LISTS ARG_CATEGORIES)
    set(categoryDir "${FREESOUND_AUDIO_ROOT_DIR}/${category}")

    set(globs "")

    foreach(extension IN LISTS FREESOUND_AUDIO_EXTENSIONS)
      list(APPEND globs "${categoryDir}/*.${extension}")
    endforeach()

    file(
      GLOB_RECURSE categoryFiles
      LIST_DIRECTORIES false
      CONFIGURE_DEPENDS
      ${globs}
    )

    if (NOT categoryFiles)
      message(FATAL_ERROR "No '${category}' category sounds inside the ${FREESOUND_AUDIO_ROOT_DIR} directory")
    endif()

    foreach(categoryFile IN LISTS categoryFiles)
      file(RELATIVE_PATH categoryRelative "${categoryDir}" "${categoryFile}")
      list(APPEND aliases "${category}/${categoryRelative}")
    endforeach()
  endforeach()

  foreach(sound IN LISTS ARG_SOUNDS)
    if (NOT EXISTS "${FREESOUND_AUDIO_ROOT_DIR}/${sound}")
      message(FATAL_ERROR "No '${sound}' sound inside the ${FREESOUND_AUDIO_ROOT_DIR} directory")
    endif()

    list(APPEND aliases "${sound}")
  endforeach()

  list(SORT aliases)
  list(REMOVE_DUPLICATES aliases)

  set(${ARG_ALIASES_VAR} "${aliases}" PARENT_SCOPE)
endfunction()

# Writes the given manifest only when it's content differs from the already
# written one, so a repeated configure run rebuilds no resources.
function(template_project_freesound_audio_write_manifest outputFile content)
  file(WRITE "${outputFile}.tmp" "${content}")

  configure_file("${outputFile}.tmp" "${outputFile}" COPYONLY)
endfunction()

# Writes a Qt resource manifest (a .qrc file) listing the selected sounds,
# ready for the qt_add_resources command or a direct rcc call. The sounds keep
# their "<category>/<path>" aliases, so the FreesoundQtResourcePath class resolves
# them at the run time.
#
#   template_project_freesound_audio_write_qrc(
#     <output-file>
#     [PREFIX <resource-prefix>]  # FREESOUND_AUDIO_QT_RESOURCE_PREFIX by default
#     [CATEGORIES  <category>...]
#     [SOUNDS <category>/<path>...]
#   )
function(template_project_freesound_audio_write_qrc outputFile)
  set(FCN_KEYWORDS_SINGLE PREFIX)
  set(FCN_KEYWORDS_MULTI CATEGORIES SOUNDS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_PREFIX)
    set(ARG_PREFIX "${FREESOUND_AUDIO_QT_RESOURCE_PREFIX}")
  endif()

  template_project_freesound_audio_select_sounds(
    ALIASES_VAR aliases
    CATEGORIES ${ARG_CATEGORIES}
    SOUNDS ${ARG_SOUNDS})

  set(entries "")

  foreach(alias IN LISTS aliases)
    list(APPEND entries "    <file alias=\"${alias}\">${FREESOUND_AUDIO_ROOT_DIR}/${alias}</file>")
  endforeach()

  string(JOIN "\n" entriesText ${entries})

  template_project_freesound_audio_write_manifest(
    "${outputFile}"
    "<!DOCTYPE RCC><RCC version=\"1.0\">\n  <qresource prefix=\"${ARG_PREFIX}\">\n${entriesText}\n  </qresource>\n</RCC>\n")

  list(LENGTH aliases count)

  message(STATUS "Freesound Qt resource manifest with ${count} sound(s): ${outputFile}")
endfunction()

# Writes a GResource manifest (a .gresource.xml file) listing the selected
# sounds, ready for the glib-compile-resources command. The sounds keep their
# "<category>/<path>" aliases, so the FreesoundGResourcePath class resolves them at
# the run time.
#
# The COMPRESSED flag stays available for the uncompressed .wav members of a
# category alone: the .ogg and the .mp3 ones carry an already compressed stream, so
# letting GLib zlib them a second time costs build time and gains nothing.
#
#   template_project_freesound_audio_write_gresource(
#     <output-file>
#     [PREFIX <resource-prefix>]  # FREESOUND_AUDIO_GRESOURCE_PREFIX by default
#     [COMPRESSED]
#     [CATEGORIES  <category>...]
#     [SOUNDS <category>/<path>...]
#   )
function(template_project_freesound_audio_write_gresource outputFile)
  set(FCN_KEYWORDS_FLAGS COMPRESSED)
  set(FCN_KEYWORDS_SINGLE PREFIX)
  set(FCN_KEYWORDS_MULTI CATEGORIES SOUNDS)

  cmake_parse_arguments(
    "ARG"
    "${FCN_KEYWORDS_FLAGS}"
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_PREFIX)
    set(ARG_PREFIX "${FREESOUND_AUDIO_GRESOURCE_PREFIX}")
  endif()

  set(compressedAttribute "")

  if (ARG_COMPRESSED)
    set(compressedAttribute " compressed=\"true\"")
  endif()

  template_project_freesound_audio_select_sounds(
    ALIASES_VAR aliases
    CATEGORIES ${ARG_CATEGORIES}
    SOUNDS ${ARG_SOUNDS})

  set(entries "")

  foreach(alias IN LISTS aliases)
    list(APPEND entries "    <file alias=\"${alias}\"${compressedAttribute}>${FREESOUND_AUDIO_ROOT_DIR}/${alias}</file>")
  endforeach()

  string(JOIN "\n" entriesText ${entries})

  template_project_freesound_audio_write_manifest(
    "${outputFile}"
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gresources>\n  <gresource prefix=\"${ARG_PREFIX}\">\n${entriesText}\n  </gresource>\n</gresources>\n")

  list(LENGTH aliases count)

  message(STATUS "Freesound GResource manifest with ${count} sound(s): ${outputFile}")
endfunction()
