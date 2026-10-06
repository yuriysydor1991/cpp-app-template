cmake_minimum_required(VERSION 3.13)

if (NOT (ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS))
  return()
endif()

# The log and the project global declarations mocks of the whole project are
# kept under the app tests, so they are taken from there rather than
# duplicated.
set(WHISPERCPP_APP_MOCKS_ROOT "${CMAKE_SOURCE_DIR}/src/app/tests/mocks")
set(WHISPERCPP_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

# The whisper.cpp sources carry an empty model (one holding no weights) for
# the tests and a speech sample, which get downloaded once so the tests have
# something to transcribe. The test cases needing them skip themselves while
# they are not available, with no network for example.
set(WHISPERCPP_TEST_MODEL "${CMAKE_CURRENT_BINARY_DIR}/for-tests-ggml-tiny.en.bin")
set(WHISPERCPP_TEST_SPEECH "${CMAKE_CURRENT_BINARY_DIR}/jfk.wav")

function(whispercpp_test_data_download URL_PATH DESTINATION SHA256)
  if (EXISTS "${DESTINATION}")
    return()
  endif()

  file(
    DOWNLOAD "https://raw.githubusercontent.com/ggml-org/whisper.cpp/v1.9.4/${URL_PATH}"
    "${DESTINATION}"
    EXPECTED_HASH SHA256=${SHA256}
    TLS_VERIFY ON
    STATUS downloadStatus
  )

  list(GET downloadStatus 0 downloadCode)

  if (NOT downloadCode EQUAL 0)
    file(REMOVE "${DESTINATION}")
    message(WARNING "Fail to download the ${URL_PATH} whisper.cpp test data: ${downloadStatus}")
  endif()
endfunction()

whispercpp_test_data_download(
  models/for-tests-ggml-tiny.en.bin "${WHISPERCPP_TEST_MODEL}"
  dd6b7796204a1cdf7164666423034e6e1a7a3e9f5c22327b4b7974c4584bd82d
)

whispercpp_test_data_download(
  samples/jfk.wav "${WHISPERCPP_TEST_SPEECH}"
  59dfb9a4acb36fe2a2affc14bacbee2920ff435cb13cc314a08c13f66ba7860e
)

add_subdirectory(unit)
add_subdirectory(component)
