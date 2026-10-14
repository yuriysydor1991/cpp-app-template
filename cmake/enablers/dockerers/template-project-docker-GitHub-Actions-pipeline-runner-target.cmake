cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE
  "Set to ON to enable the single local run of the GitHub Actions pipeline inside the Docker containers (with the act tool)"
  OFF
)

option(
  GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD
  "Set to ON to force rebuild the local GitHub Actions runner image"
  OFF
)

set(
  GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL
  ""
  CACHE STRING
  "The runs-on label of the workflow jobs the local runner image stands in for (e.g. ubuntu-26.04), the one the workflows name when empty"
)

set(
  GITHUB_ACTIONS_PIPELINE_DOCKER_IMAGE_NAME
  "${PROJECT_BINARY_NAME_lower}-github-actions-pipeline-image"
  CACHE STRING
  "The local GitHub Actions runner image name, tagged with the runner label"
)

set(
  GITHUB_ACTIONS_PIPELINE_DOCKERFILE_SRC
  "${CMAKE_SOURCE_DIR}/misc/Dockerfiles/Dockerfile.GitHub.Actions.pipeline.in"
  CACHE STRING
  "The local GitHub Actions runner Dockerfile full path"
)

set(
  GITHUB_ACTIONS_PIPELINE_DOCKERFILE_DST
  "Dockerfile.GitHub.Actions.pipeline"
  CACHE STRING
  "The local GitHub Actions runner Dockerfile destination name"
)

set(
  GITHUB_ACTIONS_PIPELINE_NODE_MAJOR
  "24"
  CACHE STRING
  "The Node.js major release the local runner image runs the JavaScript actions with"
)

set(
  GITHUB_ACTIONS_PIPELINE_JOB
  ""
  CACHE STRING
  "The single workflow job ID the local run is limited to (e.g. code-format), every job when empty"
)

if (NOT ENABLE_GITHUB_ACTIONS_DOCKER_PIPELINE)
  return()
endif()

find_program(ACT_EXEC act)

if (NOT ACT_EXEC)
  message(FATAL_ERROR "No act executable found! Install the https://github.com/nektos/act tool to run the GitHub Actions pipeline locally, e.g. with the scripts/packages/install-debian.sh --local-pipelines command.")
endif()

include(template-project-docker-local-pipeline-variables-declare)

# act maps every runs-on label to an image of its own, while a job of a label
# with no image is skipped with a mere notice - a green run of nothing. So the
# label is taken from the workflows of the branch itself unless given.
if (GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL STREQUAL "")
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" grep -h -E "^[[:space:]]*runs-on:" "${LOCAL_PIPELINE_BRANCH_NAME}" -- .github/workflows
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE GITHUB_ACTIONS_PIPELINE_RUNS_ON_LINES
  )

  string(
    REGEX MATCHALL "runs-on:[ \t]*['\"]?[A-Za-z0-9._-]+"
    GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS
    "${GITHUB_ACTIONS_PIPELINE_RUNS_ON_LINES}"
  )
  list(TRANSFORM GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS REPLACE "^runs-on:[ \t]*['\"]?" "")
  list(REMOVE_DUPLICATES GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS)
  list(LENGTH GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS_COUNT)

  if (NOT GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS_COUNT EQUAL 1)
    message(FATAL_ERROR "The workflows of the '${LOCAL_PIPELINE_BRANCH_NAME}' branch name the runner labels '${GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS}' instead of a single one! Pick the one to run with the GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL variable!")
  endif()

  set(GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL_NAME "${GITHUB_ACTIONS_PIPELINE_RUNNER_LABELS}")
else()
  set(GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL_NAME "${GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL}")
endif()

# The hosted ubuntu-XX.YY runner is stood in for by the ubuntu:XX.YY image of
# the very same release, the one the GitLab CI/CD pipeline runs inside as well.
if (NOT GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL_NAME MATCHES "^ubuntu-(.+)$")
  message(FATAL_ERROR "No local image for the '${GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL_NAME}' runner - act runs the Linux jobs inside the Docker containers alone!")
endif()

set(GITHUB_ACTIONS_PIPELINE_BASE_IMAGE "ubuntu:${CMAKE_MATCH_1}")
set(GITHUB_ACTIONS_PIPELINE_DOCKER_IMAGE "${GITHUB_ACTIONS_PIPELINE_DOCKER_IMAGE_NAME}:${GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL_NAME}")

configure_file(${GITHUB_ACTIONS_PIPELINE_DOCKERFILE_SRC} ${GITHUB_ACTIONS_PIPELINE_DOCKERFILE_DST})

# The image takes nothing of the project, so the build gets an empty directory
# instead of the whole binary tree to upload.
set(GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_CONTEXT ${CMAKE_CURRENT_BINARY_DIR}/github-actions-pipeline-context)

file(MAKE_DIRECTORY ${GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_CONTEXT})

# The image is small and every layer of it is cached, so it is built on every
# run instead of probed for - a changed Dockerfile is picked up with no flag.
if (GITHUB_ACTIONS_PIPELINE_FORCE_REBUILD)
  set(GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_FLAGS --no-cache --pull)
endif()

set(
  GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_CMD
    ${CMAKE_COMMAND} -E env DOCKER_BUILDKIT=1
    ${DOCKER_EXEC} build ${GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_FLAGS}
      -f "${CMAKE_CURRENT_BINARY_DIR}/${GITHUB_ACTIONS_PIPELINE_DOCKERFILE_DST}"
      -t ${GITHUB_ACTIONS_PIPELINE_DOCKER_IMAGE}
      ${GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_CONTEXT}
)

set(GITHUB_ACTIONS_PIPELINE_WORKSPACE ${CMAKE_CURRENT_BINARY_DIR}/github-actions-pipeline-workspace)
set(GITHUB_ACTIONS_PIPELINE_ARTIFACTS ${CMAKE_CURRENT_BINARY_DIR}/github-actions-pipeline-artifacts)

# The workflow_dispatch event is the "Run workflow" button of the Actions page,
# the single one which takes the parameters. The image is a local one, so act
# must not try to pull it, and the containers of a failed job are erased too,
# since the next run starts from a clean workspace anyway.
set(
  GITHUB_ACTIONS_PIPELINE_ACT_RUN_CMD
    ${ACT_EXEC} workflow_dispatch
      --directory "${GITHUB_ACTIONS_PIPELINE_WORKSPACE}"
      --workflows "${GITHUB_ACTIONS_PIPELINE_WORKSPACE}/.github/workflows/"
      --platform "${GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL_NAME}=${GITHUB_ACTIONS_PIPELINE_DOCKER_IMAGE}"
      --pull=false
      --rm
      --artifact-server-path "${GITHUB_ACTIONS_PIPELINE_ARTIFACTS}"
      --input run_cppcheck=${LOCAL_PIPELINE_RUN_CPPCHECK_VALUE}
)

if (NOT LOCAL_PIPELINE_MAX_PARALLEL_JOBS STREQUAL "")
  list(APPEND GITHUB_ACTIONS_PIPELINE_ACT_RUN_CMD --concurrent-jobs ${LOCAL_PIPELINE_MAX_PARALLEL_JOBS})
endif()

if (NOT GITHUB_ACTIONS_PIPELINE_JOB STREQUAL "")
  list(APPEND GITHUB_ACTIONS_PIPELINE_ACT_RUN_CMD --job ${GITHUB_ACTIONS_PIPELINE_JOB})
endif()

message(STATUS "GitHub Actions pipeline runner label: ${GITHUB_ACTIONS_PIPELINE_RUNNER_LABEL_NAME}")
message(STATUS "GitHub Actions pipeline docker build command: ${GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_CMD}")
message(STATUS "GitHub Actions pipeline act run command: ${GITHUB_ACTIONS_PIPELINE_ACT_RUN_CMD}")
message(STATUS "GitHub Actions pipeline artifacts (the JUnit reports): ${GITHUB_ACTIONS_PIPELINE_ARTIFACTS}")

add_custom_target(
  github-actions-pipeline-docker-build
  COMMAND ${GITHUB_ACTIONS_PIPELINE_DOCKER_BUILD_CMD}
  COMMENT "Building the local GitHub Actions runner image ${GITHUB_ACTIONS_PIPELINE_DOCKER_IMAGE}"
  VERBATIM
)

add_custom_target(
  github-actions-pipeline-docker-run
  COMMAND ${CMAKE_COMMAND}
    -DGIT_EXECUTABLE=${GIT_EXECUTABLE}
    -DLOCAL_PIPELINE_SOURCE_DIR=${CMAKE_SOURCE_DIR}
    -DLOCAL_PIPELINE_BRANCH=${LOCAL_PIPELINE_BRANCH_NAME}
    -DLOCAL_PIPELINE_WORKSPACE=${GITHUB_ACTIONS_PIPELINE_WORKSPACE}
    -P ${LOCAL_PIPELINE_WORKSPACE_SCRIPT}
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${GITHUB_ACTIONS_PIPELINE_ARTIFACTS}
  COMMAND ${GITHUB_ACTIONS_PIPELINE_ACT_RUN_CMD}
  DEPENDS github-actions-pipeline-docker-build
  COMMENT "Running the GitHub Actions pipeline of the '${LOCAL_PIPELINE_BRANCH_NAME}' branch locally"
  USES_TERMINAL
  VERBATIM
)
