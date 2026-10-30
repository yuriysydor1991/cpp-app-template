cmake_minimum_required(VERSION 3.13)

set(
  DOCKER_SINGLE_BUILD_CMD
    DOCKER_BUILDKIT=1 ${DOCKER_EXEC} build 
      --build-context project=${PROJECT_SOURCE_DIR} 
      --build-arg CACHEBUST="${PROJECT_CONFIGURE_DATE}" 
      -t ${DOCKER_SINGLE_RUN_NAME} .
)

# The container draws on the host X server, whose access granted to it is
# revoked on every exit of the run, the failed and the interrupted ones included.
set(
  DOCKER_SINGLE_RUN_CMD
    sh -c "trap 'xhost -local:docker' EXIT && trap 'exit 130' INT TERM && \
      xhost +local:docker && \
      ${DOCKER_EXEC} run --rm \
      -e DISPLAY=$DISPLAY \
      -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
      --device /dev/dri \
      --group-add video \
      ${DOCKER_SINGLE_RUN_NAME}"
)

message(STATUS "docker single build command: ${DOCKER_SINGLE_BUILD_CMD}")
message(STATUS "docker single run command: ${DOCKER_SINGLE_RUN_CMD}")

add_custom_target(
  docker-single-build
  COMMAND ${DOCKER_SINGLE_BUILD_CMD}
  COMMENT "Building the docker single run instance"
)

add_custom_target(
  docker-single-run
  COMMAND ${DOCKER_SINGLE_RUN_CMD}
  DEPENDS docker-single-build
  COMMENT "Running the docker single run instance"
  VERBATIM
)
