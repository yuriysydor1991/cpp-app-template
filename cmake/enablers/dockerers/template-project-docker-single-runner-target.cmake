cmake_minimum_required(VERSION 3.13)

set(
  DOCKER_SINGLE_BUILD_CMD
    DOCKER_BUILDKIT=1 ${DOCKER_EXEC} build 
      --build-context project=${CMAKE_SOURCE_DIR} 
      --build-arg CACHEBUST="${PROJECT_CONFIGURE_DATE}" 
      -t ${DOCKER_SINGLE_RUN_NAME} .
)

# the console application reads the host system bus alone, so the bus socket is
# all the container needs (no X server access)
set(
  DOCKER_SINGLE_RUN_CMD
    ${DOCKER_EXEC} run --rm
    --volume /run/dbus/system_bus_socket:/run/dbus/system_bus_socket
    ${DOCKER_SINGLE_RUN_NAME}
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
