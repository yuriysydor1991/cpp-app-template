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
set(TEMPLATE_APP_LOG4CPP_GIT_TAG "REL_1.1.6_Mar_12_2026" CACHE STRING "The log4cpp project git repository tag of interest")

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
    template_project_default_3rdparty_enabler(
      NAME log4cpp
      GIT_REPOSITORY ${TEMPLATE_APP_LOG4CPP_GIT}
      GIT_TAG ${TEMPLATE_APP_LOG4CPP_GIT_TAG}
      DISABLE_SYSTEM_PROBE
    )

    # The FetchContent variables set by the enabler function above stay in its
    # own scope, so the fetched sources directory is queried here once more.
    include(FetchContent)
    FetchContent_GetProperties(log4cpp)

    # Keeps the headers, the libraries and the tests of the fetched sources out
    # of the project installation, its packages and its ctest run; the static
    # library is still built, since the project links it.
    set_property(DIRECTORY "${log4cpp_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)

    # The fetched sources register their tests unconditionally, so the ctest
    # runs of the project ignore them by the CTestCustom.cmake of the build.
    get_property(LOG4CPP_FETCHED_TESTS DIRECTORY "${log4cpp_SOURCE_DIR}/tests" PROPERTY TESTS)

    file(
      WRITE "${CMAKE_BINARY_DIR}/CTestCustom.cmake"
      "set(CTEST_CUSTOM_TESTS_IGNORE ${LOG4CPP_FETCHED_TESTS})\n"
    )

    # The CMake build of the log4cpp 1.1.6 generates its own log4cpp/config.h
    # and carries the include directories and the threading library within its
    # targets.
    add_library(LOG4CPP::log4cpp ALIAS log4cpp_static)
endif()

# Both of the paths above provide the very same LOG4CPP::log4cpp target, so
# link it to your target(s) of interest (e.g. the ${PROJECT_BINARY_NAME}
# executable or any of your own libraries) with the keyword signature:
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE LOG4CPP::log4cpp)
