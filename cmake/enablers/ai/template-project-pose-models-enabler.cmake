cmake_minimum_required(VERSION 3.13)

# The pose estimation models are downloaded into the misc/models directory of
# the source tree, out of the build directories (whatever their names are),
# which the scripts/build scripts erase on every configure, so all the build
# directories share a single download. The .gitignore and the .dockerignore
# files keep the downloaded models out of the commits and the docker builds.
set(TEMPLATE_APP_POSE_MODELS_DIR "${PROJECT_SOURCE_DIR}/misc/models" CACHE PATH "The directory the pose estimation models are downloaded into")

# The install step copies the downloaded models into the data directory of
# the project, where the installed binary looks for them relative to it's own
# location first (see the src/app/DataLocator.h file), so the installation
# needs no source tree.
set(PROJECT_DATA_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/${PROJECT_BINARY_NAME}")
set(PROJECT_DATA_INSTALLED_DIR "${CMAKE_INSTALL_FULL_DATADIR}/${PROJECT_BINARY_NAME}")

file(
  RELATIVE_PATH PROJECT_DATA_INSTALLED_RELATIVE_DIR
  "/${PROJECT_BINARY_INSTALLATION_DIR}" "/${PROJECT_DATA_INSTALL_DIR}"
)

# Downloads the file of the URL into the given path unless it exists. The
# download lands in a .part file beside it first and gets checked against the
# SHA256 checksum, so an interrupted or a damaged download is never taken for
# the file, while a failed one only warns. The given archive member, if any,
# is the file taken out of the downloaded archive.
function(template_project_download_model file url sha256)
  if (EXISTS "${file}")
    return()
  endif()

  get_filename_component(name "${file}" NAME)
  set(part "${file}.part")

  file(REMOVE_RECURSE "${part}")

  message(STATUS "Downloading the ${name} model file, which takes a while")

  file(DOWNLOAD "${url}" "${part}/download" TLS_VERIFY ON STATUS status)

  list(GET status 0 code)

  if (code EQUAL 0)
    file(SHA256 "${part}/download" actual)

    if (NOT actual STREQUAL sha256)
      message(WARNING "The downloaded ${url} checksum ${actual} differs from the expected ${sha256}")
      set(code 1)
    endif()
  endif()

  set(downloaded "${part}/download")

  if (code EQUAL 0 AND ARGC GREATER 3)
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E tar xf download
      WORKING_DIRECTORY "${part}"
      RESULT_VARIABLE code
    )

    file(GLOB_RECURSE downloaded "${part}/${ARGV3}")
  endif()

  if (code EQUAL 0 AND EXISTS "${downloaded}")
    get_filename_component(directory "${file}" DIRECTORY)
    file(MAKE_DIRECTORY "${directory}")
    file(RENAME "${downloaded}" "${file}")
  else()
    message(WARNING "Fail to download the ${name} model file of ${url}, so the application needs the --model parameter")
  endif()

  file(REMOVE_RECURSE "${part}")
endfunction()
