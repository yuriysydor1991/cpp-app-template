cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_OPENPOSE
    "Enables the OpenPose pose estimation of the project"
    ON
)

if (NOT ENABLE_OPENPOSE)
    return()
endif()

include(template-project-pose-models-enabler)

# The OpenPose COCO body model: the network of the OpenPose repository pinned
# to it's commit and the weights of the OpenCV models mirror, since the CMU
# server of the models is gone.
set(TEMPLATE_APP_OPENPOSE_NETWORK_URL "https://raw.githubusercontent.com/CMU-Perceptual-Computing-Lab/openpose/5c5d96523ef917bd30301245fdc8343937cae48d/models/pose/coco/pose_deploy_linevec.prototxt" CACHE STRING "The OpenPose COCO network file to download")
set(TEMPLATE_APP_OPENPOSE_NETWORK_SHA256 "17051b87f709aa094e09c5da7b78e9016a1f37b2b452ed1f190fe74cce70b1ad" CACHE STRING "The SHA256 checksum the downloaded network file is checked against")
set(TEMPLATE_APP_OPENPOSE_WEIGHTS_URL "https://dl.opencv.org/models/openpose_pose_coco.caffemodel" CACHE STRING "The OpenPose COCO weights file to download")
set(TEMPLATE_APP_OPENPOSE_WEIGHTS_SHA256 "b4cf475576abd7b15d5316f1ee65eb492b5c9f5865e70a2e7882ed31fb682549" CACHE STRING "The SHA256 checksum the downloaded weights file is checked against")

option(
    ENABLE_OPENPOSE_MODEL_DOWNLOAD
    "Downloads the OpenPose model into the TEMPLATE_APP_POSE_MODELS_DIR directory while configuring"
    ON
)

set(PROJECT_POSE_MODEL "" CACHE STRING "The directory of the OpenPose COCO network and weights files the application loads while no --model parameter is given, the downloaded one if empty")

# The OpenPose license allows the noncommercial research use alone and no
# redistribution, so the model is never installed or packaged: the installed
# binary loads the one of the build tree or of the --model parameter.
if (NOT PROJECT_POSE_MODEL)
    set(PROJECT_POSE_MODEL "${TEMPLATE_APP_POSE_MODELS_DIR}/openpose-coco")

    if (ENABLE_OPENPOSE_MODEL_DOWNLOAD)
        template_project_download_model(
            "${PROJECT_POSE_MODEL}/pose_deploy_linevec.prototxt"
            "${TEMPLATE_APP_OPENPOSE_NETWORK_URL}"
            "${TEMPLATE_APP_OPENPOSE_NETWORK_SHA256}"
        )
        template_project_download_model(
            "${PROJECT_POSE_MODEL}/pose_iter_440000.caffemodel"
            "${TEMPLATE_APP_OPENPOSE_WEIGHTS_URL}"
            "${TEMPLATE_APP_OPENPOSE_WEIGHTS_SHA256}"
        )
    endif()
endif()

message(STATUS "The OpenPose model: ${PROJECT_POSE_MODEL}")
