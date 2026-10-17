cmake_minimum_required(VERSION 3.13)

# The destination OS of the package file names, so the packages of the
# different OS releases differ in name: the ID and the VERSION_ID of the
# os-release the Linux distributions and the FreeBSD ship (e.g. ubuntu-24.04,
# freebsd-15.1), the CMake name and version of the system elsewhere (e.g. the
# windows-10.0 the Windows 10 and 11 share).

include_guard(GLOBAL)

set(osReleaseFile ${CMAKE_SYSROOT}/etc/os-release)

# a cross build reads the os-release of its sysroot alone, never the host one
if(EXISTS ${osReleaseFile} AND (CMAKE_SYSROOT OR NOT CMAKE_CROSSCOMPILING))
  foreach(osReleaseKey ID VERSION_ID)
    file(STRINGS ${osReleaseFile} osReleaseValue REGEX "^${osReleaseKey}=")
    string(REGEX REPLACE "^${osReleaseKey}=[\"']?([^\"']*)[\"']?$" "\\1" osReleaseValue "${osReleaseValue}")
    list(APPEND packageOs ${osReleaseValue})
  endforeach()
else()
  string(TOLOWER ${CMAKE_SYSTEM_NAME} packageOs)
  string(REGEX MATCH "^[0-9]+(\\.[0-9]+)?" systemVersion "${CMAKE_SYSTEM_VERSION}")
  list(APPEND packageOs ${systemVersion})
endif()

string(REPLACE ";" "-" packageOs "${packageOs}")

set(
  TEMPLATE_PROJECT_PACKAGE_OS
  ${packageOs}
  CACHE STRING
  "The destination OS of the package file names (e.g. ubuntu-24.04, debian-13, fedora-44, freebsd-15.1)"
)
