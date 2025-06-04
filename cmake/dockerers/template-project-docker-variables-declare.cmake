cmake_minimum_required(VERSION 3.13)

string(TOLOWER ${PROJECT_BINARY_NAME} PROJECT_BINARY_NAME_lower)

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
  DOCKER_SINGLE_RUN_NAME
  "${PROJECT_BINARY_NAME_lower}-docker-single-run"
)

set(
  DOCKERFILE_SRC 
  "${CMAKE_SOURCE_DIR}/misc/Dockerfile.in" 
  CACHE STRING 
  "The Dockerfile full path"
)

set(
  DOCKERFILE_DST
  "Dockerfile"
  CACHE STRING 
  "The Dockerfile destination name"
)

message(STATUS "Docker executable: ${DOCKER_EXEC}")
message(STATUS "Dockerfile configure source full path: ${DOCKERFILE_SRC}")
message(STATUS "Dockerfile destination name: ${DOCKERFILE_DST}")
message(STATUS "Docker single run instance name: ${DOCKER_SINGLE_RUN_NAME}")
message(STATUS "Docker host address and port: ${DOCKER_HOST_STR}")
message(STATUS "Project current branch name: ${PROJECT_CURRENT_BRANCH_NAME}")
