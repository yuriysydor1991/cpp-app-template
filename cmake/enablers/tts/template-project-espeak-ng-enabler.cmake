cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_ESPEAK_NG
    "Enables the eSpeak NG speech synthesis library for the project usage through the system installed one"
    ON
)

if (NOT ENABLE_ESPEAK_NG)
    return()
endif()

set(PROJECT_TTS_TEXT "Hello, eSpeak NG! Insert your text here!" CACHE STRING "The text the application speaks while no --text parameter is given")
set(PROJECT_TTS_VOICE "en" CACHE STRING "The eSpeak NG voice (en, uk, de, en-us etc.) the application speaks with while no --voice parameter is given")

# Every eSpeak NG installation ships an espeak-ng.pc file along with the voices
# data the library reads at the run time, so the installed library is the one
# the project takes.
find_package(PkgConfig QUIET)

if (PkgConfig_FOUND)
    pkg_check_modules(ESPEAKNG QUIET IMPORTED_TARGET GLOBAL espeak-ng)
endif()

if (NOT TARGET PkgConfig::ESPEAKNG)
    message(
      FATAL_ERROR
      "No eSpeak NG library is found through the pkg-config espeak-ng module. Install the pkg-config "
      "and the libespeak-ng-dev (Debian, Ubuntu), the espeak-ng-devel (Fedora, RHEL) or the "
      "espeak-ng (FreeBSD) package, point the PKG_CONFIG_PATH environment variable at the "
      "espeak-ng.pc file of a custom installation, or turn the speech synthesis off with the "
      "-DENABLE_ESPEAK_NG=OFF parameter together with the src/ESpeakNG sources."
    )
endif()

message(STATUS "System already contains the eSpeak NG ${ESPEAKNG_VERSION} library")

add_library(ESpeakNG::espeak-ng ALIAS PkgConfig::ESPEAKNG)

# Link the ESpeakNG::espeak-ng target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE ESpeakNG::espeak-ng)
