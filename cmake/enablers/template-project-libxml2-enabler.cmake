cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_LIBXML2
    "Enables the libxml2 library for the project usage through system installed one or FetchContent by internet"
    OFF
)

if (NOT ENABLE_LIBXML2)
    return()
endif()

# original repo @ https://gitlab.gnome.org/GNOME/libxml2.git
set(TEMPLATE_APP_LIBXML2_GIT "https://github.com/GNOME/libxml2.git")
set(TEMPLATE_APP_LIBXML2_GIT_TAG "master")

find_package(LibXml2 QUIET)

if (LibXml2_FOUND)
  message(STATUS "System already contains the LibXml2 library")
else()
  message(STATUS "The LibXml2 library is not available in the system")

  message(STATUS "LibXml2 was not found in the system (or probing is OFF)")
  message(STATUS "Trying to make LibXml2 library available through the Internet")

  message(STATUS "LibXml2 URL: ${TEMPLATE_APP_LIBXML2_GIT}")
  message(STATUS "LibXml2 Tag: ${TEMPLATE_APP_LIBXML2_GIT_TAG}")

  include(FetchContent)

  FetchContent_Declare(
    LibXml2
    GIT_REPOSITORY ${TEMPLATE_APP_LIBXML2_GIT}
    GIT_TAG        ${TEMPLATE_APP_LIBXML2_GIT_TAG}
  )

  FetchContent_MakeAvailable(LibXml2)
endif()

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  LibXml2::LibXml2
)
