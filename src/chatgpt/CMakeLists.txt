cmake_minimum_required(VERSION 3.13)

# Both are hard requirements of this branch rather than optional integrations:
# the ChatGPT client performs it's own HTTP and reads it's own JSON.
if (NOT TARGET CURL::libcurl)
  message(
    FATAL_ERROR
    "The ChatGPT client sends it's requests with the libcurl. Keep the "
    "ENABLE_LIBCURL option ON."
  )
endif()

if (NOT TARGET nlohmann_json::nlohmann_json)
  message(
    FATAL_ERROR
    "The ChatGPT client reads the answers with the nlohmann JSON library. "
    "Keep the ENABLE_NLOHMANN_JSON option ON."
  )
endif()

add_library(
  TemplateProjectChatGPTControllerObj OBJECT
  ChatGPTController.cpp
)

target_include_directories(
  TemplateProjectChatGPTControllerObj
  PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CURL_INCLUDE_DIRS}
)

target_link_libraries(
  TemplateProjectChatGPTControllerObj
  PRIVATE CURL::libcurl
  PRIVATE nlohmann_json::nlohmann_json
)

target_link_libraries(
  ${PROJECT_BINARY_NAME}
  TemplateProjectChatGPTControllerObj
  nlohmann_json::nlohmann_json
)

add_subdirectory(tests)
