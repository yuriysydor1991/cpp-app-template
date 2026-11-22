cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_MOVENET
    "Enables the MoveNet pose estimation of the project"
    ON
)

if (NOT ENABLE_MOVENET)
    return()
endif()

include(template-project-pose-models-enabler)

# The tf2onnx conversion of the MoveNet MultiPose Lightning model of the
# Google, pinned to it's commit, since the Google publishes the TFLite, the
# SavedModel and the TF.js models only.
set(TEMPLATE_APP_MOVENET_MODEL_URL "https://huggingface.co/Xenova/movenet-multipose-lightning/resolve/8506174df310cf154b97352afa98d1ea4b1e4b47/onnx/model.onnx" CACHE STRING "The MoveNet MultiPose ONNX model to download")
set(TEMPLATE_APP_MOVENET_MODEL_SHA256 "60f724a56f0119d22d2afcf530019db307c77d4ea598eb5bd53bb65afe93930d" CACHE STRING "The SHA256 checksum the downloaded model is checked against")

option(
    ENABLE_MOVENET_MODEL_DOWNLOAD
    "Downloads the TEMPLATE_APP_MOVENET_MODEL_URL model into the TEMPLATE_APP_POSE_MODELS_DIR directory while configuring and installs it with the binary"
    ON
)

set(PROJECT_POSE_MODEL "" CACHE STRING "The MoveNet MultiPose ONNX model the application loads while no --model parameter is given, the downloaded one if empty")

if (NOT PROJECT_POSE_MODEL)
    set(PROJECT_POSE_MODEL "${TEMPLATE_APP_POSE_MODELS_DIR}/movenet-multipose-lightning.onnx")

    if (ENABLE_MOVENET_MODEL_DOWNLOAD)
        template_project_download_model(
            "${PROJECT_POSE_MODEL}"
            "${TEMPLATE_APP_MOVENET_MODEL_URL}"
            "${TEMPLATE_APP_MOVENET_MODEL_SHA256}"
        )

        # A failed download leaves no model to install.
        install(FILES "${PROJECT_POSE_MODEL}" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL)
    endif()
endif()

message(STATUS "The MoveNet model: ${PROJECT_POSE_MODEL}")
