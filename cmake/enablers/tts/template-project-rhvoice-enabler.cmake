cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_RHVOICE
    "Enables the RHVoice speech synthesis library for the project usage through the system installed one"
    ON
)

if (NOT ENABLE_RHVOICE)
    return()
endif()

set(PROJECT_TTS_TEXT "Hello, RHVoice! Insert your text here!" CACHE STRING "The text the application speaks while no --text parameter is given")
set(PROJECT_TTS_VOICE "Alan" CACHE STRING "The RHVoice voice (Alan, Slt, Anatol, Natalia etc.) the application speaks with while no --voice parameter is given")

# No RHVoice installation ships a pkg-config or a CMake package file, so the
# header and the library are looked up directly. The library reads the voices
# data of it's installation at the run time.
find_path(RHVOICE_INCLUDE_DIR RHVoice.h)
find_library(RHVOICE_LIBRARY RHVoice)

if (NOT RHVOICE_INCLUDE_DIR OR NOT RHVOICE_LIBRARY)
    message(
      FATAL_ERROR
      "No RHVoice library is found. Install the librhvoice-dev (Debian, Ubuntu) or the rhvoice "
      "(FreeBSD) package together with the voices (the rhvoice-english, rhvoice-ukrainian etc. "
      "packages), build it out of it's sources on the Fedora and the RHEL (the "
      "scripts/packages/install-redhat.sh script does), point the CMAKE_PREFIX_PATH variable at "
      "a custom installation, or turn the speech synthesis off with the -DENABLE_RHVOICE=OFF "
      "parameter together with the src/RHVoice sources."
    )
endif()

message(STATUS "System already contains the RHVoice library: ${RHVOICE_LIBRARY}")

add_library(RHVoice::RHVoice UNKNOWN IMPORTED GLOBAL)

set_target_properties(
    RHVoice::RHVoice PROPERTIES
    IMPORTED_LOCATION "${RHVOICE_LIBRARY}"
    INTERFACE_INCLUDE_DIRECTORIES "${RHVOICE_INCLUDE_DIR}"
)

# Link the RHVoice::RHVoice target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE RHVoice::RHVoice)
