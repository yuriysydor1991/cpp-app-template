cmake_minimum_required(VERSION 3.13)

include(FetchContent)
include(ProcessorCount)

# Populates the declared project and installs it into the build tree by a
# separate CMake invocation. Required by the projects which resolve their own
# sources through the ${CMAKE_SOURCE_DIR} and thus can not be added as a
# subdirectory of the current one. The install prefix is provided through the
# TEMPLATE_PROJECT_STANDALONE_INSTALL_DIR variable of the caller scope.
function(template_project_standalone_3rdparty_build)
  set(FCN_KEYWORDS_SINGLE NAME)
  set(FCN_KEYWORDS_MULTI CMAKE_ARGS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  string(TOLOWER ${ARG_NAME} NAME_LOWER)

  FetchContent_MakeAvailable(${ARG_NAME})

  set(INSTALL_DIR ${FETCHCONTENT_BASE_DIR}/${NAME_LOWER}-install)
  set(STAMP_FILE ${INSTALL_DIR}/${NAME_LOWER}-standalone-build.stamp)

  set(TEMPLATE_PROJECT_STANDALONE_INSTALL_DIR ${INSTALL_DIR} PARENT_SCOPE)

  if (EXISTS ${STAMP_FILE})
    message(STATUS "The ${ARG_NAME} is already installed into ${INSTALL_DIR}")
    return()
  endif()

  message(STATUS "Configuring the standalone ${ARG_NAME} build")

  file(REMOVE_RECURSE ${${NAME_LOWER}_BINARY_DIR})
  file(MAKE_DIRECTORY ${${NAME_LOWER}_BINARY_DIR})

  execute_process(
    COMMAND
      ${CMAKE_COMMAND}
      -G ${CMAKE_GENERATOR}
      -S ${${NAME_LOWER}_SOURCE_DIR}
      -B ${${NAME_LOWER}_BINARY_DIR}
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
      ${ARG_CMAKE_ARGS}
    WORKING_DIRECTORY ${${NAME_LOWER}_BINARY_DIR}
    RESULT_VARIABLE CONFIGURE_RESULT
  )

  if (NOT CONFIGURE_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to configure the standalone ${ARG_NAME} build")
  endif()

  ProcessorCount(JOBS)

  if (JOBS EQUAL 0)
    set(JOBS 1)
  endif()

  message(STATUS "Building and installing the ${ARG_NAME} into ${INSTALL_DIR}")

  execute_process(
    COMMAND
      ${CMAKE_COMMAND}
      --build ${${NAME_LOWER}_BINARY_DIR}
      --parallel ${JOBS}
      --target install
    WORKING_DIRECTORY ${${NAME_LOWER}_BINARY_DIR}
    RESULT_VARIABLE BUILD_RESULT
  )

  if (NOT BUILD_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to build the standalone ${ARG_NAME} project")
  endif()

  file(TOUCH ${STAMP_FILE})
endfunction()
