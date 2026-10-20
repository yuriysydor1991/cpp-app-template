cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_SHERPA_ONNX
    "Enables the sherpa-onnx speech synthesis library for the project usage through FetchContent by internet"
    ON
)

if (NOT ENABLE_SHERPA_ONNX)
    return()
endif()

set(TEMPLATE_APP_SHERPA_ONNX_GIT "https://github.com/k2-fsa/sherpa-onnx.git" CACHE STRING "The sherpa-onnx library git source repository")
set(TEMPLATE_APP_SHERPA_ONNX_GIT_TAG "v1.13.8" CACHE STRING "The sherpa-onnx project git repository tag of interest")

set(PROJECT_TTS_TEXT "Hello, sherpa-onnx! Insert your text here!" CACHE STRING "The text the application speaks while no --text parameter is given")

# No distribution packages the sherpa-onnx, so it's sources are fetched and
# built with the C and the C++ APIs alone: no binaries, Python, tests,
# PortAudio, websocket, GPU or speaker diarization. The onnxruntime is the
# pre-installed one where the distribution packages it (the
# libonnxruntime-dev, the onnxruntime-devel, the FreeBSD misc/onnxruntime
# ones) and the sherpa-onnx prebuilt download otherwise, while the
# SHERPA_ONNXRUNTIME_INCLUDE_DIR and SHERPA_ONNXRUNTIME_LIB_DIR environment
# variables point at a custom installation. The libraries are the shared
# ones, since the static prebuilt onnxruntime, built with an older GCC, breaks
# the libstdc++ templates the executable shares with it. The function scope
# keeps these options away from the rest of the project, while the CMP0077
# policy makes the older dependencies of the sherpa-onnx take them as well.
function(template_project_sherpa_onnx_fetch)
  set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
  set(BUILD_SHARED_LIBS ON)
  set(SHERPA_ONNX_ENABLE_C_API ON)
  set(SHERPA_ONNX_ENABLE_TTS ON)
  set(SHERPA_ONNX_USE_PRE_INSTALLED_ONNXRUNTIME_IF_AVAILABLE ON)

  foreach(unused IN ITEMS BINARY PYTHON TESTS PORTAUDIO WEBSOCKET GPU SPEAKER_DIARIZATION)
    set(SHERPA_ONNX_ENABLE_${unused} OFF)
  endforeach()

  message(STATUS "sherpa-onnx URL: ${TEMPLATE_APP_SHERPA_ONNX_GIT}")
  message(STATUS "sherpa-onnx Tag: ${TEMPLATE_APP_SHERPA_ONNX_GIT_TAG}")

  include(FetchContent)

  # The EXCLUDE_FROM_ALL keeps the sherpa-onnx install rules (it's headers,
  # libraries and pkg-config file) out of the project installation, which
  # takes the libraries the executable needs alone (see the
  # src/SherpaONNX/CMakeLists.txt file).
  FetchContent_Declare(
      sherpa-onnx
      GIT_REPOSITORY ${TEMPLATE_APP_SHERPA_ONNX_GIT}
      GIT_TAG        ${TEMPLATE_APP_SHERPA_ONNX_GIT_TAG}
      GIT_SHALLOW    ON
      EXCLUDE_FROM_ALL
  )

  FetchContent_MakeAvailable(sherpa-onnx)
endfunction()

template_project_sherpa_onnx_fetch()

# The fetched sherpa-onnx is the 3rd-party code, so it's headers stay out of
# the project warnings and the clang-tidy checks.
set_target_properties(sherpa-onnx-c-api sherpa-onnx-cxx-api PROPERTIES SYSTEM ON)

add_library(SherpaONNX::cxx-api ALIAS sherpa-onnx-cxx-api)

# The install rules of the sherpa-onnx dependencies stay out of the
# installation, yet the Devel component the Eigen one declares would still make
# the DEB and the RPM packagers produce an empty package of it, so the packages
# take the components of the project install rules alone.
set(CPACK_COMPONENTS_ALL Unspecified)

set(TEMPLATE_APP_SHERPA_ONNX_MODEL "kokoro-int8-multi-lang-v1_0" CACHE STRING "The sherpa-onnx tts-models release model to download: a Kokoro (kokoro-int8-multi-lang-v1_0, kokoro-en-v0_19 etc.) or a VITS (vits-melo-tts-zh_en, vits-piper-en_US-amy-low-int8 etc.) one")

option(
    ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD
    "Downloads the TEMPLATE_APP_SHERPA_ONNX_MODEL model into the build directory while configuring and installs it with the binary"
    ON
)

# The SHA256 checksums of the sherpa-onnx tts-models release archives. The
# TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256 one checks any other model.
set(
  sherpaOnnxKnownModelsSha256
  kokoro-int8-multi-lang-v1_0=4c3052abaa60943a341f193888cf6abd68787dae6ab8ae5c925a706caa247e4e
  kokoro-multi-lang-v1_0=c5f7e2d2caf082bc1d20fb70334a61d99d20b484500aad32e7cf84c128ea3298
  kokoro-int8-en-v0_19=c9f0dd393615805b0bab050c340834d5e684e732aec91c0e860cd30e982c08bd
  kokoro-en-v0_19=912804855a04745fa77a30be545b3f9a5d15c4d66db00b88cbcd4921df605ac7
  vits-melo-tts-zh_en=e58351ed7149f290a54534538badd4077cdbe6fddc964b24d0bee870415d1514
  vits-piper-en_US-amy-low-int8=93070ac9fadf512e56c46bdd0c5d2ce96b424fdc4e683d560167410bd2c4df7d
)

set(TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256 "" CACHE STRING "The SHA256 checksum the downloaded model archive is checked against, the known one of the listed models if empty")

set(sherpaOnnxModelSha256 "${TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256}")

foreach(knownModel IN LISTS sherpaOnnxKnownModelsSha256)
  if (NOT sherpaOnnxModelSha256 AND knownModel MATCHES "^${TEMPLATE_APP_SHERPA_ONNX_MODEL}=([0-9a-f]+)$")
    set(sherpaOnnxModelSha256 "${CMAKE_MATCH_1}")
  endif()
endforeach()

set(PROJECT_TTS_VOICE "" CACHE STRING "The sherpa-onnx model directory, optionally with the :<id> speaker id suffix, the application speaks with while no --voice parameter is given, the downloaded TEMPLATE_APP_SHERPA_ONNX_MODEL one if empty")

# The install step copies the downloaded model directory into the data
# directory of the project, where the installed binary looks for it relative
# to it's own location first (see the src/app/DataLocator.h file), so the
# installation needs no build tree.
set(PROJECT_DATA_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}")
set(PROJECT_DATA_INSTALLED_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_BINARY_NAME}")

file(
  RELATIVE_PATH PROJECT_DATA_INSTALLED_RELATIVE_DIR
  "/${PROJECT_BINARY_INSTALLATION_DIR}" "/${PROJECT_DATA_INSTALL_DIR}"
)

if (NOT PROJECT_TTS_VOICE)
    set(modelDir "${CMAKE_BINARY_DIR}/models")
    set(PROJECT_TTS_VOICE "${modelDir}/${TEMPLATE_APP_SHERPA_ONNX_MODEL}")

    if (ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD AND NOT EXISTS "${PROJECT_TTS_VOICE}/tokens.txt")
        set(modelArchive "${modelDir}/${TEMPLATE_APP_SHERPA_ONNX_MODEL}.tar.bz2")

        message(STATUS "Downloading the ${TEMPLATE_APP_SHERPA_ONNX_MODEL} sherpa-onnx model, which takes a while")

        file(
            DOWNLOAD "https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/${TEMPLATE_APP_SHERPA_ONNX_MODEL}.tar.bz2"
            "${modelArchive}"
            TLS_VERIFY ON
            STATUS modelStatus
        )

        list(GET modelStatus 0 modelDownloadCode)

        # A downloaded model of a wrong checksum is no model to load.
        if (modelDownloadCode EQUAL 0)
            if (sherpaOnnxModelSha256)
                file(SHA256 "${modelArchive}" downloadedModelSha256)

                if (NOT downloadedModelSha256 STREQUAL sherpaOnnxModelSha256)
                    message(WARNING "The downloaded ${TEMPLATE_APP_SHERPA_ONNX_MODEL} sherpa-onnx model checksum ${downloadedModelSha256} differs from the expected ${sherpaOnnxModelSha256}")
                    set(modelDownloadCode 1)
                endif()
            else()
                message(STATUS "No known checksum of the ${TEMPLATE_APP_SHERPA_ONNX_MODEL} sherpa-onnx model to check the download against, set the TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256 one")
            endif()
        endif()

        if (modelDownloadCode EQUAL 0)
            execute_process(
                COMMAND ${CMAKE_COMMAND} -E tar xf "${modelArchive}"
                WORKING_DIRECTORY "${modelDir}"
                RESULT_VARIABLE modelDownloadCode
            )
        endif()

        file(REMOVE "${modelArchive}")

        if (NOT modelDownloadCode EQUAL 0 OR NOT EXISTS "${PROJECT_TTS_VOICE}/tokens.txt")
            message(WARNING "Fail to download the ${TEMPLATE_APP_SHERPA_ONNX_MODEL} sherpa-onnx model, so the application needs the --voice parameter")
        endif()
    endif()

    # The installation takes the downloaded model directory, while a failed
    # download leaves none to install.
    if (ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD)
        install(DIRECTORY "${PROJECT_TTS_VOICE}" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL)
    endif()
endif()

message(STATUS "The sherpa-onnx voice: ${PROJECT_TTS_VOICE}")

# Link the SherpaONNX::cxx-api target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE SherpaONNX::cxx-api)
