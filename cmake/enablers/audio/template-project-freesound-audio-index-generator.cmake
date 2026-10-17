cmake_minimum_required(VERSION 3.13)

# Reads the manifest naming every sound together with it's download URL and
# it's license and the file SHA-256 checksum, filling the FREESOUND_AUDIO_SOUNDS
# list, the FREESOUND_AUDIO_SOUND_URLS, FREESOUND_AUDIO_SOUND_LICENSES and
# FREESOUND_AUDIO_SOUND_HASHES ones of the same order and the FREESOUND_AUDIO_CATEGORIES one out of it. All of them are
# rewritten on every configure run, so a sound dropped from the manifest leaves
# no license behind for a leftover file to pass the license check with, and the
# aliases are kept as they are, so no two sounds may share an entry.
#
# Freesound publishes it's sounds under CC0, CC-BY and CC-BY-NC alike, one
# license per sound rather than one for the whole database, so a sound with no
# recorded license is refused instead of silently assumed to be a CC0 one.
function(template_project_freesound_audio_read_manifest)
  if (NOT EXISTS "${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST}")
    message(
      FATAL_ERROR
      "No ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} Freesound sounds manifest. Point the TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST variable at one or fill the misc/freesound-sounds.txt file with the sounds of interest."
    )
  endif()

  file(STRINGS "${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST}" manifestLines)

  set(sounds "")
  set(urls "")
  set(licenses "")
  set(hashes "")
  set(categories "")

  foreach(manifestLine IN LISTS manifestLines)
    string(STRIP "${manifestLine}" manifestLine)

    if (manifestLine STREQUAL "" OR manifestLine MATCHES "^#")
      continue()
    endif()

    if (NOT manifestLine MATCHES "^([^|]+)\\|([^|]+)\\|([^|]+)\\|([0-9A-Fa-f]+)$")
      message(
        FATAL_ERROR
        "The '${manifestLine}' line of the ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest follows no <category>/<file>|<download URL>|<license>|<file SHA-256> form"
      )
    endif()

    string(STRIP "${CMAKE_MATCH_1}" soundAlias)
    string(STRIP "${CMAKE_MATCH_2}" soundUrl)
    string(STRIP "${CMAKE_MATCH_3}" soundLicense)
    string(TOLOWER "${CMAKE_MATCH_4}" soundHash)
    string(LENGTH "${soundHash}" soundHashLength)

    if (NOT soundHashLength EQUAL 64)
      message(
        FATAL_ERROR
        "The '${manifestLine}' line of the ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest carries no 64 digits SHA-256 checksum"
      )
    endif()

    if (NOT soundAlias MATCHES "^([^/]+)/(.+)$")
      message(
        FATAL_ERROR
        "The '${soundAlias}' sound of the ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest carries no <category>/<file> alias"
      )
    endif()

    if (soundAlias IN_LIST sounds)
      message(
        FATAL_ERROR
        "The '${soundAlias}' sound is named twice by the ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest"
      )
    endif()

    list(APPEND sounds "${soundAlias}")
    list(APPEND urls "${soundUrl}")
    list(APPEND licenses "${soundLicense}")
    list(APPEND hashes "${soundHash}")
    list(APPEND categories "${CMAKE_MATCH_1}")
  endforeach()

  if (NOT sounds)
    message(
      FATAL_ERROR
      "The ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest names no sound at all. Fill it with the Freesound submissions of interest, one <category>/<file>|<download URL>|<license>|<file SHA-256> line each."
    )
  endif()

  list(REMOVE_DUPLICATES categories)
  list(SORT categories)

  set(FREESOUND_AUDIO_SOUNDS "${sounds}" CACHE INTERNAL "The sounds the manifest names")
  set(FREESOUND_AUDIO_SOUND_URLS "${urls}" CACHE INTERNAL "The download URLs of the FREESOUND_AUDIO_SOUNDS sounds")
  set(FREESOUND_AUDIO_SOUND_LICENSES "${licenses}" CACHE INTERNAL "The licenses of the FREESOUND_AUDIO_SOUNDS sounds")
  set(FREESOUND_AUDIO_SOUND_HASHES "${hashes}" CACHE INTERNAL "The SHA-256 checksums of the FREESOUND_AUDIO_SOUNDS sound files")
  set(FREESOUND_AUDIO_CATEGORIES "${categories}" CACHE INTERNAL "The categories the sounds manifest groups the sounds into" FORCE)

  list(LENGTH sounds soundsCount)
  list(LENGTH categories categoriesCount)

  message(STATUS "Freesound sounds named by the manifest: ${soundsCount} in ${categoriesCount} category(ies)")
endfunction()

# Downloads the given URL into the given file through a temporary file of it's
# own and accepts the download only when it's SHA-256 checksum is the expected
# one, so neither an interrupted nor an altered download is ever taken for the
# pinned file.
function(template_project_freesound_audio_download url destination expectedHash)
  file(
    DOWNLOAD "${url}" "${destination}.part"
    STATUS downloadStatus
    SHOW_PROGRESS
    TLS_VERIFY ON
  )

  list(GET downloadStatus 0 downloadCode)

  if (NOT downloadCode EQUAL 0)
    list(GET downloadStatus 1 downloadError)
    file(REMOVE "${destination}.part")

    message(
      FATAL_ERROR
      "Fail to download ${url}: ${downloadError}. Correct it's line of the ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest, run the misc/scripts/fetch-freesound-audio.sh script by hand, or point the TEMPLATE_APP_FREESOUND_AUDIO_DIR variable to an already downloaded sounds directory."
    )
  endif()

  file(SHA256 "${destination}.part" actualHash)

  if (NOT actualHash STREQUAL expectedHash)
    file(REMOVE "${destination}.part")

    message(
      FATAL_ERROR
      "The ${url} download carries the ${actualHash} SHA-256 checksum instead of the ${expectedHash} one the ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest pins. Update it's manifest line only once the new file is checked to be the expected one."
    )
  endif()

  file(RENAME "${destination}.part" "${destination}")
endfunction()

# Downloads every sound the manifest names into the FREESOUND_AUDIO_ROOT_DIR
# directory, one subdirectory per category. An already downloaded sound is left
# alone, so a reconfigure costs no download at all.
#
# A Freesound submission is a single sound file rather than an archive, hence
# the plain file(DOWNLOAD) with no extraction step at all. The download URL is
# the manifest's business: the site's own API needs a token, so the manifest
# records whatever address the sound is really reachable by.
function(template_project_freesound_audio_fetch_sounds)
  file(MAKE_DIRECTORY "${FREESOUND_AUDIO_ROOT_DIR}")

  foreach(soundAlias IN LISTS FREESOUND_AUDIO_SOUNDS)
    set(soundFile "${FREESOUND_AUDIO_ROOT_DIR}/${soundAlias}")

    if (EXISTS "${soundFile}")
      message(STATUS "Freesound sound already available: ${soundAlias}")
      continue()
    endif()

    list(FIND FREESOUND_AUDIO_SOUNDS "${soundAlias}" soundIndex)
    list(GET FREESOUND_AUDIO_SOUND_URLS ${soundIndex} soundUrl)
    list(GET FREESOUND_AUDIO_SOUND_HASHES ${soundIndex} soundHash)

    get_filename_component(soundDir "${soundFile}" DIRECTORY)
    file(MAKE_DIRECTORY "${soundDir}")

    message(STATUS "Downloading the Freesound ${soundAlias} sound: ${soundUrl}")

    template_project_freesound_audio_download("${soundUrl}" "${soundFile}" "${soundHash}")
  endforeach()
endfunction()

# Gathers the sound file names of every category out of the directory in use
# and generates the FreesoundGeneratedSounds implementation into the build
# directory, so the complete sound set - and the license and the source page of
# every single sound - becomes reachable from the code with no directory
# scanning at the run time and with no sound names hand written into the
# sources.
function(template_project_freesound_audio_generate_index)
  set(generatedSource "${CMAKE_BINARY_DIR}/generated/freesoundaudio/sounds/FreesoundGeneratedSounds.cpp")

  set(FREESOUND_AUDIO_GENERATED_SOUNDS "")
  set(FREESOUND_AUDIO_GENERATED_LICENSES "")
  set(FREESOUND_AUDIO_GENERATED_SOURCES "")
  set(total 0)

  foreach(category IN LISTS FREESOUND_AUDIO_CATEGORIES)
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

    set(names "")

    foreach(categoryFile IN LISTS categoryFiles)
      file(RELATIVE_PATH categoryRelative "${categoryDir}" "${categoryFile}")

      list(APPEND names "             \"${categoryRelative}\"")

      set(soundAlias "${category}/${categoryRelative}")
      list(FIND FREESOUND_AUDIO_SOUNDS "${soundAlias}" soundIndex)

      if (soundIndex EQUAL -1)
        message(
          FATAL_ERROR
          "The ${soundAlias} sound file sits inside the ${FREESOUND_AUDIO_ROOT_DIR} directory but the ${TEMPLATE_APP_FREESOUND_AUDIO_MANIFEST} manifest records no license of it. Add it's <category>/<file>|<download URL>|<license> line or drop the file."
        )
      endif()

      list(GET FREESOUND_AUDIO_SOUND_LICENSES ${soundIndex} soundLicense)
      list(GET FREESOUND_AUDIO_SOUND_URLS ${soundIndex} soundUrl)

      string(
        APPEND FREESOUND_AUDIO_GENERATED_LICENSES
        "      {\"${soundAlias}\", \"${soundLicense}\"},\n"
      )

      string(
        APPEND FREESOUND_AUDIO_GENERATED_SOURCES
        "      {\"${soundAlias}\", \"${soundUrl}\"},\n"
      )
    endforeach()

    list(LENGTH names categoryCount)

    if (categoryCount EQUAL 0)
      message(WARNING "No ${FREESOUND_AUDIO_EXTENSIONS} sound files found under ${categoryDir}")
      continue()
    endif()

    list(SORT names)
    math(EXPR total "${total} + ${categoryCount}")

    string(JOIN ",\n" namesText ${names})

    string(
      APPEND FREESOUND_AUDIO_GENERATED_SOUNDS
      "        {\"${category}\",\n"
      "         {\n${namesText},\n         }},\n"
    )

    message(STATUS "Freesound ${category} category sounds: ${categoryCount}")
  endforeach()

  if (total EQUAL 0)
    message(
      FATAL_ERROR
      "The ${FREESOUND_AUDIO_ROOT_DIR} directory carries no ${FREESOUND_AUDIO_EXTENSIONS} sound files of the ${FREESOUND_AUDIO_CATEGORIES} categories"
    )
  endif()

  configure_file(
    "${CMAKE_SOURCE_DIR}/src/freesoundaudio/sounds/FreesoundGeneratedSounds.cpp.in"
    "${generatedSource}"
    @ONLY
  )

  set(FREESOUND_AUDIO_GENERATED_SOUNDS_SOURCE "${generatedSource}" CACHE INTERNAL "The generated Freesound sounds index implementation file")
  set(FREESOUND_AUDIO_SOUNDS_COUNT "${total}" CACHE INTERNAL "The count of the Freesound sounds made available")

  message(STATUS "Freesound sounds made available: ${total}")
endfunction()
