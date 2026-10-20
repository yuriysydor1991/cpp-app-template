cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_PIPER
    "Enables the Piper neural speech synthesis library (the libpiper of the piper1-gpl project) for the project usage, built out of it's sources fetched by internet"
    ON
)

if (NOT ENABLE_PIPER)
    return()
endif()

include(ExternalProject)
include(GNUInstallDirs)

set(TEMPLATE_APP_PIPER_GIT "https://github.com/OHF-Voice/piper1-gpl.git" CACHE STRING "The Piper (piper1-gpl) git source repository")
set(TEMPLATE_APP_PIPER_GIT_TAG "v1.8.0" CACHE STRING "The Piper project git repository tag of interest")

# The onnxruntime runs the Piper voices. The installed one is taken where the
# system packages it, while the Piper build downloads the prebuilt one of the
# GNU/Linux, the MS Windows or the macOS otherwise.
find_package(onnxruntime QUIET)

if (onnxruntime_FOUND)
    message(STATUS "System already contains the onnxruntime ${onnxruntime_VERSION} library")
else()
    message(STATUS "No onnxruntime library is found, so the Piper build downloads the prebuilt one")
endif()

# No system packages the libpiper and it's CMake project builds as the top
# level one only, so it is built and installed into the build directory as a
# separate project, away from the project warnings and the clang-tidy checks.
# It builds the pinned espeak-ng it phonemizes the text with statically and
# installs the espeak-ng-data of it beside the library, where the controller
# looks for it. The espeak-ng limits it's data paths to 160 characters, so the
# directories are kept short and the build directory path has to stay below 90
# characters or so.
set(piperPrefix "${CMAKE_BINARY_DIR}/piper")
set(piperLibrary "${piperPrefix}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}piper${CMAKE_SHARED_LIBRARY_SUFFIX}")

ExternalProject_Add(
  piper_external
  GIT_REPOSITORY ${TEMPLATE_APP_PIPER_GIT}
  GIT_TAG ${TEMPLATE_APP_PIPER_GIT_TAG}
  GIT_SHALLOW ON
  UPDATE_DISCONNECTED ON
  PREFIX ${piperPrefix}
  SOURCE_DIR ${piperPrefix}/source
  BINARY_DIR ${piperPrefix}/build
  SOURCE_SUBDIR libpiper
  CMAKE_CACHE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DCMAKE_INSTALL_PREFIX:PATH=${piperPrefix}
    -DCMAKE_INSTALL_LIBDIR:PATH=lib
    -DCMAKE_INSTALL_DATAROOTDIR:PATH=lib
    -DCMAKE_INSTALL_RPATH:STRING=$ORIGIN
    -Donnxruntime_DIR:PATH=${onnxruntime_DIR}
  BUILD_BYPRODUCTS ${piperLibrary}
)

file(MAKE_DIRECTORY "${piperPrefix}/include")

add_library(Piper::piper SHARED IMPORTED GLOBAL)

set_target_properties(
  Piper::piper PROPERTIES
  IMPORTED_LOCATION ${piperLibrary}
  INTERFACE_INCLUDE_DIRECTORIES "${piperPrefix}/include"
)

add_dependencies(Piper::piper piper_external)

# The installed executable finds the libpiper, the downloaded onnxruntime and
# the espeak-ng-data in the library directory of the project.
install(
  DIRECTORY "${piperPrefix}/lib/"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_BINARY_NAME}"
)

set(PROJECT_TTS_TEXT "Hello, Piper! Insert your text here!" CACHE STRING "The text the application speaks while no --text parameter is given")

set(TEMPLATE_APP_PIPER_VOICE "en_US-lessac-medium" CACHE STRING "The Piper voice (en_US-lessac-medium, uk_UA-ukrainian_tts-medium etc.) to download")
set(TEMPLATE_APP_PIPER_VOICES_URL "https://huggingface.co/rhasspy/piper-voices/resolve/c10ece1aade47bb51c153c893d14e5bf8e5b7117" CACHE STRING "The pinned revision of the Piper voices repository to download the voice from")

option(
    ENABLE_PIPER_VOICE_DOWNLOAD
    "Downloads the TEMPLATE_APP_PIPER_VOICE voice into the build directory while configuring and installs it with the binary"
    ON
)

# The SHA256 checksums of the voices of the pinned revision. The other voices
# are downloaded unchecked.
set(
  piperKnownVoicesSha256
  en_US-lessac-medium.onnx=5efe09e69902187827af646e1a6e9d269dee769f9877d17b16b1b46eeaaf019f
  en_US-lessac-medium.onnx.json=efe19c417bed055f2d69908248c6ba650fa135bc868b0e6abb3da181dab690a0
  uk_UA-ukrainian_tts-medium.onnx=7920419ac5f6fd8b6450520f24b52ed5a319cb53dd018fbcd71c9e079cbac84f
  uk_UA-ukrainian_tts-medium.onnx.json=4e96e72917ca9b94edc77d6ccfee03a73f450ba2fc1ca93c2e562bc014e5aa55
)

set(PROJECT_TTS_VOICE "" CACHE STRING "The Piper voice model (an .onnx file with it's .onnx.json config beside it) the application speaks with while no --voice parameter is given, the downloaded TEMPLATE_APP_PIPER_VOICE one if empty")

# The install step copies the downloaded voice into the data directory of the
# project, where the installed binary looks for it relative to it's own
# location first (see the src/app/DataLocator.h file), so the installation
# needs no build tree.
set(PROJECT_DATA_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}")
set(PROJECT_DATA_INSTALLED_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_BINARY_NAME}")

file(
  RELATIVE_PATH PROJECT_DATA_INSTALLED_RELATIVE_DIR
  "/${PROJECT_BINARY_INSTALLATION_DIR}" "/${PROJECT_DATA_INSTALL_DIR}"
)

if (NOT PROJECT_TTS_VOICE)
    set(voiceDir "${CMAKE_BINARY_DIR}/voices")
    set(PROJECT_TTS_VOICE "${voiceDir}/${TEMPLATE_APP_PIPER_VOICE}.onnx")

    # The voices are kept by the language, the region, the name and the
    # quality: the en_US-lessac-medium one in the en/en_US/lessac/medium
    # directory.
    string(REGEX REPLACE "^(([^_]+)_[^-]+)-(.+)-([^-]+)$" "\\2/\\1/\\3/\\4" voicePath "${TEMPLATE_APP_PIPER_VOICE}")

    foreach(voiceFile IN ITEMS ${TEMPLATE_APP_PIPER_VOICE}.onnx.json ${TEMPLATE_APP_PIPER_VOICE}.onnx)
        if (NOT ENABLE_PIPER_VOICE_DOWNLOAD OR EXISTS "${voiceDir}/${voiceFile}")
            continue()
        endif()

        message(STATUS "Downloading the ${voiceFile} Piper voice file")

        file(
            DOWNLOAD "${TEMPLATE_APP_PIPER_VOICES_URL}/${voicePath}/${voiceFile}"
            "${voiceDir}/${voiceFile}"
            TLS_VERIFY ON
            STATUS voiceStatus
        )

        list(GET voiceStatus 0 voiceCode)

        # A downloaded known voice of a wrong checksum is no voice to load.
        foreach(knownVoice IN LISTS piperKnownVoicesSha256)
            if (voiceCode EQUAL 0 AND knownVoice MATCHES "^${voiceFile}=([0-9a-f]+)$")
                set(knownHash "${CMAKE_MATCH_1}")
                file(SHA256 "${voiceDir}/${voiceFile}" voiceHash)

                if (NOT voiceHash STREQUAL knownHash)
                    set(voiceCode 1)
                    set(voiceStatus "the ${voiceHash} checksum differs from the expected ${knownHash} one")
                endif()
            endif()
        endforeach()

        # A failed download leaves a broken file behind, which would be taken
        # for a downloaded voice next time.
        if (NOT voiceCode EQUAL 0)
            file(REMOVE "${voiceDir}/${voiceFile}")
            message(WARNING "Fail to download the ${voiceFile} Piper voice file (${voiceStatus}), so the application needs the --voice parameter")
        endif()
    endforeach()

    # The installation takes the downloaded voice with it's config, while a
    # failed download leaves none to install.
    if (ENABLE_PIPER_VOICE_DOWNLOAD)
        install(FILES "${PROJECT_TTS_VOICE}" "${PROJECT_TTS_VOICE}.json" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL)
    endif()
endif()

message(STATUS "The Piper voice: ${PROJECT_TTS_VOICE}")

# Link the Piper::piper target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE Piper::piper)
