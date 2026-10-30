cmake_minimum_required(VERSION 3.13)

# The library is a hard requirement of this branch rather than an optional
# integration: the application asks the ChatGPT through it.
if (NOT TARGET oai::oai)
  message(
    FATAL_ERROR
    "The application asks the ChatGPT through the liboai library. Keep the "
    "ENABLE_LIBOAI option ON."
  )
endif()

add_library(
  TemplateProjectOAIControllerObj OBJECT
  OAIController.cpp
)

target_include_directories(
  TemplateProjectOAIControllerObj
  PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(
  TemplateProjectOAIControllerObj
  PRIVATE oai::oai
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  PRIVATE TemplateProjectOAIControllerObj
  oai::oai
)

add_subdirectory(tests)
