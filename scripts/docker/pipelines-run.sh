#!/bin/bash -e
#
# Runs both the GitHub Actions and the GitLab CI/CD pipelines once locally, one
# after the other, on the committed tip of the checked out branch
# (-DLOCAL_PIPELINE_BRANCH=<branch> picks another one) - the pair a push to the
# origin remote with both its push URLs starts.
#
# The first failed pipeline stops the run. The --rebuild flag builds the local
# GitHub Actions runner image anew, with the base image of the Dockerfile
# pulled and no cache reused.

PROJECT_ROOT=$(realpath "$(dirname "$0")/../..")
BUILD_SCRIPTS_ROOT=$(realpath "${PROJECT_ROOT}/scripts/build")

FORCE_REBUILD=OFF

if [[ $* =~ --rebuild ]] ; then
    FORCE_REBUILD=ON
fi

${BUILD_SCRIPTS_ROOT}/release-configure.sh \
  -DENABLE_DOCKER=ON \
  -DENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE=ON \
  -DENABLE_GITLAB_CI_DOCKER_PIPELINE=ON \
  -DGITHUB_ACTIONS_PIPELINE_FORCE_REBUILD=${FORCE_REBUILD} \
  "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target github-actions-pipeline-docker-run "$@"

${BUILD_SCRIPTS_ROOT}/release-build.sh --target gitlab-ci-pipeline-docker-run "$@"
