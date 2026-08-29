cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_LOG4CPP
    "Enables the log4cpp logging library for the project usage through system installed one or FetchContent by internet"
    ON
)

if (NOT ENABLE_LOG4CPP)
    return()
endif()

set(TEMPLATE_APP_LOG4CPP_GIT "https://git.code.sf.net/p/log4cpp/codegit" CACHE STRING "The log4cpp library git source repository")
set(TEMPLATE_APP_LOG4CPP_GIT_TAG "REL_1.1.5rc1_Aug_23_2024" CACHE STRING "The log4cpp project git repository tag of interest")

# The autotools build of the log4cpp ships a log4cpp.pc file only, so the system
# probe here is a pkg-config one instead of the find_package based probe of the
# enabler function used below.
find_package(PkgConfig QUIET)

if (PkgConfig_FOUND)
    pkg_check_modules(LOG4CPP QUIET IMPORTED_TARGET GLOBAL log4cpp)
endif()

if (TARGET PkgConfig::LOG4CPP)
    message(STATUS "System already contains the log4cpp ${LOG4CPP_VERSION} library")

    add_library(LOG4CPP::log4cpp ALIAS PkgConfig::LOG4CPP)
else()
    # The CMakeLists.txt of the fetched sources installs the headers into the
    # CMAKE_INSTALL_INCLUDEDIR one, which the GNUInstallDirs module declares.
    include(GNUInstallDirs)

    template_project_default_3rdparty_enabler(
      NAME log4cpp
      GIT_REPOSITORY ${TEMPLATE_APP_LOG4CPP_GIT}
      GIT_TAG ${TEMPLATE_APP_LOG4CPP_GIT_TAG}
      DISABLE_SYSTEM_PROBE
    )

    # The Debug builds of the fetched sources rename their library target.
    if (TARGET log4cpp)
      set(LOG4CPP_FETCHED_TARGET log4cpp)
    else()
      set(LOG4CPP_FETCHED_TARGET log4cppD)
    endif()

    # The log4cpp/config.h is a configure step product of the autotools build,
    # which the CMake one of the fetched sources leaves out entirely, so the
    # POSIX values of it are written here.
    set(LOG4CPP_CONFIG_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/log4cpp-config-include")

    file(
      GENERATE
      OUTPUT "${LOG4CPP_CONFIG_INCLUDE_DIR}/log4cpp/config.h"
      CONTENT
"#define LOG4CPP_HAVE_SSTREAM 1
#define LOG4CPP_HAVE_UNISTD_H 1
#define LOG4CPP_HAVE_STDINT_H 1
#define LOG4CPP_HAVE_INT64_T 1
#define LOG4CPP_HAVE_IN_ADDR_T 1
#define LOG4CPP_HAVE_SNPRINTF 1
#define LOG4CPP_HAVE_LOCALTIME_R 1
#define LOG4CPP_HAVE_GETTIMEOFDAY 1
#define LOG4CPP_HAVE_SYSLOG 1
#define LOG4CPP_HAVE_THREADING 1
#define LOG4CPP_USE_PTHREADS 1
"
    )

    # The fetched CMakeLists.txt keeps its include directories directory scoped
    # and links no threading library at all.
    target_include_directories(
      ${LOG4CPP_FETCHED_TARGET}
      PUBLIC
        "${log4cpp_SOURCE_DIR}/include"
        "${LOG4CPP_CONFIG_INCLUDE_DIR}"
    )

    find_package(Threads REQUIRED)

    target_link_libraries(${LOG4CPP_FETCHED_TARGET} PUBLIC Threads::Threads)

    add_library(LOG4CPP::log4cpp ALIAS ${LOG4CPP_FETCHED_TARGET})
endif()

# Both of the paths above provide the very same LOG4CPP::log4cpp target, so
# link it to your target(s) of interest (e.g. the ${PROJECT_BINARY_NAME}
# executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} LOG4CPP::log4cpp)
