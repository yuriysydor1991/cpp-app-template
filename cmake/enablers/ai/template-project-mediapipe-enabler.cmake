cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_MEDIAPIPE
    "Enables the MediaPipe Pose estimation of the project"
    ON
)

if (NOT ENABLE_MEDIAPIPE)
    return()
endif()

include(template-project-pose-models-enabler)

# The MediaPipe builds with the Bazel alone, while it's official PyPI wheel
# ships the prebuilt MediaPipe Tasks C API library the Python Tasks API loads,
# so the configure takes that library out of the GNU/Linux x86-64 wheel and
# the C API headers out of the sources of the same v1.2.3 release.
set(TEMPLATE_APP_MEDIAPIPE_WHEEL_URL "https://files.pythonhosted.org/packages/31/2a/5217e7c5d9984f71fedcc6b33862f6141178ac598d06b0d4b81ea647b9fc/mediapipe-1.2.3-py3-none-manylinux_2_28_x86_64.whl" CACHE STRING "The MediaPipe PyPI wheel the C API library is taken out of")
set(TEMPLATE_APP_MEDIAPIPE_WHEEL_SHA256 "1fcda646cc7b96f73453acc416ce31d0fba287d0f1fc095865272a7ea6986497" CACHE STRING "The SHA256 checksum the downloaded wheel is checked against")
set(TEMPLATE_APP_MEDIAPIPE_SOURCES_URL "https://raw.githubusercontent.com/google-ai-edge/mediapipe/1b9800ed7baddd397b888eaaaf0c841fe0358241" CACHE STRING "The MediaPipe sources of the wheel release the C API headers are downloaded from")

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Linux" OR NOT CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    message(FATAL_ERROR "The MediaPipe C API library of the TEMPLATE_APP_MEDIAPIPE_WHEEL_URL wheel runs on the GNU/Linux x86-64 alone")
endif()

include(FetchContent)

# The extracted files get the time of the extraction, so a changed archive
# rebuilds them.
if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# The wheel is a zip archive, which the FetchContent unpacks under the zip
# name alone.
FetchContent_Declare(
    mediapipe_wheel
    URL ${TEMPLATE_APP_MEDIAPIPE_WHEEL_URL}
    URL_HASH SHA256=${TEMPLATE_APP_MEDIAPIPE_WHEEL_SHA256}
    DOWNLOAD_NAME mediapipe.zip
)

FetchContent_MakeAvailable(mediapipe_wheel)

set(mediapipeInclude "${PROJECT_BINARY_DIR}/mediapipe/include")

foreach(
    header IN ITEMS
    components/containers/landmark.h components/containers/rect.h
    core/base_options.h core/common.h core/mp_status.h
    vision/core/image.h vision/core/image_processing_options.h
    vision/pose_landmarker/pose_landmarker.h
    vision/pose_landmarker/pose_landmarker_result.h
)
    set(headerFile "${mediapipeInclude}/mediapipe/tasks/c/${header}")

    if (NOT EXISTS "${headerFile}")
        file(DOWNLOAD "${TEMPLATE_APP_MEDIAPIPE_SOURCES_URL}/mediapipe/tasks/c/${header}" "${headerFile}" TLS_VERIFY ON STATUS headerStatus)

        list(GET headerStatus 0 headerCode)

        if (NOT headerCode EQUAL 0)
            file(REMOVE "${headerFile}")
            message(FATAL_ERROR "Fail to download the ${header} MediaPipe C API header: ${headerStatus}")
        endif()
    endif()
endforeach()

add_library(MediaPipe::mediapipe SHARED IMPORTED GLOBAL)

set_target_properties(
    MediaPipe::mediapipe PROPERTIES
    IMPORTED_LOCATION "${mediapipe_wheel_SOURCE_DIR}/mediapipe/tasks/c/libmediapipe.so"
    INTERFACE_INCLUDE_DIRECTORIES "${mediapipeInclude}"
)

# The Google pose landmarker models: the lite, the full and the heavy one.
set(TEMPLATE_APP_MEDIAPIPE_MODEL_URL "https://storage.googleapis.com/mediapipe-models/pose_landmarker/pose_landmarker_full/float16/1/pose_landmarker_full.task" CACHE STRING "The MediaPipe pose landmarker model to download")
set(TEMPLATE_APP_MEDIAPIPE_MODEL_SHA256 "5134a3aad27a58b93da0088d431f366da362b44e3ccfbe3462b3827a839011b1" CACHE STRING "The SHA256 checksum the downloaded model is checked against")

option(
    ENABLE_MEDIAPIPE_MODEL_DOWNLOAD
    "Downloads the TEMPLATE_APP_MEDIAPIPE_MODEL_URL model into the TEMPLATE_APP_POSE_MODELS_DIR directory while configuring and installs it with the binary"
    ON
)

set(PROJECT_POSE_MODEL "" CACHE STRING "The MediaPipe pose landmarker .task model the application loads while no --model parameter is given, the downloaded one if empty")

if (NOT PROJECT_POSE_MODEL)
    set(PROJECT_POSE_MODEL "${TEMPLATE_APP_POSE_MODELS_DIR}/pose_landmarker_full.task")

    if (ENABLE_MEDIAPIPE_MODEL_DOWNLOAD)
        template_project_download_model(
            "${PROJECT_POSE_MODEL}"
            "${TEMPLATE_APP_MEDIAPIPE_MODEL_URL}"
            "${TEMPLATE_APP_MEDIAPIPE_MODEL_SHA256}"
        )

        # A failed download leaves no model to install.
        install(FILES "${PROJECT_POSE_MODEL}" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL)
    endif()
endif()

message(STATUS "The MediaPipe model: ${PROJECT_POSE_MODEL}")
