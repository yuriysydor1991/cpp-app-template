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

# the Debian name of the destination CPU, the one the CPack DEB generator asks
# the dpkg for when given none
execute_process(
  COMMAND dpkg --print-architecture
  OUTPUT_VARIABLE dpkgArchitecture
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(
  TEMPLATE_PROJECT_DEB_PACKAGE_ARCHITECTURE
  "${dpkgArchitecture}"
  CACHE STRING
  "The destination CPU architecture of the DEB package (e.g. amd64, arm64, armhf, i386)"
)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT ${PROJECT_MAINTAINER_EMAIL})
set(CPACK_DEB_MAINTAINER "${PROJECT_MAINTAINER} ${PROJECT_MAINTAINER_EMAIL}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${PROJECT_MAINTAINER} ${PROJECT_MAINTAINER_EMAIL}")
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_PACKAGE_DESCRIPTION ${CMAKE_PROJECT_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${TEMPLATE_PROJECT_DEB_PACKAGE_ARCHITECTURE})
# the runtime libraries the binary links: SDL2 and the GLVND OpenGL one
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-2.0-0, libopengl0")

# the CPACK_SYSTEM_NAME of the default file name names the system alone, so the
# destination CPU takes its place
set(
  CPACK_PACKAGE_FILE_NAME
  ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${TEMPLATE_PROJECT_DEB_PACKAGE_ARCHITECTURE}
)

include(CPack)
