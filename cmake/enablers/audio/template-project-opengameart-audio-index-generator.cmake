cmake_minimum_required(VERSION 3.13)

# Reads the manifest naming every pack together with it's archive URL and it's
# license, filling the OPENGAMEART_AUDIO_PACKS list and the per pack
# OPENGAMEART_AUDIO_URL_OF_<pack> and OPENGAMEART_AUDIO_LICENSE_OF_<pack>
# variables out of it.
#
# OpenGameArt hosts it's submissions under several different licenses, so a
# pack with no recorded license is refused instead of silently assumed to be a
# CC0 one.
function(template_project_opengameart_audio_read_manifest)
  if (NOT EXISTS "${TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST}")
    message(
      FATAL_ERROR
      "No ${TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST} OpenGameArt packs manifest. Point the TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST variable at one or fill the misc/opengameart-packs.txt file with the submissions of interest."
    )
  endif()

  file(STRINGS "${TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST}" manifestLines)

  set(packs "")

  foreach(manifestLine IN LISTS manifestLines)
    string(STRIP "${manifestLine}" manifestLine)

    if (manifestLine STREQUAL "" OR manifestLine MATCHES "^#")
      continue()
    endif()

    if (NOT manifestLine MATCHES "^([^|]+)\\|([^|]+)\\|([^|]+)$")
      message(
        FATAL_ERROR
        "The '${manifestLine}' line of the ${TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST} manifest follows no <pack>|<archive URL>|<license> form"
      )
    endif()

    string(STRIP "${CMAKE_MATCH_1}" pack)
    string(STRIP "${CMAKE_MATCH_2}" packUrl)
    string(STRIP "${CMAKE_MATCH_3}" packLicense)

    list(APPEND packs "${pack}")

    set(OPENGAMEART_AUDIO_URL_OF_${pack} "${packUrl}" CACHE INTERNAL "The archive URL of the ${pack} pack")
    set(OPENGAMEART_AUDIO_LICENSE_OF_${pack} "${packLicense}" CACHE INTERNAL "The license of the ${pack} pack")
  endforeach()

  if (NOT packs)
    message(
      FATAL_ERROR
      "The ${TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST} manifest names no pack at all. Fill it with the OpenGameArt submissions of interest, one <pack>|<archive URL>|<license> line each."
    )
  endif()

  list(REMOVE_DUPLICATES packs)
  list(SORT packs)

  set(OPENGAMEART_AUDIO_PACKS "${packs}" CACHE INTERNAL "The OpenGameArt sound packs the manifest names" FORCE)

  list(LENGTH packs packsCount)

  message(STATUS "OpenGameArt packs named by the manifest: ${packsCount}")
endfunction()

# Downloads and unpacks every pack the manifest names into the
# OPENGAMEART_AUDIO_ROOT_DIR directory, one subdirectory per pack. An already
# unpacked pack is left alone, so a reconfigure costs no download at all.
#
# The archives are plain ZIP files rather than a git checkout, hence the
# file(DOWNLOAD) and the "cmake -E tar" extraction instead of a FetchContent
# declaration. The extraction goes through "cmake -E tar" and not through the
# file(ARCHIVE_EXTRACT) command, because the latter needs CMake 3.18 while this
# project stays buildable with 3.13.
function(template_project_opengameart_audio_fetch_packs)
  file(MAKE_DIRECTORY "${OPENGAMEART_AUDIO_ROOT_DIR}")

  foreach(pack IN LISTS OPENGAMEART_AUDIO_PACKS)
    set(packDir "${OPENGAMEART_AUDIO_ROOT_DIR}/${pack}")

    if (EXISTS "${packDir}")
      message(STATUS "OpenGameArt pack already available: ${pack}")
      continue()
    endif()

    set(packUrl "${OPENGAMEART_AUDIO_URL_OF_${pack}}")
    set(packArchive "${OPENGAMEART_AUDIO_ROOT_DIR}/${pack}.zip")

    message(STATUS "Downloading the OpenGameArt ${pack} pack: ${packUrl}")

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
        "Fail to download the OpenGameArt ${pack} pack from ${packUrl}: ${downloadError}. Correct it's line of the ${TEMPLATE_APP_OPENGAMEART_AUDIO_MANIFEST} manifest, run the misc/scripts/fetch-opengameart-audio.sh script by hand, or point the TEMPLATE_APP_OPENGAMEART_AUDIO_DIR one to an already downloaded packs directory."
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
      message(FATAL_ERROR "Fail to unpack the downloaded OpenGameArt ${pack} pack archive")
    endif()
  endforeach()
endfunction()

# Gathers the sound file names of every pack out of the directory in use and
# generates the OpenGameArtGeneratedSounds implementation into the build
# directory, so the complete sound set of that very directory - and the license
# of every pack it came from - becomes reachable from the code with no
# directory scanning at the run time and with no sound names hand written into
# the sources.
#
# A pack ships it's files under a subdirectory of it's own, which differs from
# pack to pack, hence the recursive glob and the pack relative alias built out
# of the found path.
function(template_project_opengameart_audio_generate_index)
  set(generatedSource "${CMAKE_BINARY_DIR}/generated/opengameartaudio/sounds/OpenGameArtGeneratedSounds.cpp")

  set(OPENGAMEART_AUDIO_GENERATED_SOUNDS "")
  set(OPENGAMEART_AUDIO_GENERATED_LICENSES "")
  set(total 0)

  foreach(pack IN LISTS OPENGAMEART_AUDIO_PACKS)
    set(packDir "${OPENGAMEART_AUDIO_ROOT_DIR}/${pack}")

    set(globs "")

    foreach(extension IN LISTS OPENGAMEART_AUDIO_EXTENSIONS)
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
      message(WARNING "No ${OPENGAMEART_AUDIO_EXTENSIONS} sound files found under ${packDir}")
      continue()
    endif()

    list(SORT names)
    math(EXPR total "${total} + ${packCount}")

    string(JOIN ",\n" namesText ${names})

    string(
      APPEND OPENGAMEART_AUDIO_GENERATED_SOUNDS
      "    {\"${pack}\",\n"
      "     {\n${namesText},\n     }},\n"
    )

    string(
      APPEND OPENGAMEART_AUDIO_GENERATED_LICENSES
      "    {\"${pack}\", \"${OPENGAMEART_AUDIO_LICENSE_OF_${pack}}\"},\n"
    )

    message(STATUS "OpenGameArt ${pack} pack sounds: ${packCount} (${OPENGAMEART_AUDIO_LICENSE_OF_${pack}})")
  endforeach()

  if (total EQUAL 0)
    message(
      FATAL_ERROR
      "The ${OPENGAMEART_AUDIO_ROOT_DIR} directory carries no ${OPENGAMEART_AUDIO_EXTENSIONS} sound files of the ${OPENGAMEART_AUDIO_PACKS} packs"
    )
  endif()

  configure_file(
    "${CMAKE_SOURCE_DIR}/src/opengameartaudio/sounds/OpenGameArtGeneratedSounds.cpp.in"
    "${generatedSource}"
    @ONLY
  )

  set(OPENGAMEART_AUDIO_GENERATED_SOUNDS_SOURCE "${generatedSource}" CACHE INTERNAL "The generated OpenGameArt sounds index implementation file")
  set(OPENGAMEART_AUDIO_SOUNDS_COUNT "${total}" CACHE INTERNAL "The count of the OpenGameArt sounds made available")

  message(STATUS "OpenGameArt sounds made available: ${total}")
endfunction()
