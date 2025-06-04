cmake_minimum_required(VERSION 3.13)

message(STATUS "Docker runner target enabled")

find_program(DOCKER_EXEC docker REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/dockerers")

include(template-project-docker-variables-declare)

configure_file(${DOCKERFILE_SRC} ${DOCKERFILE_DST})

include(template-project-docker-single-runner-target)
