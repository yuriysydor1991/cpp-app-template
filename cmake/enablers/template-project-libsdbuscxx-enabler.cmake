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

template_project_default_3rdparty_enabler(
  NAME sdbus-c++ 
  GIT_REPOSITORY ${TEMPLATE_APP_SDBUSCXX_GIT}
  GIT_TAG        ${TEMPLATE_APP_SDBUSCXX_GIT_TAG}
)

if (TARGET SDBusCpp::sdbus-c++)
  set(SDBUSCPP_LINK_TARGET SDBusCpp::sdbus-c++)
elseif (TARGET sdbus-c++)
  set(SDBUSCPP_LINK_TARGET sdbus-c++)
else()
  message(FATAL_ERROR "sdbus-c++ was enabled but no usable target was found")
endif()
