cmake_minimum_required(VERSION 3.13)

function(template_project_default_3rdparty_enabler)
  set(FCN_KEYWORDS_FLAGS DISABLE_SYSTEM_PROBE STANDALONE_BUILD NO_FIND_PACKAGE_FLAGS)
  set(FCN_KEYWORDS_SINGLE NAME GIT_REPOSITORY GIT_TAG)
  set(FCN_KEYWORDS_MULTI COMPONENTS CMAKE_ARGS)

  cmake_parse_arguments(
    "ARG"
    "${FCN_KEYWORDS_FLAGS}"
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  # A package configuration file may forward the QUIET and REQUIRED flags by
  # value into its own find_package() calls, which makes those calls invalid.
  # Such a package is searched flagless in the config mode, since only its own
  # configuration file provides it anyway.
  if (ARG_NO_FIND_PACKAGE_FLAGS)
    set(FIND_FLAGS_STR CONFIG)
  else()
    set(FIND_FLAGS_STR QUIET)
  endif()

  if(ARG_COMPONENTS)
    set(COMPONENTS_STR COMPONENTS ${ARG_COMPONENTS})
  endif()

  if (ARG_STANDALONE_BUILD)
    # A subdirectory without the CMakeLists.txt keeps the population from
    # adding the standalone built project into the current one.
    set(SOURCE_SUBDIR_STR SOURCE_SUBDIR standalone-build-no-subdirectory)
  endif()

  if (NOT ARG_DISABLE_SYSTEM_PROBE)
    message(STATUS "Trying to probe system installed ${ARG_NAME}")
    find_package(${ARG_NAME} ${FIND_FLAGS_STR} ${COMPONENTS_STR})
  endif()

  if (${ARG_NAME}_FOUND)
    message(STATUS "System already contains the ${ARG_NAME} library")
  else()
    message(STATUS "The '${ARG_NAME}' is not available in the system (or probing is OFF)")
    message(STATUS "Trying to make ${ARG_NAME} library available through the Internet")

    message(STATUS "${ARG_NAME} URL: ${ARG_GIT_REPOSITORY}")
    message(STATUS "${ARG_NAME} Tag: ${ARG_GIT_TAG}")

    include(FetchContent)

    FetchContent_Declare(
        ${ARG_NAME}
        GIT_REPOSITORY ${ARG_GIT_REPOSITORY}
        GIT_TAG        ${ARG_GIT_TAG}
        ${SOURCE_SUBDIR_STR}
    )

    if (ARG_STANDALONE_BUILD)
      template_project_standalone_3rdparty_build(
        NAME ${ARG_NAME}
        CMAKE_ARGS ${ARG_CMAKE_ARGS}
      )

      find_package(
        ${ARG_NAME} ${FIND_FLAGS_STR} ${COMPONENTS_STR}
        PATHS ${TEMPLATE_PROJECT_STANDALONE_INSTALL_DIR}
        NO_DEFAULT_PATH)

      if (NOT ${ARG_NAME}_FOUND)
        message(FATAL_ERROR
          "The standalone built ${ARG_NAME} is not found in the "
          "${TEMPLATE_PROJECT_STANDALONE_INSTALL_DIR} directory")
      endif()
    else()
      FetchContent_MakeAvailable(${ARG_NAME})
    endif()
  endif()

  message(STATUS "The project ${ARG_NAME} is made available")
endfunction()
