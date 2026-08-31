cmake_minimum_required(VERSION 3.13)

function(template_project_default_3rdparty_enabler)
  set(FCN_KEYWORDS_FLAGS DISABLE_SYSTEM_PROBE)
  set(FCN_KEYWORDS_SINGLE NAME GIT_REPOSITORY GIT_TAG)
  set(FCN_KEYWORDS_MULTI COMPONENTS)

  cmake_parse_arguments(
    "ARG"
    "${FCN_KEYWORDS_FLAGS}"
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  if(ARG_COMPONENTS)
    set(COMPONENTS_STR COMPONENTS ${ARG_COMPONENTS})
  endif()

  if (NOT ARG_DISABLE_SYSTEM_PROBE)
    message(STATUS "Trying to probe system installed ${ARG_NAME}")
    find_package(${ARG_NAME} QUIET ${COMPONENTS_STR})
  endif()

  if (${ARG_NAME}_FOUND)
    message(STATUS "System already contains the ${ARG_NAME} library")
  else()
    message(STATUS "The '${ARG_NAME}' is not available in the system (or probing is OFF)")
    message(STATUS "Trying to make ${ARG_NAME} library available through the Internet")

    message(STATUS "${ARG_NAME} URL: ${ARG_GIT_REPOSITORY}")
    message(STATUS "${ARG_NAME} Tag: ${ARG_GIT_TAG}")

    include(FetchContent)

    # A fetched copy stays invisible to the find_package call of a nested
    # project (like the liboai one asking for it's own dependencies) unless the
    # CMake is told to redirect that call into the fetched copy.
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
      set(FIND_PACKAGE_OVERRIDE OVERRIDE_FIND_PACKAGE)
    endif()

    FetchContent_Declare(
        ${ARG_NAME}
        GIT_REPOSITORY ${ARG_GIT_REPOSITORY}
        GIT_TAG        ${ARG_GIT_TAG}
        ${FIND_PACKAGE_OVERRIDE}
    )

    FetchContent_MakeAvailable(${ARG_NAME})
  endif()

  message(STATUS "The project ${ARG_NAME} is made available")
endfunction()
