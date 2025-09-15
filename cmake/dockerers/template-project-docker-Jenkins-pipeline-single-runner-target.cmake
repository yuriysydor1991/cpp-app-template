cmake_minimum_required(VERSION 3.13)

if (NOT ENABLE_JENKINS_DOCKER_PIPELINE)
  return()
endif()

set(
  JENKINS_PIPELINE_DOCKERFILE_SRC 
  "${CMAKE_SOURCE_DIR}/misc/Dockerfile.Jenkins.pipeline.in" 
  CACHE STRING 
  "The Jenkins pipeline Dockerfile full path"
)

set(
  JENKINS_PIPELINE_DOCKERFILE_DST
  "Dockerfile.Jenkins.pipeline"
  CACHE STRING 
  "The Jenkins pipeline Dockerfile destination name"
)

configure_file(${JENKINS_PIPELINE_DOCKERFILE_SRC} ${JENKINS_PIPELINE_DOCKERFILE_DST})

set(
  JENKINS_PIPELINE_DOCKER_SINGLE_RUN_NAME
  "${PROJECT_BINARY_NAME_lower}-jenkins-pipeline-run"
)

set(
  JENKINS_PIPELINE_DOCKER_SINGLE_CONTAINER_NAME
  "${PROJECT_BINARY_NAME_lower}-jenkins-pipeline-run-container"
)

# --no-cache
set(
  JENKINS_PIPELINE_DOCKER_SINGLE_BUILD_CMD
    DOCKER_HOST=${DOCKER_HOST_STR} DOCKER_BUILDKIT=1 ${DOCKER_EXEC} build
      -f "${JENKINS_PIPELINE_DOCKERFILE_DST}"
      --build-context project=${CMAKE_SOURCE_DIR} 
      --build-arg CACHEBUST="${PROJECT_CONFIGURE_DATE}" 
      -t ${JENKINS_PIPELINE_DOCKER_SINGLE_RUN_NAME} .
)

#--restart=on-failure -d
set(
  JENKINS_PIPELINE_DOCKER_SINGLE_RUN_CMD
    DOCKER_HOST=${DOCKER_HOST_STR} ${DOCKER_EXEC} run -it
    -p 8080:8080 
    -p 50000:50000
    --name ${JENKINS_PIPELINE_DOCKER_SINGLE_CONTAINER_NAME}
    ${JENKINS_PIPELINE_DOCKER_SINGLE_RUN_NAME}
)

message(STATUS "docker single build command: ${DOCKER_SINGLE_BUILD_CMD}")
message(STATUS "docker single run command: ${DOCKER_SINGLE_RUN_CMD}")

add_custom_target(
  jenkins-pipeline-docker-single-build
  COMMAND ${JENKINS_PIPELINE_DOCKER_SINGLE_BUILD_CMD}
  COMMENT "Building the Jenkins pipeline Docker single run instance"
)

add_custom_target(
  jenkins-pipeline-docker-single-run
  COMMAND ${JENKINS_PIPELINE_DOCKER_SINGLE_RUN_CMD}
  DEPENDS jenkins-pipeline-docker-single-build
  COMMENT "Running the Jenkins pipeline inside docker single run instance"
)

