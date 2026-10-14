cmake_minimum_required(VERSION 3.13)

# The settings the local pipeline runners share - the GitHub Actions and the
# GitLab CI/CD ones. Each runner target includes it once it is enabled, so the
# guard keeps the checks below from running twice when both of them are.
include_guard(GLOBAL)

set(
  LOCAL_PIPELINE_BRANCH
  ""
  CACHE STRING
  "The branch whose committed tip the local pipelines check, the checked out one when empty"
)

option(
  LOCAL_PIPELINE_RUN_CPPCHECK
  "Set to ON to run the optional cppcheck stage of the local pipelines (their RUN_CPPCHECK / run_cppcheck parameter)"
  OFF
)

set(
  LOCAL_PIPELINE_MAX_PARALLEL_JOBS
  ""
  CACHE STRING
  "The maximum number of the pipeline jobs a local run starts at once, all of them when empty"
)

set(
  LOCAL_PIPELINE_WORKSPACE_SCRIPT
  "${CMAKE_SOURCE_DIR}/cmake/tools/template-project-local-pipeline-workspace.cmake"
)

if (LOCAL_PIPELINE_BRANCH STREQUAL "")
  set(LOCAL_PIPELINE_BRANCH_NAME "${PROJECT_CURRENT_BRANCH_NAME}")
else()
  set(LOCAL_PIPELINE_BRANCH_NAME "${LOCAL_PIPELINE_BRANCH}")
endif()

if (LOCAL_PIPELINE_BRANCH_NAME STREQUAL "")
  message(FATAL_ERROR "No branch is checked out (a detached HEAD?) to run the local pipelines of! Specify one with the LOCAL_PIPELINE_BRANCH variable!")
endif()

execute_process(
  COMMAND "${GIT_EXECUTABLE}" rev-parse --verify --quiet "refs/heads/${LOCAL_PIPELINE_BRANCH_NAME}"
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_QUIET
  RESULT_VARIABLE LOCAL_PIPELINE_BRANCH_RESULT
)

if (NOT LOCAL_PIPELINE_BRANCH_RESULT EQUAL 0)
  message(FATAL_ERROR "No local '${LOCAL_PIPELINE_BRANCH_NAME}' branch found to run the local pipelines of! Check the LOCAL_PIPELINE_BRANCH variable!")
endif()

# Both pipelines take the parameter as the literal word, the GitHub Actions one
# as its boolean input and the GitLab CI/CD one as its variable.
if (LOCAL_PIPELINE_RUN_CPPCHECK)
  set(LOCAL_PIPELINE_RUN_CPPCHECK_VALUE true)
else()
  set(LOCAL_PIPELINE_RUN_CPPCHECK_VALUE false)
endif()

message(STATUS "Local pipelines branch: ${LOCAL_PIPELINE_BRANCH_NAME}")
message(STATUS "Local pipelines cppcheck stage: ${LOCAL_PIPELINE_RUN_CPPCHECK_VALUE}")
