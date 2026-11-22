cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_RTMPOSE
    "Enables the RTMPose family pose estimation of the project"
    ON
)

if (NOT ENABLE_RTMPOSE)
    return()
endif()

include(template-project-pose-models-enabler)

# The ONNX exports of the OpenMMLab: the RTMW-m model of the 133 COCO-WholeBody
# keypoints (the body, the feet, the face and the hands) and the YOLOX-tiny
# person detector the rtmlib pairs it with.
set(TEMPLATE_APP_RTMPOSE_MODEL_URL "https://download.openmmlab.com/mmpose/v1/projects/rtmw/onnx_sdk/rtmw-dw-l-m_simcc-cocktail14_270e-256x192_20231122.zip" CACHE STRING "The RTMW ONNX model archive to download")
set(TEMPLATE_APP_RTMPOSE_MODEL_SHA256 "a6d08a575c9d8b8da7ce6c13e1c7341047fca35594a6d35de04b739eba51139c" CACHE STRING "The SHA256 checksum the downloaded model archive is checked against")
set(TEMPLATE_APP_RTMPOSE_DETECTOR_URL "https://download.openmmlab.com/mmpose/v1/projects/rtmposev1/onnx_sdk/yolox_tiny_8xb8-300e_humanart-6f3252f9.zip" CACHE STRING "The YOLOX person detector ONNX model archive to download")
set(TEMPLATE_APP_RTMPOSE_DETECTOR_SHA256 "36e09ca555916253fa1b5d51bec01e48e98e1f0af966c51ce3e844d8c8fc4cfc" CACHE STRING "The SHA256 checksum the downloaded detector archive is checked against")

option(
    ENABLE_RTMPOSE_MODEL_DOWNLOAD
    "Downloads the RTMW and the detector models into the TEMPLATE_APP_POSE_MODELS_DIR directory while configuring and installs them with the binary"
    ON
)

set(PROJECT_POSE_MODEL "" CACHE STRING "The directory of the detector.onnx and the pose.onnx models the application loads while no --model parameter is given, the downloaded one if empty")

if (NOT PROJECT_POSE_MODEL)
    set(PROJECT_POSE_MODEL "${TEMPLATE_APP_POSE_MODELS_DIR}/rtmw-m")

    if (ENABLE_RTMPOSE_MODEL_DOWNLOAD)
        template_project_download_model(
            "${PROJECT_POSE_MODEL}/detector.onnx"
            "${TEMPLATE_APP_RTMPOSE_DETECTOR_URL}"
            "${TEMPLATE_APP_RTMPOSE_DETECTOR_SHA256}"
            end2end.onnx
        )
        template_project_download_model(
            "${PROJECT_POSE_MODEL}/pose.onnx"
            "${TEMPLATE_APP_RTMPOSE_MODEL_URL}"
            "${TEMPLATE_APP_RTMPOSE_MODEL_SHA256}"
            end2end.onnx
        )

        # A failed download leaves no models to install.
        install(DIRECTORY "${PROJECT_POSE_MODEL}" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL)
    endif()
endif()

message(STATUS "The RTMW models: ${PROJECT_POSE_MODEL}")
