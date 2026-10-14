cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_GITLAB_CI_DOCKER_PIPELINE
  "Set to ON to enable the single local run of the GitLab CI/CD pipeline inside the Docker containers (with the gitlab-ci-local tool)"
  OFF
)

set(
  GITLAB_CI_PIPELINE_JOBS
  ""
  CACHE STRING
  "The space separated pipeline job names the local run is limited to (e.g. code-format), every job when empty"
)

if (NOT ENABLE_GITLAB_CI_DOCKER_PIPELINE)
  return()
endif()

find_program(GITLAB_CI_LOCAL_EXEC gitlab-ci-local)

if (NOT GITLAB_CI_LOCAL_EXEC)
  message(FATAL_ERROR "No gitlab-ci-local executable found! Install the https://github.com/firecow/gitlab-ci-local tool to run the GitLab CI/CD pipeline locally.")
endif()

# gitlab-ci-local copies the project into the job containers with the rsync of
# the host.
find_program(RSYNC_EXEC rsync)

if (NOT RSYNC_EXEC)
  message(FATAL_ERROR "No rsync executable found! The gitlab-ci-local tool demands it to copy the project into the job containers.")
endif()

include(template-project-docker-local-pipeline-variables-declare)

# The tool refuses an absolute --cwd, so the run target starts it inside the
# binary directory and points it at the workspace relative to that one.
set(GITLAB_CI_PIPELINE_WORKSPACE_NAME gitlab-ci-pipeline-workspace)
set(GITLAB_CI_PIPELINE_WORKSPACE ${CMAKE_CURRENT_BINARY_DIR}/${GITLAB_CI_PIPELINE_WORKSPACE_NAME})

separate_arguments(GITLAB_CI_PIPELINE_JOBS_LIST UNIX_COMMAND "${GITLAB_CI_PIPELINE_JOBS}")

# The job names go first: the array options of the tool take every word which
# follows them as one more of their values. The image of the jobs comes from
# the .gitlab-ci.yml itself, so no image of its own is built here.
set(
  GITLAB_CI_PIPELINE_RUN_CMD
    ${GITLAB_CI_LOCAL_EXEC} ${GITLAB_CI_PIPELINE_JOBS_LIST}
      --cwd "${GITLAB_CI_PIPELINE_WORKSPACE_NAME}"
      --container-executable "${DOCKER_EXEC}"
      --variable RUN_CPPCHECK=${LOCAL_PIPELINE_RUN_CPPCHECK_VALUE}
)

if (NOT LOCAL_PIPELINE_MAX_PARALLEL_JOBS STREQUAL "")
  list(APPEND GITLAB_CI_PIPELINE_RUN_CMD --concurrency ${LOCAL_PIPELINE_MAX_PARALLEL_JOBS})
endif()

message(STATUS "GitLab CI/CD pipeline gitlab-ci-local run command: ${GITLAB_CI_PIPELINE_RUN_CMD}")

add_custom_target(
  gitlab-ci-pipeline-docker-run
  COMMAND ${CMAKE_COMMAND}
    -DGIT_EXECUTABLE=${GIT_EXECUTABLE}
    -DLOCAL_PIPELINE_SOURCE_DIR=${CMAKE_SOURCE_DIR}
    -DLOCAL_PIPELINE_BRANCH=${LOCAL_PIPELINE_BRANCH_NAME}
    -DLOCAL_PIPELINE_WORKSPACE=${GITLAB_CI_PIPELINE_WORKSPACE}
    -P ${LOCAL_PIPELINE_WORKSPACE_SCRIPT}
  COMMAND ${GITLAB_CI_PIPELINE_RUN_CMD}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Running the GitLab CI/CD pipeline of the '${LOCAL_PIPELINE_BRANCH_NAME}' branch locally"
  USES_TERMINAL
  VERBATIM
)
