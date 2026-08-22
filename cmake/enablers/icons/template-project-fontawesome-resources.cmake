cmake_minimum_required(VERSION 3.13)

# Selects the icons to hand over to a GUI resource system and gives their
# "<style>/<name>.svg" aliases back. The alias is what the code refers to an
# icon by (see the FontAwesomeIcon::alias accessor) and, at the same time, the
# path of it's SVG file relative to the FONTAWESOME_SVGS_DIR directory.
#
#   template_project_fontawesome_select_icons(
#     ALIASES_VAR <variable>
#     [STYLES <style>...]         # every icon of the given styles
#     [ICONS  <style>/<name>...]  # the single icons of interest
#   )
#
# Requesting neither STYLES nor ICONS selects the whole available icon set.
function(template_project_fontawesome_select_icons)
  set(FCN_KEYWORDS_SINGLE ALIASES_VAR)
  set(FCN_KEYWORDS_MULTI STYLES ICONS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_ALIASES_VAR)
    message(FATAL_ERROR "No ALIASES_VAR output variable given to select the Font Awesome icons into")
  endif()

  if (NOT ARG_STYLES AND NOT ARG_ICONS)
    set(ARG_STYLES ${FONTAWESOME_STYLES})
  endif()

  set(aliases "")

  foreach(style IN LISTS ARG_STYLES)
    file(
      GLOB styleFiles
      LIST_DIRECTORIES false
      CONFIGURE_DEPENDS
      "${FONTAWESOME_SVGS_DIR}/${style}/*.svg"
    )

    if (NOT styleFiles)
      message(FATAL_ERROR "No '${style}' style icons inside the ${FONTAWESOME_SVGS_DIR} directory")
    endif()

    foreach(styleFile IN LISTS styleFiles)
      get_filename_component(iconFileName "${styleFile}" NAME)
      list(APPEND aliases "${style}/${iconFileName}")
    endforeach()
  endforeach()

  foreach(icon IN LISTS ARG_ICONS)
    string(REGEX REPLACE "\\.svg$" "" icon "${icon}")

    if (NOT icon MATCHES "^([^/]+)/([^/]+)$")
      message(FATAL_ERROR "The '${icon}' icon follows no <style>/<name> form")
    endif()

    if (NOT EXISTS "${FONTAWESOME_SVGS_DIR}/${icon}.svg")
      message(FATAL_ERROR "No '${icon}' icon inside the ${FONTAWESOME_SVGS_DIR} directory")
    endif()

    list(APPEND aliases "${icon}.svg")
  endforeach()

  list(SORT aliases)
  list(REMOVE_DUPLICATES aliases)

  set(${ARG_ALIASES_VAR} "${aliases}" PARENT_SCOPE)
endfunction()

# Writes the given manifest only when it's content differs from the already
# written one, so a repeated configure run rebuilds no resources.
function(template_project_fontawesome_write_manifest outputFile content)
  file(WRITE "${outputFile}.tmp" "${content}")

  configure_file("${outputFile}.tmp" "${outputFile}" COPYONLY)
endfunction()

# Writes a Qt resource manifest (a .qrc file) listing the selected icons, ready
# for the qt_add_resources command or a direct rcc call. The icons keep their
# "<style>/<name>.svg" aliases, so the FontAwesomeQtResourcePath class resolves
# them at the run time.
#
#   template_project_fontawesome_write_qrc(
#     <output-file>
#     [PREFIX <resource-prefix>]  # FONTAWESOME_QT_RESOURCE_PREFIX by default
#     [STYLES <style>...]
#     [ICONS  <style>/<name>...]
#   )
function(template_project_fontawesome_write_qrc outputFile)
  set(FCN_KEYWORDS_SINGLE PREFIX)
  set(FCN_KEYWORDS_MULTI STYLES ICONS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_PREFIX)
    set(ARG_PREFIX "${FONTAWESOME_QT_RESOURCE_PREFIX}")
  endif()

  template_project_fontawesome_select_icons(
    ALIASES_VAR aliases
    STYLES ${ARG_STYLES}
    ICONS ${ARG_ICONS})

  set(entries "")

  foreach(alias IN LISTS aliases)
    list(APPEND entries "    <file alias=\"${alias}\">${FONTAWESOME_SVGS_DIR}/${alias}</file>")
  endforeach()

  string(JOIN "\n" entriesText ${entries})

  template_project_fontawesome_write_manifest(
    "${outputFile}"
    "<!DOCTYPE RCC><RCC version=\"1.0\">\n  <qresource prefix=\"${ARG_PREFIX}\">\n${entriesText}\n  </qresource>\n</RCC>\n")

  list(LENGTH aliases count)

  message(STATUS "Font Awesome Qt resource manifest with ${count} icon(s): ${outputFile}")
endfunction()

# Writes a GResource manifest (a .gresource.xml file) listing the selected
# icons, ready for the glib-compile-resources command. The icons keep their
# "<style>/<name>.svg" aliases, so the FontAwesomeGResourcePath class resolves
# them at the run time.
#
#   template_project_fontawesome_write_gresource(
#     <output-file>
#     [PREFIX <resource-prefix>]  # FONTAWESOME_GRESOURCE_PREFIX by default
#     [COMPRESSED]                # let GLib zlib compress the embedded SVGs
#     [STYLES <style>...]
#     [ICONS  <style>/<name>...]
#   )
function(template_project_fontawesome_write_gresource outputFile)
  set(FCN_KEYWORDS_FLAGS COMPRESSED)
  set(FCN_KEYWORDS_SINGLE PREFIX)
  set(FCN_KEYWORDS_MULTI STYLES ICONS)

  cmake_parse_arguments(
    "ARG"
    "${FCN_KEYWORDS_FLAGS}"
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if (NOT ARG_PREFIX)
    set(ARG_PREFIX "${FONTAWESOME_GRESOURCE_PREFIX}")
  endif()

  set(compressedAttribute "")

  if (ARG_COMPRESSED)
    set(compressedAttribute " compressed=\"true\"")
  endif()

  template_project_fontawesome_select_icons(
    ALIASES_VAR aliases
    STYLES ${ARG_STYLES}
    ICONS ${ARG_ICONS})

  set(entries "")

  foreach(alias IN LISTS aliases)
    list(APPEND entries "    <file alias=\"${alias}\"${compressedAttribute}>${FONTAWESOME_SVGS_DIR}/${alias}</file>")
  endforeach()

  string(JOIN "\n" entriesText ${entries})

  template_project_fontawesome_write_manifest(
    "${outputFile}"
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gresources>\n  <gresource prefix=\"${ARG_PREFIX}\">\n${entriesText}\n  </gresource>\n</gresources>\n")

  list(LENGTH aliases count)

  message(STATUS "Font Awesome GResource manifest with ${count} icon(s): ${outputFile}")
endfunction()
