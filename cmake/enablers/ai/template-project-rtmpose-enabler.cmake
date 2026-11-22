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

# The RTMW3D-x model of the 133 COCO-WholeBody keypoints in 3D: the ONNX
# export of the community the rtmlib downloads, pinned to it's commit, since
# the OpenMMLab publishes the PyTorch checkpoints of it alone, and the
# YOLOX-tiny person detector ONNX export of the OpenMMLab.
set(TEMPLATE_APP_RTMPOSE_MODEL_URL "https://huggingface.co/Soykaf/RTMW3D-x/resolve/a4f0d54c52ee44ee4e1dda1936d714490c6234d2/onnx/rtmw3d-x_8xb64_cocktail14-384x288-b0a0eab7_20240626.onnx" CACHE STRING "The RTMW3D ONNX model to download")
set(TEMPLATE_APP_RTMPOSE_MODEL_SHA256 "4a289c0e99d47eb595e99679d9d4a2d1def1b4241f9adcbafba44b9ff585ebcd" CACHE STRING "The SHA256 checksum the downloaded model is checked against")
set(TEMPLATE_APP_RTMPOSE_DETECTOR_URL "https://download.openmmlab.com/mmpose/v1/projects/rtmposev1/onnx_sdk/yolox_tiny_8xb8-300e_humanart-6f3252f9.zip" CACHE STRING "The YOLOX person detector ONNX model archive to download")
set(TEMPLATE_APP_RTMPOSE_DETECTOR_SHA256 "36e09ca555916253fa1b5d51bec01e48e98e1f0af966c51ce3e844d8c8fc4cfc" CACHE STRING "The SHA256 checksum the downloaded detector archive is checked against")

option(
    ENABLE_RTMPOSE_MODEL_DOWNLOAD
    "Downloads the RTMW3D and the detector models into the TEMPLATE_APP_POSE_MODELS_DIR directory while configuring and installs them with the binary"
    ON
)

set(PROJECT_POSE_MODEL "" CACHE STRING "The directory of the detector.onnx and the pose.onnx models the application loads while no --model parameter is given, the downloaded one if empty")

if (NOT PROJECT_POSE_MODEL)
    set(PROJECT_POSE_MODEL "${TEMPLATE_APP_POSE_MODELS_DIR}/rtmw3d-x")

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
        )

        # A failed download leaves no models to install.
        install(DIRECTORY "${PROJECT_POSE_MODEL}" DESTINATION "${PROJECT_DATA_INSTALL_DIR}" OPTIONAL)
    endif()
endif()

message(STATUS "The RTMW3D models: ${PROJECT_POSE_MODEL}")
