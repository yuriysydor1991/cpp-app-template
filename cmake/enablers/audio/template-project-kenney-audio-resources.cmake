cmake_minimum_required(VERSION 3.13)

# Selects the sounds to hand over to a GUI resource system and gives their
# "<pack>/<path>" aliases back. The alias is what the code refers to a sound by
# (see the KenneySound::alias accessor) and, at the same time, the path of it's
# sound file relative to the KENNEY_AUDIO_ROOT_DIR directory.
#
#   template_project_kenney_audio_select_sounds(
#     ALIASES_VAR <variable>
#     [PACKS  <pack>...]          # every sound of the given packs
#     [SOUNDS <pack>/<path>...]   # the single sounds of interest
#   )
#
# Requesting neither PACKS nor SOUNDS selects the whole available sound set.
function(template_project_kenney_audio_select_sounds)
  set(FCN_KEYWORDS_SINGLE ALIASES_VAR)
  set(FCN_KEYWORDS_MULTI PACKS SOUNDS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_ALIASES_VAR)
    message(FATAL_ERROR "No ALIASES_VAR output variable given to select the Kenney sounds into")
  endif()

  if (NOT ARG_PACKS AND NOT ARG_SOUNDS)
    set(ARG_PACKS ${KENNEY_AUDIO_PACKS})
  endif()

  set(aliases "")

  foreach(pack IN LISTS ARG_PACKS)
    set(packDir "${KENNEY_AUDIO_ROOT_DIR}/${pack}")

    set(globs "")

    foreach(extension IN LISTS KENNEY_AUDIO_EXTENSIONS)
      list(APPEND globs "${packDir}/*.${extension}")
    endforeach()

    file(
      GLOB_RECURSE packFiles
      LIST_DIRECTORIES false
      CONFIGURE_DEPENDS
      ${globs}
    )

    if (NOT packFiles)
      message(FATAL_ERROR "No '${pack}' pack sounds inside the ${KENNEY_AUDIO_ROOT_DIR} directory")
    endif()

    foreach(packFile IN LISTS packFiles)
      file(RELATIVE_PATH packRelative "${packDir}" "${packFile}")
      list(APPEND aliases "${pack}/${packRelative}")
    endforeach()
  endforeach()

  foreach(sound IN LISTS ARG_SOUNDS)
    if (NOT EXISTS "${KENNEY_AUDIO_ROOT_DIR}/${sound}")
      message(FATAL_ERROR "No '${sound}' sound inside the ${KENNEY_AUDIO_ROOT_DIR} directory")
    endif()

    list(APPEND aliases "${sound}")
  endforeach()

  list(SORT aliases)
  list(REMOVE_DUPLICATES aliases)

  set(${ARG_ALIASES_VAR} "${aliases}" PARENT_SCOPE)
endfunction()

# Writes the given manifest only when it's content differs from the already
# written one, so a repeated configure run rebuilds no resources.
function(template_project_kenney_audio_write_manifest outputFile content)
  file(WRITE "${outputFile}.tmp" "${content}")

  configure_file("${outputFile}.tmp" "${outputFile}" COPYONLY)
endfunction()

# Writes a Qt resource manifest (a .qrc file) listing the selected sounds,
# ready for the qt_add_resources command or a direct rcc call. The sounds keep
# their "<pack>/<path>" aliases, so the KenneyQtResourcePath class resolves
# them at the run time.
#
#   template_project_kenney_audio_write_qrc(
#     <output-file>
#     [PREFIX <resource-prefix>]  # KENNEY_AUDIO_QT_RESOURCE_PREFIX by default
#     [PACKS  <pack>...]
#     [SOUNDS <pack>/<path>...]
#   )
function(template_project_kenney_audio_write_qrc outputFile)
  set(FCN_KEYWORDS_SINGLE PREFIX)
  set(FCN_KEYWORDS_MULTI PACKS SOUNDS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_PREFIX)
    set(ARG_PREFIX "${KENNEY_AUDIO_QT_RESOURCE_PREFIX}")
  endif()

  template_project_kenney_audio_select_sounds(
    ALIASES_VAR aliases
    PACKS ${ARG_PACKS}
    SOUNDS ${ARG_SOUNDS})

  set(entries "")

  foreach(alias IN LISTS aliases)
    list(APPEND entries "    <file alias=\"${alias}\">${KENNEY_AUDIO_ROOT_DIR}/${alias}</file>")
  endforeach()

  string(JOIN "\n" entriesText ${entries})

  template_project_kenney_audio_write_manifest(
    "${outputFile}"
    "<!DOCTYPE RCC><RCC version=\"1.0\">\n  <qresource prefix=\"${ARG_PREFIX}\">\n${entriesText}\n  </qresource>\n</RCC>\n")

  list(LENGTH aliases count)

  message(STATUS "Kenney Qt resource manifest with ${count} sound(s): ${outputFile}")
endfunction()

# Writes a GResource manifest (a .gresource.xml file) listing the selected
# sounds, ready for the glib-compile-resources command. The sounds keep their
# "<pack>/<path>" aliases, so the KenneyGResourcePath class resolves them at
# the run time.
#
# The COMPRESSED flag stays available for the uncompressed .wav members of a
# pack alone: the .ogg and the .mp3 ones carry an already compressed stream, so
# letting GLib zlib them a second time costs build time and gains nothing.
#
#   template_project_kenney_audio_write_gresource(
#     <output-file>
#     [PREFIX <resource-prefix>]  # KENNEY_AUDIO_GRESOURCE_PREFIX by default
#     [COMPRESSED]
#     [PACKS  <pack>...]
#     [SOUNDS <pack>/<path>...]
#   )
function(template_project_kenney_audio_write_gresource outputFile)
  set(FCN_KEYWORDS_FLAGS COMPRESSED)
  set(FCN_KEYWORDS_SINGLE PREFIX)
  set(FCN_KEYWORDS_MULTI PACKS SOUNDS)

  cmake_parse_arguments(
    "ARG"
    "${FCN_KEYWORDS_FLAGS}"
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_PREFIX)
    set(ARG_PREFIX "${KENNEY_AUDIO_GRESOURCE_PREFIX}")
  endif()

  set(compressedAttribute "")

  if (ARG_COMPRESSED)
    set(compressedAttribute " compressed=\"true\"")
  endif()

  template_project_kenney_audio_select_sounds(
    ALIASES_VAR aliases
    PACKS ${ARG_PACKS}
    SOUNDS ${ARG_SOUNDS})

  set(entries "")

  foreach(alias IN LISTS aliases)
    list(APPEND entries "    <file alias=\"${alias}\"${compressedAttribute}>${KENNEY_AUDIO_ROOT_DIR}/${alias}</file>")
  endforeach()

  string(JOIN "\n" entriesText ${entries})

  template_project_kenney_audio_write_manifest(
    "${outputFile}"
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gresources>\n  <gresource prefix=\"${ARG_PREFIX}\">\n${entriesText}\n  </gresource>\n</gresources>\n")

  list(LENGTH aliases count)

  message(STATUS "Kenney GResource manifest with ${count} sound(s): ${outputFile}")
endfunction()
