cmake_minimum_required(VERSION 3.13)

# Reads the manifest naming every pack together with it's archive URL and the
# SHA-256 checksum of that archive, filling the KENNEY_AUDIO_PACKS list and the
# KENNEY_AUDIO_PACK_URLS and KENNEY_AUDIO_PACK_HASHES ones of the same order out
# of it. All three are rewritten on every configure run, so a pack dropped from
# the manifest leaves nothing behind.
function(template_project_kenney_audio_read_manifest)
  if (NOT EXISTS "${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST}")
    message(
      FATAL_ERROR
      "No ${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST} Kenney packs manifest. Point the TEMPLATE_APP_KENNEY_AUDIO_MANIFEST variable at one or fill the misc/kenney-packs.txt file with the packs of interest."
    )
  endif()

  file(STRINGS "${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST}" manifestLines)

  set(packs "")
  set(urls "")
  set(hashes "")

  foreach(manifestLine IN LISTS manifestLines)
    string(STRIP "${manifestLine}" manifestLine)

    if (manifestLine STREQUAL "" OR manifestLine MATCHES "^#")
      continue()
    endif()

    if (NOT manifestLine MATCHES "^([^|]+)\\|([^|]+)\\|([0-9A-Fa-f]+)$")
      message(
        FATAL_ERROR
        "The '${manifestLine}' line of the ${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST} manifest follows no <pack>|<archive URL>|<archive SHA-256> form"
      )
    endif()

    string(STRIP "${CMAKE_MATCH_1}" pack)
    string(STRIP "${CMAKE_MATCH_2}" packUrl)
    string(TOLOWER "${CMAKE_MATCH_3}" packHash)
    string(LENGTH "${packHash}" packHashLength)

    if (NOT packHashLength EQUAL 64 OR pack IN_LIST packs)
      message(
        FATAL_ERROR
        "The '${manifestLine}' line of the ${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST} manifest carries no 64 digits SHA-256 checksum or names an already named pack"
      )
    endif()

    list(APPEND packs "${pack}")
    list(APPEND urls "${packUrl}")
    list(APPEND hashes "${packHash}")
  endforeach()

  if (NOT packs)
    message(
      FATAL_ERROR
      "The ${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST} manifest names no pack at all. Fill it with the Kenney packs of interest, one <pack>|<archive URL>|<archive SHA-256> line each."
    )
  endif()

  set(KENNEY_AUDIO_PACKS "${packs}" CACHE INTERNAL "The Kenney sound packs the manifest names")
  set(KENNEY_AUDIO_PACK_URLS "${urls}" CACHE INTERNAL "The archive URLs of the KENNEY_AUDIO_PACKS packs")
  set(KENNEY_AUDIO_PACK_HASHES "${hashes}" CACHE INTERNAL "The archive SHA-256 checksums of the KENNEY_AUDIO_PACKS packs")

  list(LENGTH packs packsCount)

  message(STATUS "Kenney packs named by the manifest: ${packsCount}")
endfunction()

# Downloads the given URL into the given file through a temporary file of it's
# own and accepts the download only when it's SHA-256 checksum is the expected
# one, so neither an interrupted nor an altered download is ever taken for the
# pinned archive.
function(template_project_kenney_audio_download url destination expectedHash)
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
      "Fail to download ${url}: ${downloadError}. Correct it's line of the ${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST} manifest, run the misc/scripts/fetch-kenney-audio.sh script by hand, or point the TEMPLATE_APP_KENNEY_AUDIO_DIR variable to an already downloaded packs directory."
    )
  endif()

  file(SHA256 "${destination}.part" actualHash)

  if (NOT actualHash STREQUAL expectedHash)
    file(REMOVE "${destination}.part")

    message(
      FATAL_ERROR
      "The ${url} download carries the ${actualHash} SHA-256 checksum instead of the ${expectedHash} one the ${TEMPLATE_APP_KENNEY_AUDIO_MANIFEST} manifest pins. Update it's manifest line only once the new archive is checked to be the expected one."
    )
  endif()

  file(RENAME "${destination}.part" "${destination}")
endfunction()

# Unpacks the given archive into the given directory, which appears only once
# the whole archive is out, so an interrupted run never leaves a half unpacked
# pack behind to be taken for a complete one on the next configure run.
#
# The archives are Windows made ones and carry the DOS read-only attribute on a
# directory of their own (the Audio one of the digital-audio pack), which the
# extraction turns into a directory no file may be created inside any more: the
# build tree stops being removable and copyable, the flatpak-builder source copy
# failing on it. Hence the extraction into a directory of it's own and the copy
# dropping the archive permissions.
#
# The extraction goes through "cmake -E tar" and not through the
# file(ARCHIVE_EXTRACT) command, because the latter needs CMake 3.18 while this
# project stays buildable with 3.13.
function(template_project_kenney_audio_unpack archive destination)
  set(unpackDir "${destination}.unpacked")
  set(copyDir "${destination}.partial")

  file(REMOVE_RECURSE "${unpackDir}" "${copyDir}")
  file(MAKE_DIRECTORY "${unpackDir}")

  execute_process(
    COMMAND "${CMAKE_COMMAND}" -E tar xf "${archive}"
    WORKING_DIRECTORY "${unpackDir}"
    RESULT_VARIABLE extractResult
  )

  if (NOT extractResult EQUAL 0)
    file(REMOVE_RECURSE "${unpackDir}")
    message(FATAL_ERROR "Fail to unpack the ${archive} archive")
  endif()

  file(COPY "${unpackDir}/" DESTINATION "${copyDir}" NO_SOURCE_PERMISSIONS)
  file(REMOVE_RECURSE "${unpackDir}")
  file(RENAME "${copyDir}" "${destination}")
endfunction()

# Downloads and unpacks every pack the manifest names into the
# KENNEY_AUDIO_ROOT_DIR directory, one subdirectory per pack. An already
# unpacked pack is left alone, so a reconfigure costs no download at all.
#
# The archives are plain ZIP files rather than a git checkout, hence the
# file(DOWNLOAD) and the archive extraction instead of a FetchContent
# declaration.
function(template_project_kenney_audio_fetch_packs)
  file(MAKE_DIRECTORY "${KENNEY_AUDIO_ROOT_DIR}")

  list(LENGTH KENNEY_AUDIO_PACKS packsCount)
  math(EXPR lastPackIndex "${packsCount} - 1")

  foreach(packIndex RANGE ${lastPackIndex})
    list(GET KENNEY_AUDIO_PACKS ${packIndex} pack)

    set(packDir "${KENNEY_AUDIO_ROOT_DIR}/${pack}")

    if (EXISTS "${packDir}")
      message(STATUS "Kenney pack already available: ${pack}")
      continue()
    endif()

    list(GET KENNEY_AUDIO_PACK_URLS ${packIndex} packUrl)
    list(GET KENNEY_AUDIO_PACK_HASHES ${packIndex} packHash)

    message(STATUS "Downloading the Kenney ${pack} pack: ${packUrl}")

    template_project_kenney_audio_download("${packUrl}" "${packDir}.zip" "${packHash}")
    template_project_kenney_audio_unpack("${packDir}.zip" "${packDir}")

    file(REMOVE "${packDir}.zip")
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

  message(STATUS "Kenney sounds made available: ${total}")
endfunction()
