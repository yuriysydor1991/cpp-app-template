#!/bin/bash -e
#
# Runs the .github/workflows pipeline once locally with the act tool, on the
# committed tip of the checked out branch (-DLOCAL_PIPELINE_BRANCH=<branch>
# picks another one), so a broken pipeline shows up before the push does.
#
# The --rebuild flag builds the runner image anew, with the base image of the
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

${BUILD_SCRIPTS_ROOT}/release-build.sh --target github-actions-pipeline-docker-run "$@"
