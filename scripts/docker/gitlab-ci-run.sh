#!/bin/bash -e
#
# Runs the .gitlab-ci.yml pipeline once locally with the gitlab-ci-local tool,
# on the committed tip of the checked out branch (-DLOCAL_PIPELINE_BRANCH=
# <branch> picks another one), so a broken pipeline shows up before the push
# does.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "${PROJECT_ROOT}/scripts/build")

${BUILD_SCRIPTS_ROOT}/release-configure.sh \
  -DENABLE_DOCKER=ON \
  -DENABLE_GITLAB_CI_DOCKER_PIPELINE=ON \
  "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target gitlab-ci-pipeline-docker-run "$@"
