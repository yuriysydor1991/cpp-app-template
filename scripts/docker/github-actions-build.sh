#!/bin/bash -e
#
# Builds the local GitHub Actions runner image alone, with no pipeline run.
#
# The --rebuild flag builds the image anew, with the base image of the
# Dockerfile pulled and no cache reused.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "${PROJECT_ROOT}/scripts/build")

FORCE_REBUILD=OFF

if [[ $* =~ --rebuild ]] ; then
    FORCE_REBUILD=ON
fi

${BUILD_SCRIPTS_ROOT}/release-configure.sh \
  -DENABLE_DOCKER=ON \
  -DENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE=ON \
  -DGITHUB_ACTIONS_PIPELINE_FORCE_REBUILD=${FORCE_REBUILD} \
  "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target github-actions-pipeline-docker-build "$@"
