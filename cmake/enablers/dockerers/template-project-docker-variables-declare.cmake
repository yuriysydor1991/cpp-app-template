cmake_minimum_required(VERSION 3.13)

string(TOLOWER ${PROJECT_LIBRARY_NAME} PROJECT_LIBRARY_NAME_lower)

set(
  DOCKER_HOST_ADDRESS
  "127.0.0.1"
  CACHE STRING "The docker service machine address"
)

set(
  DOCKER_HOST_PORT
  "2375"
  CACHE STRING "The docker service machine port"
)

set(
  DOCKER_HOST_STR
  "tcp://${DOCKER_HOST_ADDRESS}:${DOCKER_HOST_PORT}"
  CACHE STRING "The docker service machine full address"
)

set(
  DOCKERFILE_SINGLE_RUN_BASE_IMAGE_NAME
  "jenkins/jenkins"
  CACHE STRING 
  "The Dockerfile source environment name (FROM ubuntu, debian, jenkins etc.)"
)

set(
  DOCKERFILE_SINGLE_RUN_BASE_IMAGE_VERSION
  "lts"
  CACHE STRING 
  "The Dockerfile source environment version"
)

set(
  DOCKERFILE_SINGLE_RUN_BASE_IMAGE_STRING
  "${DOCKERFILE_SINGLE_RUN_BASE_IMAGE_NAME}:${DOCKERFILE_SINGLE_RUN_BASE_IMAGE_VERSION}"
  CACHE STRING 
  "The Dockerfile source environment full string (e.g. ubuntu:22.04)"
)

set(
  PROJECT_BINARY_PATH
  ${CMAKE_BINARY_DIR}/src/${PROJECT_LIBRARY_NAME}
)

message(STATUS "Docker executable: ${DOCKER_EXEC}")
message(STATUS "Dockerfile configure source full path: ${DOCKERFILE_SRC}")
message(STATUS "Dockerfile destination name: ${DOCKERFILE_DST}")
message(STATUS "Docker host address and port: ${DOCKER_HOST_STR}")
message(STATUS "Project current branch name: ${PROJECT_CURRENT_BRANCH_NAME}")
message(STATUS "Project binary filepath: ${PROJECT_BINARY_PATH}")
message(STATUS "Docker source environment base image string: ${DOCKERFILE_SINGLE_RUN_BASE_IMAGE_STRING}")
