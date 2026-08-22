cmake_minimum_required(VERSION 3.13)

# Reads the Font Awesome version out of the checkout in use, so a reused
# TEMPLATE_APP_FONTAWESOME_DIR copy reports it's own version instead of the tag
# this project would have downloaded otherwise. Every Font Awesome release
# stamps it's version into the CSS banner, which is the cheapest place to
# probe.
function(template_project_fontawesome_probe_version outVersion)
  set(bannerFile "${FONTAWESOME_ROOT_DIR}/css/all.css")
  set(probed "${TEMPLATE_APP_FONTAWESOME_GIT_TAG}")

  if (EXISTS "${bannerFile}")
    file(READ "${bannerFile}" banner LIMIT 512)

    string(REGEX MATCH "Font Awesome Free ([0-9][^ ]*)" matched "${banner}")

    if (matched)
      set(probed "${CMAKE_MATCH_1}")
    endif()
  endif()

  set(${outVersion} "${probed}" PARENT_SCOPE)
endfunction()

# Gathers the icon names of every enabled style out of the checkout in use and
# generates the FontAwesomeGeneratedIcons implementation into the build
# directory, so the complete icon set of that very checkout becomes reachable
# from the code with no directory scanning at the run time and with no icon
# names hand written into the sources.
function(template_project_fontawesome_generate_index)
  set(generatedSource "${CMAKE_BINARY_DIR}/generated/fontawesome/icons/FontAwesomeGeneratedIcons.cpp")

  set(FONTAWESOME_GENERATED_ICONS "")
  set(total 0)

  foreach(style IN LISTS FONTAWESOME_STYLES)
    file(
      GLOB styleFiles
      LIST_DIRECTORIES false
      CONFIGURE_DEPENDS
      "${FONTAWESOME_SVGS_DIR}/${style}/*.svg"
    )

    set(names "")

    foreach(styleFile IN LISTS styleFiles)
      get_filename_component(iconFileName "${styleFile}" NAME)
      string(REGEX REPLACE "\\.svg$" "" iconName "${iconFileName}")
      list(APPEND names "         \"${iconName}\"")
    endforeach()

    list(LENGTH names styleCount)

    if (styleCount EQUAL 0)
      message(WARNING "No ${style} style icons found under ${FONTAWESOME_SVGS_DIR}")
      continue()
    endif()

    list(SORT names)
    math(EXPR total "${total} + ${styleCount}")

    string(JOIN ",\n" namesText ${names})

    string(
      APPEND FONTAWESOME_GENERATED_ICONS
      "    {\"${style}\",\n"
      "     {\n${namesText},\n     }},\n"
    )

    message(STATUS "Font Awesome ${style} style icons: ${styleCount}")
  endforeach()

  if (total EQUAL 0)
    message(FATAL_ERROR "The ${FONTAWESOME_SVGS_DIR} directory carries no icons of the ${FONTAWESOME_STYLES} styles")
  endif()

  configure_file(
    "${CMAKE_SOURCE_DIR}/src/fontawesome/icons/FontAwesomeGeneratedIcons.cpp.in"
    "${generatedSource}"
    @ONLY
  )

  set(FONTAWESOME_GENERATED_ICONS_SOURCE "${generatedSource}" CACHE INTERNAL "The generated Font Awesome icons index implementation file")
  set(FONTAWESOME_ICONS_COUNT "${total}" CACHE INTERNAL "The count of the Font Awesome icons made available")

  message(STATUS "Font Awesome icons made available: ${total}")
endfunction()
