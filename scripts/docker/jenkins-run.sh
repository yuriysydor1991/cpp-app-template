#!/bin/bash -e
#
# The --rebuild flag erases the image and the container and builds the image
# anew, with the base image of the Dockerfile pulled and no cache reused.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "${PROJECT_ROOT}/scripts/build")

FORCE_REBUILD=OFF

if [[ $* =~ --rebuild ]] ; then
    FORCE_REBUILD=ON
fi

${BUILD_SCRIPTS_ROOT}/release-configure.sh \
  -DENABLE_DOCKER=ON \
  -DENABLE_JENKINS_DOCKER_PIPELINE=ON \
  -DJENKINS_PIPELINE_FORCE_REBUILD=${FORCE_REBUILD} \
  "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target jenkins-pipeline-docker-run "$@"
