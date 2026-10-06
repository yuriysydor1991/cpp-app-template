cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_WHISPERCPP
    "Enables the whisper.cpp speech recognition library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_WHISPERCPP)
    return()
endif()

set(TEMPLATE_APP_WHISPERCPP_GIT "https://github.com/ggml-org/whisper.cpp.git" CACHE STRING "The whisper.cpp library git source repository")
set(TEMPLATE_APP_WHISPERCPP_GIT_TAG "v1.9.4" CACHE STRING "The whisper.cpp project git repository tag of interest")

# The fetched sources build their examples, tests and server as the top level
# project only, so the whisper and the ggml libraries are all they build here.
template_project_default_3rdparty_enabler(
  NAME whisper
  GIT_REPOSITORY ${TEMPLATE_APP_WHISPERCPP_GIT}
  GIT_TAG ${TEMPLATE_APP_WHISPERCPP_GIT_TAG}
)

# The fetched whisper.cpp and ggml are the 3rd-party code as much as the
# installed ones, so their headers stay out of the project warnings and the
# clang-tidy checks.
foreach(whisperTarget IN ITEMS whisper ggml ggml-base)
  if (TARGET ${whisperTarget})
    set_target_properties(${whisperTarget} PROPERTIES SYSTEM ON)
  endif()
endforeach()

set(PROJECT_WHISPER_LANGUAGE "auto" CACHE STRING "The spoken language code (en, uk, de etc.) the multilingual whisper.cpp models transcribe, auto to detect it")

set(TEMPLATE_APP_WHISPERCPP_MODEL "base.en" CACHE STRING "The whisper.cpp ggml model (tiny, base.en, small, large-v3-turbo etc.) to download")

option(
    ENABLE_WHISPERCPP_MODEL_DOWNLOAD
    "Downloads the TEMPLATE_APP_WHISPERCPP_MODEL whisper.cpp model into the build directory while configuring"
    OFF
)

set(PROJECT_WHISPER_MODEL_PATH "" CACHE STRING "The whisper.cpp model the application loads while no --model parameter is given, the downloaded TEMPLATE_APP_WHISPERCPP_MODEL one if empty")

if (NOT PROJECT_WHISPER_MODEL_PATH)
    set(PROJECT_WHISPER_MODEL_PATH "${CMAKE_BINARY_DIR}/models/ggml-${TEMPLATE_APP_WHISPERCPP_MODEL}.bin")
endif()

if (ENABLE_WHISPERCPP_MODEL_DOWNLOAD AND NOT EXISTS "${PROJECT_WHISPER_MODEL_PATH}")
    message(STATUS "Downloading the ${TEMPLATE_APP_WHISPERCPP_MODEL} whisper.cpp model, which takes a while")

    file(
        DOWNLOAD "https://huggingface.co/ggerganov/whisper.cpp/resolve/main/ggml-${TEMPLATE_APP_WHISPERCPP_MODEL}.bin"
        "${PROJECT_WHISPER_MODEL_PATH}"
        TLS_VERIFY ON
        STATUS modelDownloadStatus
    )

    list(GET modelDownloadStatus 0 modelDownloadCode)

    # A failed download leaves a broken file behind, which no later configure
    # would replace.
    if (NOT modelDownloadCode EQUAL 0)
        file(REMOVE "${PROJECT_WHISPER_MODEL_PATH}")
        message(WARNING "Fail to download the ${TEMPLATE_APP_WHISPERCPP_MODEL} whisper.cpp model: ${modelDownloadStatus}")
    endif()
endif()

message(STATUS "The whisper.cpp model: ${PROJECT_WHISPER_MODEL_PATH}")

# Link the whisper target, the very same one for the system installed and the
# fetched library, to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} whisper)
