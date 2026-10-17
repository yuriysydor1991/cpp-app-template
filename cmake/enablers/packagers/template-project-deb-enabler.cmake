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
# the Qt6 libraries the binary links and the QML modules its QML files import;
# the 64-bit time_t transition renamed the Qt6 base libraries with a t64 suffix
# (every release for the core one, Ubuntu 24.04 for the rest)
string(
  JOIN ", " CPACK_DEBIAN_PACKAGE_DEPENDS
  libqt6core6t64 "libqt6gui6 | libqt6gui6t64"
  libqt6qml6 libqt6quick6 libqt6quickcontrols2-6 libqt6webenginequick6
  qml6-module-qtqml-workerscript qml6-module-qtquick
  qml6-module-qtquick-controls qml6-module-qtquick-layouts
  qml6-module-qtquick-templates qml6-module-qtquick-window
  qml6-module-qtwebengine
)

# the CPACK_SYSTEM_NAME of the default file name names the system alone, so the
# destination CPU takes its place
set(
  CPACK_PACKAGE_FILE_NAME
  ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${TEMPLATE_PROJECT_DEB_PACKAGE_ARCHITECTURE}
)

include(CPack)
