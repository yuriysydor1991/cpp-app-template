cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_JENKINS_DOCKER_PIPELINE
  "Set to ON to enable the Jenkins pipeline run inside the Docker container"
  OFF
)

option(
  JENKINS_PIPELINE_FORCE_REBUILD
  "Set to ON to force rebuild the default Jenkins pipeline image and container"
  OFF
)

option(
  JENKINS_PIPELINE_RENEW_CONTAINER
  "Set to ON to erase the Jenkins pipeline container alone and start a new one of the available image"
  OFF
)

set(
  JENKINS_PIPELINE_DOCKER_IMAGE_NAME
  "${PROJECT_BINARY_NAME_lower}-jenkins-pipeline-image"
  CACHE STRING 
  "The Jenkins pipeline Dockerfile image name"
)

set(
  JENKINS_PIPELINE_DOCKER_CONTAINER_NAME
  "${PROJECT_BINARY_NAME_lower}-jenkins-pipeline-run-container"
  CACHE STRING 
  "The Jenkins pipeline Dockerfile container name"
)

set(
  JENKINS_PIPELINES_PANEL_HTTP_PORT
  "8080"
  CACHE STRING
  "The Jenkins UI port on the docker container"
)

set(
  JENKINS_PIPELINE_DOCKERFILE_SRC 
  "${CMAKE_SOURCE_DIR}/misc/Dockerfiles/Dockerfile.Jenkins.pipeline.in" 
  CACHE STRING 
  "The Jenkins pipeline Dockerfile full path"
)

set(
  JENKINS_PIPELINE_DOCKERFILE_DST
  "Dockerfile.Jenkins.pipeline"
  CACHE STRING 
  "The Jenkins pipeline Dockerfile destination name"
)

set(
  JENKINS_PIPELINE_DOCKER_MAX_CORES
  10
  CACHE STRING 
  "The Jenkins pipeline docker containers max allowed CPU cores"
)

# Every runtime, SDK and base application the flatpak manifests of the branches
# ask for. The image seeds them into the per user installation the flatpak
# target builds against, so no pipeline run downloads them again. Trim the list
# to the branches of interest to spare the image the gigabytes of the unused
# ones.
set(
  JENKINS_PIPELINE_FLATPAK_RUNTIMES
  "org.freedesktop.Platform//24.08 org.freedesktop.Sdk//24.08 org.freedesktop.Platform//25.08 org.freedesktop.Sdk//25.08 org.gnome.Platform//49 org.gnome.Sdk//49 org.kde.Platform//6.10 org.kde.Sdk//6.10 org.kde.Platform//5.15-25.08 org.kde.Sdk//5.15-25.08 io.qt.qtwebengine.BaseApp//6.10"
  CACHE STRING
  "Space separated flatpak refs the Jenkins pipeline image installs for the flatpak packager checks"
)

if (NOT ENABLE_JENKINS_DOCKER_PIPELINE)
  return()
endif()

find_program(SCRIPT_EXEC script REQUIRED)

configure_file(${JENKINS_PIPELINE_DOCKERFILE_SRC} ${JENKINS_PIPELINE_DOCKERFILE_DST})

# The image takes its sources from the project build context alone, so the
# build gets an empty directory instead of the whole binary tree to upload.
set(JENKINS_PIPELINE_DOCKER_BUILD_CONTEXT ${CMAKE_CURRENT_BINARY_DIR}/jenkins-pipeline-context)

file(MAKE_DIRECTORY ${JENKINS_PIPELINE_DOCKER_BUILD_CONTEXT})

execute_process(
  COMMAND ${SCRIPT_EXEC} -q -c "${DOCKER_EXEC} images -q ${JENKINS_PIPELINE_DOCKER_IMAGE_NAME}" /dev/null
  OUTPUT_VARIABLE JENKINS_PIPELINE_DOCKER_IMAGE_NAME_PRESENT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND ${SCRIPT_EXEC} -q -c "${DOCKER_EXEC} ps -aq -f name=${JENKINS_PIPELINE_DOCKER_CONTAINER_NAME}" /dev/null
  OUTPUT_VARIABLE JENKINS_PIPELINE_DOCKER_CONTAINER_PRESENT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (JENKINS_PIPELINE_FORCE_REBUILD OR JENKINS_PIPELINE_RENEW_CONTAINER)
  if (NOT JENKINS_PIPELINE_DOCKER_CONTAINER_PRESENT STREQUAL "")
    message(STATUS "Stopping and erasing the ${JENKINS_PIPELINE_DOCKER_CONTAINER_NAME} container")
    set(JENKINS_PIPELINE_DOCKER_CONTAINER_PRESENT "")
    execute_process(
      COMMAND ${SCRIPT_EXEC} -q -c "${DOCKER_EXEC} container stop ${JENKINS_PIPELINE_DOCKER_CONTAINER_NAME}" /dev/null
    )
    execute_process(
      COMMAND ${SCRIPT_EXEC} -q -c "${DOCKER_EXEC} container rm ${JENKINS_PIPELINE_DOCKER_CONTAINER_NAME}" /dev/null
    )
  endif()
endif()

if (JENKINS_PIPELINE_FORCE_REBUILD)
  if (NOT JENKINS_PIPELINE_DOCKER_IMAGE_NAME_PRESENT STREQUAL "")
    message(STATUS "Erasing the ${JENKINS_PIPELINE_DOCKER_IMAGE_NAME} image")
    set(JENKINS_PIPELINE_DOCKER_IMAGE_NAME_PRESENT "")
    execute_process(
      COMMAND ${SCRIPT_EXEC} -q -c "${DOCKER_EXEC} image rm -f ${JENKINS_PIPELINE_DOCKER_IMAGE_NAME}" /dev/null
    )
  endif()

  # the erased image leaves both its own layers and the pulled base image of
  # the Dockerfile behind in the builder cache, so the build reproduces the
  # very same image until the cache is refused and the base image pulled anew
  set(JENKINS_PIPELINE_DOCKER_BUILD_FLAGS --no-cache --pull)
endif()

if (JENKINS_PIPELINE_DOCKER_IMAGE_NAME_PRESENT STREQUAL "")
  set(
    JENKINS_PIPELINE_DOCKER_BUILD_CMD
      DOCKER_BUILDKIT=1 ${DOCKER_EXEC} build ${JENKINS_PIPELINE_DOCKER_BUILD_FLAGS}
        -f "${CMAKE_CURRENT_BINARY_DIR}/${JENKINS_PIPELINE_DOCKERFILE_DST}"
        --build-context project=${CMAKE_SOURCE_DIR} 
        --build-arg CACHEBUST="${PROJECT_CONFIGURE_DATE}" 
        -t ${JENKINS_PIPELINE_DOCKER_IMAGE_NAME} ${JENKINS_PIPELINE_DOCKER_BUILD_CONTEXT}
  )
else()
  set(
    JENKINS_PIPELINE_DOCKER_BUILD_CMD
      echo "Image ${JENKINS_PIPELINE_DOCKER_IMAGE_NAME} already build"
  )
endif()

# -d --restart=on-failure
#
# The flatpak-builder sandbox and the AppImage runtime of the packager stages
# demand the FUSE device with the mount permission, which the default seccomp
# and AppArmor profiles of the container deny. The bubblewrap sandbox of the
# flatpak-builder mounts a procfs of its own, which the kernel refuses while
# the masked and the read only /proc paths of the container keep the mounted
# one partly hidden, so the system paths go unconfined as well.
if (JENKINS_PIPELINE_DOCKER_CONTAINER_PRESENT STREQUAL "")
  set(
    JENKINS_PIPELINE_DOCKER_RUN_CMD
      ${DOCKER_EXEC} run -it
      --device /dev/fuse
      -p ${JENKINS_PIPELINES_PANEL_HTTP_PORT}:8080
      -p 50000:50000
      --name ${JENKINS_PIPELINE_DOCKER_CONTAINER_NAME}
      --cpus ${JENKINS_PIPELINE_DOCKER_MAX_CORES}
      --cap-add=SYS_ADMIN
      --security-opt apparmor=unconfined
      --security-opt seccomp=unconfined
      --security-opt systempaths=unconfined
      ${JENKINS_PIPELINE_DOCKER_IMAGE_NAME}
  )
else()
  set(
    JENKINS_PIPELINE_DOCKER_RUN_CMD
      ${DOCKER_EXEC} container start 
        -ia ${JENKINS_PIPELINE_DOCKER_CONTAINER_NAME}
  )
endif()

message(STATUS "Jenkins pipeline docker build command: ${JENKINS_PIPELINE_DOCKER_BUILD_CMD}")
message(STATUS "Jenkins pipeline docker run command: ${JENKINS_PIPELINE_DOCKER_RUN_CMD}")
message(STATUS "Jenkins pipeline flatpak runtimes: ${JENKINS_PIPELINE_FLATPAK_RUNTIMES}")

add_custom_target(
  jenkins-pipeline-docker-build
  COMMAND ${JENKINS_PIPELINE_DOCKER_BUILD_CMD}
  COMMENT "Building the Jenkins pipeline Docker run instance"
)

add_custom_target(
  jenkins-pipeline-docker-run
  COMMAND echo "Connect to the Jenkins GUI at started docker at http://127.0.0.1:${JENKINS_PIPELINES_PANEL_HTTP_PORT}"
  COMMAND ${JENKINS_PIPELINE_DOCKER_RUN_CMD}
  DEPENDS jenkins-pipeline-docker-build
  COMMENT "Running the Jenkins pipeline inside docker run instance"
)

include(template-project-docker-Jenkins-export-jobs-2-xml)
