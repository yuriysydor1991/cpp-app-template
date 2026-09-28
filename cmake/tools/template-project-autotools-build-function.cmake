cmake_minimum_required(VERSION 3.13)

include(FetchContent)

# Fetches the source archive of an autotools project and installs it into the
# build tree by its own configure script and GNU make at the configure time,
# so the installed files are ready for the probe which follows. The install
# prefix is provided through the TEMPLATE_PROJECT_AUTOTOOLS_INSTALL_DIR
# variable of the caller scope.
function(template_project_autotools_3rdparty_build)
  set(FCN_KEYWORDS_SINGLE NAME URL URL_HASH)
  set(FCN_KEYWORDS_MULTI CONFIGURE_ARGS)

  cmake_parse_arguments(
    "ARG"
    ""
    "${FCN_KEYWORDS_SINGLE}"
    "${FCN_KEYWORDS_MULTI}"
    ${ARGN})

  string(TOLOWER ${ARG_NAME} NAME_LOWER)

  set(INSTALL_DIR ${FETCHCONTENT_BASE_DIR}/${NAME_LOWER}-install)

  # The autotools makefiles expand the install directories unquoted.
  if (INSTALL_DIR MATCHES " ")
    message(
      FATAL_ERROR
      "The ${ARG_NAME} autotools build can not install into the "
      "\"${INSTALL_DIR}\" path with spaces. Install the system ${ARG_NAME} "
      "package or use a build directory without spaces."
    )
  endif()

  message(STATUS "Trying to make ${ARG_NAME} library available through the Internet")
  message(STATUS "${ARG_NAME} URL: ${ARG_URL}")

  # The archive timestamps keep the shipped configure script newer than its
  # configure.ac, so the make never tries to rerun the autoconf.
  FetchContent_Declare(
    ${ARG_NAME}
    URL ${ARG_URL}
    URL_HASH ${ARG_URL_HASH}
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )

  FetchContent_MakeAvailable(${ARG_NAME})

  set(SOURCE_DIR ${${NAME_LOWER}_SOURCE_DIR})

  # Another archive replaces the whole source directory, the stamp included.
  set(STAMP_FILE ${SOURCE_DIR}/${NAME_LOWER}-autotools-build.stamp)

  set(TEMPLATE_PROJECT_AUTOTOOLS_INSTALL_DIR ${INSTALL_DIR} PARENT_SCOPE)

  if (EXISTS ${STAMP_FILE})
    message(STATUS "The ${ARG_NAME} is already installed into ${INSTALL_DIR}")
    return()
  endif()

  find_program(GNU_MAKE_EXECUTABLE NAMES gmake make REQUIRED)

  message(STATUS "Building and installing the ${ARG_NAME} into ${INSTALL_DIR}")

  execute_process(
    COMMAND sh ./configure --prefix=${INSTALL_DIR} ${ARG_CONFIGURE_ARGS}
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_QUIET
    COMMAND_ERROR_IS_FATAL ANY
  )

  execute_process(
    COMMAND ${GNU_MAKE_EXECUTABLE} install
    WORKING_DIRECTORY ${SOURCE_DIR}
    OUTPUT_QUIET
    COMMAND_ERROR_IS_FATAL ANY
  )

  file(TOUCH ${STAMP_FILE})
endfunction()
