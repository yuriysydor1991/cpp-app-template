cmake_minimum_required(VERSION 3.13)

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

    string(REPLACE "<pack>" "${pack}" packUrl "${TEMPLATE_APP_KENNEY_AUDIO_URL_TEMPLATE}")

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
        "Fail to download the Kenney ${pack} pack from ${packUrl}: ${downloadError}. Correct the TEMPLATE_APP_KENNEY_AUDIO_URL_TEMPLATE variable, run the misc/scripts/fetch-kenney-audio.sh script by hand, or point the TEMPLATE_APP_KENNEY_AUDIO_DIR one to an already downloaded packs directory."
      )
    endif()

    file(MAKE_DIRECTORY "${packDir}")

    execute_process(
      COMMAND "${CMAKE_COMMAND}" -E tar xf "${packArchive}"
      WORKING_DIRECTORY "${packDir}"
      RESULT_VARIABLE extractResult
    )

    file(REMOVE "${packArchive}")

    if (NOT extractResult EQUAL 0)
      file(REMOVE_RECURSE "${packDir}")
      message(FATAL_ERROR "Fail to unpack the downloaded Kenney ${pack} pack archive")
    endif()
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
