cmake_minimum_required(VERSION 3.13)

if (NOT JENKINS_CLI_JAR_TARGETS)
    return()
endif()

option(
    JENKINS_CLI_IMPORT_JOBS
    "Set to ON to import (create / update) the exported *.xml Jenkins jobs into the target Jenkins server during the CMake configure step"
    OFF
)

if (NOT JENKINS_CLI_IMPORT_JOBS)
    return()
endif()

set(
    JENKINS_CLI_JAR_PATH
    ""
    CACHE STRING
    "The file to the jenkins-cli.jar executable to connect to the Jenkins instance. Downloadable from Jenkins instance web panel."
)

set(
    JENKINS_CLI_LOGIN
    ""
    CACHE STRING
    "Login name to connect to the Jenkins instance"
)

set(
    JENKINS_CLI_SECRET
    ""
    CACHE STRING
    "Secret pass code to connect to the Jenkins instance"
)

set(
    JENKINS_IMPORT_SERVER_URL
    "http://127.0.0.1:${JENKINS_PIPELINES_PANEL_HTTP_PORT}/"
    CACHE STRING
    "The target Jenkins server URL the *.xml jobs are imported (created / updated) into"
)

set(
    JENKINS_IMPORT_JOBS_DIR
    "${CMAKE_BINARY_DIR}/Jenkins-exported-jobs"
    CACHE STRING
    "The directory holding the *.xml Jenkins job configurations to import into the target server"
)

find_program(JAVA_EXEC java REQUIRED)

if (JENKINS_CLI_JAR_PATH STREQUAL "")
    message(FATAL_ERROR "No jenkins-cli.jar path found! Specify the JENKINS_CLI_JAR_PATH to point into the required executable!")
endif()

if (JENKINS_CLI_LOGIN STREQUAL "")
    message(FATAL_ERROR "No jenkins login found! Set the JENKINS_CLI_LOGIN variable!")
endif()

if (JENKINS_CLI_SECRET STREQUAL "")
    message(FATAL_ERROR "No Jenkins pass key found! Specify the JENKINS_CLI_SECRET variable!")
endif()

if (JENKINS_IMPORT_SERVER_URL STREQUAL "")
    message(FATAL_ERROR "No target Jenkins server URL found! Specify the JENKINS_IMPORT_SERVER_URL variable!")
endif()

file(GLOB JENKINS_IMPORT_JOB_FILES "${JENKINS_IMPORT_JOBS_DIR}/*.xml")

if (NOT JENKINS_IMPORT_JOB_FILES)
    message(WARNING "No *.xml Jenkins job files found in '${JENKINS_IMPORT_JOBS_DIR}' to import")
    return()
endif()

# Fetch the jobs already present on the target server so each *.xml is routed to
# create-job (a brand new job) or update-job (an existing one). create-job fails
# on a job that already exists and update-job fails on a missing one, so the
# distinction has to be made up front.
execute_process(
    COMMAND ${JAVA_EXEC} -jar "${JENKINS_CLI_JAR_PATH}"
            -auth ${JENKINS_CLI_LOGIN}:${JENKINS_CLI_SECRET}
            -s "${JENKINS_IMPORT_SERVER_URL}" list-jobs
    OUTPUT_VARIABLE JENKINS_EXISTING_JOBS_STRING
)

string(REPLACE "\n" ";" JENKINS_EXISTING_JOBS_LIST "${JENKINS_EXISTING_JOBS_STRING}")
list(REMOVE_ITEM JENKINS_EXISTING_JOBS_LIST "")

foreach(JENKINS_JOB_FILE IN LISTS JENKINS_IMPORT_JOB_FILES)
    get_filename_component(JENKINS_JOB_FILE_NAME "${JENKINS_JOB_FILE}" NAME)
    string(REGEX REPLACE "\\.xml$" "" JENKINS_JOB "${JENKINS_JOB_FILE_NAME}")

    if (JENKINS_JOB IN_LIST JENKINS_EXISTING_JOBS_LIST)
        set(JENKINS_IMPORT_CLI_VERB update-job)
        message(STATUS "Updating the existing Jenkins job '${JENKINS_JOB}' on ${JENKINS_IMPORT_SERVER_URL} from ${JENKINS_JOB_FILE}")
    else()
        set(JENKINS_IMPORT_CLI_VERB create-job)
        message(STATUS "Creating the new Jenkins job '${JENKINS_JOB}' on ${JENKINS_IMPORT_SERVER_URL} from ${JENKINS_JOB_FILE}")
    endif()

    execute_process(
        COMMAND ${JAVA_EXEC} -jar "${JENKINS_CLI_JAR_PATH}"
                -auth ${JENKINS_CLI_LOGIN}:${JENKINS_CLI_SECRET}
                -s "${JENKINS_IMPORT_SERVER_URL}" ${JENKINS_IMPORT_CLI_VERB} "${JENKINS_JOB}"
        INPUT_FILE "${JENKINS_JOB_FILE}"
        RESULT_VARIABLE JENKINS_IMPORT_RESULT
    )

    if (NOT JENKINS_IMPORT_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to import the Jenkins job '${JENKINS_JOB}' into ${JENKINS_IMPORT_SERVER_URL} (jenkins-cli ${JENKINS_IMPORT_CLI_VERB} exit code: ${JENKINS_IMPORT_RESULT})")
    endif()
endforeach()
