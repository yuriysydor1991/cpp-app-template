cmake_minimum_required(VERSION 3.13)

# Gives the address of the given pack's archive back, read out of the pack's
# own page at kenney.nl.
#
# The archive address carries a content hash the site regenerates whenever the
# pack is updated, so a hand written address goes stale instead of downloading
# anything, while the page naming it stays reachable under the pack name.
function(template_project_kenney_audio_pack_url pack outVar)
  string(REPLACE "<pack>" "${pack}" packPage "${TEMPLATE_APP_KENNEY_AUDIO_PAGE_TEMPLATE}")

  set(pageFile "${KENNEY_AUDIO_ROOT_DIR}/${pack}.html")

  file(DOWNLOAD "${packPage}" "${pageFile}" STATUS pageStatus TLS_VERIFY ON)

  list(GET pageStatus 0 pageCode)

  if (NOT pageCode EQUAL 0)
    list(GET pageStatus 1 pageError)
    file(REMOVE "${pageFile}")

    message(
      FATAL_ERROR
      "Fail to read the Kenney ${pack} pack page at ${packPage}: ${pageError}. Correct the TEMPLATE_APP_KENNEY_AUDIO_PAGE_TEMPLATE variable, run the misc/scripts/fetch-kenney-audio.sh script by hand, or point the TEMPLATE_APP_KENNEY_AUDIO_DIR one to an already downloaded packs directory."
    )
  endif()

  file(READ "${pageFile}" pageText)
  file(REMOVE "${pageFile}")

  string(REGEX MATCH "https://[^\"' \t\r\n]*/assets/${pack}/[^\"' \t\r\n]*\\.zip" packUrl "${pageText}")

  if (NOT packUrl)
    message(
      FATAL_ERROR
      "The Kenney ${pack} pack page at ${packPage} names no pack archive to download. Check the pack name of the KENNEY_AUDIO_PACKS list against kenney.nl/assets or point the TEMPLATE_APP_KENNEY_AUDIO_DIR variable to an already downloaded packs directory."
    )
  endif()

  set(${outVar} "${packUrl}" PARENT_SCOPE)
endfunction()

# Downloads and unpacks every pack of the KENNEY_AUDIO_PACKS list into the
# KENNEY_AUDIO_ROOT_DIR directory, one subdirectory per pack. An already
# unpacked pack is left alone, so a reconfigure costs no download at all.
#
# The archives are plain ZIP files rather than a git checkout, hence the
# file(DOWNLOAD) and the "cmake -E tar" extraction instead of a FetchContent
# declaration. The extraction goes through "cmake -E tar" and not through the
# file(ARCHIVE_EXTRACT) command, because the latter needs CMake 3.18 while this
# project stays buildable with 3.13.
function(template_project_kenney_audio_fetch_packs)
  file(MAKE_DIRECTORY "${KENNEY_AUDIO_ROOT_DIR}")

  foreach(pack IN LISTS KENNEY_AUDIO_PACKS)
    set(packDir "${KENNEY_AUDIO_ROOT_DIR}/${pack}")

    if (EXISTS "${packDir}")
      message(STATUS "Kenney pack already available: ${pack}")
      continue()
    endif()

    template_project_kenney_audio_pack_url("${pack}" packUrl)

    set(packArchive "${KENNEY_AUDIO_ROOT_DIR}/${pack}.zip")

    message(STATUS "Downloading the Kenney ${pack} pack: ${packUrl}")

    file(
      DOWNLOAD "${packUrl}" "${packArchive}"
      STATUS downloadStatus
      SHOW_PROGRESS
      TLS_VERIFY ON
    )

    list(GET downloadStatus 0 downloadCode)

    if (NOT downloadCode EQUAL 0)
      list(GET downloadStatus 1 downloadError)
      file(REMOVE "${packArchive}")

      message(
        FATAL_ERROR
        "Fail to download the Kenney ${pack} pack from ${packUrl}: ${downloadError}. Correct the TEMPLATE_APP_KENNEY_AUDIO_PAGE_TEMPLATE variable, run the misc/scripts/fetch-kenney-audio.sh script by hand, or point the TEMPLATE_APP_KENNEY_AUDIO_DIR one to an already downloaded packs directory."
      )
    endif()

    set(packUnpackDir "${packDir}.unpacked")

    file(MAKE_DIRECTORY "${packUnpackDir}")

    execute_process(
      COMMAND "${CMAKE_COMMAND}" -E tar xf "${packArchive}"
      WORKING_DIRECTORY "${packUnpackDir}"
      RESULT_VARIABLE extractResult
    )

    file(REMOVE "${packArchive}")

    if (NOT extractResult EQUAL 0)
      file(REMOVE_RECURSE "${packUnpackDir}")
      message(FATAL_ERROR "Fail to unpack the downloaded Kenney ${pack} pack archive")
    endif()

    # The archives are Windows made ones and carry the DOS read-only attribute
    # on a directory of their own (the Audio one of the digital-audio pack),
    # which the extraction turns into a directory no file may be created inside
    # any more: the build tree stops being removable and copyable, the
    # flatpak-builder source copy failing on it. Hence the extraction into a
    # directory of it's own and the copy dropping the archive permissions.
    file(COPY "${packUnpackDir}/" DESTINATION "${packDir}" NO_SOURCE_PERMISSIONS)

    file(REMOVE_RECURSE "${packUnpackDir}")
  endforeach()
endfunction()

# Gathers the sound file names of every pack out of the directory in use and
# generates the KenneyGeneratedSounds implementation into the build directory,
# so the complete sound set of that very directory becomes reachable from the
# code with no directory scanning at the run time and with no sound names hand
# written into the sources.
#
# A pack ships it's files under a subdirectory of it's own ("Audio" as a rule),
# which differs from pack to pack, hence the recursive glob and the pack
# relative alias built out of the found path.
function(template_project_kenney_audio_generate_index)
  set(generatedSource "${CMAKE_BINARY_DIR}/generated/kenneyaudio/sounds/KenneyGeneratedSounds.cpp")

  set(KENNEY_AUDIO_GENERATED_SOUNDS "")
  set(total 0)

  foreach(pack IN LISTS KENNEY_AUDIO_PACKS)
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

    set(names "")

    foreach(packFile IN LISTS packFiles)
      file(RELATIVE_PATH packRelative "${packDir}" "${packFile}")
      list(APPEND names "         \"${packRelative}\"")
    endforeach()

    list(LENGTH names packCount)

    if (packCount EQUAL 0)
      message(WARNING "No ${KENNEY_AUDIO_EXTENSIONS} sound files found under ${packDir}")
      continue()
    endif()

    list(SORT names)
    math(EXPR total "${total} + ${packCount}")

    string(JOIN ",\n" namesText ${names})

    string(
      APPEND KENNEY_AUDIO_GENERATED_SOUNDS
      "    {\"${pack}\",\n"
      "     {\n${namesText},\n     }},\n"
    )

    message(STATUS "Kenney ${pack} pack sounds: ${packCount}")
  endforeach()

  if (total EQUAL 0)
    message(
      FATAL_ERROR
      "The ${KENNEY_AUDIO_ROOT_DIR} directory carries no ${KENNEY_AUDIO_EXTENSIONS} sound files of the ${KENNEY_AUDIO_PACKS} packs"
    )
  endif()

  configure_file(
    "${CMAKE_SOURCE_DIR}/src/kenneyaudio/sounds/KenneyGeneratedSounds.cpp.in"
    "${generatedSource}"
    @ONLY
  )

  set(KENNEY_AUDIO_GENERATED_SOUNDS_SOURCE "${generatedSource}" CACHE INTERNAL "The generated Kenney sounds index implementation file")
  set(KENNEY_AUDIO_SOUNDS_COUNT "${total}" CACHE INTERNAL "The count of the Kenney sounds made available")

  message(STATUS "Kenney sounds made available: ${total}")
endfunction()
