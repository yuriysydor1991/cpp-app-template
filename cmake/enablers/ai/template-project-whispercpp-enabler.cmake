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

# The SHA1 checksums of the models the whisper.cpp models/README.md of the
# v1.9.4 release lists. The TEMPLATE_APP_WHISPERCPP_MODEL_SHA1 one checks any
# other model.
set(
  whisperKnownModelsSha1
  tiny=bd577a113a864445d4c299885e0cb97d4ba92b5f
  tiny.en=c78c86eb1a8faa21b369bcd33207cc90d64ae9df
  base=465707469ff3a37a2b9b8d8f89f2f99de7299dac
  base.en=137c40403d78fd54d454da0f9bd998f78703390c
  small=55356645c2b361a969dfd0ef2c5a50d530afd8d5
  small.en=db8a495a91d927739e50b3fc1cc4c6b8f6c2d022
  small.en-tdrz=b6c6e7e89af1a35c08e6de56b66ca6a02a2fdfa1
  medium=fd9727b6e1217c2f614f9b698455c4ffd82463b4
  medium.en=8c30f0e44ce9560643ebd10bbe50cd20eafd3723
  large-v1=b1caaf735c4cc1429223d5a74f0f4d0b9b59a299
  large-v2=0f4c8e34f21cf1a914c59d8b3ce882345ad349d6
  large-v2-q5_0=00e39f2196344e901b3a2bd5814807a769bd1630
  large-v3=ad82bf6a9043ceed055076d0fd39f5f186ff8062
  large-v3-q5_0=e6e2ed78495d403bef4b7cff42ef4aaadcfea8de
  large-v3-turbo=4af2b29d7ec73d781377bfd1758ca957a807e941
  large-v3-turbo-q5_0=e050f7970618a659205450ad97eb95a18d69c9ee
)

set(TEMPLATE_APP_WHISPERCPP_MODEL_SHA1 "" CACHE STRING "The SHA1 checksum the downloaded model is checked against, the known one of the listed models if empty")

set(whisperModelSha1 "${TEMPLATE_APP_WHISPERCPP_MODEL_SHA1}")

foreach(knownModel IN LISTS whisperKnownModelsSha1)
  if (NOT whisperModelSha1 AND knownModel MATCHES "^${TEMPLATE_APP_WHISPERCPP_MODEL}=([0-9a-f]+)$")
    set(whisperModelSha1 "${CMAKE_MATCH_1}")
  endif()
endforeach()

set(PROJECT_WHISPER_MODEL_PATH "" CACHE STRING "The whisper.cpp model the application loads while no --model parameter is given, the downloaded TEMPLATE_APP_WHISPERCPP_MODEL one if empty")

if (NOT PROJECT_WHISPER_MODEL_PATH)
    set(modelDir "${CMAKE_BINARY_DIR}/models")
    set(PROJECT_WHISPER_MODEL_PATH "${modelDir}/ggml-${TEMPLATE_APP_WHISPERCPP_MODEL}.bin")

    if (ENABLE_WHISPERCPP_MODEL_DOWNLOAD AND NOT EXISTS "${PROJECT_WHISPER_MODEL_PATH}")
        # The model download scripts come with the whisper.cpp sources and with
        # no system package, so the one of the TEMPLATE_APP_WHISPERCPP_GIT_TAG
        # release is fetched first. It downloads the model from the Hugging Face
        # with the curl, the wget or, on the MS Windows, the PowerShell.
        # The script runs at the configure time, so the one of the v1.9.4
        # release is taken whatever the library tag is and its checksum is
        # checked before it runs.
        if (WIN32)
            set(modelScript download-ggml-model.cmd)
            set(modelScriptShell cmd /c)
            set(modelScriptSha256 cd2b8e77ea186175409672c2ec3b945a8587e7d6f36222cf98ccdb4b6df02dd3)
        else()
            set(modelScript download-ggml-model.sh)
            set(modelScriptShell sh)
            set(modelScriptSha256 fa7e697dc9eb77c1fdba7936687f73adfae6897075e5e2661758cfb3f3aa6aa4)
        endif()

        file(
            DOWNLOAD "https://raw.githubusercontent.com/ggml-org/whisper.cpp/v1.9.4/models/${modelScript}"
            "${modelDir}/${modelScript}"
            EXPECTED_HASH SHA256=${modelScriptSha256}
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

        # A downloaded model of a wrong checksum is no model to load.
        if (modelDownloadCode EQUAL 0 AND EXISTS "${PROJECT_WHISPER_MODEL_PATH}")
            if (whisperModelSha1)
                file(SHA1 "${PROJECT_WHISPER_MODEL_PATH}" downloadedModelSha1)

                if (NOT downloadedModelSha1 STREQUAL whisperModelSha1)
                    message(WARNING "The downloaded ${TEMPLATE_APP_WHISPERCPP_MODEL} whisper.cpp model checksum ${downloadedModelSha1} differs from the expected ${whisperModelSha1}")
                    set(modelDownloadCode 1)
                endif()
            else()
                message(STATUS "No known checksum of the ${TEMPLATE_APP_WHISPERCPP_MODEL} whisper.cpp model to check the download against, set the TEMPLATE_APP_WHISPERCPP_MODEL_SHA1 one")
            endif()
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
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE whisper)
