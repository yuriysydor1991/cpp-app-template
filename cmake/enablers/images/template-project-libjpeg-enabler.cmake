cmake_minimum_required(VERSION 3.13)

option(
    ENABLE_LIBJPEG
    "Enables the libjpeg-turbo (JPG/JPEG image format) library for the project (system installation only)"
    OFF
)

if (NOT ENABLE_LIBJPEG)
    return()
endif()

# libjpeg-turbo refuses to be built through add_subdirectory(), which the CMake
# FetchContent relies on, so it is probed from the system exclusively.
find_package(JPEG)

if (NOT JPEG_FOUND)
  message(
    FATAL_ERROR
    "The ENABLE_LIBJPEG=ON requires the system installed libjpeg-turbo "
    "development package: libjpeg-dev on Debian/Ubuntu, libjpeg-turbo-devel on "
    "Fedora/RHEL, jpeg-turbo on Homebrew and FreeBSD. Install it or set "
    "ENABLE_LIBJPEG=OFF."
  )
endif()

message(STATUS "libjpeg ${JPEG_VERSION} found: ${JPEG_INCLUDE_DIRS}")

# Link the following JPEG target to your target(s) of interest (e.g. the
# ${PROJECT_BINARY_NAME} executable or any of your own libraries):
#   - system install, via find_package(JPEG): JPEG::JPEG
# For example:
#   target_link_libraries(${PROJECT_BINARY_NAME} PRIVATE JPEG::JPEG)
