cmake_minimum_required(VERSION 3.13)

set(
  DOCKER_SINGLERUN_CMD
    DOCKER_HOST=${DOCKER_HOST_STR} DOCKER_BUILDKIT=1 ${DOCKER_EXEC} build 
      --build-context project=${CMAKE_SOURCE_DIR} 
      --build-arg CACHEBUST="${PROJECT_CONFIGURE_DATE}" 
      -t ${DOCKER_SINGLE_RUN_NAME} . &&
    DOCKER_HOST=${DOCKER_HOST_STR} ${DOCKER_EXEC} run --rm ${DOCKER_SINGLE_RUN_NAME}
)

message(STATUS "docker single run command: ${DOCKER_SINGLERUN_CMD}")

add_custom_target(
  docker-single-run
  COMMAND ${DOCKER_SINGLERUN_CMD}
  COMMENT "Building and running the docker single run instance"
)
