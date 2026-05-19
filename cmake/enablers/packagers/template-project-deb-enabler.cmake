cmake_minimum_required(VERSION 3.13)

option(
  ENABLE_DEB
  "Set to ON to enable the deb package creation from the project build artifacts"
  OFF
)

if(NOT ENABLE_DEB)
    return()
endif()

include(InstallRequiredSystemLibraries)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT ${PROJECT_MAINTAINER_EMAIL})
set(CPACK_DEB_MAINTAINER "${PROJECT_MAINTAINER} ${PROJECT_MAINTAINER_EMAIL}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${PROJECT_MAINTAINER} ${PROJECT_MAINTAINER_EMAIL}")
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_PACKAGE_DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_DEB_PACKAGE_ARCHITECTURE "amd64")  # Or arm64
set(CPACK_DEBIAN_PACKAGE_DEPENDS
  "libsdl3-dev, libsdl3-doc,
  libsdl3-image0, libsdl3-image-dev,
  libsdl3-ttf0, libsdl3-ttf-dev")

include(CPack)
