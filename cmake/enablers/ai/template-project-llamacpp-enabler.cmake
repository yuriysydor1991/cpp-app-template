cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_LLAMACPP
    "Enables the llama.cpp large language models library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_LLAMACPP)
    return()
endif()

set(TEMPLATE_APP_LLAMACPP_ARCHIVE "https://github.com/ggml-org/llama.cpp/archive/refs/tags/v0.7.0.tar.gz" CACHE STRING "The llama.cpp release sources archive to fetch")
set(TEMPLATE_APP_LLAMACPP_ARCHIVE_SHA256 "55d67acf3ad2ad747a9bbeb75f9f0e173dbcc0d1753a471038a90c819421c5e1" CACHE STRING "The SHA256 checksum of the TEMPLATE_APP_LLAMACPP_ARCHIVE archive")
set(TEMPLATE_APP_LLAMACPP_MIN_VERSION "0.0.8751" CACHE STRING "The oldest system installed llama.cpp taken, since the older ones load no Gemma 4 E4B model")
set(TEMPLATE_APP_LLAMACPP_BUILD_TYPE "Release" CACHE STRING "The build type of the fetched llama.cpp, whatever the project one is")

# The system installed llama.cpp too old for the Gemma 4 models gives way to
# the fetched one, and so do the ones older than the v0.x releases, whose
# version file the find_package reads not. The older llama.cpp packages fail
# to be found twice, so this is the single system probe.
find_package(llama ${TEMPLATE_APP_LLAMACPP_MIN_VERSION} QUIET)

if (llama_FOUND)
    message(STATUS "System already contains the llama library ${llama_VERSION}")
else()
    message(STATUS "Fetching the ${TEMPLATE_APP_LLAMACPP_ARCHIVE} llama.cpp through the Internet")

    include(FetchContent)

    # The extracted files get the time of the extraction, so a changed archive
    # rebuilds them.
    if (POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
    endif()

    # The release archive of tens of megabytes is fetched, since even the
    # shallow clone of the repository takes hundreds of them.
    FetchContent_Declare(
        llama
        URL ${TEMPLATE_APP_LLAMACPP_ARCHIVE}
        URL_HASH SHA256=${TEMPLATE_APP_LLAMACPP_ARCHIVE_SHA256}
    )

    # The fetched sources build their examples, tools and tests as the top
    # level project only, so the llama and the ggml libraries are all they
    # build here. The tensor kernels of a Debug build take minutes for a single
    # answer, so they get the TEMPLATE_APP_LLAMACPP_BUILD_TYPE build type, while
    # the project keeps it's own one. The libraries get linked into the
    # executable statically and installed nowhere, so no package carries their
    # files, which clash with the ggml packages of the distributions.
    set(CMAKE_BUILD_TYPE ${TEMPLATE_APP_LLAMACPP_BUILD_TYPE})
    set(BUILD_SHARED_LIBS OFF)
    FetchContent_MakeAvailable(llama)
    unset(BUILD_SHARED_LIBS)
    unset(CMAKE_BUILD_TYPE)

    set_property(DIRECTORY ${llama_SOURCE_DIR} PROPERTY EXCLUDE_FROM_ALL ON)
endif()

# The fetched llama.cpp and ggml are the 3rd-party code as much as the
# installed ones, so their headers stay out of the project warnings and the
# clang-tidy checks.
foreach(llamaTarget IN ITEMS llama ggml ggml-base ggml-cpu)
  if (TARGET ${llamaTarget})
    set_target_properties(${llamaTarget} PROPERTIES SYSTEM ON)
  endif()
endforeach()

set(TEMPLATE_APP_LLAMACPP_MODEL "gemma-4-E4B" CACHE STRING "The GGUF model to download: the gemma-4-E4B one runs within 8 GB of RAM, while the gemma-4-12B one needs 16 GB")
set_property(CACHE TEMPLATE_APP_LLAMACPP_MODEL PROPERTY STRINGS gemma-4-E4B gemma-4-12B)

option(
    ENABLE_LLAMACPP_MODEL_DOWNLOAD
    "Downloads the TEMPLATE_APP_LLAMACPP_MODEL model into the TEMPLATE_APP_LLAMACPP_MODELS_DIR directory while configuring and installs it with the binary"
    ON
)

# The models of several gigabytes are kept out of the build directories, which
# the scripts/build scripts erase on every configure, so the build directories
# of the source tree share a single download.
set(TEMPLATE_APP_LLAMACPP_MODELS_DIR "${CMAKE_SOURCE_DIR}/build/models" CACHE PATH "The directory the models are downloaded into")

# The quantization aware trained Q4_0 Gemma 4 models of the Google with their
# SHA256 checksums, downloaded from the pinned revisions of their repositories.
set(
  llamaKnownModels
  "gemma-4-E4B|https://huggingface.co/google/gemma-4-E4B-it-qat-q4_0-gguf/resolve/4b4a2c1d584be7264f87aac328a1bc739ce81b6c/gemma-4-E4B_q4_0-it.gguf|676c35070db6dbe52f93e9c864ee0fba4eddea94b9c875d9cb10daff453fbaee"
  "gemma-4-12B|https://huggingface.co/google/gemma-4-12B-it-qat-q4_0-gguf/resolve/29d097773436b69ff9feafd636ab4cf873786537/gemma-4-12b-it-qat-q4_0.gguf|93567e57a8fe10b23569b9d9ec38cd005deedf71e29477c421a4b83f418a538b"
)

set(PROJECT_LLAMACPP_MODEL_PATH "" CACHE STRING "The GGUF model the application loads while no --model parameter is given, the downloaded TEMPLATE_APP_LLAMACPP_MODEL one if empty")

# The install step copies the downloaded model into the data directory of the
# project, where the installed binary looks for it relative to it's own
# location first (see the src/app/DataLocator.h file), so the installation
# needs no source tree.
set(PROJECT_DATA_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}")
set(PROJECT_DATA_INSTALLED_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_BINARY_NAME}")

file(
  RELATIVE_PATH PROJECT_DATA_INSTALLED_RELATIVE_DIR
  "/${PROJECT_BINARY_INSTALLATION_DIR}" "/${PROJECT_DATA_INSTALL_DIR}"
)

if (NOT PROJECT_LLAMACPP_MODEL_PATH)
    foreach(knownModel IN LISTS llamaKnownModels)
        if (knownModel MATCHES "^${TEMPLATE_APP_LLAMACPP_MODEL}\\|(.+/([^/]+))\\|([0-9a-f]+)$")
            set(modelUrl "${CMAKE_MATCH_1}")
            set(PROJECT_LLAMACPP_MODEL_PATH "${TEMPLATE_APP_LLAMACPP_MODELS_DIR}/${CMAKE_MATCH_2}")
            set(modelSha256 "${CMAKE_MATCH_3}")
        endif()
    endforeach()

    if (NOT PROJECT_LLAMACPP_MODEL_PATH)
        message(FATAL_ERROR "No ${TEMPLATE_APP_LLAMACPP_MODEL} llama.cpp model is known, pick the gemma-4-E4B or the gemma-4-12B one, or give any other GGUF model with the PROJECT_LLAMACPP_MODEL_PATH variable")
    endif()

    if (ENABLE_LLAMACPP_MODEL_DOWNLOAD AND NOT EXISTS "${PROJECT_LLAMACPP_MODEL_PATH}")
        message(STATUS "Downloading the ${TEMPLATE_APP_LLAMACPP_MODEL} llama.cpp model of several gigabytes, which takes a while")

        # The download goes into a separate file first, so an interrupted one
        # is never taken for the downloaded model.
        file(
            DOWNLOAD "${modelUrl}" "${PROJECT_LLAMACPP_MODEL_PATH}.part"
            SHOW_PROGRESS
            TLS_VERIFY ON
            STATUS modelStatus
        )

        list(GET modelStatus 0 modelCode)

        if (modelCode EQUAL 0)
            file(SHA256 "${PROJECT_LLAMACPP_MODEL_PATH}.part" modelHash)

            if (modelHash STREQUAL modelSha256)
                file(RENAME "${PROJECT_LLAMACPP_MODEL_PATH}.part" "${PROJECT_LLAMACPP_MODEL_PATH}")
            else()
                set(modelStatus "the ${modelHash} checksum differs from the expected ${modelSha256} one")
            endif()
        endif()

        file(REMOVE "${PROJECT_LLAMACPP_MODEL_PATH}.part")

        if (NOT EXISTS "${PROJECT_LLAMACPP_MODEL_PATH}")
            message(WARNING "Fail to download the ${TEMPLATE_APP_LLAMACPP_MODEL} llama.cpp model (${modelStatus}), so the application needs the --model parameter")
        endif()
    endif()

    # The installation takes the downloaded model, while a failed download
    # leaves none to install.
    if (ENABLE_LLAMACPP_MODEL_DOWNLOAD)
        install(FILES "${PROJECT_LLAMACPP_MODEL_PATH}" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL)
    endif()
endif()

message(STATUS "The llama.cpp model: ${PROJECT_LLAMACPP_MODEL_PATH}")

# Link the llama target, the very same one for the system installed and the
# fetched library, to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE llama)
