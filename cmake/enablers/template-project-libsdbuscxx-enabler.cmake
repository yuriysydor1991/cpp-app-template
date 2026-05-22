cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_LIBSDBUSCXX
  "Enable the libsdbus-c++ in the project or precatch it from the system"
  ON
)

if (NOT ENABLE_LIBSDBUSCXX)
  return()
endif()

set(TEMPLATE_APP_SDBUSCXX_GIT "https://github.com/Kistler-Group/sdbus-cpp.git")
set(TEMPLATE_APP_SDBUSCXX_GIT_TAG "v2.1.0")

find_package(sdbus-c++ QUIET)

if (sdbus-c++_FOUND)
  message(STATUS "System already contains the sdbus-c++ library")
else()
  message(STATUS "The sdbus-c++ library is no available in the system")
  message(STATUS "WARNING! sdbus-c++ MAY NOT WORK!!!")

  message(STATUS "sdbus-c++ was not found in the system (or probing is OFF)")
  message(STATUS "Trying to make sdbus-c++ library available through the Internet")

  message(STATUS "sdbus-c++ URL: ${TEMPLATE_APP_SDBUSCXX_GIT}")
  message(STATUS "sdbus-c++ Tag: ${TEMPLATE_APP_SDBUSCXX_GIT_TAG}")

  include(FetchContent)

  set(SDBUSCPP_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(SDBUSCPP_BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
  set(CMAKE_INSTALL_COMPONENT OFF CACHE BOOL "" FORCE)

  FetchContent_Declare(
    libsdbus-cxx
    GIT_REPOSITORY ${TEMPLATE_APP_SDBUSCXX_GIT}
    GIT_TAG        ${TEMPLATE_APP_SDBUSCXX_GIT_TAG}
  )

  FetchContent_MakeAvailable(libsdbus-cxx)
endif()

# When sdbus-c++ is found as an installed package it exposes the namespaced
# SDBusCpp::sdbus-c++ imported target; when it is brought in through FetchContent
# (add_subdirectory) only the plain sdbus-c++ build target exists. Resolve
# whichever is available so both acquisition paths link correctly.
if (TARGET SDBusCpp::sdbus-c++)
  set(SDBUSCPP_LINK_TARGET SDBusCpp::sdbus-c++)
elseif (TARGET sdbus-c++)
  set(SDBUSCPP_LINK_TARGET sdbus-c++)
else()
  message(FATAL_ERROR "sdbus-c++ was enabled but no usable target was found")
endif()

target_link_libraries(
  TemplateProjectSDBusCxxControllerObj
  ${SDBUSCPP_LINK_TARGET}
)

target_link_libraries(
  TemplateProjectDBusServerObjectsObj
  ${SDBUSCPP_LINK_TARGET}
)

# The test executables compile the server object sources directly and therefore
# need the sdbus-c++ usage requirements (headers + link) too. They are declared
# while processing the src/ tree (before this enabler runs in the post step) and
# only exist when unit/component testing is enabled, hence the per-target guard.
foreach(sdbuscxx_test_target
        UTEST_CurrentDateServerObject
        UTEST_DBusServerObjectFactory
        CTEST_CurrentDateServerObject)
  if (TARGET ${sdbuscxx_test_target})
    target_link_libraries(${sdbuscxx_test_target} ${SDBUSCPP_LINK_TARGET})
  endif()
endforeach()
