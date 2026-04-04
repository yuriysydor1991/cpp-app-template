cmake_minimum_required(VERSION 3.13)

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

execute_process(
  COMMAND ${JAVA_EXEC} -jar "${JENKINS_CLI_JAR_PATH}"
          -auth ${JENKINS_CLI_LOGIN}:${JENKINS_CLI_SECRET} 
          -s http://127.0.0.1:${JENKINS_PIPELINES_PANEL_HTTP_PORT}/ list-jobs
  OUTPUT_VARIABLE JENKINS_ALL_JOBS_STRING
)

string(REPLACE "\n" ";" JENKINS_ALL_JOBS_LIST "${JENKINS_ALL_JOBS_STRING}")
list(REMOVE_ITEM JENKINS_ALL_JOBS_LIST "")

set(JENKINS_JOBS_EXPORT_COMMAND "")

foreach(JENKINS_JOB IN LISTS JENKINS_ALL_JOBS_LIST)
    set(JENKINS_JOB_PATH "${CMAKE_BINARY_DIR}/Jenkins-exported-jobs/${JENKINS_JOB}.xml")

    message(STATUS "Exporting the Jenkins job: '${JENKINS_JOB}' into ${JENKINS_JOB_PATH}")

    execute_process(
        COMMAND ${JAVA_EXEC} -jar ${JENKINS_CLI_JAR_PATH}
                -auth ${JENKINS_CLI_LOGIN}:${JENKINS_CLI_SECRET} 
                -s http://127.0.0.1:${JENKINS_PIPELINES_PANEL_HTTP_PORT}/ get-job "${JENKINS_JOB}"
        OUTPUT_VARIABLE JENKINS_JOB_XML_CONF
    )

    file(WRITE "${JENKINS_JOB_PATH}" "${JENKINS_JOB_XML_CONF}")
endforeach()
