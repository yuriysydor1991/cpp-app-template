cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_DOCKER
  "Set to ON to enable the dockers run"
  OFF
)

if (NOT ENABLE_DOCKER)
    return()
endif()

message(STATUS "Docker runner target enabled")

find_program(DOCKER_EXEC docker REQUIRED)

include(template-project-docker-variables-declare)
include(template-project-docker-Jenkins-pipeline-runner-target)
