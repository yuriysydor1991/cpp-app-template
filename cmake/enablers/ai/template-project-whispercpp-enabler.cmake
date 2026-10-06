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

set(TEMPLATE_APP_WHISPERCPP_MODEL "small" CACHE STRING "The whisper.cpp ggml model to download: a multilingual one (tiny, base, small, medium, large-v3-turbo etc.) transcribes the English, the Ukrainian and the other languages, while the .en ones the English only")

option(
    ENABLE_WHISPERCPP_MODEL_DOWNLOAD
    "Downloads the TEMPLATE_APP_WHISPERCPP_MODEL model into the build directory with the whisper.cpp download script while configuring"
    ON
)

set(PROJECT_WHISPER_MODEL_PATH "" CACHE STRING "The whisper.cpp model the application loads while no --model parameter is given, the downloaded TEMPLATE_APP_WHISPERCPP_MODEL one if empty")

if (NOT PROJECT_WHISPER_MODEL_PATH)
    set(modelDir "${CMAKE_BINARY_DIR}/models")
    set(PROJECT_WHISPER_MODEL_PATH "${modelDir}/ggml-${TEMPLATE_APP_WHISPERCPP_MODEL}.bin")

    if (ENABLE_WHISPERCPP_MODEL_DOWNLOAD AND NOT EXISTS "${PROJECT_WHISPER_MODEL_PATH}")
        # The model download scripts come with the whisper.cpp sources and with
        # no system package, so the one of the TEMPLATE_APP_WHISPERCPP_GIT_TAG
        # release is fetched first. It downloads the model from the Hugging Face
        # with the curl, the wget or, on the MS Windows, the PowerShell.
        if (WIN32)
            set(modelScript download-ggml-model.cmd)
            set(modelScriptShell cmd /c)
        else()
            set(modelScript download-ggml-model.sh)
            set(modelScriptShell sh)
        endif()

        file(
            DOWNLOAD "https://raw.githubusercontent.com/ggml-org/whisper.cpp/${TEMPLATE_APP_WHISPERCPP_GIT_TAG}/models/${modelScript}"
            "${modelDir}/${modelScript}"
            TLS_VERIFY ON
            STATUS modelScriptStatus
        )

        list(GET modelScriptStatus 0 modelScriptCode)

        if (modelScriptCode EQUAL 0)
            message(STATUS "Downloading the ${TEMPLATE_APP_WHISPERCPP_MODEL} whisper.cpp model, which takes a while")

            file(TO_NATIVE_PATH "${modelDir}/${modelScript}" nativeModelScript)
            file(TO_NATIVE_PATH "${modelDir}" nativeModelDir)

            execute_process(
                COMMAND ${modelScriptShell} "${nativeModelScript}" ${TEMPLATE_APP_WHISPERCPP_MODEL} "${nativeModelDir}"
                RESULT_VARIABLE modelDownloadCode
            )
        endif()

        # A failed download leaves a broken file behind, which the script would
        # take for a downloaded model next time.
        if (NOT modelDownloadCode EQUAL 0 OR NOT EXISTS "${PROJECT_WHISPER_MODEL_PATH}")
            file(REMOVE "${PROJECT_WHISPER_MODEL_PATH}")
            message(WARNING "Fail to download the ${TEMPLATE_APP_WHISPERCPP_MODEL} whisper.cpp model, so the application needs the --model parameter")
        endif()
    endif()
endif()

message(STATUS "The whisper.cpp model: ${PROJECT_WHISPER_MODEL_PATH}")

# Link the whisper target, the very same one for the system installed and the
# fetched library, to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} whisper)
