# Clones the committed tip of a branch into a pipeline workspace of its own, so
# a local pipeline run checks exactly what a push of the branch would publish:
# neither the uncommitted changes nor the untracked files nor the build trees
# of the source tree get in, and the state the runners leave behind stays out
# of the source tree.
#
# Runs in the script mode at the build time of the local pipeline targets, so
# every run takes the commits made after the configure step as well:
#
#   cmake -DGIT_EXECUTABLE=<git>
#         -DLOCAL_PIPELINE_SOURCE_DIR=<repository>
#         -DLOCAL_PIPELINE_BRANCH=<branch>
#         -DLOCAL_PIPELINE_WORKSPACE=<directory to clone into>
#         -P template-project-local-pipeline-workspace.cmake

cmake_minimum_required(VERSION 3.13)

foreach(REQUIRED_VAR GIT_EXECUTABLE LOCAL_PIPELINE_SOURCE_DIR LOCAL_PIPELINE_BRANCH LOCAL_PIPELINE_WORKSPACE)
  if ("${${REQUIRED_VAR}}" STREQUAL "")
    message(FATAL_ERROR "No ${REQUIRED_VAR} given to the local pipeline workspace script")
  endif()
endforeach()

execute_process(
  COMMAND "${GIT_EXECUTABLE}" branch --show-current
  WORKING_DIRECTORY "${LOCAL_PIPELINE_SOURCE_DIR}"
  OUTPUT_VARIABLE LOCAL_PIPELINE_CHECKED_OUT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# The changes of the checked out branch which wait for a commit are what a push
# would leave behind, so they are left out of the run as well - with a notice,
# since that is the most likely source of a "but it worked locally" surprise.
if (LOCAL_PIPELINE_CHECKED_OUT_BRANCH STREQUAL LOCAL_PIPELINE_BRANCH)
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" status --porcelain --untracked-files=no
    WORKING_DIRECTORY "${LOCAL_PIPELINE_SOURCE_DIR}"
    OUTPUT_VARIABLE LOCAL_PIPELINE_UNCOMMITTED
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  if (NOT LOCAL_PIPELINE_UNCOMMITTED STREQUAL "")
    message(WARNING
      "The uncommitted changes below are left out of the local pipeline run, "
      "it checks the committed tip of the '${LOCAL_PIPELINE_BRANCH}' branch only:\n"
      "${LOCAL_PIPELINE_UNCOMMITTED}"
    )
  endif()
endif()

file(REMOVE_RECURSE "${LOCAL_PIPELINE_WORKSPACE}")

execute_process(
  COMMAND "${GIT_EXECUTABLE}" clone --quiet --branch "${LOCAL_PIPELINE_BRANCH}"
          "${LOCAL_PIPELINE_SOURCE_DIR}" "${LOCAL_PIPELINE_WORKSPACE}"
  RESULT_VARIABLE LOCAL_PIPELINE_CLONE_RESULT
)

if (NOT LOCAL_PIPELINE_CLONE_RESULT EQUAL 0)
  message(FATAL_ERROR "Failed to clone the '${LOCAL_PIPELINE_BRANCH}' branch of ${LOCAL_PIPELINE_SOURCE_DIR} into ${LOCAL_PIPELINE_WORKSPACE}")
endif()

# The runners take the repository name out of the origin remote, so the clone
# points at the very same remote as the source tree instead of its local path.
execute_process(
  COMMAND "${GIT_EXECUTABLE}" remote get-url origin
  WORKING_DIRECTORY "${LOCAL_PIPELINE_SOURCE_DIR}"
  OUTPUT_VARIABLE LOCAL_PIPELINE_ORIGIN_URL
  OUTPUT_STRIP_TRAILING_WHITESPACE
  RESULT_VARIABLE LOCAL_PIPELINE_ORIGIN_RESULT
  ERROR_QUIET
)

if (LOCAL_PIPELINE_ORIGIN_RESULT EQUAL 0 AND NOT LOCAL_PIPELINE_ORIGIN_URL STREQUAL "")
  execute_process(
    COMMAND "${GIT_EXECUTABLE}" remote set-url origin "${LOCAL_PIPELINE_ORIGIN_URL}"
    WORKING_DIRECTORY "${LOCAL_PIPELINE_WORKSPACE}"
  )
endif()

execute_process(
  COMMAND "${GIT_EXECUTABLE}" log -1 "--format=%h %s"
  WORKING_DIRECTORY "${LOCAL_PIPELINE_WORKSPACE}"
  OUTPUT_VARIABLE LOCAL_PIPELINE_COMMIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Local pipeline workspace ${LOCAL_PIPELINE_WORKSPACE} holds the '${LOCAL_PIPELINE_BRANCH}' branch at ${LOCAL_PIPELINE_COMMIT}")
