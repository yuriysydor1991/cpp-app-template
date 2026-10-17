cmake_minimum_required(VERSION 3.13)

# The sdbus-c++ is a hard requirement of this branch rather than an optional
# integration, since the whole src/sdbuscxx example is built around it.
if (NOT ENABLE_LIBSDBUSCXX)
  message(
    FATAL_ERROR
    "The src/sdbuscxx sources require the sdbus-c++ library which is turned "
    "off by the ENABLE_LIBSDBUSCXX=OFF parameter. Drop the "
    "add_subdirectory(sdbuscxx) call from the src/CMakeLists.txt file together "
    "with the whole src/sdbuscxx subdirectory and its usage of the "
    "src/app/applications/Application.cpp file to build the project without "
    "it."
  )
endif()

add_library(
  TemplateProjectSDBusCxxControllerObj OBJECT
  SDBusCxxController.cpp
)

target_include_directories(
  TemplateProjectSDBusCxxControllerObj 
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectSDBusCxxControllerObj
  ${SDBUSCPP_LINK_TARGET}
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectSDBusCxxControllerObj
)

add_subdirectory(server-objects)
add_subdirectory(tests)
