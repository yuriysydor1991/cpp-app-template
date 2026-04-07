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
    xhost +local:root && 
    DOCKER_HOST=${DOCKER_HOST_STR} ${DOCKER_EXEC} run --rm 
    --env DISPLAY=$$DISPLAY
    --env QT_X11_NO_MITSHM=1
    --volume /tmp/.X11-unix:/tmp/.X11-unix
    --volume $$HOME/.Xauthority:/root/.Xauthority
    -v $(XDG_RUNTIME_DIR):$(XDG_RUNTIME_DIR)
    --network host
    ${DOCKER_SINGLE_RUN_NAME} &&
    xhost -local:root
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
