cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_SHERPA_ONNX
    "Enables the sherpa-onnx speech recognition library for the project usage through FetchContent by internet"
    ON
)

if (NOT ENABLE_SHERPA_ONNX)
    return()
endif()

set(TEMPLATE_APP_SHERPA_ONNX_GIT "https://github.com/k2-fsa/sherpa-onnx.git" CACHE STRING "The sherpa-onnx library git source repository")
set(TEMPLATE_APP_SHERPA_ONNX_GIT_TAG "v1.13.8" CACHE STRING "The sherpa-onnx project git repository tag of interest")

# No distribution packages the sherpa-onnx, so it's sources are fetched and
# built with the C and the C++ APIs alone: no binaries, Python, tests, TTS,
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
  set(SHERPA_ONNX_USE_PRE_INSTALLED_ONNXRUNTIME_IF_AVAILABLE ON)

  foreach(unused IN ITEMS BINARY PYTHON TESTS TTS PORTAUDIO WEBSOCKET GPU SPEAKER_DIARIZATION)
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

set(TEMPLATE_APP_SHERPA_ONNX_MODEL "sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8" CACHE STRING "The sherpa-onnx asr-models release NeMo transducer model to download: the multilingual sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8 or sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8 one, the English only sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8 one etc.")

option(
    ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD
    "Downloads the TEMPLATE_APP_SHERPA_ONNX_MODEL model into the build directory while configuring and installs it with the binary"
    ON
)

# The SHA256 checksums of the sherpa-onnx asr-models release archives. The
# TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256 one checks any other model.
set(
  sherpaOnnxKnownModelsSha256
  sherpa-onnx-nemo-parakeet-tdt-0.6b-v3-int8=5793d0fd397c5778d2cf2126994d58e9d56b1be7c04d13c7a15bb1b4eafb16bf
  sherpa-onnx-nemo-parakeet-tdt-0.6b-v2-int8=157c157bc51155e03e37d2466522a3a737dd9c72bb25f36eb18912964161e1ad
  sherpa-onnx-nemo-fast-conformer-transducer-be-de-en-es-fr-hr-it-pl-ru-uk-20k-int8=06072bad277f0f4c29cc866d7c62b0e47936da39afafeae453faa925025ccad6
)

set(TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256 "" CACHE STRING "The SHA256 checksum the downloaded model archive is checked against, the known one of the listed models if empty")

set(sherpaOnnxModelSha256 "${TEMPLATE_APP_SHERPA_ONNX_MODEL_SHA256}")

foreach(knownModel IN LISTS sherpaOnnxKnownModelsSha256)
  if (NOT sherpaOnnxModelSha256 AND knownModel MATCHES "^${TEMPLATE_APP_SHERPA_ONNX_MODEL}=([0-9a-f]+)$")
    set(sherpaOnnxModelSha256 "${CMAKE_MATCH_1}")
  endif()
endforeach()

set(PROJECT_STT_MODEL "" CACHE STRING "The sherpa-onnx NeMo transducer model directory the application recognizes the speech with while no --model parameter is given, the downloaded TEMPLATE_APP_SHERPA_ONNX_MODEL one if empty")

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

if (NOT PROJECT_STT_MODEL)
    set(modelDir "${PROJECT_BINARY_DIR}/models")
    set(PROJECT_STT_MODEL "${modelDir}/${TEMPLATE_APP_SHERPA_ONNX_MODEL}")

    if (ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD AND NOT EXISTS "${PROJECT_STT_MODEL}/tokens.txt")
        set(modelArchive "${modelDir}/${TEMPLATE_APP_SHERPA_ONNX_MODEL}.tar.bz2")

        message(STATUS "Downloading the ${TEMPLATE_APP_SHERPA_ONNX_MODEL} sherpa-onnx model, which takes a while")

        file(
            DOWNLOAD "https://github.com/k2-fsa/sherpa-onnx/releases/download/asr-models/${TEMPLATE_APP_SHERPA_ONNX_MODEL}.tar.bz2"
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

        if (NOT modelDownloadCode EQUAL 0 OR NOT EXISTS "${PROJECT_STT_MODEL}/tokens.txt")
            message(WARNING "Fail to download the ${TEMPLATE_APP_SHERPA_ONNX_MODEL} sherpa-onnx model, so the application needs the --model parameter")
        endif()
    endif()

    # The installation takes the downloaded model directory but it's test
    # recordings, while a failed download leaves none to install.
    if (ENABLE_SHERPA_ONNX_MODEL_DOWNLOAD)
        install(
            DIRECTORY "${PROJECT_STT_MODEL}" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL
            PATTERN test_wavs EXCLUDE
        )
    endif()
endif()

message(STATUS "The sherpa-onnx model: ${PROJECT_STT_MODEL}")

# Link the SherpaONNX::cxx-api target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE SherpaONNX::cxx-api)
