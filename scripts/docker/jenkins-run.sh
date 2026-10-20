#!/bin/bash -e
#
# Builds the Jenkins pipeline Docker image and starts its container: a release
# configure with the ENABLE_DOCKER and the ENABLE_JENKINS_DOCKER_PIPELINE options
# enabled, then the `jenkins-pipeline-docker-run` target of that build, which
# depends on the `jenkins-pipeline-docker-build` one.
#
# Every extra parameter is forwarded to the meson setup step.
#
# The --rebuild flag erases the image and the container and builds the image
# anew, with the base image of the Dockerfile pulled and no cache reused.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "${PROJECT_ROOT}/scripts/build")

. "${BUILD_SCRIPTS_ROOT}/common.sh"

filter_script_args "$@"

FORCE_REBUILD=false

if [[ $* =~ --rebuild ]] ; then
    FORCE_REBUILD=true
fi

SETUP_ARGS=(--buildtype=release "-DENABLE_DOCKER=true" "-DENABLE_JENKINS_DOCKER_PIPELINE=true"
    "-DJENKINS_PIPELINE_FORCE_REBUILD=${FORCE_REBUILD}")

if [[ -d "${BUILD_DIR}" ]] ; then
    SETUP_ARGS+=(--reconfigure)
fi

meson setup "${BUILD_DIR}" "${PROJECT_ROOT}" "${SETUP_ARGS[@]}" "${BUILD_ARGS[@]}"

meson compile -C "${BUILD_DIR}" jenkins-pipeline-docker-run
