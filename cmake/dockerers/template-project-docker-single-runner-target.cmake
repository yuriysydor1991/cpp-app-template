cmake_minimum_required(VERSION 3.13)

set(
  DOCKER_SINGLE_BUILD_CMD
    DOCKER_HOST=${DOCKER_HOST_STR} DOCKER_BUILDKIT=1 ${DOCKER_EXEC} build 
      --build-context project=${CMAKE_SOURCE_DIR} 
      --build-arg CACHEBUST="${PROJECT_CONFIGURE_DATE}" 
      -t ${DOCKER_SINGLE_RUN_NAME} .
)

set(
  DOCKER_SINGLE_RUN_CMD
    xhost +local:docker &&
    DOCKER_HOST=${DOCKER_HOST_STR} ${DOCKER_EXEC} run --rm -it
    --env DISPLAY=$$DISPLAY
    --env QT_X11_NO_MITSHM=1
    --env XDG_RUNTIME_DIR=$$XDG_RUNTIME_DIR
    --env XAUTHORITY=$$XAUTHORITY
    --volume /tmp/.X11-unix:/tmp/.X11-unix
    --volume $$XAUTHORITY:$$XAUTHORITY
    --volume $$XDG_RUNTIME_DIR:$$XDG_RUNTIME_DIR
    --device /dev/dri
    --group-add video
    --network host
    ${DOCKER_SINGLE_RUN_NAME} &&
    xhost -local:docker
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
)
