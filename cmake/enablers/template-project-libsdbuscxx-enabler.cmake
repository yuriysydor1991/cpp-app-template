cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_LIBSDBUSCXX
  "Enable the libsdbus-c++ in the project or precatch it from the system"
  ON
)

if (NOT ENABLE_LIBSDBUSCXX)
  return()
endif()

set(TEMPLATE_APP_SDBUSCXX_GIT "https://github.com/Kistler-Group/sdbus-cpp.git" CACHE STRING "The sdbus-c++ library git source repository")
set(TEMPLATE_APP_SDBUSCXX_GIT_TAG "v2.1.0" CACHE STRING "The sdbus-c++ library git source repository revision")

# The code is written for the sdbus-c++ 2 API, so an older system library
# (the 1.x of the Ubuntu 24.04, the EPEL 9 or the Fedora up to 42) is no match
# and the TEMPLATE_APP_SDBUSCXX_GIT_TAG sources get fetched instead.
find_package(sdbus-c++ 2 QUIET)

if (sdbus-c++_FOUND)
  message(STATUS "System already contains the sdbus-c++ ${sdbus-c++_VERSION} library")
else()
  # The fetched library is linked into the executable statically, so none of
  # its headers, libraries, CMake and pkg-config files or docs belong to the
  # project installation and packages.
  set(SDBUSCPP_INSTALL OFF CACHE BOOL "Install the fetched sdbus-c++ files" FORCE)
  set(SDBUSCPP_BUILD_DOCS OFF CACHE BOOL "Build the fetched sdbus-c++ docs" FORCE)

  template_project_default_3rdparty_enabler(
    NAME sdbus-c++
    GIT_REPOSITORY ${TEMPLATE_APP_SDBUSCXX_GIT}
    GIT_TAG        ${TEMPLATE_APP_SDBUSCXX_GIT_TAG}
    DISABLE_SYSTEM_PROBE
  )
endif()

if (TARGET SDBusCpp::sdbus-c++)
  set(SDBUSCPP_LINK_TARGET SDBusCpp::sdbus-c++)
elseif (TARGET sdbus-c++)
  set(SDBUSCPP_LINK_TARGET sdbus-c++)
else()
  message(FATAL_ERROR "sdbus-c++ was enabled but no usable target was found")
endif()
