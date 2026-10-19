cmake_minimum_required(VERSION 3.13)

if (NOT (ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS))
  return()
endif()

# The log mock of the whole project is kept under the app tests, so it is taken
# from there rather than duplicated.
set(LLAMACPP_APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")

# The tiny llama model of the TinyStories, the one of a megabyte the llama.cpp
# own tests run, gets downloaded once, so the tests evaluate a real model with
# no download of gigabytes. The test cases needing it skip themselves while it
# is not available, with no network for example.
set(LLAMACPP_TEST_MODEL "${CMAKE_CURRENT_BINARY_DIR}/stories260K-f32.gguf")

if (NOT EXISTS "${LLAMACPP_TEST_MODEL}")
  file(
    DOWNLOAD "https://huggingface.co/ggml-org/test-model-stories260K/resolve/479896ec924af6d40fd419ab8f4d1eb2101de00d/stories260K-f32.gguf"
    "${LLAMACPP_TEST_MODEL}"
    EXPECTED_HASH SHA256=270cba1bd5109f42d03350f60406024560464db173c0e387d91f0426d3bd256d
    TLS_VERIFY ON
    STATUS testModelStatus
  )

  list(GET testModelStatus 0 testModelCode)

  if (NOT testModelCode EQUAL 0)
    file(REMOVE "${LLAMACPP_TEST_MODEL}")
    message(WARNING "Fail to download the llama.cpp test model: ${testModelStatus}")
  endif()
endif()

add_subdirectory(unit)
add_subdirectory(component)
